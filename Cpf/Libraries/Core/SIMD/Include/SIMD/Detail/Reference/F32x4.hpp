//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"
#include "SIMD/Detail/Ref32x4_4.hpp"
#include <cmath>

namespace Cpf
{
	namespace SIMD
	{
		namespace Reference
		{
			//////////////////////////////////////////////////////////////////////////
			struct alignas(16) float4
			{
				using Type = float;
				static constexpr int Alignment = 16;
				static constexpr int LaneCount = 4; 
				
				float4() {}
				explicit constexpr float4(float v0) : mData{ v0, v0, v0, v0 } {}
				explicit constexpr float4(float v0, float v1) : mData{ v0, v1, v0, v0 } {}
				explicit constexpr float4(float v0, float v1, float v2) : mData{ v0, v1, v2, v0 } {}
				explicit constexpr float4(float v0, float v1, float v2, float v3) : mData{ v0, v1, v2, v3 } {}

				float mData[4];
			};


			//////////////////////////////////////////////////////////////////////////
			template <typename STORAGE, typename LANE_TYPE, int LANES_USED>
			struct alignas(16) F32x4;

			//////////////////////////////////////////////////////////////////////////
			template<int LANES_USED>
			struct alignas(16) F32x4<float4, float, LANES_USED>
			{
				using StorageType = float4;
				using LaneType = typename StorageType::Type;
				static constexpr int LaneCount = LANES_USED;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = F32x4<float4, float, 1>;
				using Lanes_2 = F32x4<float4, float, 2>;
				using Lanes_3 = F32x4<float4, float, 3>;
				using Lanes_4 = F32x4<float4, float, 4>;

				F32x4() {}
				explicit F32x4(StorageType value) : mSIMD(value) {}
				
				//////////////////////////////////////////////////////////////////////////
				explicit F32x4(LaneType value) : mSIMD{ value, value, value, value } {}

				//////////////////////////////////////////////////////////////////////////
				F32x4(LaneType v0, LaneType v1)
					: mSIMD(v0, v1) {}
				F32x4(LaneType v0, LaneType v1, LaneType v2)
					: mSIMD(v0, v1, v2) {}
				F32x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3)
					: mSIMD(v0, v1, v2, v3) {}

				//////////////////////////////////////////////////////////////////////////
				template <typename = typename std::enable_if<(LANES_USED >= 3), LaneType>>
				F32x4(Lanes_2 v01, LaneType v2)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v2)
				{
				}
				template <typename = typename std::enable_if<(LANES_USED >= 3), LaneType>>
				F32x4(LaneType v0, Lanes_2 v12)
					: mSIMD(v0, v12.mSIMD.mData[0], v12.mSIMD.mData[1])
				{
				}

				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>>
				F32x4(Lanes_2 v01, LaneType v2, LaneType v3)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v2, v3)
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>>
				F32x4(float v0, Lanes_2 v12, LaneType v3)
					: mSIMD(v0, v12.mSIMD.mData[0], v12.mSIMD.mData[1], v3)
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>>
				F32x4(float v0, float v1, Lanes_2 v23)
					: mSIMD(v0, v1, v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>>
				F32x4(Lanes_2 v01, Lanes_2 v23)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}

				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>>
				F32x4(Lanes_3 v012, LaneType v3)
					: mSIMD(v012.mSIMD.mData[0], v012.mSIMD.mData[1], v012.mSIMD.mData[2], v3)
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>>
				F32x4(LaneType v0, Lanes_3 v123)
					: mSIMD(v0, v123.mSIMD.mData[0], v123.mSIMD.mData[1], v123.mSIMD.mData[2])
				{
				}

				F32x4& operator = (StorageType value) { mSIMD = value; return *this; }

				template <typename = typename std::enable_if<LANES_USED == 1, LaneType>>
				constexpr operator const LaneType() const { return mSIMD.mData[0]; }

				void SetLane(int index, float value)
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
			using F32x4_ = F32x4<float4, float, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int LANES_USED>
			template <int I0>
			typename F32x4<float4, float, LANES_USED>::LaneType F32x4<float4, float, LANES_USED>::GetLane() const
			{
				return mSIMD.mData[I0];
			};

