//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/functional.h"
#	include "EASTL/hash_set.h"
#else
#	include <functional>
#	include <unordered_set>
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	// Just alias in std::unordered_set for the moment.
	template<typename T, typename Hash = CPF_STL_NAMESPACE::hash<T>>

#ifdef CPF_USE_EASTL
	using UnorderedSet = CPF_STL_NAMESPACE::hash_set<T, Hash>;

	template<typename T>
	using UnorderedMultiSet = CPF_STL_NAMESPACE::hash_multiset<T>;
#else
	using UnorderedSet = CPF_STL_NAMESPACE::unordered_set<T, Hash>;

	template<typename T>
	using UnorderedMultiSet = CPF_STL_NAMESPACE::unordered_multiset<T>;
#endif
}
