//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <set>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename T, typename C = std::less<T>>
	using Set = std::set<T, C>;
}
