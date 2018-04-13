//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iImageView.hpp"
#include "DescriptorManager.hpp"
#include "CPF/Std/Move.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct DepthStencilViewDesc;
	}
}

namespace CPF
{
	namespace Driver
	{
		namespace D3D12
		{
			class Image;

			class ImageView final : public GOM::tUnknown<Graphics::iImageView>
			{
			public:
				ImageView(Descriptor&& desc) : mDescriptor(STD::Move(desc)) {}
				ImageView(Device*, Image*, const Graphics::DepthStencilViewDesc*);

				Descriptor& GetDescriptor() { return mDescriptor; }

			private:
				Descriptor mDescriptor;
			};
		}
	}
}
