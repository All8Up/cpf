//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

namespace CPF
{
	enum SectionID : uint64_t { eInvalid = 0 };

	class CPF_ALIGN(16) DataBlock
	{
	public:
		static DataBlock* Create(size_t count, size_t dataSize);
		static void Destroy(DataBlock* dataBlock);

		size_t GetSectionCount() const;
		void* GetSection(SectionID id) const;

	private:
		friend class DataBlockBuilder;

		DataBlock(size_t totalSize, size_t sectionCount);
		~DataBlock();

		struct SectionEntry
		{
			SectionID mID;
			size_t mOffset;
		};

		size_t mTotalSize;
		size_t mSectionCount;
		SectionEntry mData[1];
	};
}
