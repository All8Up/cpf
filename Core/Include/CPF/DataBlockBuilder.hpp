//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/DataBlock.hpp"
#include "Std/Map.hpp"
#include "Std/Vector.hpp"
#include "Option.hpp"

namespace CPF
{
	class CPF_EXPORT DataBlockBuilder
	{
	public:
		DataBlockBuilder();
		~DataBlockBuilder();

		bool AddSection(SectionID id, const void* data, size_t size);
		Option<const STD::Vector<uint8_t>*> GetSection(SectionID id) const;

		size_t GetTotalSize() const;
		DataBlock* Create() const;
		DataBlock* Store(void* buffer, size_t size) const;

	private:
		size_t _HeaderSize() const;

		struct SectionData
		{
			int32_t mIndex;
			STD::Vector<uint8_t> mData;
		};
		using SectionMap = STD::Map<SectionID, SectionData>;
		int32_t mSectionCount;
		CPF_DLL_SAFE_BEGIN;
		SectionMap mSectionMap;
		CPF_DLL_SAFE_END;
	};
}
