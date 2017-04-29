//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iImageView.hpp"
#include "DescriptorManager.hpp"
#include "Move.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct DepthStencilViewDesc;
	}
}

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Image;

			class ImageView : public tRefCounted<Graphics::iImageView>
			{
			public:
				ImageView(Descriptor&& desc) : mDescriptor(Move(desc)) {}
				ImageView(Device*, Image*, const Graphics::DepthStencilViewDesc*);

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				Descriptor& GetDescriptor() { return mDescriptor; }

			private:
				Descriptor mDescriptor;
			};
		}
	}
}
