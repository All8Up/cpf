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
				ConstantBuffer(Device* device, size_t size, const void* initData);
				~ConstantBuffer() override;

				void Update(size_t offset, size_t size, const void* data) override;

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
