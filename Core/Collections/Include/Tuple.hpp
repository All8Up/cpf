//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/tuple.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename... T>
	using Tuple = eastl::tuple<T...>;
	template <size_t I, typename T>
	using TupleElement = eastl::tuple_element<I, T>;
	template <typename T>
	using TupleSize = eastl::tuple_size<T>;
}
