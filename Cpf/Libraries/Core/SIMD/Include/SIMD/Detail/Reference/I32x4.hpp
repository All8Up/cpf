//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"

namespace Cpf
{
	namespace SIMD
	{
		namespace Reference
		{
			struct int32x4
			{
				using Type = int32_t;
				static constexpr int Alignment = 16;
				static constexpr int LaneCount = 4;

				int32x4() {}
				constexpr int32x4(int32_t v0) : mData{ v0, v0, v0, v0 } {}
				constexpr int32x4(int32_t v0, int32_t v1) : mData{ v0, v1, v0, v0 } {}
				constexpr int32x4(int32_t v0, int32_t v1, int32_t v2) : mData{ v0, v1, v2, v0 } {}
				constexpr int32x4(int32_t v0, int32_t v1, int32_t v2, int32_t v3) : mData{ v0, v1, v2, v3 } {}

				int32_t mData[4];
			};

			//////////////////////////////////////////////////////////////////////////
			template <typename STORAGE, typename LANE_TYPE, int LANES_USED>
			struct alignas(16) I32x4;

			//////////////////////////////////////////////////////////////////////////
			template<int LANES_USED>
			struct alignas(16) I32x4<int32x4, int32_t, LANES_USED>
			{
				using BoolType = Bool4_<LANES_USED>;

				using StorageType = int32x4;
				using LaneType = typename StorageType::Type;
				static constexpr int LaneCount = LANES_USED;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = I32x4<int32x4, int32_t, 1>;
				using Lanes_2 = I32x4<int32x4, int32_t, 2>;
				using Lanes_3 = I32x4<int32x4, int32_t, 3>;
				using Lanes_4 = I32x4<int32x4, int32_t, 4>;

				I32x4() {}
				I32x4(LaneType value) : mSIMD{ value, value, value, value } {}
				I32x4(LaneType v0, LaneType v1) : mSIMD(v0, v1) {}
				I32x4(LaneType v0, LaneType v1, LaneType v2) : mSIMD(v0, v1, v2) {}
				I32x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3) : mSIMD(v0, v1, v2, v3) {}

				I32x4(Lanes_2 v01, LaneType v2)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v2)
				{
				}
				I32x4(LaneType v0, Lanes_2 v12)
					: mSIMD(v0, v12.mSIMD.mData[0], v12.mSIMD.mData[1])
				{
				}

