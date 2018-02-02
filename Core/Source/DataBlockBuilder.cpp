//////////////////////////////////////////////////////////////////////////
#include "CPF/DataBlockBuilder.hpp"

using namespace CPF;

DataBlockBuilder::DataBlockBuilder()
{}

DataBlockBuilder::~DataBlockBuilder()
{}

bool DataBlockBuilder::AddSection(SectionID id, size_t alignment, void* data, size_t size)
{
	const auto it = mSectionMap.find(id);
	if (it != mSectionMap.end())
		return false;

	SectionData section
	{
		alignment,
		size,
		nullptr
	};
	mSectionMap.insert({ id, section });
	return true;
}

void* DataBlockBuilder::GetSection(SectionID id) const
{
	const auto it = mSectionMap.find(id);
	if (it == mSectionMap.end())
		return nullptr;
	return it->second.mpData;
}

size_t DataBlockBuilder::GetTotalSize() const
{
	return 0;
}

DataBlock* DataBlockBuilder::GetDataBlock() const
{
	return nullptr;
}
