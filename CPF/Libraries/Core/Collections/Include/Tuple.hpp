//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/tuple.h"
#else
#	include <tuple>
#endif

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename... T>
	using Tuple = CPF_STL_NAMESPACE::tuple<T...>;
	template <size_t I, typename T>
	using TupleElement = CPF_STL_NAMESPACE::tuple_element<I, T>;
	template <typename T>
	using TupleSize = CPF_STL_NAMESPACE::tuple_size<T>;
}
