//////////////////////////////////////////////////////////////////////////
#pragma once
#include "FPU.hpp"
#include "SIMD/Detail/FPU/Bool4.hpp"

namespace CPF
{
	namespace SIMD
	{
		namespace FPU
		{
			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(4) F32x4<float4, float, COUNT>
			{
				using BoolType = Bool4<int32_t, bool, COUNT>;

				using StorageType = float4;
				using LaneType = float;
				static constexpr int LaneCount = COUNT;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = F32x4<float4, float, 1>;
				using Lanes_2 = F32x4<float4, float, 2>;
				using Lanes_3 = F32x4<float4, float, 3>;
				using Lanes_4 = F32x4<float4, float, 4>;

				F32x4() {}
				explicit F32x4(LaneType value) : mVector{ value, value, value, value } {}
				F32x4(LaneType v0, LaneType v1) : mVector(v0, v1) {}
				F32x4(LaneType v0, LaneType v1, LaneType v2) : mVector(v0, v1, v2) {}
				F32x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3) : mVector(v0, v1, v2, v3) {}

				F32x4(Lanes_2 v01, LaneType v2)
					: mVector(v01.mVector.mData[0], v01.mVector.mData[1], v2)
				{
				}
				F32x4(LaneType v0, Lanes_2 v12)
					: mVector(v0, v12.mVector.mData[0], v12.mVector.mData[1])
				{
				}

				F32x4(Lanes_2 v01, LaneType v2, LaneType v3)
					: mVector(v01.mVector.mData[0], v01.mVector.mData[1], v2, v3)
				{
				}
				F32x4(float v0, Lanes_2 v12, LaneType v3)
					: mVector(v0, v12.mVector.mData[0], v12.mVector.mData[1], v3)
				{
				}
				F32x4(float v0, float v1, Lanes_2 v23)
					: mVector(v0, v1, v23.mVector.mData[0], v23.mVector.mData[1])
				{
				}
				F32x4(Lanes_2 v01, Lanes_2 v23)
					: mVector(v01.mVector.mData[0], v01.mVector.mData[1], v23.mVector.mData[0], v23.mVector.mData[1])
				{
				}

				F32x4(Lanes_3 v012, LaneType v3)
					: mVector(v012.mVector.mData[0], v012.mVector.mData[1], v012.mVector.mData[2], v3)
				{
				}
				F32x4(LaneType v0, Lanes_3 v123)
					: mVector(v0, v123.mVector.mData[0], v123.mVector.mData[1], v123.mVector.mData[2])
				{
				}

				explicit constexpr F32x4(StorageType value) : mVector(value) {}

				F32x4& operator = (StorageType value) { mVector = value; return *this; }

				explicit operator StorageType () const { return mVector; }

				template <typename = typename std::enable_if<(COUNT == 1), LaneType>::type>
				operator const LaneType() const { return mVector.mData[0]; }

				void SetLane(int index, float value)
				{
					mVector.mData[index] = value;
				}
				template <int INDEX>
				LaneType GetLane() const
				{
					return mVector.mData[INDEX];
				}
				template <int I0, int I1>
				StorageType GetLanes() const
				{
					StorageType result(mVector.mData[I0], mVector.mData[I1]);
					return result;
				}
				template <int I0, int I1, int I2>
				StorageType GetLanes() const
				{
					StorageType result(mVector.mData[I0], mVector.mData[I1], mVector.mData[I2]);
					return result;
				}
				template <int I0, int I1, int I2, int I3>
				StorageType GetLanes() const
				{
					StorageType result(mVector.mData[I0], mVector.mData[I1], mVector.mData[I2], mVector.mData[i3]);
					return result;
				}

				StorageType mVector;
			};

			template<int COUNT>
			using F32x4_ = F32x4<float4, float, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT> Cross(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs);

