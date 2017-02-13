//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/hash_map.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename K, typename V>
	using UnorderedMap = eastl::hash_map<K, V>;

	template<typename K, typename V>
	using UnorderedMultiMap = eastl::hash_multimap<K, V>;
}
