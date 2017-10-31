//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/LaneRef.hpp"
#include "SIMD/Detail/LaneIndex.hpp"
#include "SIMD/Detail/Reference/Bool4.hpp"
#include <cmath>

namespace CPF
{
	namespace SIMD
	{
		namespace Reference
		{
			//////////////////////////////////////////////////////////////////////////
			struct alignas(16) double4
			{
				using Type = double;
				static constexpr int Alignment = 16;
				static constexpr int LaneCount = 4;

				double4() {}
				explicit constexpr double4(double v0) : mData{ v0, v0, v0, v0 } {}
				explicit constexpr double4(double v0, double v1) : mData{ v0, v1, v0, v0 } {}
				explicit constexpr double4(double v0, double v1, double v2) : mData{ v0, v1, v2, v0 } {}
				explicit constexpr double4(double v0, double v1, double v2, double v3) : mData{ v0, v1, v2, v3 } {}

				double mData[4];
			};


			//////////////////////////////////////////////////////////////////////////
			template <typename STORAGE, typename LANE_TYPE, int LANES_USED>
			struct alignas(16) F64x4;

			//////////////////////////////////////////////////////////////////////////
			template<int LANES_USED>
			struct alignas(16) F64x4<double4, double, LANES_USED>
			{
				using BoolType = Bool4_<LANES_USED>;

				using StorageType = double4;
				using LaneType = typename StorageType::Type;
				static constexpr int LaneCount = LANES_USED;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = F64x4<double4, double, 1>;
				using Lanes_2 = F64x4<double4, double, 2>;
				using Lanes_3 = F64x4<double4, double, 3>;
				using Lanes_4 = F64x4<double4, double, 4>;

				F64x4() {}
				explicit F64x4(StorageType value) : mSIMD(value) {}

				//////////////////////////////////////////////////////////////////////////
				explicit F64x4(LaneType value) : mSIMD{ value, value, value, value } {}

				//////////////////////////////////////////////////////////////////////////
				F64x4(LaneType v0, LaneType v1)
					: mSIMD(v0, v1) {}
				F64x4(LaneType v0, LaneType v1, LaneType v2)
					: mSIMD(v0, v1, v2) {}
				F64x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3)
					: mSIMD(v0, v1, v2, v3) {}

