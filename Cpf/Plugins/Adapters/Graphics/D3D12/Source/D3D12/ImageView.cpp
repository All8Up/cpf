//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/ImageView.hpp"
#include "Adapter/D3D12/Image.hpp"
#include "Adapter/D3D12/Device.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

ImageView::ImageView(Device* device, Image* image, const Graphics::DepthStencilViewDesc* desc)
	: mDescriptor(device->GetDepthStencilViewDescriptors().Alloc())
{
	D3D12_DEPTH_STENCIL_VIEW_DESC d3dDesc;
	D3D12_DEPTH_STENCIL_VIEW_DESC* pd3dDesc = nullptr;
	if (desc)
	{
		CPF_ASSERT_ALWAYS; // Not implemented yet.
		pd3dDesc = &d3dDesc;
	}
//	device->GetD3DDevice()->CreateRenderTargetView(image->GetResource(), nullptr, mDescriptor);;
	device->GetD3DDevice()->CreateDepthStencilView(image->GetResource(), pd3dDesc, mDescriptor);
}

GOM::Result CPF_STDCALL ImageView::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;
		case iImageView::kIID.GetID():
			*outIface = static_cast<iImageView*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
