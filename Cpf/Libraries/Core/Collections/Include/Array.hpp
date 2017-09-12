//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/array.h"
#else
#	include <array>
#endif


//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename T, size_t SIZE>
	using Array = CPF_STL_NAMESPACE::array<T, SIZE>;
}
