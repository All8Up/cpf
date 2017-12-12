//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <unordered_set>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	// Just alias in std::unordered_set for the moment.
	template<typename T, typename Hash = std::hash<T>>

	using UnorderedSet = std::unordered_set<T, Hash>;

	template<typename T>
	using UnorderedMultiSet = std::unordered_multiset<T>;
}
