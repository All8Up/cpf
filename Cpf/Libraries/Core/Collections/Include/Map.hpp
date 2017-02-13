//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/map.h"
#else
#	include <map>
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename K, typename V>
	using Map = CPF_STL_NAMESPACE::map<K, V>;
}
