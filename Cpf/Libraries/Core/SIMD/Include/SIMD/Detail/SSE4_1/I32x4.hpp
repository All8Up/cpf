//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "Utilities.hpp"
#include <immintrin.h>

namespace Cpf
{
	namespace SIMD
	{
		namespace SSE4_1
		{
#define cpf_movehl_epi32(lhs, rhs) _mm_castps_si128(_mm_movehl_ps(_mm_castsi128_ps(static_cast<__m128i>(lhs)), _mm_castsi128_ps(static_cast<__m128i>(rhs))))
#define cpf_movelh_epi32(lhs, rhs) _mm_castps_si128(_mm_movelh_ps(_mm_castsi128_ps(static_cast<__m128i>(lhs)), _mm_castsi128_ps(static_cast<__m128i>(rhs))))

			union alignas(16) UInt32x4
			{
				uint32_t UInt32[4];
				__m128i mVector;
			};


			template <typename STORAGE_TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(16)I32x4;

			//////////////////////////////////////////////////////////////////////////
			template<int LANES_USED>
			struct alignas(16) I32x4<__m128i, int32_t, LANES_USED>
			{
				using BoolType = Bool4_<LANES_USED>;
				using StorageType = __m128i;
				using LaneType = int32_t;
				static constexpr int LaneCount = LANES_USED;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = I32x4<__m128i, int32_t, 1>;
				using Lanes_2 = I32x4<__m128i, int32_t, 2>;
				using Lanes_3 = I32x4<__m128i, int32_t, 3>;
				using Lanes_4 = I32x4<__m128i, int32_t, 4>;

				constexpr I32x4() {}
				constexpr I32x4(LaneType value) : mVector(_mm_set_epi32(value, value, value, value)) {}
				constexpr I32x4(LaneType v0, LaneType v1) : mVector(_mm_set_epi32(0, 0, v1, v0)) {}
				constexpr I32x4(LaneType v0, LaneType v1, LaneType v2) : mVector(_mm_set_epi32(0, v2, v1, v0)) {}
				constexpr I32x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3) : mVector(_mm_set_epi32(v3, v2, v1, v0)) {}

				I32x4(Lanes_2 v01, LaneType v2)
					: mVector(Shuffle<0, 1, 0, 1>(
						static_cast<__m128i>(v01),
						_mm_set_epi32(v2, 0, 0, 0))
					)
				{
				}
				I32x4(LaneType v0, Lanes_2 v12)
					: mVector(_mm_set_epi32(0, v12.GetLane<1>(), v12.GetLane<0>(), v0))
				{
				}

				I32x4(Lanes_2 v01, LaneType v2, LaneType v3)
					: mVector(Shuffle<0, 1, 0, 1>(
						static_cast<__m128i>(v01),
						_mm_set_epi32(0, 0, v3, v2))
					)
				{
				}
				I32x4(LaneType v0, Lanes_2 v12, LaneType v3)
				{
					const auto t = Shuffle<0, 1, 0, 1>(
						static_cast<__m128i>(v12),
						_mm_set_epi32(0, 0, v0, v3)
						);
					mVector = Swizzle<3, 0, 1, 2>(t);
				}
				I32x4(LaneType v0, LaneType v1, Lanes_2 v23)
					: mVector(
						Shuffle<0, 1, 0, 1>(_mm_set_epi32(0, 0, v1, v0), static_cast<__m128i>(v23))
					)
				{
				}
				I32x4(Lanes_2 v01, I32x4<StorageType, LaneType, 2> v23)
					: mVector(
						Shuffle<0, 1, 0, 1>(static_cast<__m128i>(v01), static_cast<__m128i>(v23))
					)
				{
				}

