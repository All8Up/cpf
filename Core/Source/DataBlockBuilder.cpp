//////////////////////////////////////////////////////////////////////////
#include "CPF/DataBlockBuilder.hpp"

using namespace CPF;

DataBlockBuilder::DataBlockBuilder()
{}

DataBlockBuilder::~DataBlockBuilder()
{}

bool DataBlockBuilder::AddSection(SectionID id, size_t alignment, const Vector<uint8_t>& data)
{
	const auto it = mSectionMap.find(id);
	if (it != mSectionMap.end())
		return false;

	SectionData section
	{
		alignment,
		data
	};
	mSectionMap.insert({ id, section });
	return true;
}

Option<const Vector<uint8_t>*> DataBlockBuilder::GetSection(SectionID id) const
{
	const auto it = mSectionMap.find(id);
	if (it == mSectionMap.end())
		return Option<const Vector<uint8_t>*>::None();
	return Option<const Vector<uint8_t>*>::Some(&it->second.mData);
}

size_t DataBlockBuilder::GetTotalSize() const
{
	return _HeaderSize();
}

DataBlock* DataBlockBuilder::CreateDataBlock() const
{
	size_t totalSize = GetTotalSize();
	uint8_t* buffer = new uint8_t[totalSize];
	if (buffer)
	{
		DataBlock* result = new(buffer) DataBlock(totalSize, mSectionMap.size());



		return result;
	}
	return nullptr;
}

size_t DataBlockBuilder::_HeaderSize() const
{
	if (!mSectionMap.empty())
	{
		size_t result = sizeof(DataBlock::SectionEntry) * mSectionMap.size();
		size_t firstAlignment = mSectionMap.begin()->second.mAlignment;
		size_t remain = result % firstAlignment;
		result = remain == 0 ? 0 : firstAlignment - remain;
		return result;
	}
	return 0;
}
