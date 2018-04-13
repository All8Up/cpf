//////////////////////////////////////////////////////////////////////////
#pragma once
#include "D3D12Utils.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/Std/Vector.hpp"


namespace CPF
{
	namespace Driver
	{
		namespace D3D12
		{
			class Device;
			class DescriptorManager;

			class Descriptor final
			{
			public:
				Descriptor();
				Descriptor(DescriptorManager* mgr, size_t index);
				Descriptor(Descriptor&& rhs);
				~Descriptor();

				DescriptorManager* GetManager() const;

				Descriptor& operator =(Descriptor&& rhs);
				operator D3D12_CPU_DESCRIPTOR_HANDLE () const;
				operator D3D12_GPU_DESCRIPTOR_HANDLE () const;

			private:
				DescriptorManager* mpManager;
				size_t mIndex;
			};

			// TODO: This will likely need to be free threaded.
			class DescriptorManager final
			{
			public:
				static constexpr size_t kInvalid = size_t(-1);

				DescriptorManager();
				~DescriptorManager();

				bool Initialize(Device*, D3D12_DESCRIPTOR_HEAP_TYPE heapType, D3D12_DESCRIPTOR_HEAP_FLAGS heapFlags, size_t count);
				bool Shutdown();

				Descriptor Alloc();

				ID3D12DescriptorHeap* GetHeap() const { return mpDescriptorHeap; }
				size_t GetIncrement() const { return mIncrement; }

			private:
				friend class Descriptor;

				size_t _Alloc();
				void _Free(size_t index);

				Device* mpDevice;
				IntrusivePtr<ID3D12DescriptorHeap> mpDescriptorHeap;
				size_t mIncrement;

				size_t mNextFree;
				STD::Vector<size_t> mFreeList;
			};
		}
	}
}
