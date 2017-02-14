//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/algorithm.h"
#else
#	include <algorithm>
#	include <functional>
#endif


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
	OutputIterator Transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation unaryOperation)
	{
		return CPF_STL_NAMESPACE::transform(first, last, result, unaryOperation);
	}


	template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation>
	OutputIterator Transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, BinaryOperation binaryOperation)
	{
		return CPF_STL_NAMESPACE::transform(first1, last1, first2, result, binaryOperation);
	}


	template <typename ForwardIterator, typename T>
	void Replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
	{
		CPF_STL_NAMESPACE::replace<ForwardIterator, T>(first, last, old_value, new_value);
	}

	template <typename InputIterator, typename Function>
	Function ForEach(InputIterator first, InputIterator last, Function func)
	{
		return CPF_STL_NAMESPACE::for_each(first, last, func);
	}

	template <typename InputIterator, typename Predicate>
	InputIterator FindIf(InputIterator first, InputIterator last, Predicate pred)
	{
		return CPF_STL_NAMESPACE::find_if(first, last, pred);
	}
}
