//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			template<int COUNT>
			F32x4<__m128, float, COUNT>::operator StorageType () const
			{
				return mSIMD;
			}

			template<int COUNT> // template <typename>
			F32x4<__m128, float, COUNT>::operator const LaneType() const
			{
				return _mm_cvtss_f32(mSIMD);
			}

			template<int COUNT>
			void F32x4<__m128, float, COUNT>::SetLane(int index, float value)
			{
				switch (index)
				{
				case 0: mSIMD = _mm_insert_ps(static_cast<__m128>(mSIMD), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 0, 0)); break;
				case 1: mSIMD = _mm_insert_ps(static_cast<__m128>(mSIMD), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 1, 0)); break;
				case 2: mSIMD = _mm_insert_ps(static_cast<__m128>(mSIMD), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 2, 0)); break;
				case 3: mSIMD = _mm_insert_ps(static_cast<__m128>(mSIMD), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 3, 0)); break;
				}
			}

			template <int LANES_USED>
			template <int I0>
			typename F32x4<__m128, float, LANES_USED>::LaneType F32x4<__m128, float, LANES_USED>::GetLane() const
			{
				LaneType result;
				_MM_EXTRACT_FLOAT(result, static_cast<__m128>(mSIMD), I0);
				return result;
			};

			template<int COUNT>
			template <int I0, int I1>
			typename F32x4<__m128, float, COUNT>::Lanes_2 F32x4<__m128, float, COUNT>::GetLanes() const
			{
				return _mm_shuffle_ps(
					static_cast<__m128>(mSIMD),
					static_cast<__m128>(mSIMD),
					_MM_SHUFFLE(0, 0, I1, I0));
			}

			template<int COUNT>
			template <int I0, int I1, int I2>
			typename F32x4<__m128, float, COUNT>::Lanes_3 F32x4<__m128, float, COUNT>::GetLanes() const
			{
				return _mm_shuffle_ps(
					static_cast<__m128>(mSIMD),
					static_cast<__m128>(mSIMD),
					_MM_SHUFFLE(0, I2, I1, I0));
			}

			template<int COUNT>
			template <int I0, int I1, int I2, int I3>
			typename F32x4<__m128, float, COUNT>::Lanes_4 F32x4<__m128, float, COUNT>::GetLanes() const
			{
				return _mm_shuffle_ps(
					static_cast<__m128>(mSIMD),
					static_cast<__m128>(mSIMD),
					_MM_SHUFFLE(I3, I2, I1, I0));
			}
		}
	}
}