			template<int LANES_USED>
			template <int I0, int I1>
			typename F32x4<float4, float, LANES_USED>::Lanes_2 F32x4<float4, float, LANES_USED>::GetLanes() const
			{
				return Lanes_2{ mSIMD.mData[I0], mSIMD.mData[I1] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2>
			typename F32x4<float4, float, LANES_USED>::Lanes_3 F32x4<float4, float, LANES_USED>::GetLanes() const
			{
				return Lanes_3{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2, int I3>
			typename F32x4<float4, float, LANES_USED>::Lanes_4 F32x4<float4, float, LANES_USED>::GetLanes() const
			{
				return Lanes_4{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2], mSIMD.mData[I3] };
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Cross(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs);

			template <>
			CPF_FORCE_INLINE F32x4_<3> Cross(const F32x4_<3> lhs, const F32x4_<3> rhs)
			{
				return F32x4_<3>(
					lhs.mSIMD.mData[1] * rhs.mSIMD.mData[2] - rhs.mSIMD.mData[1] * lhs.mSIMD.mData[2],
					lhs.mSIMD.mData[2] * rhs.mSIMD.mData[0] - rhs.mSIMD.mData[2] * lhs.mSIMD.mData[0],
					lhs.mSIMD.mData[0] * rhs.mSIMD.mData[1] - rhs.mSIMD.mData[0] * lhs.mSIMD.mData[1]);
			}



			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE int operator == (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] == rhs.mSIMD.mData[i])
						result |= 1<<i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator != (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] != rhs.mSIMD.mData[i])
						result |= 1<<i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator < (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] < rhs.mSIMD.mData[i])
						result |= 1<<i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator <= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] <= rhs.mSIMD.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator > (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] > rhs.mSIMD.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator >= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] >= rhs.mSIMD.mData[i])
						result |= 1 << i;
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator - (const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = -value.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator + (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] + rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator - (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] - rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator * (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] * rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> operator / (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] / rhs.mSIMD.mData[i];
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Min(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] <= rhs.mSIMD.mData[i] ? lhs.mSIMD.mData[i] : rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<1> HMin(const F32x4_<COUNT> value)
			{
				float result = value.mSIMD.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result < value.mSIMD.mData[i] ? result : value.mSIMD.mData[i];
				return F32x4_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Max(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] >= rhs.mSIMD.mData[i] ? lhs.mSIMD.mData[i] : rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<1> HMax(const F32x4_<COUNT> value)
			{
				float result = value.mSIMD.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result >= value.mSIMD.mData[i] ? result : value.mSIMD.mData[i];
				return F32x4_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Sqrt(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::sqrt(value.mSIMD.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Reciprocal(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = 1.0f / value.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> RSqrt(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = 1.0f / std::sqrt(value.mSIMD.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Clamp(const F32x4_<COUNT> value, typename F32x4_<COUNT>::LaneType low, typename F32x4_<COUNT>::LaneType high)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = (value.mSIMD.mData[i] <= low) ? low : value.mSIMD.mData[i] >= high ? high : value.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::LaneType Dot(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				typename F32x4_<COUNT>::LaneType result = 0.0f;
				for (int i = 0; i < COUNT; ++i)
					result += lhs.mSIMD.mData[i] * rhs.mSIMD.mData[i];
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
						result.mSIMD.mData[i] = std::round(value.mSIMD.mData[i]);
						break;
					case Rounding::eUp:
						result.mSIMD.mData[i] = std::ceil(value.mSIMD.mData[i]);
						break;
					case Rounding::eDown:
						result.mSIMD.mData[i] = std::floor(value.mSIMD.mData[i]);
						break;
					case Rounding::eTruncate:
						{
							int32_t v = int32_t(value.mSIMD.mData[i]);
							result.mSIMD.mData[i] = float(v);
						}
						break;
					case Rounding::eNearest:
						result.mSIMD.mData[i] = std::round(value.mSIMD.mData[i]);
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
					result.mSIMD.mData[i] = std::floor(value.mSIMD.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Ceil(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::ceil(value.mSIMD.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Modulus(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::fmod(lhs.mSIMD.mData[i], rhs.mSIMD.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Abs(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::abs(value.mSIMD.mData[i]);
				return result;
			}

			CPF_FORCE_INLINE bool Near(const float lhs, const float rhs, float tolerance)
			{
				return std::fabs(lhs - rhs) <= tolerance;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Near(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs, float tolerance)
			{
				return (Abs(lhs - rhs) <= F32x4_<COUNT>(tolerance)) == F32x4_<COUNT>::LaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Valid(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> test(value * F32x4_<COUNT>{ 0.0f });
				return (test == F32x4_<COUNT>{0.0f}) == F32x4_<COUNT>::LaneMask;
			}

			//////////////////////////////////////////////////////////////////////////
			using F32x4_1 = F32x4<float4, float, 1>;
			using F32x4_2 = F32x4<float4, float, 2>;
			using F32x4_3 = F32x4<float4, float, 3>;
			using F32x4_4 = F32x4<float4, float, 4>;
		}
	}
}
