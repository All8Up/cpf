//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/hash_map.h"
#else
#	include <unordered_map>
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
#ifdef CPF_USE_EASTL
	template<typename K, typename V>
	using UnorderedMap = eastl::hash_map<K, V>;

	template<typename K, typename V>
	using UnorderedMultiMap = eastl::hash_multimap<K, V>;
#else
	template<typename K, typename V>
	using UnorderedMap = CPF_STL_NAMESPACE::unordered_map<K, V>;

	template<typename K, typename V>
	using UnorderedMultiMap = CPF_STL_NAMESPACE::unordered_multimap<K, V>;
#endif
}
