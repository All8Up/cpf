//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iImage.hpp"
#include "Graphics/Interfaces/iImageView.hpp"
#include "D3D12Utils.hpp"
#include "DescriptorManager.hpp"
#include "Move.hpp"

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
				Image(Device*, const void* initData, const Graphics::ImageDesc* desc);
				~Image() override;

				const Graphics::ImageDesc& GetDesc() const override;

				ID3D12Resource* GetResource();

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				Graphics::ImageDesc mDesc;
			};

			class ImageView : public tRefCounted<Graphics::iImageView>
			{
			public:
				ImageView(Descriptor&& desc) : mDescriptor(Move(desc)) {}
				ImageView(Device*, Image*, const Graphics::DepthStencilViewDesc*);

				Descriptor& GetDescriptor() { return mDescriptor; }

			private:
				Descriptor mDescriptor;
			};
		}
	}
}
