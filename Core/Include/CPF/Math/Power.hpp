//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		TYPE Pow(TYPE lhs, TYPE rhs)
		{
			return std::pow(lhs, rhs);
		}

		template <typename TYPE>
		TYPE Sqrt(TYPE value)
		{
			return std::sqrt(value);
		}
	}
}
