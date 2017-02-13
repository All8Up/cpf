//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/stack.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename T>
	using Stack = eastl::stack<T>;
}
