//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <algorithm>


//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
	OutputIterator Transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation unaryOperation)
	{
		return std::transform(first, last, result, unaryOperation);
	}


	template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation>
	OutputIterator Transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, BinaryOperation binaryOperation)
	{
		return std::transform(first1, last1, first2, result, binaryOperation);
	}


	template <typename ForwardIterator, typename T>
	void Replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
	{
		std::replace<ForwardIterator, T>(first, last, old_value, new_value);
	}

	template <typename InputIterator, typename Function>
	Function ForEach(InputIterator first, InputIterator last, Function func)
	{
		return std::for_each(first, last, func);
	}

	template <typename InputIterator, typename T>
	InputIterator Find(InputIterator first, InputIterator last, const T& val)
	{
		return std::find(first, last, val);
	}

	template <typename InputIterator, typename T, typename COMP>
	InputIterator Find(InputIterator first, InputIterator last, const T& val, COMP comp)
	{
		return std::find(first, last, val, comp);
	}

	template <typename InputIterator, typename Predicate>
	InputIterator FindIf(InputIterator first, InputIterator last, Predicate pred)
	{
		return std::find_if(first, last, pred);
	}

	template <typename LHS, typename RHS>
	LHS Min(LHS lhs, RHS rhs)
	{
		return std::min(lhs, rhs);
	}

	template <typename LHS, typename RHS>
	LHS Max(LHS lhs, RHS rhs)
	{
		return std::max(lhs, rhs);
	}

	template <typename ForwardIterator, typename T>
	ForwardIterator LowerBound(ForwardIterator first, ForwardIterator last, const T& val)
	{
		return std::lower_bound(first, last, val);
	}

	template <typename ForwardIterator, typename T, typename COMP>
	ForwardIterator LowerBound(ForwardIterator first, ForwardIterator last, const T& val, COMP comp)
	{
		return std::lower_bound(first, last, val, comp);
	}

	template <typename ForwardIterator, typename T>
	ForwardIterator UpperBound(ForwardIterator first, ForwardIterator last, const T& val)
	{
		return std::upper_bound(first, last, val);
	}

	template <typename ForwardIterator, typename T, typename COMP>
	ForwardIterator UpperBound(ForwardIterator first, ForwardIterator last, const T& val, COMP comp)
	{
		return std::upper_bound(first, last, val, comp);
	}

	template <typename ForwardIterator, typename T>
	bool BinarySearch(ForwardIterator first, ForwardIterator last, const T& val)
	{
		return std::binary_search(first, last, val);
	}

	template <typename ForwardIterator, typename T, typename COMP>
	bool BinarySearch(ForwardIterator first, ForwardIterator last, const T& val, COMP comp)
	{
		return std::binary_search(first, last, val, comp);
	}
}
