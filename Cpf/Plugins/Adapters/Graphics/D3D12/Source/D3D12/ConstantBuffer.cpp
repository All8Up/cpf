//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/ConstantBuffer.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

ConstantBuffer::ConstantBuffer(Device* device, const Graphics::ResourceDesc* desc, const void* initData)
	: mSize(desc->GetWidth())
	, mpBuffer(nullptr)
{
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	D3D12_RESOURCE_DESC resourceDesc
	{
		D3D12_RESOURCE_DIMENSION_BUFFER, // Dimension
		0, // Alignment
		UINT64((sizeof(desc->GetWidth()) + 255) & ~255), // Width
		1, // Height
		1, // DepthOrArraySize
		1, // MipLevels
		DXGI_FORMAT_UNKNOWN, // Format
		{ 1, 0 }, // SampleDesc
		D3D12_TEXTURE_LAYOUT_ROW_MAJOR, // Layout
		D3D12_RESOURCE_FLAG_NONE // Flags
	};
	device->GetD3DDevice()->CreateCommittedResource(
		&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(mpResource.AsTypePP())
	);

	// Describe and create a constant buffer view.
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = mpResource->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (sizeof(desc->GetWidth()) + 255) & ~255;	// CB size is required to be 256-byte aligned.
	mDescriptor = device->GetShaderResourceDescriptors().Alloc();
	D3D12_CPU_DESCRIPTOR_HANDLE handle = mDescriptor;
	device->GetD3DDevice()->CreateConstantBufferView(&cbvDesc, handle);

	// Keeping this mapped permanently is valid, see: https://msdn.microsoft.com/en-us/library/windows/desktop/dn788712.aspx#Advanced_Usage_Models
	CD3DX12_RANGE readRange(0, 0);
	mpResource->Map(0, &readRange, reinterpret_cast<void**>(&mpBuffer));

	if (initData)
		memcpy(mpBuffer, initData, desc->GetWidth());

	CPF_LOG(D3D12, Info) << "Created constant buffer: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr()) << " - " << intptr_t(mpBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
	mpResource->Unmap(0, nullptr);
	CPF_LOG(D3D12, Info) << "Destroyed constant buffer: " << intptr_t(this) << " - " << intptr_t(mpResource.Ptr()) << " - " << intptr_t(mpBuffer);
}

COM::Result CPF_STDCALL ConstantBuffer::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iConstantBuffer::kIID.GetID():
			*outIface = static_cast<iConstantBuffer*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool ConstantBuffer::Map(void**, const Graphics::Range*)
{
	return false;
}

void ConstantBuffer::Unmap(const Graphics::Range*)
{
}

void ConstantBuffer::Update(size_t offset, size_t size, const void* data)
{
	CPF_ASSERT(mpBuffer);
	CPF_ASSERT(offset + size <= mSize);
	::memcpy(mpBuffer + offset, data, size);
}
