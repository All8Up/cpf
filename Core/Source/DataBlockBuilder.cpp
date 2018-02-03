//////////////////////////////////////////////////////////////////////////
#include "CPF/DataBlockBuilder.hpp"
#include "CPF/Std/Memory.hpp"

using namespace CPF;

DataBlockBuilder::DataBlockBuilder()
{}

DataBlockBuilder::~DataBlockBuilder()
{}

bool DataBlockBuilder::AddSection(SectionID id, const void* data, size_t size)
{
	const auto it = mSectionMap.find(id);
	if (it != mSectionMap.end())
		return false;
	mSectionMap.insert({ id, Vector<uint8_t>(reinterpret_cast<const uint8_t*>(data), reinterpret_cast<const uint8_t*>(data) + size) });
	return true;
}

Option<const Vector<uint8_t>*> DataBlockBuilder::GetSection(SectionID id) const
{
	const auto it = mSectionMap.find(id);
	if (it == mSectionMap.end())
		return Option<const Vector<uint8_t>*>::None();
	return Option<const Vector<uint8_t>*>::Some(&it->second);
}

size_t DataBlockBuilder::GetTotalSize() const
{
	size_t sectionOffset = _HeaderSize();
	CPF_ASSERT((sectionOffset % kDataBlockAlign) == 0);
	for (const auto& section : mSectionMap)
	{
		sectionOffset += section.second.size();
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
		auto* sectionPtr = reinterpret_cast<uint8_t*>(buffer) + _HeaderSize();

		size_t i = 0;
		for (const auto& section : mSectionMap)
		{
			// Fill in the header portion.
			size_t offset = sectionPtr - static_cast<uint8_t*>(buffer);
			header[i++] = { section.first, offset, section.second.size() };

			// Store the section data.
			Std::MemCpy(sectionPtr, section.second.data(), section.second.size());

			// Move to the next section.
			sectionPtr += section.second.size();

			CPF_ASSERT(sectionPtr <= reinterpret_cast<uint8_t*>(buffer) + size);

			// Align the sectionPtr if needed.
			const size_t remain = intptr_t(sectionPtr) % kDataBlockAlign;
			sectionPtr += (remain == 0) ? 0 : kDataBlockAlign - remain;
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