				//////////////////////////////////////////////////////////////////////////
				template <typename = typename std::enable_if<(LANES_USED >= 3), LaneType>::type>
				F64x4(Lanes_2 v01, LaneType v2)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v2)
				{
				}
				template <typename = typename std::enable_if<(LANES_USED >= 3), LaneType>::type>
				F64x4(LaneType v0, Lanes_2 v12)
					: mSIMD(v0, v12.mSIMD.mData[0], v12.mSIMD.mData[1])
				{
				}

				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>::type>
				F64x4(Lanes_2 v01, LaneType v2, LaneType v3)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v2, v3)
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>::type>
				F64x4(double v0, Lanes_2 v12, LaneType v3)
					: mSIMD(v0, v12.mSIMD.mData[0], v12.mSIMD.mData[1], v3)
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>::type>
				F64x4(double v0, double v1, Lanes_2 v23)
					: mSIMD(v0, v1, v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>::type>
				F64x4(Lanes_2 v01, Lanes_2 v23)
					: mSIMD(v01.mSIMD.mData[0], v01.mSIMD.mData[1], v23.mSIMD.mData[0], v23.mSIMD.mData[1])
				{
				}

				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>::type>
				F64x4(Lanes_3 v012, LaneType v3)
					: mSIMD(v012.mSIMD.mData[0], v012.mSIMD.mData[1], v012.mSIMD.mData[2], v3)
				{
				}
				template <typename = typename std::enable_if<LANES_USED == 4, LaneType>::type>
				F64x4(LaneType v0, Lanes_3 v123)
					: mSIMD(v0, v123.mSIMD.mData[0], v123.mSIMD.mData[1], v123.mSIMD.mData[2])
				{
				}

				F64x4& operator = (StorageType value) { mSIMD = value; return *this; }

				template <typename = typename std::enable_if<LANES_USED == 1, LaneType>::type>
				constexpr operator const LaneType() const { return mSIMD.mData[0]; }

				void SetLane(int index, double value)
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
			using F64x4_ = F64x4<double4, double, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int LANES_USED>
			template <int I0>
			typename F64x4<double4, double, LANES_USED>::LaneType F64x4<double4, double, LANES_USED>::GetLane() const
			{
				return mSIMD.mData[I0];
			};

			template<int LANES_USED>
			template <int I0, int I1>
			typename F64x4<double4, double, LANES_USED>::Lanes_2 F64x4<double4, double, LANES_USED>::GetLanes() const
			{
				return Lanes_2{ mSIMD.mData[I0], mSIMD.mData[I1] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2>
			typename F64x4<double4, double, LANES_USED>::Lanes_3 F64x4<double4, double, LANES_USED>::GetLanes() const
			{
				return Lanes_3{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2] };
			}
			template<int LANES_USED>
			template <int I0, int I1, int I2, int I3>
			typename F64x4<double4, double, LANES_USED>::Lanes_4 F64x4<double4, double, LANES_USED>::GetLanes() const
			{
				return Lanes_4{ mSIMD.mData[I0], mSIMD.mData[I1], mSIMD.mData[I2], mSIMD.mData[I3] };
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			inline F64x4_<COUNT> Cross(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs);

			template <>
			inline F64x4_<3> Cross(const F64x4_<3> lhs, const F64x4_<3> rhs)
			{
				return F64x4_<3>(
					lhs.mSIMD.mData[1] * rhs.mSIMD.mData[2] - rhs.mSIMD.mData[1] * lhs.mSIMD.mData[2],
					lhs.mSIMD.mData[2] * rhs.mSIMD.mData[0] - rhs.mSIMD.mData[2] * lhs.mSIMD.mData[0],
					lhs.mSIMD.mData[0] * rhs.mSIMD.mData[1] - rhs.mSIMD.mData[0] * lhs.mSIMD.mData[1]);
			}



			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			inline Bool4_<COUNT> operator == (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				Bool4_<COUNT> result(Bool4_<COUNT>::False);
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] == rhs.mSIMD.mData[i])
						result.SetLane(i, Bool4_<COUNT>::True);
				return result;
			}
			template <int COUNT>
			inline Bool4_<COUNT> operator != (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				Bool4_<COUNT> result(Bool4_<COUNT>::False);
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] != rhs.mSIMD.mData[i])
						result.SetLane(i, Bool4_<COUNT>::True);
				return result;
			}
			template <int COUNT>
			inline Bool4_<COUNT> operator < (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				Bool4_<COUNT> result(Bool4_<COUNT>::False);
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] < rhs.mSIMD.mData[i])
						result.SetLane(i, Bool4_<COUNT>::True);
				return result;
			}
			template <int COUNT>
			inline Bool4_<COUNT> operator <= (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				Bool4_<COUNT> result(Bool4_<COUNT>::False);
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] <= rhs.mSIMD.mData[i])
						result.SetLane(i, Bool4_<COUNT>::True);
				return result;
			}
			template <int COUNT>
			inline Bool4_<COUNT> operator > (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				Bool4_<COUNT> result(Bool4_<COUNT>::False);
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] > rhs.mSIMD.mData[i])
						result.SetLane(i, Bool4_<COUNT>::True);
				return result;
			}
			template <int COUNT>
			inline Bool4_<COUNT> operator >= (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				Bool4_<COUNT> result(Bool4_<COUNT>::False);
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mSIMD.mData[i] >= rhs.mSIMD.mData[i])
						result.SetLane(i, Bool4_<COUNT>::True);
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			inline F64x4_<COUNT> operator - (const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = -value.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			inline F64x4_<COUNT> operator + (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] + rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			inline F64x4_<COUNT> operator - (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] - rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			inline F64x4_<COUNT> operator * (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] * rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			inline F64x4_<COUNT> operator / (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] / rhs.mSIMD.mData[i];
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			inline F64x4_<COUNT> Min(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] <= rhs.mSIMD.mData[i] ? lhs.mSIMD.mData[i] : rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			inline F64x4_<1> HMin(const F64x4_<COUNT> value)
			{
				double result = value.mSIMD.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result < value.mSIMD.mData[i] ? result : value.mSIMD.mData[i];
				return F64x4_<1>(result);
			}
			template <int COUNT>
			inline F64x4_<COUNT> Max(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = lhs.mSIMD.mData[i] >= rhs.mSIMD.mData[i] ? lhs.mSIMD.mData[i] : rhs.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			inline F64x4_<1> HMax(const F64x4_<COUNT> value)
			{
				double result = value.mSIMD.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result >= value.mSIMD.mData[i] ? result : value.mSIMD.mData[i];
				return F64x4_<1>(result);
			}
			template <int COUNT>
			inline F64x4_<COUNT> Sqrt(const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::sqrt(value.mSIMD.mData[i]);
				return result;
			}
			template <int COUNT>
			inline F64x4_<COUNT> Reciprocal(const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = 1.0f / value.mSIMD.mData[i];
				return result;
			}
			template <int COUNT>
			inline F64x4_<COUNT> RSqrt(const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = 1.0f / std::sqrt(value.mSIMD.mData[i]);
				return result;
			}
			template <int COUNT>
			inline F64x4_<COUNT> Clamp(const F64x4_<COUNT> value, typename F64x4_<COUNT>::LaneType low, typename F64x4_<COUNT>::LaneType high)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = (value.mSIMD.mData[i] <= low) ? low : value.mSIMD.mData[i] >= high ? high : value.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			inline typename F64x4_<COUNT>::LaneType Dot(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				typename F64x4_<COUNT>::LaneType result = 0.0;
				for (int i = 0; i < COUNT; ++i)
					result += lhs.mSIMD.mData[i] * rhs.mSIMD.mData[i];
				return result;
			}

			template <int COUNT>
			inline typename F64x4_<COUNT>::LaneType Magnitude(const F64x4_<COUNT> value)
			{
				return std::sqrt(Dot(value, value));
			}

			template <int COUNT>
			inline typename F64x4_<COUNT>::LaneType MagnitudeSq(const F64x4_<COUNT> value)
			{
				return Dot(value, value);
			}

			template <int COUNT>
			inline F64x4_<COUNT> Normalize(const F64x4_<COUNT> value)
			{
				return value / F64x4_<COUNT>(Magnitude(value));
			}

			template <int COUNT>
			inline F64x4_<COUNT> Round(const F64x4_<COUNT> value, Rounding mode)
			{
				F64x4_<COUNT> result;
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
						result.mSIMD.mData[i] = double(v);
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
			inline F64x4_<COUNT> Floor(const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::floor(value.mSIMD.mData[i]);
				return result;
			}

			template <int COUNT>
			inline F64x4_<COUNT> Ceil(const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::ceil(value.mSIMD.mData[i]);
				return result;
			}

			template <int COUNT>
			inline F64x4_<COUNT> Modulus(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::mod(lhs.mSIMD.mData[i], rhs.mSIMD.mData[i]);
				return result;
			}

			template <int COUNT>
			inline F64x4_<COUNT> Abs(const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mSIMD.mData[i] = std::abs(value.mSIMD.mData[i]);
				return result;
			}

			inline bool Near(const double lhs, const double rhs, double tolerance)
			{
				return std::abs(lhs - rhs) <= tolerance;
			}

			template <int COUNT>
			inline bool Near(const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs, double tolerance)
			{
				return All(Abs(lhs - rhs) <= F64x4_<COUNT>(tolerance));
			}

			template <int COUNT>
			inline bool Valid(const F64x4_<COUNT> value)
			{
				F64x4_<COUNT> test(value * F64x4_<COUNT>{ 0.0 });
				return All(test == F64x4_<COUNT>{0.0});
			}

			//////////////////////////////////////////////////////////////////////////
			using F64x4_1 = F64x4<double4, double, 1>;
			using F64x4_2 = F64x4<double4, double, 2>;
			using F64x4_3 = F64x4<double4, double, 3>;
			using F64x4_4 = F64x4<double4, double, 4>;
		}
	}
}
