//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Image.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;


Image::Image(ID3D12Resource* resource)
	: mpResource(resource)
{
}

Image::Image(Device* device, const void* initData, const Graphics::ImageDesc* desc CPF_GFX_DEBUG_PARAM_DEF)
	: mDesc(*desc)
{
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
			initData==nullptr ? D3D12_RESOURCE_STATE_COMMON : D3D12_RESOURCE_STATE_COPY_DEST,
			initData==nullptr ? &clearValue : nullptr,
			IID_PPV_ARGS(mpResource.AsTypePP()));
	}

	CPF_LOG(D3D12, Info) << "Created image: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());

	if (initData)
	{
		ID3D12Resource* upload = nullptr;
		CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
		CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(mDesc.mWidth * mDesc.mHeight * 4);
		device->GetD3DDevice()->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&upload));

		Graphics::BinaryBlob* blob = nullptr;
		Graphics::BinaryBlob::Create(mDesc.mWidth * mDesc.mHeight * 4, initData, &blob);

		D3D12_SUBRESOURCE_DATA textureData = {};
		textureData.pData = blob->GetData();
		textureData.RowPitch = desc->mWidth * 4;
		textureData.SlicePitch = textureData.RowPitch * desc->mHeight;

		mpResource->AddRef();
		device->QueueUpdateSubResource(
			upload, mpResource, textureData, blob,
			D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON);
	}

	if (!mDesc.mFlags)
	{
		::memset(&mResourceView, 0, sizeof(mResourceView));
		mResourceView.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		mResourceView.Format = Convert(mDesc.mFormat);
		mResourceView.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		mResourceView.Texture2D.MipLevels = 1;

		mDescriptor = device->GetShaderResourceDescriptors().Alloc();
		device->GetD3DDevice()->CreateShaderResourceView(GetResource(), &mResourceView, mDescriptor);
	}

#ifdef CPF_GFX_TRACKING
	std::wstringstream str;
	str << dbgFilename << " : " << dbgLineNumber;
	mpResource->SetName(str.str().c_str());
#endif
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
