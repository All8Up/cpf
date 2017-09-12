//////////////////////////////////////////////////////////////////////////
#pragma once
#include "FPU.hpp"

namespace CPF
{
	namespace SIMD
	{
		namespace FPU
		{
			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(4) Bool4<int32_t, bool, COUNT>
			{
				using StorageType = int32_t;
				using LaneType = bool;
				static constexpr int LaneCount = COUNT;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = Bool4<int32_t, bool, 1>;
				using Lanes_2 = Bool4<int32_t, bool, 2>;
				using Lanes_3 = Bool4<int32_t, bool, 3>;
				using Lanes_4 = Bool4<int32_t, bool, 4>;

				Bool4() {}
				explicit constexpr Bool4(StorageType value)
					: mVector(value)
				{}
				explicit Bool4(LaneType value)
				{
					mVector = value ? LaneMask : 0;
				}
				Bool4(LaneType v0, LaneType v1)
				{
					mVector = (v0 ? 1 : 0) | (v1 ? 2 : 0);
				}
				Bool4(LaneType v0, LaneType v1, LaneType v2)
				{
					mVector = (v0 ? 1 : 0) | (v1 ? 2 : 0) | (v2 ? 4 : 0);
				}
				Bool4(LaneType v0, LaneType v1, LaneType v2, LaneType v3)
				{
					mVector = (v0 ? 1 : 0) | (v1 ? 2 : 0) | (v2 ? 4 : 0) | (v3 ? 8 : 0);
				}

				Bool4(Lanes_2 v01, LaneType v2)
				{
					mVector = v01.ToMask() & LaneMask;
					mVector |= v2 ? 4 : 0;
				}
				Bool4(LaneType v0, Lanes_2 v12)
				{
					mVector = v0 ? 1 : 0;
					mVector |= (v12.ToMask() & 0x03) << 1;
				}

				Bool4(Lanes_2 v01, LaneType v2, LaneType v3)
				{
					mVector = v01.ToMask() & 0x03;
					mVector |= v2 ? 4 : 0;
					mVector |= v3 ? 8 : 0;
				}
				Bool4(LaneType v0, Lanes_2 v12, LaneType v3)
				{
					mVector = v0 ? 1 : 0;
					mVector |= (v12.ToMask() & 0x03) << 1;
					mVector |= v3 ? 8 : 0;
				}
				Bool4(LaneType v0, LaneType v1, Lanes_2 v23)
				{
					mVector = (v0 ? 1 : 0) | (v1 ? 2 : 0);
					mVector |= (v23.ToMask() & 0x03) << 2;
				}
				Bool4(Lanes_2 v01, Lanes_2 v23)
				{
					mVector = v01.ToMask();
					mVector |= (v23.ToMask() & 0x03) << 2;
				}

				Bool4(Lanes_3 v012, LaneType v3)
				{
					mVector = v012.ToMask() & 0x07;
					mVector |= v3 ? 8 : 0;
				}
				Bool4(LaneType v0, Lanes_3 v123)
				{
					mVector = v0 ? 1 : 0;
					mVector |= (v123.ToMask() & 0x07) << 1;
				}

				Bool4& operator = (StorageType value)
				{
					mVector = value;
					return *this;
				}

				explicit operator StorageType () const
				{
					return mVector;
				}

				void SetLane(int index, bool value)
				{
					StorageType bit = 1 << index;
					mVector.mData = (mVector.mData & ~bit) | value ? bit : 0;
				}
				template <int INDEX>
				LaneType GetLane() const
				{
					return (mVector.mData & (1 << INDEX)) >> INDEX;
				}
				template <int I0, int I1>
				StorageType GetLanes() const
				{
					return StorageType(GetLane<I0>(), GetLane<I1>());
				}
				template <int I0, int I1, int I2>
				StorageType GetLanes() const
				{
					return StorageType(GetLane<I0>(), GetLane<I1>(), GetLane<I2>());
				}
				template <int I0, int I1, int I2, int I3>
				StorageType GetLanes() const
				{
					return StorageType(GetLane<I0>(), GetLane<I1>(), GetLane<I2>(), GetLane<I3>());
				}

				int32_t ToMask() const
				{
					return mVector;
				}

				StorageType mVector;
			};

			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			using Bool4_ = Bool4<int32_t, bool, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE bool operator == (const Bool4_<COUNT> lhs, const Bool4_<COUNT> rhs)
			{
				return lhs.mVector == rhs.mVector;
			}
			template <int COUNT>
			CPF_FORCE_INLINE bool operator != (const Bool4_<COUNT> lhs, const Bool4_<COUNT> rhs)
			{
				return lhs.mVector != rhs.mVector;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE bool Any(const Bool4_<COUNT> value)
			{
				return value.mVector != 0;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool All(const Bool4_<COUNT> value)
			{
				return value.mVector == Bool4_<COUNT>::LaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool None(const Bool4_<COUNT> value)
			{
				return value.mVector == 0;
			}

			//////////////////////////////////////////////////////////////////////////
			using Bool4_1 = Bool4<int32_t, bool, 1>;
			using Bool4_2 = Bool4<int32_t, bool, 2>;
			using Bool4_3 = Bool4<int32_t, bool, 3>;
			using Bool4_4 = Bool4<int32_t, bool, 4>;
		}
	}
}
