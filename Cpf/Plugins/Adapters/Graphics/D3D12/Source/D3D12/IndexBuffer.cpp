//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/IndexBuffer.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/HeapType.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;
using namespace Adapter;
using namespace D3D12;

IndexBuffer::IndexBuffer(Device* device, const Graphics::ResourceDesc* desc, Graphics::Format format)
	: mSize(desc->GetWidth())
{
	{
		CD3DX12_HEAP_PROPERTIES heapProps;
		switch (desc->GetHeapType())
		{
		case Graphics::HeapType::eCustom:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_CUSTOM);
			break;
		case Graphics::HeapType::eDefault:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
			break;
		case Graphics::HeapType::eReadback:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
			break;
		case Graphics::HeapType::eUpload:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			break;
		}

		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;
		//flags |= (initData ? D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS : D3D12_RESOURCE_FLAGS(0));
		D3D12_RESOURCE_DESC resourceDesc
		{
			D3D12_RESOURCE_DIMENSION_BUFFER, // Dimension
			0, // Alignment
			UINT64(desc->GetWidth()), // Width
			1, // Height
			1, // DepthOrArraySize
			1, // MipLevels
			DXGI_FORMAT_UNKNOWN, // Format
			{ 1, 0 }, // SampleDesc
			D3D12_TEXTURE_LAYOUT_ROW_MAJOR, // Layout
			flags // Flags
		};
		device->GetD3DDevice()->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			Convert(desc->GetResourceState()),
			nullptr,
			IID_PPV_ARGS(mpResource.AsTypePP())
		);
	}

	// Create the view.
	mView.BufferLocation = mpResource->GetGPUVirtualAddress();
	mView.Format = Convert(format);
	mView.SizeInBytes = UINT(desc->GetWidth());

	CPF_LOG(D3D12, Info) << "Created resource: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

IndexBuffer::~IndexBuffer()
{
}

GOM::Result CPF_STDCALL IndexBuffer::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iResource::kIID.GetID():
			*outIface = static_cast<iResource*>(this);
			break;
		case iIndexBuffer::kIID.GetID():
			*outIface = static_cast<iIndexBuffer*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

bool IndexBuffer::Map(void** mapping, const Graphics::Range* range)
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

void IndexBuffer::Unmap(const Graphics::Range* range)
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

ID3D12Resource* IndexBuffer::GetResource() const
{
	return mpResource;
}

const D3D12_INDEX_BUFFER_VIEW* IndexBuffer::GetView() const
{
	return &mView;
}
