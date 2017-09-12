//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"


namespace CPF
{
	template<typename TYPE>
	inline typename TYPE::const_iterator FindAnyOf(
		typename TYPE::const_iterator begin,
		typename TYPE::const_iterator end,
		const TYPE& values)
	{
		for (auto it = begin; it != end; ++it)
		{
			for (auto vit = values.begin(); vit != values.end(); ++vit)
			{
				if (*it == *vit)
					return it;
			}
		}
		return end;
	}


	template<typename TYPE>
	inline typename TYPE::const_iterator FindAnyNotOf(
		typename TYPE::const_iterator begin,
		typename TYPE::const_iterator end,
		const TYPE& values)
	{
		for (auto it = begin; it != end; ++it)
		{
			auto found = false;
			for (auto vit = values.begin(); vit != values.end(); ++vit)
			{
				if (*it == *vit)
				{
					found = true;
					break;
				}
			}
			if (!found)
				return it;
		}

		return end;
	}
}
