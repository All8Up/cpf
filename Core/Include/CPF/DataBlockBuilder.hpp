//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/DataBlock.hpp"
#include "Std/Map.hpp"

namespace CPF
{
	class DataBlock;

	class DataBlockBuilder
	{
	public:
		DataBlockBuilder();
		~DataBlockBuilder();

		bool AddSection(SectionID id, size_t alignment, void* data, size_t size);
		void* GetSection(SectionID id) const;

		size_t GetTotalSize() const;
		DataBlock* GetDataBlock() const;

	private:
		struct SectionData
		{
			size_t mAlignment;
			size_t mSize;
			void* mpData;
		};
		using SectionMap = Map<SectionID, SectionData>;
		SectionMap mSectionMap;
	};
}
