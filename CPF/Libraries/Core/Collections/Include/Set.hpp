//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/set.h"
#else
#	include <set>
#endif


//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename T, typename C = CPF_STL_NAMESPACE::less<T>>
	using Set = CPF_STL_NAMESPACE::set<T, C>;
}
