//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Utilities.hpp"

namespace CPF
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4()
			{}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType value)
				: mSIMD(_mm_set_ps(value, value, value, value))
			{}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, LaneType v1)
				: mSIMD(_mm_set_ps(0.0f, 0.0f, v1, v0))
			{}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, LaneType v1, LaneType v2)
				: mSIMD(_mm_set_ps(0.0f, v2, v1, v0))
			{}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3)
				: mSIMD(_mm_set_ps(v3, v2, v1, v0))
			{}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(Lanes_2 v01, LaneType v2)
				: mSIMD(Shuffle<0, 1, 0, 1>(
					v01.mSIMD,
					_mm_set_ps(v2, 0, 0, 0))
				)
			{
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, Lanes_2 v12)
				: mSIMD(_mm_set_ps(0, v12.GetLane<1>(), v12.GetLane<0>(), v0))
			{
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(Lanes_2 v01, LaneType v2, LaneType v3)
				: mSIMD(Shuffle<0, 1, 0, 1>(
					v01.mSIMD,
					_mm_set_ps(0, 0, v3, v2))
				)
			{
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, Lanes_2 v12, LaneType v3)
			{
				auto t = Shuffle<0, 1, 0, 1>(_mm_set_ps(0, 0, v3, v0), v12.mSIMD);
				mSIMD = Swizzle<0, 2, 3, 1>(t);
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, LaneType v1, Lanes_2 v23)
				: mSIMD(Shuffle<0, 1, 0, 1>(
					_mm_set_ps(0, 0, v1, v0),
					v23.mSIMD)
				)
			{
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(Lanes_2 v01, Lanes_2 v23)
				: mSIMD(Shuffle<0, 1, 0, 1>(
					v01.mSIMD,
					v23.mSIMD)
				)
			{
			}


			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(Lanes_3 v012, LaneType v3)
			{
				auto mask = _mm_set_epi32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
				auto t = _mm_and_si128(_mm_castps_si128(v012.mSIMD), mask);
				auto a = _mm_or_si128(t, _mm_set_epi32(*reinterpret_cast<int*>(&v3), 0, 0, 0));
				mSIMD = _mm_castsi128_ps(a);
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, Lanes_3 v123)
			{
				auto t = _mm_slli_si128(_mm_castps_si128(v123.mSIMD), 4);
				auto a = _mm_or_si128(t, _mm_set_epi32(0, 0, 0, *reinterpret_cast<int*>(&v0)));
				mSIMD = _mm_castsi128_ps(a);
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>& F32x4<__m128, float, COUNT>::operator = (StorageType value)
			{
				mSIMD = value;
				return *this;
			}
		}
	}
}
