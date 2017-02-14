//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Ratio
		{
			Ratio();
			Ratio(int32_t num, int32_t denom);

			explicit operator float() const;

			int32_t mNumerator;
			int32_t mDenominator;
		};
	}
}
