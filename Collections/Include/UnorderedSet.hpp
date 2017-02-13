//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/functional.h"
#include "EASTL/hash_set.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	// Just alias in std::unordered_set for the moment.
	template<typename T, typename Hash = eastl::hash<T>>
	using UnorderedSet = eastl::hash_set<T, Hash>;

	template<typename T>
	using UnorderedMultiSet = eastl::hash_multiset<T>;
}