				I32x4(Lanes_3 v012, LaneType v3)
				{
					auto mask = _mm_set_epi32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
					auto t = _mm_and_si128(static_cast<__m128i>(v012), mask);
					auto a = _mm_or_si128(t, _mm_set_epi32(*reinterpret_cast<int*>(&v3), 0, 0, 0));
					mVector = a;
				}
				I32x4(LaneType v0, Lanes_3 v123)
				{
					auto t = _mm_slli_si128(static_cast<__m128i>(v123), 4);
					auto a = _mm_or_si128(t, _mm_set_epi32(0, 0, 0, *reinterpret_cast<int*>(&v0)));
					mVector = a;
				}
				explicit constexpr I32x4(StorageType value) : mVector(value) {}

				I32x4& operator = (StorageType value) { mVector = value; return *this; }

				explicit operator StorageType () const { return mVector; }

				operator const LaneType() const
				{
					return _mm_cvtsi128_si32(mVector);
				}

				void SetLane(int index, int32_t value)
				{
					switch(index)
					{
					case 0: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 0); break;
					case 1: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 1); break;
					case 2: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 2); break;
					case 3: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 3); break;
					}
				}
				
				template <int I0> LaneType GetLane() const;
				template <int I0, int I1> Lanes_2 GetLanes() const;
				template <int I0, int I1, int I2> Lanes_3 GetLanes() const;
				template <int I0, int I1, int I2, int I3> Lanes_4 GetLanes() const;

				StorageType mVector;
			};

			template<int COUNT>
			using I32x4_ = I32x4<__m128i, int32_t, COUNT>;
			
			//////////////////////////////////////////////////////////////////////////
			template <int LANES_USED>
			template <int I0>
			typename I32x4<__m128i, int32_t, LANES_USED>::LaneType I32x4<__m128i, int32_t, LANES_USED>::GetLane() const
			{
				LaneType result;
				_MM_EXTRACT_FLOAT(*reinterpret_cast<float*>(&result), _mm_castsi128_ps(static_cast<__m128i>(mVector)), I0);
				return result;
			};
			
			template<int LANES_USED>
			template <int I0, int I1>
			typename I32x4<__m128i, int32_t, LANES_USED>::Lanes_2 I32x4<__m128i, int32_t, LANES_USED>::GetLanes() const
			{
				return Lanes_2(Swizzle<I0, I1, -1, -1>(static_cast<__m128i>(mVector)));
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2>
			typename I32x4<__m128i, int32_t, LANES_USED>::Lanes_3 I32x4<__m128i, int32_t, LANES_USED>::GetLanes() const
			{
				return Lanes_3(Swizzle<I0, I1, I2, -1>(static_cast<__m128i>(mVector)));
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2, int I3>
			typename I32x4<__m128i, int32_t, LANES_USED>::Lanes_4 I32x4<__m128i, int32_t, LANES_USED>::GetLanes() const
			{
				return Lanes_4(Swizzle<I0, I1, I2, I3>(static_cast<__m128i>(mVector)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator == (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto cmp = _mm_cmpeq_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs));
				return Bool4_<COUNT>(cmp);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator != (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto cmp = _mm_andnot_si128(
					_mm_cmpeq_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)),
					_mm_set_epi32(~0, ~0, ~0, ~0));
				return Bool4_<COUNT>(cmp);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator < (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_cmplt_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator <= (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto cmp = _mm_andnot_si128(
					_mm_cmpgt_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)),
					_mm_set_epi32(~0, ~0, ~0, ~0));
				return Bool4_<COUNT>(cmp);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator > (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_cmpgt_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator >= (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto cmp = _mm_andnot_si128(
					_mm_cmplt_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)),
					_mm_set_epi32(~0, ~0, ~0, ~0));
				return Bool4_<COUNT>(cmp);
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator - (const I32x4_<COUNT> value)
			{
				auto l = _mm_cvtepi32_ps(static_cast<__m128i>(value));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_mul_ps(l, _mm_set_ps(-1.0f, -1.0f, -1.0f, -1.0f))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator + (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_add_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator - (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_sub_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator * (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto l = _mm_cvtepi32_ps(static_cast<__m128i>(lhs));
				auto r = _mm_cvtepi32_ps(static_cast<__m128i>(rhs));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_mul_ps(l, r)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator / (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto l = _mm_cvtepi32_ps(static_cast<__m128i>(lhs));
				auto r = _mm_cvtepi32_ps(static_cast<__m128i>(rhs));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_div_ps(l, r)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Min(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_min_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<2> value)
			{
				auto second = _mm_castps_si128(
					_mm_shuffle_ps(
						_mm_castsi128_ps(static_cast<__m128i>(value)),
						_mm_castsi128_ps(static_cast<__m128i>(value)), _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_low = _mm_min_epi32(static_cast<__m128i>(value), second);
				return I32x4_<1>(the_low);
			}
			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<3> value)
			{
				auto folded = _mm_castps_si128(_mm_movehl_ps(
					_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value))));
				auto two_low = _mm_castsi128_ps(_mm_min_epi32(static_cast<__m128i>(value), folded));
				auto second = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value)), _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_low = _mm_min_epi32(_mm_castps_si128(two_low), second);
				return I32x4_<1>(the_low);
			}
			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<4> value)
			{
				auto folded = _mm_castps_si128(_mm_movehl_ps(
					_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value))));
				auto two_low = _mm_castsi128_ps(_mm_min_epi32(static_cast<__m128i>(value), folded));
				auto second = _mm_castps_si128(_mm_shuffle_ps(two_low, two_low, _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_low = _mm_min_epi32(_mm_castps_si128(two_low), second);
				return I32x4_<1>(the_low);
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Max(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_max_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<2> value)
			{
				auto second = _mm_castps_si128(
					_mm_shuffle_ps(
						_mm_castsi128_ps(static_cast<__m128i>(value)),
						_mm_castsi128_ps(static_cast<__m128i>(value)), _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_high = _mm_max_epi32(static_cast<__m128i>(value), second);
				return I32x4_<1>(the_high);
			}
			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<3> value)
			{
				auto folded = _mm_movehl_ps(_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value)));
				auto two_high = _mm_max_epi32(static_cast<__m128i>(value), _mm_castps_si128(folded));
				auto second = _mm_shuffle_ps(folded, folded, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_high = _mm_max_epi32(two_high, _mm_castps_si128(second));
				return I32x4_<1>(the_high);
			}

			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<4> value)
			{
				auto folded = cpf_movehl_epi32(static_cast<__m128i>(value), static_cast<__m128i>(value));
				auto two_low = _mm_max_epi32(static_cast<__m128i>(value), folded);
				auto second = Swizzle<1, -1, -1, -1>(two_low);
				auto the_high = _mm_max_epi32(two_low, second);
				return I32x4_<1>(the_high);
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Sqrt(const I32x4_<COUNT> value)
			{
				auto v = _mm_cvtepi32_ps(static_cast<__m128i>(value));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_sqrt_ps(v)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Clamp(
				const I32x4_<COUNT> value, typename I32x4_<COUNT>::LaneType low, typename I32x4_<COUNT>::LaneType high)
			{
				return I32x4_<COUNT>(
					_mm_min_epi32(_mm_set_epi32(high, high, high, high),
						_mm_max_epi32(_mm_set_epi32(low, low, low, low), static_cast<__m128i>(value))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Modulus(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result = lhs / rhs;
				result = result * rhs;
				result = lhs - result;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Abs(const I32x4_<COUNT> value)
			{
				static constexpr UInt32x4 kSignBits = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
				return I32x4_<COUNT>(_mm_andnot_si128(kSignBits.mVector, static_cast<__m128i>(value)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs, int32_t tolerance)
			{
				return All(Abs(lhs - rhs) <= I32x4_<COUNT>(tolerance));
			}

			//////////////////////////////////////////////////////////////////////////
			using I32x4_1 = I32x4<__m128i, int32_t, 1>;
			using I32x4_2 = I32x4<__m128i, int32_t, 2>;
			using I32x4_3 = I32x4<__m128i, int32_t, 3>;
			using I32x4_4 = I32x4<__m128i, int32_t, 4>;
		}
	}
}
