//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		TYPE Min(const TYPE& lhs, const TYPE& rhs)
		{
			return (lhs < rhs) ? lhs : rhs;
		}

		template <typename TYPE, typename COMP>
		TYPE Min(const TYPE& lhs, const TYPE& rhs, COMP comp)
		{
			return comp(lhs, rhs) ? lhs : rhs;
		}

		template <typename TYPE>
		TYPE Max(const TYPE& lhs, const TYPE& rhs)
		{
			return (lhs > rhs) ? lhs : rhs;
		}

		template <typename TYPE, typename COMP>
		TYPE Max(const TYPE& lhs, const TYPE& rhs, COMP comp)
		{
			return comp(lhs, rhs) ? lhs : rhs;
		}

		template <typename TYPE>
		TYPE Clamp(TYPE value, TYPE low, TYPE high)
		{
			return value < low ? low :
				value > high ? high :
				value;
		}
	}
}
