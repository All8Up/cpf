//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

namespace CPF
{
	namespace SIMD
	{
		enum class Rounding : int
		{
			eCurrent,
			eNearest,
			eUp,
			eDown,
			eTruncate
		};
	}
}
