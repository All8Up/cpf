//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		TYPE Exp(TYPE value)
		{
			return std::exp(value);
		}

		template <typename TYPE>
		TYPE Exp2(TYPE value)
		{
			return std::exp2(value);
		}

		template <typename TYPE>
		TYPE Log(TYPE value)
		{
			return std::log(value);
		}

		template <typename TYPE>
		TYPE Log10(TYPE value)
		{
			return std::log10(value);
		}

		template <typename TYPE>
		TYPE Log2(TYPE value)
		{
			return std::log2(value);
		}
	}
}
