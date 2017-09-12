//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"

namespace CPF
{
	namespace SIMD
	{
		namespace Reference
		{
			struct boolx4
			{
				using Type = int32_t;
				static constexpr int Alignment = 16;
				static constexpr int LaneCount = 4;

				boolx4() {}
				constexpr boolx4(int32_t v0) : mData{ v0, v0, v0, v0 } {}
				constexpr boolx4(int32_t v0, int32_t v1) : mData{ v0, v1, v0, v0 } {}
				constexpr boolx4(int32_t v0, int32_t v1, int32_t v2) : mData{ v0, v1, v2, v0 } {}
				constexpr boolx4(int32_t v0, int32_t v1, int32_t v2, int32_t v3) : mData{ v0, v1, v2, v3 } {}

				int32_t mData[4];
			};

			//////////////////////////////////////////////////////////////////////////
			template <typename STORAGE, typename LANE_TYPE, int LANES_USED>
			struct alignas(16) Bool4;

			//////////////////////////////////////////////////////////////////////////
			template<int LANES_USED>
			struct alignas(16) Bool4<boolx4, bool, LANES_USED>
			{
				using StorageType = boolx4;
				using LaneType = bool;
				static constexpr int LaneCount = LANES_USED;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = Bool4<boolx4, bool, 1>;
				using Lanes_2 = Bool4<boolx4, bool, 2>;
				using Lanes_3 = Bool4<boolx4, bool, 3>;
				using Lanes_4 = Bool4<boolx4, bool, 4>;

				static constexpr int32_t True = 0xFFFFFFFF;
				static constexpr int32_t False = 0x00000000;

				static constexpr int32_t GetValue(bool flag) { return flag ? True : false; }

				Bool4() {}
				Bool4(LaneType value) : mSIMD{ GetValue(value), GetValue(value), GetValue(value), GetValue(value) } {}
				Bool4(LaneType v0, LaneType v1) : mSIMD(GetValue(v0), GetValue(v1)) {}
				Bool4(LaneType v0, LaneType v1, LaneType v2) : mSIMD(GetValue(v0), GetValue(v1), GetValue(v2)) {}
				Bool4(LaneType v0, LaneType v1, LaneType v2, LaneType v3) : mSIMD(GetValue(v0), GetValue(v1), GetValue(v2), GetValue(v3)) {}

				Bool4(Lanes_2 v01, LaneType v2)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], GetValue(v2))
				{
				}
				Bool4(LaneType v0, Lanes_2 v12)
					: mSIMD(GetValue(v0), v12.mSIMD.mData[0], v12.mSIMD.mData[1])
				{
				}

				Bool4(Lanes_2 v01, LaneType v2, LaneType v3)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], GetValue(v2), GetValue(v3))
				{
				}
				Bool4(LaneType v0, Lanes_2 v12, LaneType v3)
					: mSIMD(v0, v12.mSIMD.mData[0], v12.mSIMD.mData[1], GetValue(v3))
				{
				}
				Bool4(LaneType v0, LaneType v1, Lanes_2 v23)
					: mSIMD(GetValue(v0), GetValue(v1), v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}
				Bool4(Lanes_2 v01, Lanes_2 v23)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}

				Bool4(Lanes_3 v012, LaneType v3)
					: mSIMD(v012.mSIMD.mData[0], v012.mSIMD.mData[1], v012.mSIMD.mData[2], GetValue(v3))
				{
				}
				Bool4(LaneType v0, Lanes_3 v123)
					: mSIMD(GetValue(v0), v123.mSIMD.mData[0], v123.mSIMD.mData[1], v123.mSIMD.mData[2])
				{
				}

				Bool4& operator = (StorageType value) { mSIMD = value; return *this; }

				void SetLane(int index, LaneType value)
				{
					mSIMD.mData[index] = GetValue(value);
				}
				template <int I0> LaneType GetLane() const;
				template <int I0, int I1> Lanes_2 GetLanes() const;
				template <int I0, int I1, int I2> Lanes_3 GetLanes() const;
				template <int I0, int I1, int I2, int I3> Lanes_4 GetLanes() const;

				int32_t ToMask() const
				{
					int32_t result = 0;
					for (int i = 0; i < LANES_USED; ++i)
						if (mSIMD.mData[i] == True)
							result |= 1 << i;
					return result;
				}

				StorageType mSIMD;
			};

			template<int COUNT>
			using Bool4_ = Bool4<boolx4, bool, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int LANES_USED>
			template <int I0>
			typename Bool4<boolx4, bool, LANES_USED>::LaneType Bool4<boolx4, bool, LANES_USED>::GetLane() const
			{
				return mSIMD.mData[I0];
			};

			template<int LANES_USED>
			template <int I0, int I1>
			typename Bool4<boolx4, bool, LANES_USED>::Lanes_2 Bool4<boolx4, bool, LANES_USED>::GetLanes() const
			{
				return Lanes_2{ mSIMD.mData[I0], mSIMD.mData[I1] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2>
			typename Bool4<boolx4, bool, LANES_USED>::Lanes_3 Bool4<boolx4, bool, LANES_USED>::GetLanes() const
			{
				return Lanes_3{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2, int I3>
			typename Bool4<boolx4, bool, LANES_USED>::Lanes_4 Bool4<boolx4, bool, LANES_USED>::GetLanes() const
			{
				return Lanes_4{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2], mSIMD.mData[I3] };
			}

			//////////////////////////////////////////////////////////////////////////

			template <int COUNT>
			CPF_FORCE_INLINE bool operator == (const Bool4_<COUNT> lhs, const Bool4_<COUNT> rhs)
			{
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] != rhs.mSIMD.mData[i])
						return false;
				}
				return true;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool operator != (const Bool4_<COUNT> lhs, const Bool4_<COUNT> rhs)
			{
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mSIMD.mData[i] != rhs.mSIMD.mData[i])
						return true;
				}
				return false;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE bool Any(const Bool4_<COUNT> value)
			{
				for (int i = 0; i < COUNT; ++i)
					if (value.mSIMD.mData[i] != 0)
						return true;
				return false;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool All(const Bool4_<COUNT> value)
			{
				for (int i = 0; i < COUNT; ++i)
					if (value.mSIMD.mData[i] == 0)
						return false;
				return true;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool None(const Bool4_<COUNT> value)
			{
				for (int i = 0; i < COUNT; ++i)
					if (value.mSIMD.mData[i] != 0)
						return false;
				return true;
			}

			//////////////////////////////////////////////////////////////////////////
			using Bool4_1 = Bool4<boolx4, bool, 1>;
			using Bool4_2 = Bool4<boolx4, bool, 2>;
			using Bool4_3 = Bool4<boolx4, bool, 3>;
			using Bool4_4 = Bool4<boolx4, bool, 4>;
		}
	}
}
