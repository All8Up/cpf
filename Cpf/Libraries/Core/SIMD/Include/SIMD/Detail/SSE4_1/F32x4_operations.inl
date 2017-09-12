//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator - (const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_mul_ps(static_cast<__m128>(value), _mm_set_ps(-1.0f, -1.0f, -1.0f, -1.0f)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator + (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_add_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator - (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_sub_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator * (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_mul_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator / (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_div_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Min(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_min_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMin(const F32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMin(const F32x4_<2> value)
			{
				auto second = _mm_shuffle_ps(static_cast<__m128>(value), static_cast<__m128>(value), _MM_SHUFFLE(0, 0, 0, 1));
				auto the_low = _mm_min_ss(static_cast<__m128>(value), second);
				return F32x4_<1>(the_low);
			}

			template <>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMin(const F32x4_<3> value)
			{
				auto folded = _mm_movehl_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto two_low = _mm_min_ps(static_cast<__m128>(value), folded);
				auto second = _mm_shuffle_ps(static_cast<__m128>(value), static_cast<__m128>(value), _MM_SHUFFLE(0, 0, 0, 1));
				auto the_low = _mm_min_ss(two_low, second);
				return F32x4_<1>(the_low);
			}

			template <>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMin(const F32x4_<4> value)
			{
				auto folded = _mm_movehl_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto two_low = _mm_min_ps(static_cast<__m128>(value), folded);
				auto second = _mm_shuffle_ps(two_low, two_low, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_low = _mm_min_ss(two_low, second);
				return F32x4_<1>(the_low);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Max(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_max_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMax(const F32x4_<COUNT> value);
			template <>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMax(const F32x4_<2> value)
			{
				auto second = _mm_shuffle_ps(static_cast<__m128>(value), static_cast<__m128>(value), _MM_SHUFFLE(0, 0, 0, 1));
				auto the_low = _mm_max_ss(static_cast<__m128>(value), second);
				return F32x4_<1>(the_low);
			}
			template <>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMax(const F32x4_<3> value)
			{
				auto folded = _mm_movehl_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto two_high = _mm_max_ps(static_cast<__m128>(value), folded);
				auto second = _mm_shuffle_ps(folded, folded, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_high = _mm_max_ss(two_high, second);
				return F32x4_<1>(the_high);
			}
			template <>
			CPF_FORCE_INLINE F32x4_<1> CPF_VECTORCALL HMax(const F32x4_<4> value)
			{
				auto folded = _mm_movehl_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto two_high = _mm_max_ps(static_cast<__m128>(value), folded);
				auto second = _mm_shuffle_ps(two_high, two_high, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_high = _mm_max_ss(two_high, second);
				return F32x4_<1>(the_high);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Sqrt(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_sqrt_ps(static_cast<__m128>(value)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Reciprocal(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_rcp_ps(static_cast<__m128>(value)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL RSqrt(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_rsqrt_ps(static_cast<__m128>(value)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Clamp(const F32x4_<COUNT> value, typename F32x4_<COUNT>::LaneType low, typename F32x4_<COUNT>::LaneType high)
			{
				return F32x4_<COUNT>(
					_mm_min_ps(static_cast<__m128>(
						_mm_set_ps(high, high, high, high)),
						_mm_max_ps(_mm_set_ps(low, low, low, low), static_cast<__m128>(value))));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Cross(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs);
			template <>
			CPF_FORCE_INLINE F32x4_<3> CPF_VECTORCALL Cross(const F32x4_<3> lhs, const F32x4_<3> rhs)
			{
				static const int swizzle1 = _MM_SHUFFLE(3, 0, 2, 1);
				static const int swizzle2 = _MM_SHUFFLE(3, 1, 0, 2);

				__m128 v1 = _mm_shuffle_ps(static_cast<__m128>(lhs), static_cast<__m128>(lhs), swizzle1);
				__m128 v2 = _mm_shuffle_ps(static_cast<__m128>(rhs), static_cast<__m128>(rhs), swizzle2);
				__m128 v3 = _mm_shuffle_ps(static_cast<__m128>(lhs), static_cast<__m128>(lhs), swizzle2);
				__m128 v4 = _mm_shuffle_ps(static_cast<__m128>(rhs), static_cast<__m128>(rhs), swizzle1);

				__m128 p1 = _mm_mul_ps(v1, v2);
				__m128 p2 = _mm_mul_ps(v3, v4);

				__m128 result = _mm_sub_ps(p1, p2);
				return F32x4_<3>(result);
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::LaneType CPF_VECTORCALL Dot(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs);

			template <>
			CPF_FORCE_INLINE typename F32x4_<2>::LaneType CPF_VECTORCALL Dot(const F32x4_<2> lhs, const F32x4_<2> rhs)
			{
				__m128 dot = _mm_dp_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs),
					1 << 4 | 1 << 5 |
					1 << 0
				);
				return _mm_cvtss_f32(dot);
			}
			template <>
			CPF_FORCE_INLINE typename F32x4_<3>::LaneType CPF_VECTORCALL Dot(const F32x4_<3> lhs, const F32x4_<3> rhs)
			{
				__m128 dot = _mm_dp_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs),
					1<<4 | 1<<5 | 1<<6 |
					1<<0
					);
				return _mm_cvtss_f32(dot);
			}
			template <>
			CPF_FORCE_INLINE typename F32x4_<4>::LaneType CPF_VECTORCALL Dot(const F32x4_<4> lhs, const F32x4_<4> rhs)
			{
				__m128 dot = _mm_dp_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs),
					1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 |
					1 << 0
				);
				return _mm_cvtss_f32(dot);
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::LaneType CPF_VECTORCALL Magnitude(const F32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE typename F32x4_<2>::LaneType CPF_VECTORCALL Magnitude(const F32x4_<2> value)
			{
				return _mm_cvtss_f32(
					_mm_sqrt_ss(
						_mm_dp_ps(static_cast<__m128>(value), static_cast<__m128>(value),
							1 << 4 | 1 << 5 |
							1 << 0
						)));
			}
			template <>
			CPF_FORCE_INLINE typename F32x4_<3>::LaneType CPF_VECTORCALL Magnitude(const F32x4_<3> value)
			{
				return _mm_cvtss_f32(
					_mm_sqrt_ss(
						_mm_dp_ps(static_cast<__m128>(value), static_cast<__m128>(value),
							1 << 4 | 1 << 5 | 1 << 6 |
							1 << 0
						)));
			}
			template <>
			CPF_FORCE_INLINE typename F32x4_<4>::LaneType CPF_VECTORCALL Magnitude(const F32x4_<4> value)
			{
				return _mm_cvtss_f32(
					_mm_sqrt_ss(
						_mm_dp_ps(static_cast<__m128>(value), static_cast<__m128>(value),
							1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 |
							1 << 0
						)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::LaneType CPF_VECTORCALL MagnitudeSq(const F32x4_<COUNT> value)
			{
				return Dot(value, value);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Normalize(const F32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE F32x4_<2> CPF_VECTORCALL Normalize(const F32x4_<2> value)
			{
				auto len =
					_mm_sqrt_ps(
						_mm_dp_ps(static_cast<__m128>(value), static_cast<__m128>(value),
							1 << 4 | 1 << 5 |
							1 << 0 | 1 << 1
						));
				return F32x4_<2>(_mm_div_ps(static_cast<__m128>(value), len));
			}
			template <>
			CPF_FORCE_INLINE F32x4_<3> CPF_VECTORCALL Normalize(const F32x4_<3> value)
			{
				auto len =
					_mm_sqrt_ps(
						_mm_dp_ps(static_cast<__m128>(value), static_cast<__m128>(value),
							1 << 4 | 1 << 5 | 1 << 6 |
							1 << 0 | 1 << 1 | 1 << 2
						));
				return F32x4_<3>(_mm_div_ps(static_cast<__m128>(value), len));
			}
			template <>
			CPF_FORCE_INLINE F32x4_<4> CPF_VECTORCALL Normalize(const F32x4_<4> value)
			{
				auto len =
					_mm_sqrt_ps(
						_mm_dp_ps(static_cast<__m128>(value), static_cast<__m128>(value),
							1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 |
							1 << 0 | 1 << 1 | 1 << 2 | 1 << 3
						));
				return F32x4_<4>(_mm_div_ps(static_cast<__m128>(value), len));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Round(const F32x4_<COUNT> value, Rounding mode)
			{
				switch (mode)
				{
				case Rounding::eCurrent: return F32x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_CUR_DIRECTION));
				case Rounding::eTruncate: return F32x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_TRUNC));
				case Rounding::eNearest: return F32x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_NEARBYINT));
				case Rounding::eDown: return F32x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_TO_NEG_INF));
				case Rounding::eUp: return F32x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_TO_POS_INF));
				}
				CPF_ASSERT_ALWAYS; // Improper mode given.
				return F32x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_CUR_DIRECTION));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Floor(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_floor_ps(static_cast<__m128>(value)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Ceil(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_ceil_ps(static_cast<__m128>(value)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Modulus(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				__m128 c = _mm_div_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs));
				__m128i i = _mm_cvttps_epi32(c);
				__m128 ct = _mm_cvtepi32_ps(i);
				__m128 bs = _mm_mul_ps(ct, static_cast<__m128>(rhs));
				__m128 r = _mm_sub_ps(static_cast<__m128>(lhs), bs);
				return F32x4_<COUNT>(r);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Abs(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_andnot_ps(_mm_castsi128_ps(_mm_set_epi32(0x80000000, 0x80000000, 0x80000000, 0x80000000)), static_cast<__m128>(value)));
			}

			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const float lhs, const float rhs, float tolerance)
			{
				return std::fabs(lhs - rhs) <= tolerance;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs, float tolerance)
			{
				return All(Abs(lhs - rhs) <= F32x4_<COUNT>(tolerance));
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Valid(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> test(_mm_mul_ps(static_cast<__m128>(value), _mm_setzero_ps()));
				test = _mm_cmpeq_ps(static_cast<__m128>(test), _mm_setzero_ps());
				int mask = _mm_movemask_ps(static_cast<__m128>(test));
				return(F32x4_<COUNT>::LaneMask == (mask & F32x4_<COUNT>::LaneMask));
			}
		}
	}
}
