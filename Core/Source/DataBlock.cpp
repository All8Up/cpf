//////////////////////////////////////////////////////////////////////////
#include "CPF/DataBlock.hpp"

using namespace CPF;

DataBlock::DataBlock(size_t totalSize, size_t sectionCount)
	: mTotalSize(totalSize)
	, mSectionCount(sectionCount)
{
}

DataBlock::~DataBlock()
{}

size_t DataBlock::GetSectionCount() const
{
	return mSectionCount;
}

const void* DataBlock::GetSection(SectionID id, size_t* size) const
{
	// Binary search for the id.
	// NOTE: this binary search my be overkill for most use cases.
	size_t l = 0;
	size_t r = mSectionCount - 1;
	size_t m = 0;
	while (l <= r)
	{
		m = (l + r) / 2;
		if (mData[m].mID < id)
		{
			l = m + 1;
			continue;
		}
		if (mData[m].mID > id)
		{
			r = m - 1;
			continue;
		}
		break;
	}
	if (!mData[m].mID == id)
		return nullptr;
	if (size)
		*size = mData[m].mSize;
	return reinterpret_cast<const uint8_t*>(mData) + mData[m].mOffset;
}
