//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/VertexBuffer.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Graphics/Range.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

VertexBuffer::VertexBuffer(Device* device, Graphics::BufferUsage usage, size_t byteSize, size_t byteStride, const void* initData)
	: mSize(byteSize)
	, mStride(byteStride)
{
	{
		D3D12_RESOURCE_STATES startState = D3D12_RESOURCE_STATE_COMMON;
		CD3DX12_HEAP_PROPERTIES heapProps;
		switch (usage)
		{
		case Graphics::BufferUsage::eDefault:
		case Graphics::BufferUsage::eImmutable:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
			startState = D3D12_RESOURCE_STATE_COPY_DEST;
			break;
		case Graphics::BufferUsage::eDynamic:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			startState = D3D12_RESOURCE_STATE_GENERIC_READ;
			break;
		case Graphics::BufferUsage::eReadback:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
			break;
		}

		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;
		switch (usage)
		{
		case Graphics::BufferUsage::eDefault:
		default:
			flags |= D3D12_RESOURCE_FLAG_NONE;
		}
		D3D12_RESOURCE_DESC resourceDesc
		{
			D3D12_RESOURCE_DIMENSION_BUFFER, // Dimension
			0, // Alignment
			UINT64(byteSize), // Width
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
			startState,
			nullptr,
			IID_PPV_ARGS(mpResource.AsTypePP())
		);
	}

	// Create the upload buffer if there is init data.
	if (initData)
	{
		// TODO: Pool these in the future.
		ID3D12Resource* upload = nullptr;
		{
			D3D12_RESOURCE_DESC resourceDesc
			{
				D3D12_RESOURCE_DIMENSION_BUFFER, // Dimension
				0, // Alignment
				UINT64(byteSize), // Width
				1, // Height
				1, // DepthOrArraySize
				1, // MipLevels
				DXGI_FORMAT_UNKNOWN, // Format
				{ 1, 0 }, // SampleDesc
				D3D12_TEXTURE_LAYOUT_ROW_MAJOR, // Layout
				D3D12_RESOURCE_FLAG_NONE // Flags
			};
			CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

			device->GetD3DDevice()->CreateCommittedResource(
				&heapProps,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&upload)
			);

			CD3DX12_RANGE range(0, 0);
			void* destData = nullptr;
			upload->Map(0, &range, &destData);
			::memcpy(destData, initData, byteSize);
			upload->Unmap(0, nullptr);
		}
		mpResource->AddRef();
		device->QueueUpload(upload, mpResource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	}

	// Create the view.
	mView.BufferLocation = mpResource->GetGPUVirtualAddress();
	mView.SizeInBytes = UINT(byteSize);
	mView.StrideInBytes = UINT(byteStride);

	CPF_LOG(D3D12, Info) << "Created resource: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

VertexBuffer::~VertexBuffer()
{
}

bool VertexBuffer::Map(void** mapping, const Graphics::Range* range)
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

void VertexBuffer::Unmap(const Graphics::Range* range)
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

ID3D12Resource* VertexBuffer::GetResource() const
{
	return mpResource;
}

const D3D12_VERTEX_BUFFER_VIEW* VertexBuffer::GetView() const
{
	return &mView;
}
