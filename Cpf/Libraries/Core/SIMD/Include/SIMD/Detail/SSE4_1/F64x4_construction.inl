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
			F64x4<double4, double, COUNT>::F64x4()
			{}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType value)
				: mSIMD{value, value, value, value}
			{}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, LaneType v1)
				: mSIMD{
					_mm_set_pd(v1, v0),
					_mm_set_pd(0.0, 0.0)
				}
			{}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, LaneType v1, LaneType v2)
				: mSIMD{
					_mm_set_pd(v1, v0),
					_mm_set_pd(0.0, v2)
				}
			{}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3)
				: mSIMD{
					_mm_set_pd(v3, v2),
					_mm_set_pd(v1, v0)
				}
			{}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_2 v01, LaneType v2)
				: mSIMD{
					v01.mSIMD.mData[0],
					_mm_set_pd(v2, 0.0)
				}
			{
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, Lanes_2 v12)
				: mSIMD{
					_mm_set_pd(_mm_cvtsd_f64(v12.mSIMD.mData[0]), v0),
					_mm_set_pd(0.0, _mm_cvtsd_f64(_mm_unpackhi_pd(v12.mSIMD.mData[0], v12.mSIMD.mData[0])))
				}
			{
			}

#if 0
			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_2 v01, LaneType v2, LaneType v3)
				: mSIMD(Shuffle<0, 1, 0, 1>(
					static_cast<double4>(v01),
					_mm_set_ps(0, 0, v3, v2))
				)
			{
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, Lanes_2 v12, LaneType v3)
			{
				auto t = Shuffle<0, 1, 0, 1>(_mm_set_ps(0, 0, v3, v0), static_cast<double4>(v12));
				mSIMD = Swizzle<0, 2, 3, 1>(t);
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, LaneType v1, Lanes_2 v23)
				: mSIMD(Shuffle<0, 1, 0, 1>(
					_mm_set_ps(0, 0, v1, v0),
					static_cast<double4>(v23))
				)
			{
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_2 v01, Lanes_2 v23)
				: mSIMD(Shuffle<0, 1, 0, 1>(
					static_cast<double4>(v01),
					static_cast<double4>(v23))
				)
			{
			}


			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_3 v012, LaneType v3)
			{
				auto mask = _mm_set_epi32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
				auto t = _mm_and_si128(_mm_castps_si128(static_cast<double4>(v012)), mask);
				auto a = _mm_or_si128(t, _mm_set_epi32(*reinterpret_cast<int*>(&v3), 0, 0, 0));
				mSIMD = _mm_castsi128_ps(a);
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, Lanes_3 v123)
			{
				auto t = _mm_slli_si128(_mm_castps_si128(static_cast<double4>(v123)), 4);
				auto a = _mm_or_si128(t, _mm_set_epi32(0, 0, 0, *reinterpret_cast<int*>(&v0)));
				mSIMD = _mm_castsi128_ps(a);
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>& F64x4<double4, double, COUNT>::operator = (StorageType value)
			{
				mSIMD = value;
				return *this;
			}
#endif
		}
	}
}
