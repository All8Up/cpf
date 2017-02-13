//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/utility.h"
#else
#	include <utility>
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename LHS, typename RHS>
	using Pair = CPF_STL_NAMESPACE::pair<LHS, RHS>;

	template<typename LHS, typename RHS> inline
	Pair<LHS, RHS> MakePair(LHS lhs, RHS rhs)
	{
		return CPF_STL_NAMESPACE::make_pair<LHS, RHS>(lhs, rhs);
	}
}
