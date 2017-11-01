//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL operator - (const F64x4_<COUNT> value)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_mul_pd(value.mSIMD.mData[0], _mm_set_pd(-1.0, -1.0)),
						_mm_mul_pd(value.mSIMD.mData[1], _mm_set_pd(-1.0, -1.0))
				});
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL operator + (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_add_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]),
						_mm_add_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1])
				});
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL operator - (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_sub_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]),
						_mm_sub_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1])
				});
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL operator * (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_mul_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]),
						_mm_mul_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1])
				});
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL operator / (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_div_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]),
						_mm_div_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1])
				});
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Min(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_min_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]),
						_mm_min_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1])
				});
			}

			template <int COUNT>
			inline F64x4_<1> CPF_VECTORCALL HMin(const F64x4_<COUNT> value);

			template <>
			inline F64x4_<1> CPF_VECTORCALL HMin(const F64x4_<2> value)
			{
				double4 result{
					_mm_min_sd(value.mSIMD.mData[0], _mm_unpackhi_pd(value.mSIMD.mData[0], value.mSIMD.mData[0])),
					_mm_set_pd(0.0, 0.0)
				};
				return F64x4_<1>(result);
			}

			template <>
			inline F64x4_<1> CPF_VECTORCALL HMin(const F64x4_<3> value)
			{
				double4 result{
					_mm_min_sd(value.mSIMD.mData[0], _mm_unpackhi_pd(value.mSIMD.mData[0], value.mSIMD.mData[0])),
					value.mSIMD.mData[1]
				};
				result.mData[0] = _mm_min_sd(result.mData[0], result.mData[1]);
				return F64x4_<1>(result);
			}

			template <>
			inline F64x4_<1> CPF_VECTORCALL HMin(const F64x4_<4> value)
			{
				double4 result{
					_mm_min_sd(value.mSIMD.mData[0], _mm_unpackhi_pd(value.mSIMD.mData[0], value.mSIMD.mData[0])),
					_mm_min_sd(value.mSIMD.mData[1], _mm_unpackhi_pd(value.mSIMD.mData[1], value.mSIMD.mData[1]))
				};
				result.mData[0] = _mm_min_sd(result.mData[0], result.mData[1]);
				return F64x4_<1>(result);
			}

			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Max(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return F64x4_<COUNT>(
					double4{
					_mm_max_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]),
					_mm_max_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1])
				});
			}

			template <int COUNT>
			inline F64x4_<1> CPF_VECTORCALL HMax(const F64x4_<COUNT> value);
			template <>
			inline F64x4_<1> CPF_VECTORCALL HMax(const F64x4_<2> value)
			{
				double4 result{
					_mm_max_sd(value.mSIMD.mData[0], _mm_unpackhi_pd(value.mSIMD.mData[0], value.mSIMD.mData[0])),
					_mm_set_pd(0.0, 0.0)
				};
				return F64x4_<1>(result);
			}
			template <>
			inline F64x4_<1> CPF_VECTORCALL HMax(const F64x4_<3> value)
			{
				double4 result{
					_mm_max_sd(value.mSIMD.mData[0], _mm_unpackhi_pd(value.mSIMD.mData[0], value.mSIMD.mData[0])),
					value.mSIMD.mData[1]
				};
				result.mData[0] = _mm_max_sd(result.mData[0], result.mData[1]);
				return F64x4_<1>(result);
			}
			template <>
			inline F64x4_<1> CPF_VECTORCALL HMax(const F64x4_<4> value)
			{
				double4 result{
					_mm_max_sd(value.mSIMD.mData[0], _mm_unpackhi_pd(value.mSIMD.mData[0], value.mSIMD.mData[0])),
					_mm_max_sd(value.mSIMD.mData[1], _mm_unpackhi_pd(value.mSIMD.mData[1], value.mSIMD.mData[1]))
				};
				result.mData[0] = _mm_max_sd(result.mData[0], result.mData[1]);
				return F64x4_<1>(result);
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Sqrt(const F64x4_<COUNT> value)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_sqrt_pd(value.mSIMD.mData[0]),
						_mm_sqrt_pd(value.mSIMD.mData[1])
				});
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Reciprocal(const F64x4_<COUNT> value)
			{
				return F64x4_<COUNT>(1.0) / value;
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL RSqrt(const F64x4_<COUNT> value)
			{
				return F64x4_<COUNT>(1.0) / Sqrt(value);
			}
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Clamp(const F64x4_<COUNT> value, typename F64x4_<COUNT>::LaneType low, typename F64x4_<COUNT>::LaneType high)
			{
				return Min(Max(value, F64x4_<COUNT>(low)), F64x4_<COUNT>(high));
			}

			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Cross(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs);
			template <>
			inline F64x4_<3> CPF_VECTORCALL Cross(const F64x4_<3> lhs, const F64x4_<3> rhs)
			{
				return F64x4_<3>(
					lhs.GetLane<1>() * rhs.GetLane<2>() - rhs.GetLane<1>() * lhs.GetLane<2>(),
					lhs.GetLane<2>() * rhs.GetLane<0>() - rhs.GetLane<2>() * lhs.GetLane<0>(),
					lhs.GetLane<0>() * rhs.GetLane<1>() - rhs.GetLane<0>() * lhs.GetLane<1>());
			}

			template <int COUNT>
			inline typename F64x4_<COUNT>::LaneType CPF_VECTORCALL Dot(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs);

			template <>
			inline typename F64x4_<2>::LaneType CPF_VECTORCALL Dot(const F64x4_<2> lhs, const F64x4_<2> rhs)
			{
				auto m0 = _mm_mul_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]);
				return _mm_cvtsd_f64(_mm_add_sd(m0, _mm_unpackhi_pd(m0, m0)));
			}
			template <>
			inline typename F64x4_<3>::LaneType CPF_VECTORCALL Dot(const F64x4_<3> lhs, const F64x4_<3> rhs)
			{
				auto m0 = _mm_mul_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]);
				auto m1 = _mm_mul_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1]);
				return _mm_cvtsd_f64(
					_mm_add_sd(
						_mm_add_sd(m0, _mm_unpackhi_pd(m0, m0)),
						m1));
			}
			template <>
			inline typename F64x4_<4>::LaneType CPF_VECTORCALL Dot(const F64x4_<4> lhs, const F64x4_<4> rhs)
			{
				auto m0 = _mm_mul_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]);
				auto m1 = _mm_mul_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1]);
				return _mm_cvtsd_f64(
					_mm_add_sd(
						_mm_add_sd(m0, _mm_unpackhi_pd(m0, m0)),
						_mm_add_sd(m1, _mm_unpackhi_pd(m1, m1))
					)
				);
			}

			template <int COUNT>
			inline typename F64x4_<COUNT>::LaneType CPF_VECTORCALL Magnitude(const F64x4_<COUNT> value);

			template <>
			inline typename F64x4_<2>::LaneType CPF_VECTORCALL Magnitude(const F64x4_<2> value)
			{
				auto sq0 = _mm_mul_pd(value.mSIMD.mData[0], value.mSIMD.mData[0]);
				auto part = _mm_add_sd(sq0, _mm_unpackhi_pd(sq0, sq0));
				return _mm_cvtsd_f64(_mm_sqrt_sd(part, part));
			}
			template <>
			inline typename F64x4_<3>::LaneType CPF_VECTORCALL Magnitude(const F64x4_<3> value)
			{
				auto sq0 = _mm_mul_pd(value.mSIMD.mData[0], value.mSIMD.mData[0]);
				auto sq1 = _mm_mul_sd(value.mSIMD.mData[1], value.mSIMD.mData[1]);
				auto part = _mm_add_sd(
					_mm_add_sd(sq0, _mm_unpackhi_pd(sq0, sq0)),
					sq1
				);
				return _mm_cvtsd_f64(_mm_sqrt_sd(part, part));
			}
			template <>
			inline typename F64x4_<4>::LaneType CPF_VECTORCALL Magnitude(const F64x4_<4> value)
			{
				auto sq0 = _mm_mul_pd(value.mSIMD.mData[0], value.mSIMD.mData[0]);
				auto sq1 = _mm_mul_sd(value.mSIMD.mData[1], value.mSIMD.mData[1]);
				auto part = _mm_add_sd(
					_mm_add_sd(sq0, _mm_unpackhi_pd(sq0, sq0)),
					_mm_add_sd(sq1, _mm_unpackhi_pd(sq1, sq1))
				);
				return _mm_cvtsd_f64(_mm_sqrt_sd(part, part));
			}

			template <int COUNT>
			inline typename F64x4_<COUNT>::LaneType CPF_VECTORCALL MagnitudeSq(const F64x4_<COUNT> value)
			{
				return Dot(value, value);
			}


			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Normalize(const F64x4_<COUNT> value);

			template <>
			inline F64x4_<2> CPF_VECTORCALL Normalize(const F64x4_<2> value)
			{
				auto sq = value * value;
				auto n = value / F64x4_<2>(Dot(value, value));
				return F64x4_<2>(n);
			}
			template <>
			inline F64x4_<3> CPF_VECTORCALL Normalize(const F64x4_<3> value)
			{
				auto sq = value * value;
				auto n = value / F64x4_<3>(Dot(value, value));
				return F64x4_<3>(n);
			}
			template <>
			inline F64x4_<4> CPF_VECTORCALL Normalize(const F64x4_<4> value)
			{
				auto sq = value * value;
				auto n = value / F64x4_<4>(Dot(value, value));
				return F64x4_<4>(n);
			}

