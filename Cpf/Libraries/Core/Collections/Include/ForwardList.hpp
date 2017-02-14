//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/forward_list.h"
#else
#	include <forward_list>
#endif


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename T>
	using ForwardList = CPF_STL_NAMESPACE::forward_list<T>;
}
