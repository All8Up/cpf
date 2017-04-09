//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Blob.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;


Blob::Blob(size_t size, const void* data)
	: mData(reinterpret_cast<const uint8_t*>(data), reinterpret_cast<const uint8_t*>(data) + size)
{
}

Blob::~Blob()
{}

COM::Result CPF_STDCALL Blob::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iBlob::kIID.GetID():
			*outIface = static_cast<iBlob*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result Blob::Initialize(const void* data, int64_t size)
{
	if (data)
	{
		Cpf::Vector<uint8_t> empty;
		mData.swap(empty);
		mData.resize(size);
		for (int i = 0; i < size; ++i)
			mData[i] = reinterpret_cast<const uint8_t*>(data)[i];
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void* Blob::GetData()
{
	return reinterpret_cast<void*>(mData.data());
}

int64_t Blob::GetSize()
{
	return int64_t(mData.size());
}
