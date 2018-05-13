//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/CPFS/Version.hpp"
#include "CPF/EnumFlagType.hpp"

namespace CPF
{
	namespace CPFS
	{
		enum class ChunkFlags : uint64_t
		{
			eNone = 0
		};
		CPF_ENUM_FLAG_TYPE(ChunkFlags);

		struct alignas(16) Chunk
		{
			static constexpr Version kDefaultVersion = Version(0, 1, 0);

			ECC mID;
			Version mVersion;
			ChunkFlags mFlags;
			uint64_t mLength;
		};
	}
}
