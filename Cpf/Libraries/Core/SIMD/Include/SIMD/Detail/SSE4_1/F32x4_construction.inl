//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
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
				: mSIMD{ value, value, value, value }
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
				: mSIMD(_mm_shuffle_ps(static_cast<__m128>(v01),
					_mm_set_ps(v2, 0, 0, 0),
					_MM_SHUFFLE(1, 0, 1, 0))
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
				: mSIMD(_mm_shuffle_ps(
					static_cast<__m128>(v01),
					_mm_set_ps(0, 0, v3, v2),
					_MM_SHUFFLE(1, 0, 1, 0))
				)
			{
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, Lanes_2 v12, LaneType v3)
			{
				auto t = _mm_movelh_ps(_mm_set_ps(0, 0, v3, v0), static_cast<__m128>(v12));
				mSIMD = _mm_shuffle_ps(t, t, _MM_SHUFFLE(1, 3, 2, 0));
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, LaneType v1, Lanes_2 v23)
				: mSIMD(_mm_shuffle_ps(
					_mm_set_ps(0, 0, v1, v0),
					static_cast<__m128>(v23),
					_MM_SHUFFLE(1, 0, 1, 0))
				)
			{
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(Lanes_2 v01, Lanes_2 v23)
				: mSIMD(_mm_shuffle_ps(
					static_cast<__m128>(v01),
					static_cast<__m128>(v23),
					_MM_SHUFFLE(1, 0, 1, 0))
				)
			{
			}


			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(Lanes_3 v012, LaneType v3)
			{
				auto mask = _mm_set_epi32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
				auto t = _mm_and_si128(_mm_castps_si128(static_cast<__m128>(v012)), mask);
				auto a = _mm_or_si128(t, _mm_set_epi32(*reinterpret_cast<int*>(&v3), 0, 0, 0));
				mSIMD = _mm_castsi128_ps(a);
			}

			template<int COUNT>
			F32x4<__m128, float, COUNT>::F32x4(LaneType v0, Lanes_3 v123)
			{
				auto t = _mm_slli_si128(_mm_castps_si128(static_cast<__m128>(v123)), 4);
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
