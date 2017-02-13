//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "eastl/queue.h"
#else
#	include <queue>
#endif


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename T>
	using Queue = CPF_STL_NAMESPACE::queue<T>;
}
