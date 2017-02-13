//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/bitset.h"

namespace Cpf
{
	template <typename TYPE, typename WORDTYPE=uint32_t>
	using BitSet = eastl::bitset<TYPE, WORDTYPE>;
}
