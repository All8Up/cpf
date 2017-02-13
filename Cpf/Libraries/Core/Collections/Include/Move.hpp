//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/algorithm.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename T>
	inline typename eastl::remove_reference<T>::type&& Move(T&& v)
	{
		return eastl::move(v);
	}
}
