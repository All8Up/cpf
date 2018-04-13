//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace STD
	{
		template<typename K, typename V, typename Hash = std::hash<K>>
		using UnorderedMap = std::unordered_map<K, V, Hash>;

		template<typename K, typename V>
		using UnorderedMultiMap = std::unordered_multimap<K, V>;
	}
}
