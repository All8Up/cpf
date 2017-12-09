//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename K, typename V>
	using UnorderedMap = std::unordered_map<K, V>;

	template<typename K, typename V>
	using UnorderedMultiMap = std::unordered_multimap<K, V>;
}
