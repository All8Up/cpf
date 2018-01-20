//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Hash/HashID.hpp"

namespace CPF
{
	namespace GOM
	{
		using ClassID = Hash::HashID<uint64_t, enum class CID : uint64_t>;
		using InterfaceID = Hash::HashID<uint64_t, enum class IID : uint64_t>;
	}
}
