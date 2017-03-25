//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/FPU/FPU.hpp"
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"
#include "SIMD/Detail/Ref32x4_4.hpp"

namespace Cpf
{
	namespace SIMD
	{
		namespace FPU
		{
			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(4) F32x2<float2, 4, 2, float, COUNT>
			{
				static constexpr int kAlignment = 4;
				using Type = float3;
				static constexpr int kLanes = 2;
				using Element = float;
				static constexpr int kCount = COUNT;
				static constexpr int kLaneMask = (1 << kCount) - 1;

				using Lanes_1 = F32x2<float2, 4, 2, float, 1>;
				using Lanes_2 = F32x2<float2, 4, 2, float, 2>;

				F32x2() {}
				explicit F32x2(Element value) : mVector{ value, value } {}
				F32x2(Element v0, Element v1) : mVector(v0, v1) {}
				F32x2(Lanes_2 v01)
					: mVector(v01.mVector)
				{
				}

				explicit constexpr F32x2(Type value) : mVector(value) {}

				F32x2& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				operator F32x2<float2, 4, 2, float, COUNT>() const { return mVector; }

				template <int INDEX>
				Element GetLane() const
				{
					return mVector.mData[INDEX];
				}
				Element GetLane(int index) const
				{
					return mVector.mData[index];
				}
				void SetLane(int index, float value)
				{
					mVector.mData[index] = value;
				}
				template <int I0, int I1>
				Type GetLanes() const
				{
					Type result(mVector.mData[I0], mVector.mData[I1]);
					return result;
				}
				template <int I0, int I1, int I2>
				Type GetLanes() const
				{
					Type result(mVector.mData[I0], mVector.mData[I1], mVector.mData[I2]);
					return result;
				}
				template <int I0, int I1, int I2, int I3>
				Type GetLanes() const
				{
					Type result(mVector.mData[I0], mVector.mData[I1], mVector.mData[I2], mVector.mData[i3]);
					return result;
				}

				Type mVector;
			};

			template<int COUNT>
			using F32x2_ = F32x2<float2, 4, 2, float, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE int operator == (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] == rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator != (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] != rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator < (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] < rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator <= (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] <= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator > (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] > rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator >= (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] >= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> operator - (const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = -value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> operator + (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] + rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> operator - (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] - rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> operator * (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> operator / (const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] / rhs.mVector.mData[i];
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Min(const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] <= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<1> HMin(const F32x2_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result < value.mVector.mData[i] ? result : value.mVector.mData[i];
				return F32x2_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Max(const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] >= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<1> HMax(const F32x2_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result >= value.mVector.mData[i] ? result : value.mVector.mData[i];
				return F32x2_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Sqrt(const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::sqrt(value.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Reciprocal(const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = 1.0f / value.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> RSqrt(const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = 1.0f / std::sqrt(value.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Clamp(const F32x2_<COUNT> value, typename F32x2_<COUNT>::Element low, typename F32x2_<COUNT>::Element high)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = (value.mVector.mData[i] <= low) ? low : value.mVector.mData[i] >= high ? high : value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x2_<COUNT>::Element Dot(const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				typename F32x2_<COUNT>::Element result = 0.0f;
				for (int i = 0; i < COUNT; ++i)
					result += lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x2_<COUNT>::Element Magnitude(const F32x2_<COUNT> value)
			{
				return std::sqrt(Dot(value, value));
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x2_<COUNT>::Element MagnitudeSq(const F32x2_<COUNT> value)
			{
				return Dot(value, value);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Normalize(const F32x2_<COUNT> value)
			{
				return value / F32x2_<COUNT>(Magnitude(value));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Round(const F32x2_<COUNT> value, Rounding mode)
			{
				F32x2_<COUNT> result;
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
			CPF_FORCE_INLINE F32x2_<COUNT> Floor(const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::floor(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Ceil(const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::ceil(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Modulus(const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::fmod(lhs.mVector.mData[i], rhs.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x2_<COUNT> Abs(const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::abs(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Near(const F32x2_<COUNT> lhs, const F32x2_<COUNT> rhs, float tolerance)
			{
				return (Abs(lhs - rhs) <= F32x2_<COUNT>(tolerance)) == F32x2_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Valid(const F32x2_<COUNT> value)
			{
				F32x2_<COUNT> test(value * F32x2_<COUNT>{ 0.0f });
				return (test == F32x2_<COUNT>{0.0f}) == F32x2_<COUNT>::kLaneMask;
			}

			//////////////////////////////////////////////////////////////////////////
			using F32x2_2 = F32x2<float2, 4, 2, float, 2>;
		}
	}
}
