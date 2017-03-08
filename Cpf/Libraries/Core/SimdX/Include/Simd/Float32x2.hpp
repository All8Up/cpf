//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Simd/Float32x4_Ref2.hpp"

namespace Cpf
{
	namespace SIMD
	{
		struct Float32x2
		{
			constexpr Float32x2(float _x, float _y) : mData{_x, _y, 0.0f, 0.0f} {}
			constexpr Float32x2(__m128 value) : mData(value) {}

			constexpr operator __m128() const { return mData; }

			Float32x2& operator = (float value) { mData = _mm_load1_ps(&value); }
			constexpr Float32x2& operator = (__m128 value) { mData = value; return *this; }

			__m128 mData;
			Ref1<__m128, float, 0> x;
			Ref1<__m128, float, 1> y;
			Ref2<__m128, float, 0, 0> xx;
			Ref2<__m128, float, 0, 1> xy;
			Ref2<__m128, float, 1, 0> yx;
			Ref2<__m128, float, 1, 1> yy;
		};
	}
}
