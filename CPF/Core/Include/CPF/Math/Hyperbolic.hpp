//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		TYPE SinH(TYPE value)
		{
			return std::sinh(value);
		}

		template <typename TYPE>
		TYPE CosH(TYPE value)
		{
			return std::cosh(value);
		}

		template <typename TYPE>
		TYPE TanH(TYPE value)
		{
			return std::tanh(value);
		}

		template <typename TYPE>
		TYPE ASinH(TYPE value)
		{
			return std::asinh(value);
		}

		template <typename TYPE>
		TYPE ACosH(TYPE value)
		{
			return std::acosh(value);
		}

		template <typename TYPE>
		TYPE ATanH(TYPE value)
		{
			return std::atanh(value);
		}
	}
}
