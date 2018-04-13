//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/ImageView.hpp"
#include "Driver/D3D12/Image.hpp"
#include "Driver/D3D12/Device.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Driver;
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
