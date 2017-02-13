//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/list.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename T>
	using List = eastl::list<T>;
}
