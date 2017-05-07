//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		TYPE Pow(TYPE value)
		{
			return std::pow(value);
		}

		template <typename TYPE>
		TYPE Sqrt(TYPE value)
		{
			return std::sqrt(value);
		}
	}
}
