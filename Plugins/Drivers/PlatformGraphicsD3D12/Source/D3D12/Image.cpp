//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/Image.hpp"
#include "Driver/D3D12/Device.hpp"
#include "CPF/Platform/Graphics/ImageFlags.hpp"
#include "CPF/Platform/Graphics/HeapType.hpp"
#include "CPF/Platform/Graphics/ClearValue.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Logging.hpp"

using namespace CPF;
using namespace Driver;
using namespace D3D12;


Image::Image(ID3D12Resource* resource)
{
	mpResource.Adopt(resource);
}

Image::Image(Device* device, Graphics::HeapType heap, const Graphics::ClearValue* cv, const Graphics::ImageDesc* desc)
	: mDesc(*desc)
{
	{
		D3D12_HEAP_TYPE heapType = D3D12_HEAP_TYPE_CUSTOM;
		switch (heap)
		{
		case Graphics::HeapType::eCustom:	heapType = D3D12_HEAP_TYPE_CUSTOM; break;
		case Graphics::HeapType::eDefault:	heapType = D3D12_HEAP_TYPE_DEFAULT; break;
		case Graphics::HeapType::eReadback:	heapType = D3D12_HEAP_TYPE_READBACK; break;
		case Graphics::HeapType::eUpload:	heapType = D3D12_HEAP_TYPE_UPLOAD; break;
		}
		CD3DX12_HEAP_PROPERTIES heapProps(heapType);

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
			(mDesc.mFlags != Graphics::ImageFlags::eAllowDepthStencil
				? D3D12_RESOURCE_FLAG_NONE
				: D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
		};

		D3D12_CLEAR_VALUE clearValue;
		if (cv)
		{
			clearValue.Format = Convert(cv->mFormat);
			if ((mDesc.mFlags & Graphics::ImageFlags::eAllowDepthStencil) == Graphics::ImageFlags::eNone)
			{
				clearValue.Color[0] = cv->mData.mColor.mColor[0];
				clearValue.Color[1] = cv->mData.mColor.mColor[1];
				clearValue.Color[2] = cv->mData.mColor.mColor[2];
				clearValue.Color[3] = cv->mData.mColor.mColor[3];
			}
			else
			{
				clearValue.DepthStencil.Depth = cv->mData.mDepthStencil.mDepth;
				clearValue.DepthStencil.Stencil = UINT8(cv->mData.mDepthStencil.mStencil);
			}
		}
		device->GetD3DDevice()->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&d3dDesc,
			Convert(desc->mState),
			cv ? &clearValue : nullptr,
			IID_PPV_ARGS(mpResource.AsTypePP()));
	}

	CPF_LOG(D3D12, Info) << "Created image: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());

	if (mDesc.mFlags == Graphics::ImageFlags::eNone)
	{
		::memset(&mResourceView, 0, sizeof(mResourceView));
		mResourceView.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		mResourceView.Format = Convert(mDesc.mFormat);
		mResourceView.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		mResourceView.Texture2D.MipLevels = 1;

		mDescriptor = device->GetShaderResourceDescriptors().Alloc();
		device->GetD3DDevice()->CreateShaderResourceView(GetResource(), &mResourceView, mDescriptor);
	}
}

Image::~Image()
{
	CPF_LOG(D3D12, Info) << "Destroyed image: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

GOM::Result Image::QueryInterface(GOM::IID id, void** outIface)
{
	if (outIface)
	{
		switch (uint64_t(id))
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iImage*>(this);
			break;
		case iResource::kIID.GetID():
			*outIface = static_cast<iResource*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

bool Image::Map(void** mapping, const Graphics::Range* range)
{
	D3D12_RANGE* prange = nullptr;
	D3D12_RANGE r;
	if (range)
	{
		r.Begin = range->mStart;
		r.End = range->mEnd;
		prange = &r;
	}
	if (SUCCEEDED(mpResource->Map(0, prange, mapping)))
		return true;
	return false;
}

void Image::Unmap(const Graphics::Range* range)
{
	D3D12_RANGE* prange = nullptr;
	D3D12_RANGE r;
	if (range)
	{
		r.Begin = range->mStart;
		r.End = range->mEnd;
		prange = &r;
	}
	mpResource->Unmap(0, prange);
}

GOM::Result Image::GetDesc(Graphics::ImageDesc* desc) const
{
	if (desc)
	{
		*desc = mDesc;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

ID3D12Resource* Image::GetResource()
{
	return mpResource;
}
