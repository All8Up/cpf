//////////////////////////////////////////////////////////////////////////
#include "Adapters/D3D12/Image.hpp"
#include "Adapters/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace D3D12;


Image::Image(ID3D12Resource* resource)
	: mpResource(resource)
{
}

Image::Image(Device* device, const Graphics::ImageDesc* desc)
	: mDesc(*desc)
{
	D3D12_RESOURCE_DESC d3dDesc
	{
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		UINT64(mDesc.mWidth), UINT(mDesc.mHeight),
		1,
		1,
		Convert(mDesc.mFormat),
		{UINT(mDesc.mSamples.mCount), UINT(mDesc.mSamples.mQuality)},
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		(mDesc.mFlags == 0 ? D3D12_RESOURCE_FLAG_NONE : D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
	};
	D3D12_HEAP_PROPERTIES heapProps =
	{
		D3D12_HEAP_TYPE_DEFAULT,
		D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
		D3D12_MEMORY_POOL_UNKNOWN,
		1, 1
	};
	D3D12_CLEAR_VALUE clearValue;
	clearValue.Format = Convert(mDesc.mFormat);
	if (mDesc.mFlags == 0)
	{
		clearValue.Color[0] = 0.0f;
		clearValue.Color[1] = 0.0f;
		clearValue.Color[2] = 0.0f;
		clearValue.Color[3] = 1.0f;
	}
	else
	{
		clearValue.DepthStencil.Depth = 1.0f;
		clearValue.DepthStencil.Stencil = 0;
	}
	device->GetD3DDevice()->CreateCommittedResource(
		&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&d3dDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&clearValue,
		IID_PPV_ARGS(mpResource.AsTypePP()));

	CPF_LOG(D3D12, Info) << "Created image: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

Image::~Image()
{
	CPF_LOG(D3D12, Info) << "Destroyed image: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

const Graphics::ImageDesc& Image::GetDesc() const
{
	return mDesc;
}

ID3D12Resource* Image::GetResource()
{
	return mpResource;
}


//////////////////////////////////////////////////////////////////////////
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
	device->GetD3DDevice()->CreateDepthStencilView(image->GetResource(), pd3dDesc, mDescriptor);
}
