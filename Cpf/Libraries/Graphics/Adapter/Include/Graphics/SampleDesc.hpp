//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct SampleDesc
		{
			SampleDesc();
			SampleDesc(int32_t count, int32_t quality);

			uint64_t GetHash() const;

			int32_t mCount;
			int32_t mQuality;
		};

		inline
		SampleDesc::SampleDesc()
			: mCount(1)
			, mQuality(0)
		{}

		inline
		SampleDesc::SampleDesc(int32_t count, int32_t quality)
			: mCount(count)
			, mQuality(quality)
		{}

		inline uint64_t SampleDesc::GetHash() const
		{
			return Hash::Crc64(reinterpret_cast<const char*>(this), sizeof(SampleDesc));
		}
	}
}
