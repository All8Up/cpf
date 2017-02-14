//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/vector.h"
#else
#	include <vector>
#endif


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	// Just alias in std::vector for the moment.
	template<typename T>
	using Vector = CPF_STL_NAMESPACE::vector<T>;
}
