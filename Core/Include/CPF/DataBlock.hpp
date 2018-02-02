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
		DataBlock();
		~DataBlock();

		size_t mBlockSize;
		size_t mSectionCount;
		uint8_t mData[1];
	};
}
