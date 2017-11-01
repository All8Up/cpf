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
			F64x4<double4, double, COUNT>::operator StorageType () const
			{
				return mSIMD;
			}

			template<int COUNT>
			F64x4<double4, double, COUNT>::operator const LaneType() const
			{
				return _mm_cvtsd_f64(mSIMD.mData[0]);
			}

			template<int COUNT>
			void F64x4<double4, double, COUNT>::SetLane(int index, double value)
			{
				switch (index)
				{
				case 0: mSIMD.mData[0] = _mm_set_pd(_mm_cvtsd_f64(_mm_unpackhi_pd(mSIMD.mData[0], mSIMD.mData[0])), value); break;
				case 1: mSIMD.mData[0] = _mm_set_pd(value, _mm_cvtsd_f64(_mm_unpacklo_pd(mSIMD.mData[0], mSIMD.mData[0]))); break;
				case 2: mSIMD.mData[1] = _mm_set_pd(_mm_cvtsd_f64(_mm_unpackhi_pd(mSIMD.mData[1], mSIMD.mData[1])), value); break;
				case 3: mSIMD.mData[1] = _mm_set_pd(value, _mm_cvtsd_f64(_mm_unpacklo_pd(mSIMD.mData[1], mSIMD.mData[1]))); break;
				}
			}

			template <int LANES_USED>
			template <int I0>
			typename F64x4<double4, double, LANES_USED>::LaneType F64x4<double4, double, LANES_USED>::GetLane() const
			{
				switch (I0)
				{
				case 0: return _mm_cvtsd_f64(mSIMD.mData[0]);
				case 1: return _mm_cvtsd_f64(_mm_unpackhi_pd(mSIMD.mData[0], mSIMD.mData[0]));
				case 2: return _mm_cvtsd_f64(mSIMD.mData[1]);
				case 3: return _mm_cvtsd_f64(_mm_unpackhi_pd(mSIMD.mData[1], mSIMD.mData[1]));
				}
				return 0.0;
			};

			// TODO: Lazy solution for the moment.  Need proper overloaded swizzles.
			template<int COUNT>
			template <int I0, int I1>
			typename F64x4<double4, double, COUNT>::Lanes_2 F64x4<double4, double, COUNT>::GetLanes() const
			{
				return F64x4<double4, double, COUNT>::Lanes_2(
					GetLane<I0>(), GetLane<I1>()
				);
			}

			template<int COUNT>
			template <int I0, int I1, int I2>
			typename F64x4<double4, double, COUNT>::Lanes_3 F64x4<double4, double, COUNT>::GetLanes() const
			{
				return F64x4<double4, double, COUNT>::Lanes_3(
					GetLane<I0>(), GetLane<I1>(), GetLane<I2>()
				);
			}

			template<int COUNT>
			template <int I0, int I1, int I2, int I3>
			typename F64x4<double4, double, COUNT>::Lanes_4 F64x4<double4, double, COUNT>::GetLanes() const
			{
				return F64x4<double4, double, COUNT>::Lanes_4(
					GetLane<I0>(), GetLane<I1>(), GetLane<I2>(), GetLane<I3>()
				);
			}
		}
	}
}