#if 0
			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Round(const F64x4_<COUNT> value, Rounding mode)
			{
				switch (mode)
				{
				case Rounding::eCurrent: return F64x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_CUR_DIRECTION));
				case Rounding::eTruncate: return F64x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_TRUNC));
				case Rounding::eNearest: return F64x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_NEARBYINT));
				case Rounding::eDown: return F64x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_TO_NEG_INF));
				case Rounding::eUp: return F64x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_TO_POS_INF));
				}
				CPF_ASSERT_ALWAYS; // Improper mode given.
				return F64x4_<COUNT>(_mm_round_ps(static_cast<__m128>(value), _MM_FROUND_CUR_DIRECTION));
			}

			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Floor(const F64x4_<COUNT> value)
			{
				return F64x4_<COUNT>(_mm_floor_ps(static_cast<__m128>(value)));
			}

			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Ceil(const F64x4_<COUNT> value)
			{
				return F64x4_<COUNT>(_mm_ceil_ps(static_cast<__m128>(value)));
			}
#endif

			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Modulus(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				auto rmode = _MM_GET_ROUNDING_MODE();
				_MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);

				auto c_0 = _mm_div_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]);
				auto i_0 = _mm_cvtpd_epi32(c_0);
				auto p_0 = _mm_cvtepi32_pd(i_0);
				auto b_0 = _mm_mul_pd(p_0, rhs.mSIMD.mData[0]);
				auto r_0 = _mm_sub_pd(lhs.mSIMD.mData[0], b_0);

				auto c_1 = _mm_div_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1]);
				auto i_1 = _mm_cvtpd_epi32(c_1);
				auto p_1 = _mm_cvtepi32_pd(i_1);
				auto b_1 = _mm_mul_pd(p_1, rhs.mSIMD.mData[1]);
				auto r_1 = _mm_sub_pd(lhs.mSIMD.mData[1], b_1);

				_MM_SET_ROUNDING_MODE(rmode);
				return F64x4_<COUNT>(double4{r_0, r_1});
			}

			template <int COUNT>
			inline F64x4_<COUNT> CPF_VECTORCALL Abs(const F64x4_<COUNT> value)
			{
				return F64x4_<COUNT>(
					double4{
						_mm_andnot_pd(
							_mm_castsi128_pd(_mm_set_epi64x(0x8000000000000000, 0x8000000000000000)),
							value.mSIMD.mData[0]
						),
						_mm_andnot_pd(
							_mm_castsi128_pd(_mm_set_epi64x(0x8000000000000000, 0x8000000000000000)),
							value.mSIMD.mData[1]
						)
				});
			}

			inline bool CPF_VECTORCALL Near(const double lhs, const double rhs, double tolerance)
			{
				return std::abs(lhs - rhs) <= tolerance;
			}

			template <int COUNT>
			inline bool CPF_VECTORCALL Near(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs, double tolerance)
			{
				return All(Abs(lhs - rhs) <= F64x4_<COUNT>(tolerance));
			}

			template <int COUNT>
			inline bool CPF_VECTORCALL Valid(const F64x4_<COUNT> value)
			{
				double4 test
				{
					_mm_cmpeq_pd(_mm_mul_pd(value.mSIMD.mData[0], _mm_setzero_pd()), _mm_setzero_pd()),
					_mm_cmpeq_pd(_mm_mul_pd(value.mSIMD.mData[1], _mm_setzero_pd()), _mm_setzero_pd())
				};
				int mask = _mm_movemask_pd(test.mData[0]) | (_mm_movemask_pd(test.mData[1]) << 2);
				return(F64x4_<COUNT>::LaneMask == (mask & F64x4_<COUNT>::LaneMask));
			}
		}
	}
}
