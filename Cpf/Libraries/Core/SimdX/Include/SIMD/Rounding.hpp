//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		/*
		Let's get the big WTF question out of the way, why wrap up a
		vector 4 to be representable as a 1 through 4 sized vector?
		Later, in the actual vector math classes there needs to be
		consistent handling of 1-4 sizes so the various accessors such
		as v.x, v.xy, v.xyz are still represented by registers in order
		to prevent spilling to memory and breaking pipelining.
		*/

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
