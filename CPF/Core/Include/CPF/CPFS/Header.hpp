//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/CPFS/Version.hpp"
#include "CPF/CPFS/TimeStamp.hpp"
#include "CPF/CPFS/ECC.hpp"
#include "CPF/EnumFlagType.hpp"

namespace CPF
{
	namespace CPFS
	{
		enum class HeaderFlags : uint64_t
		{
			eNone = 0
		};
		CPF_ENUM_FLAG_TYPE(HeaderFlags);


		struct alignas(16) Header
		{
			static constexpr ECC kMagic = MakeECC('_', '_', 'C', 'P', 'F', 'S', '_', '_');
			static constexpr Version kVersion = Version(0, 1, 0);

			ECC mMagic;
			Version mVersion;
			TimeStamp mTimeStamp;
			HeaderFlags mFlags;
		};
	}
}
