//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iResourceBinding.hpp"
#include "Driver/D3D12/D3D12Utils.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct ResourceBindingDesc;
		struct ResourceBindingDescX;
	}

	namespace Driver
	{
		namespace D3D12
		{
			class Device;

			class ResourceBinding final : public GOM::tUnknown<Graphics::iResourceBinding>
			{
			public:
				ResourceBinding(Device* device, const Graphics::ResourceBindingDesc* desc);
				virtual ~ResourceBinding();

				ID3D12RootSignature* GetSignature() const { return mpSignature; }

			private:
				bool _BuildSignature(const Graphics::ResourceBindingDesc* desc, ID3DBlob** result) const;

				IntrusivePtr<ID3D12RootSignature> mpSignature;
			};
		}
	}
}
