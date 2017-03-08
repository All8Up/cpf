//////////////////////////////////////////////////////////////////////////
#pragma once
// New version only supports 4.1 + but will probably need to backport to SSE 3 to get best coverage.
#include <smmintrin.h>
#include "Simd/Float32x4_RefOne.hpp"

namespace Cpf
{
	namespace SIMD
	{
		union Float32x4
		{
		public:
			constexpr Float32x4(float _x, float _y, float _z, float _w)
				: mData{ _x, _y, _z, _w }
			{}

			__m128 mData;
			RefOne<__m128, float, 0> x;
			RefOne<__m128, float, 1> y;
			RefOne<__m128, float, 2> z;
			RefOne<__m128, float, 3> w;
		};
	}
}
