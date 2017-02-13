//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/utility.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename LHS, typename RHS>
	using Pair = eastl::pair<LHS, RHS>;

	template<typename LHS, typename RHS> inline
	Pair<LHS, RHS> MakePair(LHS lhs, RHS rhs)
	{
		return eastl::make_pair<LHS, RHS>(lhs, rhs);
	}
}
