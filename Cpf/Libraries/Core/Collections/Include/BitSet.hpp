//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/bitset.h"
#else
#	include <bitset>
#endif

namespace Cpf
{
#ifdef CPF_USE_EASTL
	template <typename TYPE, typename WORDTYPE=uint32_t>
	using BitSet = CPF_STL_NAMESPACE::bitset<TYPE, WORDTYPE>;
#else
	template <typename TYPE>
	using BitSet = CPF_STL_NAMESPACE::bitset<TYPE>;
#endif
}
