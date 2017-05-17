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

GOM::Result CPF_STDCALL Blob::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iBlob::kIID.GetID():
			*outIface = static_cast<iBlob*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result Blob::Initialize(const void* data, int64_t size)
{
	if (data)
	{
		Cpf::Vector<uint8_t> empty;
		mData.swap(empty);
		mData.resize(size);
		for (int i = 0; i < size; ++i)
			mData[i] = reinterpret_cast<const uint8_t*>(data)[i];
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

void* Blob::GetData()
{
	return reinterpret_cast<void*>(mData.data());
}

int64_t Blob::GetSize()
{
	return int64_t(mData.size());
}
