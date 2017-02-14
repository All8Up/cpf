//////////////////////////////////////////////////////////////////////////
#pragma once
#include "D3D12Utils.hpp"
#include "IntrusivePtr.hpp"
#include "Vector.hpp"


namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Device;
			class DescriptorManager;

			class Descriptor
			{
			public:
				Descriptor();
				Descriptor(DescriptorManager* mgr, size_t index);
				Descriptor(Descriptor&& rhs);
				~Descriptor();

				Descriptor& operator =(Descriptor&& rhs);
				operator D3D12_CPU_DESCRIPTOR_HANDLE () const;

			private:
				DescriptorManager* mpManager;
				size_t mIndex;
			};

			// TODO: This will likely need to be free threaded.
			class DescriptorManager
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
				Vector<size_t> mFreeList;
			};
		}
	}
}
