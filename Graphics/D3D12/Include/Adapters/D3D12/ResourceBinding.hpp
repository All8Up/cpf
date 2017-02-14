//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iResourceBinding.hpp"
#include "Adapters/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class ResourceBindingDesc;
	}

	namespace Adapters
	{
		namespace D3D12
		{
			class Device;

			class ResourceBinding : public tRefCounted<Graphics::iResourceBinding>
			{
			public:
				ResourceBinding(Device* device, const Graphics::ResourceBindingDesc* desc);
				~ResourceBinding() override;

				ID3D12RootSignature* GetSignature() const { return mpSignature; }

			private:
				bool _BuildSignature(const Graphics::ResourceBindingDesc* desc, ID3DBlob** result) const;

				IntrusivePtr<ID3D12RootSignature> mpSignature;
			};
		}
	}
}
