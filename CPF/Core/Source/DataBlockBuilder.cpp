//////////////////////////////////////////////////////////////////////////
#include "CPF/DataBlockBuilder.hpp"
#include "CPF/CSTD/Memory.hpp"

using namespace CPF;

DataBlockBuilder::DataBlockBuilder()
	: mSectionCount(0)
{}

DataBlockBuilder::~DataBlockBuilder()
{}

bool DataBlockBuilder::AddSection(SectionID id, const void* data, size_t size)
{
	const auto it = mSectionMap.find(id);
	if (it != mSectionMap.end())
		return false;
	mSectionMap.insert({ id, { mSectionCount++, STD::Vector<uint8_t>(reinterpret_cast<const uint8_t*>(data), reinterpret_cast<const uint8_t*>(data) + size)} });
	return true;
}

Option<const STD::Vector<uint8_t>*> DataBlockBuilder::GetSection(SectionID id) const
{
	const auto it = mSectionMap.find(id);
	if (it == mSectionMap.end())
		return Option<const STD::Vector<uint8_t>*>::None();
	return Option<const STD::Vector<uint8_t>*>::Some(&it->second.mData);
}

size_t DataBlockBuilder::GetTotalSize() const
{
	size_t sectionOffset = _HeaderSize();
	CPF_ASSERT((sectionOffset % kDataBlockAlign) == 0);
	for (const auto& section : mSectionMap)
	{
		sectionOffset += section.second.mData.size();
		const size_t remain = sectionOffset % kDataBlockAlign;
		sectionOffset += (remain == 0) ? 0 : kDataBlockAlign - remain;
		CPF_ASSERT((sectionOffset % kDataBlockAlign) == 0);
	}
	
	return sectionOffset;
}

DataBlock* DataBlockBuilder::Create() const
{
	const size_t totalSize = GetTotalSize();
	auto* dataBlock = DataBlock::Create(totalSize, mSectionMap.size());
	if (dataBlock)
		return Store(dataBlock, totalSize);
	return nullptr;
}

DataBlock* DataBlockBuilder::Store(void* buffer, size_t size) const
{
	const size_t totalSize = GetTotalSize();
	if (size >= totalSize && buffer)
	{
		// Builds the header.
		auto* result = reinterpret_cast<DataBlock*>(buffer);

		// Get a pointer to the raw data section.
		auto* header = result->mData;

		// Compute section offsets based on order.
		using SectionOffsets = STD::Map<int32_t, size_t>;
		SectionOffsets offsets;
		// First pass, just initialize the map.
		for (const auto& section : mSectionMap)
		{
			CPF_ASSERT(offsets.find(section.second.mIndex) == offsets.end());
			offsets[section.second.mIndex] = 0;
		}
		// Second pass, add the sizes.
		for (auto& offset : offsets)
		{
			for (const auto& section : mSectionMap)
			{
				if (offset.first > section.second.mIndex)
				{
					// This section is inserted before the target offset, add the size to the current offset.
					auto sectionSize = section.second.mData.size() + (kDataBlockAlign - 1);
					sectionSize = (sectionSize / kDataBlockAlign) * kDataBlockAlign;
					offset.second += sectionSize;
				}
			}
		}

		size_t i = 0;
		auto* sectionPtr = reinterpret_cast<uint8_t*>(buffer) + _HeaderSize();
		for (const auto& section : mSectionMap)
		{
			// Fill in the header portion.
			size_t offset = offsets[section.second.mIndex];
			header[i++] = { section.first, offset + _HeaderSize(), section.second.mData.size() };

			// Store the section data.
			CSTD::MemCpy(sectionPtr + offsets[section.second.mIndex], section.second.mData.data(), section.second.mData.size());
		}

		return result;
	}
	return nullptr;
}

size_t DataBlockBuilder::_HeaderSize() const
{
	if (!mSectionMap.empty())
	{
		size_t result = sizeof(DataBlock) + (sizeof(DataBlock::SectionEntry) * (mSectionMap.size() - 1));
		const size_t remain = result % kDataBlockAlign;
		result += (remain == 0) ? 0 : kDataBlockAlign - remain;
		return result;
	}
	return 0;
}
