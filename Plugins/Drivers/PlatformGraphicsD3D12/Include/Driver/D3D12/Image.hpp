//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics.hpp"
#include "CPF/Platform/Graphics/iImage.hpp"
#include "CPF/Platform/Graphics/ImageDesc.hpp"
#include "DescriptorManager.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct ClearValue;
	}

	namespace Driver
	{
		namespace D3D12
		{
			class Image final : public GOM::tUnknown<Graphics::iImage>
			{
			public:
				Image(ID3D12Resource* resource);
				Image(Device*, Graphics::HeapType heap, const Graphics::ClearValue* clearValue, const Graphics::ImageDesc* desc);
				virtual ~Image();

				GOM::Result QueryInterface(GOM::IID id, void** outIface) override;

				bool Map(void**, const Graphics::Range* = nullptr) override;
				void Unmap(const Graphics::Range* range) override;

				GOM::Result GetDesc(Graphics::ImageDesc* desc) const override;

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
