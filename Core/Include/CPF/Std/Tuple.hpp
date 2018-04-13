//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <tuple>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace STD
	{
		template<typename... T>
		using Tuple = std::tuple<T...>;
		template <size_t I, typename T>
		using TupleElement = std::tuple_element<I, T>;
		template <typename T>
		using TupleSize = std::tuple_size<T>;
	}
}
