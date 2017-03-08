//////////////////////////////////////////////////////////////////////////
#pragma once
// New version only supports 4.1 + but will probably need to backport to SSE 3 to get best coverage.
#include <smmintrin.h>
#include "Simd/Float32x4_Ref1.hpp"
#include "Simd/Float32x4_Ref2.hpp"
#include "Simd/Float32x4_Ref3.hpp"
#include "Simd/Float32x4_Ref4.hpp"

namespace Cpf
{
	namespace SIMD
	{
		union Float32x4
		{
		public:
			static constexpr __m128 kZero = { 0.0f, 0.0f, 0.0f, 0.0f };
			static constexpr __m128 kXAxis = { 1.0f, 0.0f, 0.0f, 0.0f };
			static constexpr __m128 kYAxis = { 0.0f, 1.0f, 0.0f, 0.0f };
			static constexpr __m128 kZAxis = { 0.0f, 0.0f, 1.0f, 0.0f };
			static constexpr __m128 kOnes = { 1.0f, 1.0f, 1.0f, 1.0f };

			constexpr Float32x4(__m128 value) : mData(value) {}
			constexpr Float32x4(float _x, float _y, float _z, float _w)
				: mData{ _x, _y, _z, _w }
			{}

			constexpr Float32x4& operator = (__m128 value) { mData = value; return *this; }

			__m128 mData;
			Ref1<__m128, float, 0> x;
			Ref1<__m128, float, 1> y;
			Ref1<__m128, float, 2> z;
			Ref1<__m128, float, 3> w;
			Ref2<__m128, float, 0, 0> xx;
		};
	}
}
