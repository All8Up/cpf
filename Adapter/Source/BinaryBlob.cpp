//////////////////////////////////////////////////////////////////////////
#include "Graphics/BinaryBlob.hpp"

using namespace Cpf;
using namespace Graphics;


BinaryBlob::BinaryBlob(size_t size, void* data)
	: mData(reinterpret_cast<const uint8_t*>(data), reinterpret_cast<const uint8_t*>(data) + size)
{
}

BinaryBlob::~BinaryBlob()
{}

bool BinaryBlob::Create(size_t size, void* data, BinaryBlob** blob)
{
	BinaryBlob* result = new BinaryBlob(size, data);
	if (result)
	{
		*blob = result;
		return true;
	}
	*blob = nullptr;
	return false;
}

const void* BinaryBlob::GetData() const
{
	return mData.data();
}

size_t BinaryBlob::GetSize() const
{
	return mData.size();
}
