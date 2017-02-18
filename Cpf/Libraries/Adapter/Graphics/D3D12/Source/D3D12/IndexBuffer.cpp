//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/IndexBuffer.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

IndexBuffer::IndexBuffer(Device* device, Graphics::Format format, Graphics::BufferUsage usage, size_t byteSize, const void* initData)
	: mSize(byteSize)
{
	{
		CD3DX12_HEAP_PROPERTIES heapProps;
		switch (usage)
		{
		case Graphics::BufferUsage::eDefault:
		case Graphics::BufferUsage::eImmutable:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
			break;
		case Graphics::BufferUsage::eDynamic:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			break;
		case Graphics::BufferUsage::eReadback:
			heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
			break;
		}

		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;
		switch (usage)
		{
		case Graphics::BufferUsage::eDefault:
		case Graphics::BufferUsage::eDynamic:
		case Graphics::BufferUsage::eImmutable:
		case Graphics::BufferUsage::eReadback:
		default:
			flags |= (initData ? D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS : D3D12_RESOURCE_FLAGS(0));
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
			initData ? D3D12_RESOURCE_STATE_COPY_DEST : D3D12_RESOURCE_STATE_GENERIC_READ,
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
		device->QueueUpload(upload, mpResource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
	}

	/*
	// If Immutable:
	//	Queue an upload to the buffer on the device.
	//	Queue a transition to common state on the device.
	*/

	// Create the view.
	mView.BufferLocation = mpResource->GetGPUVirtualAddress();
	mView.Format = Convert(format);
	mView.SizeInBytes = UINT(byteSize);

	if (usage == Graphics::BufferUsage::eDynamic)
	{
		mpResource->Map(0, nullptr, &mpMapping);
	}

	CPF_LOG(D3D12, Info) << "Created resource: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr());
}

IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::Map(int32_t start, int32_t end, void** mapping)
{
	(void)start; (void)end;
	*mapping = mpMapping;
	return mpMapping != nullptr;
}

bool IndexBuffer::Unmap()
{
	return mpMapping != nullptr;
}

ID3D12Resource* IndexBuffer::GetResource() const
{
	return mpResource;
}

const D3D12_INDEX_BUFFER_VIEW* IndexBuffer::GetView() const
{
	return &mView;
}
