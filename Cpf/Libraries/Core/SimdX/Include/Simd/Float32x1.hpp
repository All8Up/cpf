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
			Float32x1(float32x1 value) : mData(value) {}
			Float32x1(__m128 value) { mData.mData = value; }

			///
			operator float() const { float result; _mm_store_ss(&result, mData.mData); return result; }
			constexpr operator float32x1() const { return mData; }
			constexpr operator __m128() const { return mData.mData; }

			///
			Float32x1& operator = (float value) { mData.mData = _mm_load1_ps(&value); }
			constexpr Float32x1& operator = (const float32x1 value) { mData = value; return *this; }

			///
			float32x1 operator + (const Float32x1 rhs) const { return _mm_add_ss(mData.mData, rhs); }
			float32x1 operator - (const Float32x1 rhs) const { return _mm_sub_ss(mData.mData, rhs); }
			float32x1 operator * (const Float32x1 rhs) const { return _mm_mul_ss(mData.mData, rhs); }
			float32x1 operator / (const Float32x1 rhs) const { return _mm_div_ss(mData.mData, rhs); }

			///
			float32x1 operator == (const Float32x1 rhs) const { return _mm_cmpeq_ss(mData.mData, rhs); }
			float32x1 operator != (const Float32x1 rhs) const { return _mm_cmpneq_ss(mData.mData, rhs); }
			float32x1 operator < (const Float32x1 rhs) const { return _mm_cmplt_ss(mData.mData, rhs); }
			float32x1 operator <= (const Float32x1 rhs) const { return _mm_cmple_ss(mData.mData, rhs); }
			float32x1 operator > (const Float32x1 rhs) const { return _mm_cmpgt_ss(mData.mData, rhs); }
			float32x1 operator >= (const Float32x1 rhs) const { return _mm_cmpge_ss(mData.mData, rhs); }

			///
			float32x1 mData;
			Ref1<float32x1, float, 0> x;
		};

		inline float32x1 Min(const Float32x1 lhs, const Float32x1 rhs)
		{
			return _mm_min_ss(lhs, rhs);
		}
		inline float32x1 Max(const Float32x1 lhs, const Float32x1 rhs)
		{
			return _mm_max_ss(lhs, rhs);
		}
		inline float32x1 Sqrt(const Float32x1 value)
		{
			return _mm_sqrt_ss(value);
		}
		inline float32x1 Reciprocal(const Float32x1 value)
		{
			return _mm_rcp_ss(value);
		}
		inline float32x1 RecipSqrt(const Float32x1 value)
		{
			return _mm_rsqrt_ss(value);
		}
		inline float32x1 Clamp(const Float32x1 value, const Float32x1 low, const Float32x1 high)
		{
			return Min(high, Max(low, value));
		}
	}
}
