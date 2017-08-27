//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			//////////////////////////////////////////////////////////////////////////
			// Intermediate mask representation to allow specializations with optimized
			// behaviors.
			template <int I0, int I1, int I2, int I3>
			struct SwizzleMask
			{
				static constexpr int Mask = _MM_SHUFFLE(
					I3 > 0 ? I3 : 0,
					I2 > 0 ? I2 : 0,
					I1 > 0 ? I1 : 0,
					I0 > 0 ? I0 : 0
				);
			};

			//////////////////////////////////////////////////////////////////////////
			// Helper template that implements Intel styled shuffles in a manner that
			// allows specialized optimizations where appropriate.
			// Use -1 as a lane index to indicate you don't care about it.
			template <typename TYPE, int I0, int I1, int I2, int I3>
			TYPE Shuffle(TYPE lhs, TYPE rhs);

			// __m128 specialization.
			template <int I0, int I1, int I2, int I3>
			__m128 Shuffle(__m128 lhs, __m128 rhs)
			{
				return ShuffleHelper(lhs, rhs, SwizzleMask<I0, I1, I2, I3>());
			}

			// __m128i specialization.
			template <int I0, int I1, int I2, int I3>
			__m128i Shuffle(__m128i lhs, __m128i rhs)
			{
				return _mm_castps_si128(
					ShuffleHelper(
						_mm_castsi128_ps(lhs),
						_mm_castsi128_ps(rhs),
						SwizzleMask<I0, I1, I2, I3>())
				);
			}

			//////////////////////////////////////////////////////////////////////////
			// Helper template to implement optimized swizzles.
			// Use -1 as a lane index to indicate you don't care about it.
			template <typename TYPE, int I0, int I1, int I2, int I3>
			TYPE Swizzle(TYPE value);

			// __m128 specialization.
			template <int I0, int I1, int I2, int I3>
			__m128 Swizzle(__m128 value)
			{
				return SwizzleHelper(value, SwizzleMask<I0, I1, I2, I3>());
			}

			// __m128i specialization.
			template <int I0, int I1, int I2, int I3>
			__m128i Swizzle(__m128i value)
			{
				return _mm_castps_si128(
					SwizzleHelper(_mm_castsi128_ps(value), SwizzleMask<I0, I1, I2, I3>()));
			}

			//////////////////////////////////////////////////////////////////////////
			// Helper which can be specialized.  NOTE: Only accepts __m128 types.
			template <typename MASK>
			__m128 ShuffleHelper(__m128 lhs, __m128 rhs, MASK)
			{
				return _mm_shuffle_ps(lhs, rhs, MASK::Mask);
			}

			// Optimized shuffle patterns.

			// Copy lanes 0, 1 from lhs to result and insert lanes 0, 1 of rhs into lanes 2, 3 of result.
			template <>
			inline __m128 ShuffleHelper(__m128 lhs, __m128 rhs, SwizzleMask<0, 1, 0, 1>())
			{
				return _mm_movelh_ps(lhs, rhs);
			}

			// Helper which can be specialized.  NOTE: Only accepts __m128 types.
			template <typename MASK>
			__m128 SwizzleHelper(__m128 value, MASK)
			{
				return _mm_shuffle_ps(value, value, MASK::Mask);
			}

			// Optimized swizzle patterns.
			// NOTE: Do not rely on the unspecified lanes to maintain current behavior,
			// future optimizations could change the results in the ignored lanes.
			// Copy lanes 0 and 1 through without modification.
			template <>
			inline __m128 SwizzleHelper(__m128 value, SwizzleMask<0, 1, -1, -1>)
			{
				return value;
			}
			// Move lanes 2 and 3 into lanes 0 and 1.
			template <>
			inline __m128 SwizzleHelper(__m128 value, SwizzleMask<2, 3, -1, -1>)
			{
				return _mm_movehl_ps(value, value);
			}

			// Copy lanes 0, 1 and 2 through without modification.
			template <>
			inline __m128 SwizzleHelper(__m128 value, SwizzleMask<0, 1, 2, -1>)
			{
				return value;
			}

			// Copy all 4 lanes without modification.
			template <>
			inline __m128 SwizzleHelper(__m128 value, SwizzleMask<0, 1, 2, 3>)
			{
				return value;
			}
		}
	}
}
