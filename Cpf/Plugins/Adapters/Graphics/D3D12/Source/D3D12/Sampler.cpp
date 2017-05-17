//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Sampler.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/SamplerDesc.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

Sampler::Sampler(Device* device, const Graphics::SamplerDesc* desc)
{
	auto& descriptors = device->GetSamplerDescriptors();
	mDescriptor = descriptors.Alloc();

	D3D12_SAMPLER_DESC d3dDesc;
	d3dDesc.Filter = D3D12_FILTER(int(desc->mMipFilter) | (int(desc->mMagFilter) << 2) | (int(desc->mMinFilter) << 4));
	d3dDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE(desc->mUWrap);
	d3dDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE(desc->mVWrap);
	d3dDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE(desc->mWWrap);
	d3dDesc.MipLODBias = desc->mLodBias;
	d3dDesc.MaxAnisotropy = 0;	// TODO: Expose this.
	d3dDesc.BorderColor[0] = 0.0f;	// TODO: Expose this.
	d3dDesc.BorderColor[1] = 0.0f;
	d3dDesc.BorderColor[2] = 0.0f;
	d3dDesc.BorderColor[3] = 0.0f;
	d3dDesc.MinLOD = desc->mLodMin;
	d3dDesc.MaxLOD = desc->mLodMax;
	d3dDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // TODO: Expose this.

	device->GetD3DDevice()->CreateSampler(&d3dDesc, mDescriptor);
}

Sampler::~Sampler()
{}

GOM::Result CPF_STDCALL Sampler::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iSampler::kIID.GetID():
			*outIface = static_cast<iSampler*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
