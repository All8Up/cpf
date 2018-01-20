//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Hash/HashID.hpp"

namespace CPF
{
	namespace GOM
	{
		enum class IID : uint64_t { eInvalid = 0 };
		enum class CID : uint64_t { eInvalid = 0 };

		using ClassID = Hash::HashID<uint64_t, GOM::CID>;
		using InterfaceID = Hash::HashID<uint64_t, GOM::IID>;
	}
}
