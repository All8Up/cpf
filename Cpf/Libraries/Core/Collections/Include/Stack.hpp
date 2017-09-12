//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/stack.h"
#else
#	include <stack>
#endif

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename T>
	using Stack = CPF_STL_NAMESPACE::stack<T>;
}
