//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <utility>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace STD
	{
		template<typename LHS, typename RHS>
		using Pair = std::pair<LHS, RHS>;

		template<typename LHS, typename RHS> inline
			Pair<LHS, RHS> MakePair(LHS lhs, RHS rhs)
		{
			return std::make_pair<LHS, RHS>(lhs, rhs);
		}
	}
}
