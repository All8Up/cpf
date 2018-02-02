//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/DataBlock.hpp"
#include "Std/Map.hpp"
#include "Std/Vector.hpp"
#include "Option.hpp"

namespace CPF
{
	class DataBlock;

	class DataBlockBuilder
	{
	public:
		DataBlockBuilder();
		~DataBlockBuilder();

		bool AddSection(SectionID id, size_t alignment, const Vector<uint8_t>& data);
		Option<const Vector<uint8_t>*> GetSection(SectionID id) const;

		size_t GetTotalSize() const;
		DataBlock* CreateDataBlock() const;

	private:
		size_t _HeaderSize() const;

		struct SectionData
		{
			size_t mAlignment;
			Vector<uint8_t> mData;
		};
		using SectionMap = Map<SectionID, SectionData>;
		SectionMap mSectionMap;
	};
}
