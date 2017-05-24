//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Resource.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/ResourceDesc.hpp"
#include "Graphics/HeapType.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

Resource::Resource(Device* device, const Graphics::ResourceDesc* desc)
{
	CD3DX12_HEAP_PROPERTIES heapProps;
	switch(desc->GetHeapType())
	{
	case Graphics::HeapType::eDefault:
		heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		break;
	case Graphics::HeapType::eUpload:
		heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		break;
	case Graphics::HeapType::eReadback:
		heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
		break;
	case Graphics::HeapType::eCustom:
		heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_CUSTOM);
		break;
	}
	D3D12_RESOURCE_DESC resourceDesc
	{
		D3D12_RESOURCE_DIMENSION(desc->GetType()), // Dimension
		0, // Alignment
		UINT64(desc->GetWidth()), // Width
		1, // Height
		1, // DepthOrArraySize
		1, // MipLevels
		DXGI_FORMAT_UNKNOWN, // Format
		{1, 0}, // SampleDesc
		D3D12_TEXTURE_LAYOUT_ROW_MAJOR, // Layout
		D3D12_RESOURCE_FLAGS(0) // Flags
	};
	device->GetD3DDevice()->CreateCommittedResource(
		&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATES(desc->GetResourceState()),
		nullptr,
		IID_PPV_ARGS(mpResource.AsTypePP())
		);
	CPF_LOG(D3D12, Info) << "Created resource: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

Resource::~Resource()
{
	CPF_LOG(D3D12, Info) << "Destroyed resource: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

GOM::Result CPF_STDCALL Resource::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
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

bool Resource::Map(void** mapping, const Graphics::Range* range)
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

void Resource::Unmap(const Graphics::Range* range)
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

D3D12_GPU_VIRTUAL_ADDRESS Resource::GetGPUAddress() const
{
	return mpResource->GetGPUVirtualAddress();
}