			template <>
			CPF_FORCE_INLINE typename F32x4_<3> Cross(const F32x4_<3> lhs, const F32x4_<3> rhs)
			{
				return F32x4_<3>(
					lhs.mVector.mData[1] * rhs.mVector.mData[2] - rhs.mVector.mData[1] * lhs.mVector.mData[2],
					lhs.mVector.mData[2] * rhs.mVector.mData[0] - rhs.mVector.mData[2] * lhs.mVector.mData[0],
					lhs.mVector.mData[0] * rhs.mVector.mData[1] - rhs.mVector.mData[0] * lhs.mVector.mData[1]);
			}



			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> operator == (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] == rhs.mVector.mData[i])
						result |= 1 << i;
				return Bool4_<COUNT>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> operator != (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] != rhs.mVector.mData[i])
						result |= 1 << i;
				return Bool4_<COUNT>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> operator < (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] < rhs.mVector.mData[i])
						result |= 1 << i;
				return Bool4_<COUNT>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> operator <= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] <= rhs.mVector.mData[i])
						result |= 1 << i;
				return Bool4_<COUNT>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> operator > (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] > rhs.mVector.mData[i])
						result |= 1 << i;
				return Bool4_<COUNT>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> operator >= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] >= rhs.mVector.mData[i])
						result |= 1 << i;
				return Bool4_<COUNT>(result);
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator - (const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = -value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator + (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] + rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator - (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] - rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator * (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator / (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] / rhs.mVector.mData[i];
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Min(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] <= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<1> HMin(const F32x4_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result < value.mVector.mData[i] ? result : value.mVector.mData[i];
				return F32x4_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Max(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] >= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<1> HMax(const F32x4_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result >= value.mVector.mData[i] ? result : value.mVector.mData[i];
				return F32x4_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Sqrt(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::sqrt(value.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Reciprocal(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = 1.0f / value.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> RSqrt(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = 1.0f / std::sqrt(value.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Clamp(const F32x4_<COUNT> value, typename F32x4_<COUNT>::LaneType low, typename F32x4_<COUNT>::LaneType high)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = (value.mVector.mData[i] <= low) ? low : value.mVector.mData[i] >= high ? high : value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::LaneType Dot(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				typename F32x4_<COUNT>::LaneType result = 0.0f;
				for (int i = 0; i < COUNT; ++i)
					result += lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::LaneType Magnitude(const F32x4_<COUNT> value)
			{
				return std::sqrt(Dot(value, value));
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::LaneType MagnitudeSq(const F32x4_<COUNT> value)
			{
				return Dot(value, value);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Normalize(const F32x4_<COUNT> value)
			{
				return value / F32x4_<COUNT>(Magnitude(value));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Round(const F32x4_<COUNT> value, Rounding mode)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
				{
					switch (mode)
					{
					case Rounding::eCurrent:
						result.mVector.mData[i] = std::round(value.mVector.mData[i]);
						break;
					case Rounding::eUp:
						result.mVector.mData[i] = std::ceil(value.mVector.mData[i]);
						break;
					case Rounding::eDown:
						result.mVector.mData[i] = std::floor(value.mVector.mData[i]);
						break;
					case Rounding::eTruncate:
					{
						int32_t v = int32_t(value.mVector.mData[i]);
						result.mVector.mData[i] = float(v);
					}
					break;
					case Rounding::eNearest:
						result.mVector.mData[i] = std::round(value.mVector.mData[i]);
						break;
					}
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Floor(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::floor(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Ceil(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::ceil(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Modulus(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::fmod(lhs.mVector.mData[i], rhs.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Abs(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::abs(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Near(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs, float tolerance)
			{
				return (Abs(lhs - rhs) <= F32x4_<COUNT>(tolerance)) == F32x4_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Valid(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> test(value * F32x4_<COUNT>{ 0.0f });
				return (test == F32x4_<COUNT>{0.0f}) == F32x4_<COUNT>::kLaneMask;
			}

			//////////////////////////////////////////////////////////////////////////
			using F32x4_1 = F32x4<float4, float, 1>;
			using F32x4_2 = F32x4<float4, float, 2>;
			using F32x4_3 = F32x4<float4, float, 3>;
			using F32x4_4 = F32x4<float4, float, 4>;
		}
	}
}
