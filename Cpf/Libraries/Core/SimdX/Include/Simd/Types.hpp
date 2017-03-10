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

		// Tags to allow the same primitive type, __m128 in VC, to represent
		// more fine grained divisions in a type safe manner.
		struct Count_1Tag;
		struct Count_2Tag;
		struct Count_3Tag;
		struct Count_4Tag;
	}
}

#include "Detail/SSE4_1/F32x4.hpp"
#include "Detail/SSE4_1/I32x4.hpp"

namespace Cpf
{
	namespace SIMD
	{
		using F32x1 = SSE4_1::F32x4_1;
		using F32x2 = SSE4_1::F32x4_2;
		using F32x3 = SSE4_1::F32x4_3;
		using F32x4 = SSE4_1::F32x4_4;

		using I32x1 = SSE4_1::I32x4_1;
		using I32x2 = SSE4_1::I32x4_2;
		using I32x3 = SSE4_1::I32x4_3;
		using I32x4 = SSE4_1::I32x4_4;
	}
}