				I32x4(I32x4<StorageType, int32_t, 2> v01, LaneType v2, LaneType v3)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v2, v3)
				{
				}
				I32x4(int32_t v0, I32x4<StorageType, int32_t, 2> v12, LaneType v3)
					: mSIMD(v0, v12.mSIMD.mData[0], v12.mSIMD.mData[1], v3)
				{
				}
				I32x4(int32_t v0, int32_t v1, I32x4<StorageType, int32_t, 2> v23)
					: mSIMD(v0, v1, v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}
				I32x4(I32x4<StorageType, int32_t, 2> v01, I32x4<StorageType, int32_t, 2> v23)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}

				I32x4(I32x4<StorageType, int32_t, 3> v012, LaneType v3)
					: mSIMD(v012.mSIMD.mData[0], v012.mSIMD.mData[1], v012.mSIMD.mData[2], v3)
				{
				}
				I32x4(LaneType v0, I32x4<StorageType, int32_t, 3> v123)
					: mSIMD(v0, v123.mSIMD.mData[0], v123.mSIMD.mData[1], v123.mSIMD.mData[2])
				{
				}

				I32x4& operator = (int32x4 value) { mSIMD = value; return *this; }

				explicit operator StorageType () const { return mSIMD; }

				template <typename = typename std::enable_if<(LANES_USED == 1), LaneType>::type>
				operator const LaneType() const { return mSIMD.mData[0]; }

				void SetLane(int index, int32_t value)
				{
					mSIMD.mData[index] = value;
				}
				template <int I0> LaneType GetLane() const;
				template <int I0, int I1> Lanes_2 GetLanes() const;
				template <int I0, int I1, int I2> Lanes_3 GetLanes() const;
				template <int I0, int I1, int I2, int I3> Lanes_4 GetLanes() const;

				StorageType mSIMD;
			};

			template<int COUNT>
			using I32x4_ = I32x4<int32x4, int32_t, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int LANES_USED>
			template <int I0>
			typename I32x4<int32x4, int32_t, LANES_USED>::LaneType I32x4<int32x4, int32_t, LANES_USED>::GetLane() const
			{
				return mSIMD.mData[I0];
			};

			template<int LANES_USED>
			template <int I0, int I1>
			typename I32x4<int32x4, int32_t, LANES_USED>::Lanes_2 I32x4<int32x4, int32_t, LANES_USED>::GetLanes() const
			{
				return Lanes_2{ mSIMD.mData[I0], mSIMD.mData[I1] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2>
			typename I32x4<int32x4, int32_t, LANES_USED>::Lanes_3 I32x4<int32x4, int32_t, LANES_USED>::GetLanes() const
			{
				return Lanes_3{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2, int I3>
			typename I32x4<int32x4, int32_t, LANES_USED>::Lanes_4 I32x4<int32x4, int32_t, LANES_USED>::GetLanes() const
			{
				return Lanes_4{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2], mSIMD.mData[I3] };
			}

			//////////////////////////////////////////////////////////////////////////

			template <int COUNT>
			CPF_FORCE_INLINE typename I32x4_<COUNT>::BoolType operator == (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				typename I32x4_<COUNT>::BoolType result(false);
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] == rhs.mSIMD.mData[i])
						result.SetLane(i, true);
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename I32x4_<COUNT>::BoolType operator != (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				typename I32x4_<COUNT>::BoolType result(false);
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] != rhs.mSIMD.mData[i])
						result.SetLane(i, true);
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename I32x4_<COUNT>::BoolType operator < (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				typename I32x4_<COUNT>::BoolType result(false);
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] < rhs.mSIMD.mData[i])
						result.SetLane(i, true);
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename I32x4_<COUNT>::BoolType operator <= (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				typename I32x4_<COUNT>::BoolType result(false);
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] <= rhs.mSIMD.mData[i])
						result.SetLane(i, true);
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename I32x4_<COUNT>::BoolType operator > (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				typename I32x4_<COUNT>::BoolType result(false);
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] > rhs.mSIMD.mData[i])
						result.SetLane(i, true);
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename I32x4_<COUNT>::BoolType operator >= (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				typename I32x4_<COUNT>::BoolType result(false);
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] >= rhs.mSIMD.mData[i])
						result.SetLane(i, true);
				}
				return result;
			}

			//////////////////////////////////////////////////////////////////////////

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> operator - (const I32x4_<COUNT> value)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = -value.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> operator + (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] + rhs.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> operator - (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] - rhs.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> operator * (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] * rhs.mSIMD.mData[i];
				return result;
			}
			
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> operator * (const I32x4_<COUNT> lhs, typename I32x4_<COUNT>::LaneType rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] * rhs;
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> operator / (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] / rhs.mSIMD.mData[i];
				return result;
			}
			
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> operator / (const I32x4_<COUNT> lhs, typename I32x4_<COUNT>::LaneType rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] / rhs;
				return result;
			}

			//////////////////////////////////////////////////////////////////////////

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> Min(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] <= rhs.mSIMD.mData[i] ? lhs.mSIMD.mData[i] : rhs.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<1> HMin(const I32x4_<COUNT> value)
			{
				int32_t result = value.mSIMD.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result <= value.mSIMD.mData[i] ? result : value.mSIMD.mData[i];
				return I32x4_<1>(result);
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> Max(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] >= rhs.mSIMD.mData[i] ? lhs.mSIMD.mData[i] : rhs.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<1> HMax(const I32x4_<COUNT> value)
			{
				int32_t result = value.mSIMD.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result >= value.mSIMD.mData[i] ? result : value.mSIMD.mData[i];
				return I32x4_<1>(result);
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> Sqrt(const I32x4_<COUNT> value)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = int32_t(std::sqrt(value.mSIMD.mData[i]));
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> Clamp(const I32x4_<COUNT> value, typename I32x4_<COUNT>::LaneType l, typename I32x4_<COUNT>::LaneType h)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
				{
					result.mSIMD.mData[i] = value.mSIMD.mData[i] <= l ? l : value.mSIMD.mData[i] >= h ? h : value.mSIMD.mData[i];
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> Modulus(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
				{
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] % rhs.mSIMD.mData[i];
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> Abs(const I32x4_<COUNT> value)
			{
				I32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = value.mSIMD.mData[i] >= 0 ? value.mSIMD.mData[i] : -value.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Near(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs, int32_t tolerance)
			{
				return All(Abs(lhs - rhs) <= I32x4_<COUNT>(tolerance));
			}

			//////////////////////////////////////////////////////////////////////////
			using I32x4_1 = I32x4<int32x4, int32_t, 1>;
			using I32x4_2 = I32x4<int32x4, int32_t, 2>;
			using I32x4_3 = I32x4<int32x4, int32_t, 3>;
			using I32x4_4 = I32x4<int32x4, int32_t, 4>;
		}
	}
}
