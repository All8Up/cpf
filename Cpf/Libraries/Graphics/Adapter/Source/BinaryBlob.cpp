//////////////////////////////////////////////////////////////////////////
#include "Graphics/BinaryBlob.hpp"

using namespace Cpf;

class BinaryBlob : public Cpf::Graphics::iBlob
{
public:
	COM::Result Initialize(const void* data, int64_t size) override;
	void* CPF_STDCALL GetData() override;
	int64_t CPF_STDCALL GetSize() override;

private:
	BinaryBlob(size_t size, const void* data);
	~BinaryBlob();

	Cpf::Vector<uint8_t> mData;
};


BinaryBlob::BinaryBlob(size_t size, const void* data)
	: mData(reinterpret_cast<const uint8_t*>(data), reinterpret_cast<const uint8_t*>(data) + size)
{
}

BinaryBlob::~BinaryBlob()
{}

COM::Result BinaryBlob::Initialize(const void* data, int64_t size)
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

void* BinaryBlob::GetData()
{
	return reinterpret_cast<void*>(mData.data());
}

int64_t BinaryBlob::GetSize()
{
	return int64_t(mData.size());
}
