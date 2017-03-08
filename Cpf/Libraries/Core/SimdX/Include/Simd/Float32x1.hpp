//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Simd/Float32x4_Ref1.hpp"

namespace Cpf
{
	namespace SIMD
	{
		struct Float32x1
		{
			///
			Float32x1(float value) { mData.mData = _mm_load1_ps(&value); }
			constexpr Float32x1(float32x1 value) : mData(value) {}

			///
			operator float() const { float result; _mm_store_ss(&result, mData.mData); return result; }
			constexpr operator float32x1() const { return mData; }

			///
			Float32x1& operator = (float value) { mData.mData = _mm_load1_ps(&value); }
			constexpr Float32x1& operator = (float32x1 value) { mData = value; return *this; }

			///
			float32x1 mData;
			Ref1<float32x1, float, 0> x;
		};
	}
}
