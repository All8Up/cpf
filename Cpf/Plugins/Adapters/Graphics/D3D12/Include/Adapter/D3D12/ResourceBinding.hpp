//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Graphics/iResourceBinding.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "IntrusivePtr.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct ResourceBindingDesc;
		struct ResourceBindingDescX;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			class ResourceBinding : public tRefCounted<Graphics::iResourceBinding>
			{
			public:
				ResourceBinding(Device* device, const Graphics::ResourceBindingDesc* desc);
				virtual ~ResourceBinding();

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				ID3D12RootSignature* GetSignature() const { return mpSignature; }

			private:
				bool _BuildSignature(const Graphics::ResourceBindingDesc* desc, ID3DBlob** result) const;

				IntrusivePtr<ID3D12RootSignature> mpSignature;
			};
		}
	}
}
