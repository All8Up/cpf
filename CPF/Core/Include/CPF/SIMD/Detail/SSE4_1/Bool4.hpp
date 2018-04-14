//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/SIMD/Rounding.hpp"
#include "Utilities.hpp"

namespace CPF
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			template <typename STORAGE_TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(16) Bool4;

			//////////////////////////////////////////////////////////////////////////
			template<int LANES_USED>
			struct alignas(16) Bool4<__m128i, bool, LANES_USED>
			{
				using StorageType = __m128i;
				using LaneType = bool;
				static constexpr int LaneCount = LANES_USED;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = Bool4<__m128i, bool, 1>;
				using Lanes_2 = Bool4<__m128i, bool, 2>;
				using Lanes_3 = Bool4<__m128i, bool, 3>;
				using Lanes_4 = Bool4<__m128i, bool, 4>;

				static constexpr int32_t True = 0xFFFFFFFF;
				static constexpr int32_t False = 0x00000000;

				static constexpr int32_t ToValue(bool flag) { return flag ? True : False; }

				constexpr Bool4() {}
				constexpr Bool4(LaneType value) : mVector(_mm_set_epi32(ToValue(value), ToValue(value), ToValue(value), ToValue(value))) {}
				constexpr Bool4(LaneType v0, LaneType v1) : mVector(_mm_set_epi32(0, 0, ToValue(v1), ToValue(v0))) {}
				constexpr Bool4(LaneType v0, LaneType v1, LaneType v2) : mVector(_mm_set_epi32(0, ToValue(v2), ToValue(v1), ToValue(v0))) {}
				constexpr Bool4(LaneType v0, LaneType v1, LaneType v2, LaneType v3) : mVector(_mm_set_epi32(ToValue(v3), ToValue(v2), ToValue(v1), ToValue(v0))) {}

				Bool4(Lanes_2 v01, LaneType v2)
					: mVector(
						Shuffle<1, 0, 1, 0>(
							static_cast<__m128i>(v01),
							_mm_set_epi32(ToValue(v2), 0, 0, 0))
					)
				{
				}
				Bool4(LaneType v0, Lanes_2 v12)
					: mVector(_mm_set_epi32(0, v12.GetLane<1>(), v12.GetLane<0>(), ToValue(v0)))
				{
				}

				Bool4(Lanes_2 v01, LaneType v2, LaneType v3)
					: mVector(
						Shuffle<1, 0, 1, 0>(
							static_cast<__m128i>(v01),
							_mm_set_epi32(0, 0, ToValue(v3), ToValue(v2)))
					)
				{
				}
				Bool4(LaneType v0, Lanes_2 v12, LaneType v3)
				{
					auto t = Shuffle<2, 3, -1, -1>(_mm_set_epi32(0, 0, ToValue(v3), ToValue(v0)), v12);
					mVector = Swizzle<1, 3, 2, -1>(t);
				}
				Bool4(LaneType v0, LaneType v1, Lanes_2 v23)
					: mVector(
						Shuffle<1, 0, 1, 0>(
							_mm_set_epi32(0, 0, ToValue(v1), ToValue(v0)),
							static_cast<__m128i>(v23))
					)
				{
				}
				Bool4(Lanes_2 v01, Lanes_2 v23)
					: mVector(
						Shuffle<0, 1, 0, 1>(
							static_cast<__m128i>(v01),
							static_cast<__m128i>(v23))
					)
				{
				}

				Bool4(Lanes_3 v012, LaneType v3)
				{
					auto mask = _mm_set_epi32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
					auto t = _mm_and_si128(static_cast<__m128i>(v012), mask);
					auto a = _mm_or_si128(t, _mm_set_epi32(*reinterpret_cast<int*>(&ToValue(v3)), 0, 0, 0));
					mVector = a;
				}
				Bool4(LaneType v0, Lanes_3 v123)
				{
					auto t = _mm_slli_si128(static_cast<__m128i>(v123), 4);
					auto a = _mm_or_si128(t, _mm_set_epi32(0, 0, 0, *reinterpret_cast<int*>(&ToValue(v0))));
					mVector = a;
				}
				explicit constexpr Bool4(StorageType value) : mVector(value) {}

				Bool4& operator = (StorageType value) { mVector = value; return *this; }

				explicit operator StorageType () const { return mVector; }

				template <typename = std::enable_if_t<LANES_USED == 1>>
				operator const LaneType() const
				{
					return _mm_cvtsi128_si32(mVector);
				}

				void SetLane(int index, LaneType value)
				{
					switch (index)
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

				int32_t ToMask() const
				{
					return _mm_movemask_ps(_mm_castsi128_ps(static_cast<__m128i>(mVector))) & LaneMask;
				}

				StorageType mVector;
			};

			template<int COUNT>
			using Bool4_ = Bool4<__m128i, bool, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int LANES_USED>
			template <int I0>
			typename Bool4<__m128i, bool, LANES_USED>::LaneType Bool4<__m128i, bool, LANES_USED>::GetLane() const
			{
				LaneType result;
				_MM_EXTRACT_FLOAT(*reinterpret_cast<float*>(&result), _mm_castsi128_ps(static_cast<__m128i>(mVector)), I0);
				return result;
			};

			template<int LANES_USED>
			template <int I0, int I1>
			typename Bool4<__m128i, bool, LANES_USED>::Lanes_2 Bool4<__m128i, bool, LANES_USED>::GetLanes() const
			{
				return Lanes_2(
					Swizzle<I0, I1, -1, -1>(mVector)
				);
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2>
			typename Bool4<__m128i, bool, LANES_USED>::Lanes_3 Bool4<__m128i, bool, LANES_USED>::GetLanes() const
			{
				return Lanes_3(
					Swizzle<I0, I1, I2, -1>(mVector)
				);
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2, int I3>
			typename Bool4<__m128i, bool, LANES_USED>::Lanes_4 Bool4<__m128i, bool, LANES_USED>::GetLanes() const
			{
				return Lanes_4(
					Swizzle<I0, I1, I2, I3>(mVector)
				);
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			inline bool CPF_VECTORCALL operator == (const Bool4_<COUNT> lhs, const Bool4_<COUNT> rhs)
			{
				auto cmp = _mm_cmpeq_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs));
				return Bool4_<COUNT>(cmp).ToMask() == Bool4_<COUNT>::LaneMask;
			}
			template <int COUNT>
			inline bool CPF_VECTORCALL operator != (const Bool4_<COUNT> lhs, const Bool4_<COUNT> rhs)
			{
				auto cmp = _mm_andnot_si128(
					_mm_cmpeq_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(lhs)),
					_mm_set_epi32(~0, ~0, ~0, ~0));
				return Bool4_<COUNT>(cmp).ToMask() == Bool4_<COUNT>::LaneMask;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			inline bool Any(const Bool4_<COUNT> value)
			{
				return (value.ToMask() & Bool4_<COUNT>::LaneMask) != 0;
			}

			template <int COUNT>
			inline bool All(const Bool4_<COUNT> value)
			{
				return value.ToMask() == Bool4_<COUNT>::LaneMask;
			}

			template <int COUNT>
			inline bool None(const Bool4_<COUNT> value)
			{
				return value.ToMask() == 0;
			}

			//////////////////////////////////////////////////////////////////////////
			using Bool4_1 = Bool4<__m128i, bool, 1>;
			using Bool4_2 = Bool4<__m128i, bool, 2>;
			using Bool4_3 = Bool4<__m128i, bool, 3>;
			using Bool4_4 = Bool4<__m128i, bool, 4>;
		}
	}
}
