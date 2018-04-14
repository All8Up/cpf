//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		TYPE Ceil(TYPE value)
		{
			return std::ceil(value);
		}

		template <typename TYPE>
		TYPE Floor(TYPE value)
		{
			return std::floor(value);
		}

		template <typename TYPE>
		TYPE Trunc(TYPE value)
		{
			return std::trunc(value);
		}

		template <typename TYPE>
		TYPE Round(TYPE value)
		{
			return std::round(value);
		}
	}
}
