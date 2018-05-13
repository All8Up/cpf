//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

namespace CPF
{
	namespace CPFS
	{
		union Version
		{
			constexpr Version()
				: mVersion(0)
			{}
			constexpr Version(uint16_t major, uint16_t minor, uint32_t patch)
				: mMajor(major)
				, mMinor(minor)
				, mPatch(patch)
			{}

			uint64_t mVersion;
			struct
			{
				uint16_t mMajor;
				uint16_t mMinor;
				uint32_t mPatch;
			};
		};
	}
}
