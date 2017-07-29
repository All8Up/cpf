//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iConstantBuffer.hpp"
#include "RefCounted.hpp"
#include "Resource.hpp"
#include "DescriptorManager.hpp"
#include "CommandBuffer.hpp"


namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			class ConstantBuffer : public tRefCounted<Graphics::iConstantBuffer>
			{
			public:
				ConstantBuffer(Device* device, const Graphics::ResourceDesc* desc, const void* initData);
				virtual ~ConstantBuffer();

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				void Update(size_t offset, size_t size, const void* data) override;

				bool Map(void**, const Graphics::Range* = nullptr) override;
				void Unmap(const Graphics::Range* range) override;

				const Descriptor& GetDescriptor() const { return mDescriptor; }
				D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const { return mpResource->GetGPUVirtualAddress(); }

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				Descriptor mDescriptor;
				size_t mSize;
				uint8_t* mpBuffer;
			};
		}
	}
}
