//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/ResourceBinding.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/ResourceBindingDesc.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;
using namespace Adapter;
using namespace D3D12;
using namespace Graphics;

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

GOM::Result CPF_STDCALL ResourceBinding::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iResourceBinding::kIID.GetID():
			*outIface = static_cast<iResourceBinding*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

bool ResourceBinding::_BuildSignature(const Graphics::ResourceBindingDesc* desc, ID3DBlob** result) const
{
	CD3DX12_ROOT_PARAMETER* parameters = new CD3DX12_ROOT_PARAMETER[desc->mCount];
	CD3DX12_DESCRIPTOR_RANGE* ranges = new CD3DX12_DESCRIPTOR_RANGE[desc->mCount];

	int i = 0;
	for (int oi=0; oi<desc->mCount; ++oi)
	{
		const auto& param = desc->mpBindings[oi];
		switch (param.mType)
		{
		case BindingType::eConstants:
		{
			parameters[i++].InitAsConstants(param.mCount, param.mIndex, 0, D3D12_SHADER_VISIBILITY(param.mVisibility));
		}
		break;
		case BindingType::eConstantBuffer:
		{
			parameters[i++].InitAsConstantBufferView(
				param.mIndex,
				0,
				D3D12_SHADER_VISIBILITY(param.mVisibility));
		}
		break;

		case BindingType::eSampler:
		{
			ranges[i].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, param.mIndex);
			parameters[i].InitAsDescriptorTable(1, &ranges[i]);
			++i;
		}
		break;

		case BindingType::eTexture:
		{
			ranges[i].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, param.mIndex);
			parameters[i].InitAsDescriptorTable(1, &ranges[i]);
			++i;
		}
		break;
		default:
			CPF_ASSERT_ALWAYS;// Type not implemented.
		}
	}

	D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	CD3DX12_ROOT_SIGNATURE_DESC signature;
	signature.Init(UINT(desc->mCount), parameters, 0, nullptr, rootSignatureFlags);

	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	if (SUCCEEDED(D3D12SerializeRootSignature(&signature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob)))
	{
		if (errorBlob)
			errorBlob->Release();
		*result = signatureBlob;
		delete[] parameters;
		delete[] ranges;
		return true;
	}
	if (signatureBlob)
		signatureBlob->Release();
	*result = errorBlob;
	delete[] parameters;
	delete[] ranges;
	return false;
}
