//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

namespace CPF
{
	enum SectionID : uint64_t { eInvalid = 0 };
	static constexpr size_t kDataBlockAlign = 16;

	/**
	 * DataBlock represents a flat area in memory consisting of
	 * several id'd subsections.  This can be thought of as an
	 * array of variants stored as flat data representations in
	 * memory.  This does not directly support arrays of data
	 * but does retain size information such that the user can
	 * store arrays of data in each section if desired.
	 */
	class CPF_EXPORT CPF_ALIGN(kDataBlockAlign) DataBlock
	{
	public:
		DataBlock(size_t totalSize, size_t sectionCount);
		~DataBlock();
		
		size_t GetSectionCount() const;
		const void* GetSection(SectionID id, size_t* size) const;

		size_t GetSize() const;
		const void* GetData() const;

		static DataBlock* Create(size_t totalSize, size_t sectionCount);
		static void Destroy(DataBlock* dataBlock);

	private:
		friend class DataBlockBuilder;

		void operator delete(void*) { }
		void* operator new (size_t) { return nullptr; }
		void* operator new (size_t, void* block) { return block; }
		void operator delete(void*, void*) {}

		struct CPF_ALIGN(kDataBlockAlign) SectionEntry
		{
			SectionID mID;
			size_t mOffset;
			size_t mSize;
		};

		size_t mTotalSize;
		size_t mSectionCount;
		SectionEntry mData[1];
	};
}
