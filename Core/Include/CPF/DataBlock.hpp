//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <iterator>
#include "Std/Pair.hpp"
#include "Std/Move.hpp"
#include "Std/Vector.hpp"

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
		// Can not copy or move.
		DataBlock() = delete;
		DataBlock(const DataBlock&) = delete;
		DataBlock& operator = (const DataBlock&) = delete;
		DataBlock(DataBlock&&) = delete;
		DataBlock& operator = (DataBlock&&) = delete;

		size_t GetSectionCount() const;
		Vector<SectionID> GetSections() const;
		const void* GetByIndex(size_t index, size_t* size) const;
		const void* GetSection(SectionID id, size_t* size) const;

		size_t GetSize() const;
		const void* GetData() const;

		static DataBlock* Create(size_t totalSize, size_t sectionCount);
		static void Destroy(DataBlock* dataBlock);

		using SectionData = Pair<const void*, size_t>;
		using SectionInfo = Pair<SectionID, SectionData>;
		class const_iterator;
		const_iterator begin() const;
		const_iterator end() const;

	private:
		friend class DataBlockBuilder;

		DataBlock(size_t totalSize, size_t sectionCount);
		~DataBlock();

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

	class DataBlock::const_iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = SectionData;
		using difference_type = size_t;
		using pointer = SectionData * ;
		using reference = SectionData & ;

		const_iterator() : mpBlock(nullptr), mIndex(0) {}
		const_iterator(const const_iterator& rhs) = default;
		const_iterator(const_iterator&& rhs) = default;
		~const_iterator() = default;

		const_iterator& operator = (const const_iterator& rhs) = default;
		const_iterator& operator = (const_iterator&& rhs) noexcept { mpBlock = Move(rhs.mpBlock); mIndex = Move(rhs.mIndex); return *this; }

		bool operator ==(const const_iterator& rhs) const { return mpBlock == rhs.mpBlock && mIndex == rhs.mIndex; }
		bool operator !=(const const_iterator& rhs) const { return !(*this == rhs); }

		bool operator <(const const_iterator& rhs) const { return mIndex < rhs.mIndex; }
		bool operator >(const const_iterator& rhs) const { return mIndex > rhs.mIndex; }

		SectionInfo operator *() const
		{
			size_t size = 0;
			const void* data = mpBlock->GetByIndex(mIndex, &size);
			SectionInfo result {
				mpBlock->mData[mIndex].mID,
				{
					data,
					size
				}
			};
			return result;
		}

		const_iterator& operator ++() { ++mIndex; return *this; }
		const_iterator operator++(int) { const_iterator result(*this); ++mIndex; return result; }
		const_iterator& operator --() { --mIndex; return *this; }
		const_iterator operator --(int) { const_iterator result(*this); --mIndex; return result; }

	private:
		friend class DataBlock;

		const_iterator(const DataBlock* block, size_t index)
			: mpBlock(block)
			, mIndex(index)
		{}

		const DataBlock * mpBlock;
		size_t mIndex;
	};
}
