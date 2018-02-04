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

Vector<SectionID> DataBlock::GetSections() const
{
	Vector<SectionID> result(mSectionCount);
	int i = 0;
	for (const auto& section : *this)
	{
		result[i++] = section.first;
	}
	return result;
}


const void* DataBlock::GetByIndex(size_t index, size_t* size) const
{
	if (index >= mSectionCount)
		return nullptr;
	if (size)
		*size = mData[index].mSize;
	return reinterpret_cast<const uint8_t*>(this) + mData[index].mOffset;
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
	return reinterpret_cast<const uint8_t*>(this) + mData[m].mOffset;
}

size_t DataBlock::GetSize() const
{
	return mTotalSize;
}

const void* DataBlock::GetData() const
{
	return this;
}

DataBlock* DataBlock::Create(size_t totalSize, size_t sectionCount)
{
	auto* buffer = new uint8_t[totalSize];
	auto* result = new(buffer) DataBlock(totalSize, sectionCount);
	CPF_ASSERT(buffer == reinterpret_cast<uint8_t*>(result));
	return result;
}

void DataBlock::Destroy(DataBlock* dataBlock)
{
	auto* buffer = reinterpret_cast<uint8_t*>(dataBlock);
	delete[] buffer;
}

DataBlock::const_iterator DataBlock::begin() const
{
	return { this, 0 };
}

DataBlock::const_iterator DataBlock::end() const
{
	return { this, mSectionCount };
}
