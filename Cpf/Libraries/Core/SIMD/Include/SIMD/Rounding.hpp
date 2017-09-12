//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

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
