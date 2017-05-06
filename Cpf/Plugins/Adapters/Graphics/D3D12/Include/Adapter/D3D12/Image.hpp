//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver.hpp"
#include "Graphics/iImage.hpp"
#include "Graphics/ImageDesc.hpp"
#include "DescriptorManager.hpp"

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Image : public tRefCounted<Graphics::iImage>
			{
			public:
				Image(ID3D12Resource* resource);
				Image(Device*, Graphics::HeapType heap, const void* initData, const Graphics::ImageDesc* desc);
				virtual ~Image();

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				const Graphics::ImageDesc& GetDesc() const override;

				ID3D12Resource* GetResource();
				const D3D12_SHADER_RESOURCE_VIEW_DESC* GetResourceViewDesc() const { return &mResourceView; }
				const Descriptor& GetDescriptor() const { return mDescriptor; }

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				Graphics::ImageDesc mDesc;
				Descriptor mDescriptor;
				D3D12_SHADER_RESOURCE_VIEW_DESC mResourceView;
			};
		}
	}
}
