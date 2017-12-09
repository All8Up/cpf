//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/algorithm.h"
#else
#	include <algorithm>
#endif


//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename T>
	typename CPF_STL_NAMESPACE::remove_reference<T>::type&& Move(T&& v)
	{
		return CPF_STL_NAMESPACE::move(v);
	}
}
