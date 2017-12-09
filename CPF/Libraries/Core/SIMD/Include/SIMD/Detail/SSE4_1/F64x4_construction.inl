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
					_mm_set_pd(v1, v0), _mm_set_pd(0.0, 0.0)					
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
					_mm_set_pd(v1, v0), _mm_set_pd(v3, v2)
				}
			{}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_2 v01, LaneType v2)
				: mSIMD{
					v01.mSIMD.mData[0], _mm_set_pd(0.0, v2)
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

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_2 v01, LaneType v2, LaneType v3)
				: mSIMD{
					v01.mSIMD.mData[0], _mm_set_pd(v3, v2),
				}
			{
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, Lanes_2 v12, LaneType v3)
				: mSIMD{
					_mm_set_pd(v12.GetLane<0>(), v0),
					_mm_set_pd(v3, v12.GetLane<1>())
				}
			{
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, LaneType v1, Lanes_2 v23)
				: mSIMD{
					_mm_set_pd(v1, v0),
					v23.mSIMD.mData[0]
				}
			{
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_2 v01, Lanes_2 v23)
				: mSIMD{
					v23.mSIMD.mData[0],
					v01.mSIMD.mData[0]
				}
			{
			}


			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(Lanes_3 v012, LaneType v3)
				: mSIMD{
					v012.mSIMD.mData[0],
					_mm_set_pd(v3, v012.GetLane<2>())
				}
			{
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::F64x4(LaneType v0, Lanes_3 v123)
				: mSIMD{
					_mm_set_pd(v123.GetLane<0>(), v0),
					_mm_set_pd(v123.GetLane<2>(), v123.GetLane<1>())
				}
			{
			}

#if 0
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
