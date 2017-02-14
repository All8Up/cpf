//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/ResourceBinding.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/Descriptors/ResourceBindingDesc.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

ResourceBinding::ResourceBinding(Device* device, const Graphics::ResourceBindingDesc* desc)
{
	IntrusivePtr<ID3DBlob> signatureBlob;
	if (_BuildSignature(desc, signatureBlob.AsTypePP()))
	{
		if (SUCCEEDED(device->GetD3DDevice()->CreateRootSignature(
			0,
			signatureBlob->GetBufferPointer(),
			signatureBlob->GetBufferSize(),
			IID_PPV_ARGS(mpSignature.AsTypePP()))
		))
		{
			CPF_LOG(D3D12, Info) << "Created resource binding: " << intptr_t(this) << " - " << intptr_t(mpSignature.Ptr());
		}
	}
	else
	{
		String errors;
		errors.resize(signatureBlob->GetBufferSize());
		errors.assign(reinterpret_cast<const char*>(signatureBlob->GetBufferPointer()), signatureBlob->GetBufferSize());
		CPF_LOG(D3D12, Info) << "Error creating root signature.";
		CPF_LOG(D3D12, Info) << errors;
		signatureBlob->Release();
	}
}

ResourceBinding::~ResourceBinding()
{
	CPF_LOG(D3D12, Info) << "Destroyed resource binding: " << intptr_t(this) << " - " << intptr_t(mpSignature.Ptr());
}

bool ResourceBinding::_BuildSignature(const Graphics::ResourceBindingDesc* desc, ID3DBlob** result) const
{
	return Convert(*desc, result);
}