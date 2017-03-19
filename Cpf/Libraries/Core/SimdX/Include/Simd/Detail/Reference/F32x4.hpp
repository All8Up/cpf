//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"
#include "SIMD/Detail/Ref32x4_4.hpp"


namespace Cpf
{
	namespace SIMD
	{
		namespace Reference
		{
			struct float4
			{
				float4() {}
				float4(float v0) : mData{ v0, v0, v0, v0 } {}
				float4(float v0, float v1) : mData{ v0, v1, v0, v0 } {}
				float4(float v0, float v1, float v2) : mData{ v0, v1, v2, v0 } {}
				float4(float v0, float v1, float v2, float v3) : mData{ v0, v1, v2, v3 } {}

				float mData[4];
			};

			template <typename TYPE, int ALIGNMENT, int LANES, typename ELEMENT, int COUNT>
			struct alignas(ALIGNMENT) F32x4;

			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(16) F32x4<float4, 16, 4, float, COUNT>
			{
				static constexpr int kAlignment = 16;
				using Type = float4;
				static constexpr int kLanes = 4;
				using Element = float;
				static constexpr int kCount = COUNT;
				static constexpr int kLaneMask = (1 << kCount) - 1;

				using Lanes_1 = F32x4<Type, 16, 4, float, 1>;
				using Lanes_2 = F32x4<Type, 16, 4, float, 2>;
				using Lanes_3 = F32x4<Type, 16, 4, float, 3>;
				using Lanes_4 = F32x4<Type, 16, 4, float, 4>;

				F32x4() {}
				F32x4(Element value) : mVector{ value, value, value, value } {}
				template <typename = std::enable_if<COUNT == 2, Element>::type>
				F32x4(Element v0, Element v1) : mVector(v0, v1) {}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				F32x4(Element v0, Element v1, Element v2) : mVector(v0, v1, v2) {}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(Element v0, Element v1, Element v2, Element v3) : mVector(v0, v1, v2, v3) {}

				template <typename = std::enable_if<COUNT == 3, Element>::type>
				F32x4(F32x4<Type, kAlignment, kLanes, Element, 2> v01, Element v2)
					: mVector(v01.mData[0], v01.mData[1], v2)
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(F32x4<Type, kAlignment, kLanes, Element, 2> v01, Element v2, Element v3)
					: mVector(v01.mData[0], v01.mData[1], v2, v3)
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(float v0, F32x4<Type, kAlignment, kLanes, Element, 2> v12, Element v3)
					: mVector(v0, v12.mData[0], v12.mData[1], v3)
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(float v0, float v1, F32x4<Type, kAlignment, kLanes, Element, 2> v23)
					: mVector(v0, v1, v23.mData[0], v23.mData[1])
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(F32x4<Type, kAlignment, kLanes, Element, 2> v01, F32x4<Type, kAlignment, kLanes, Element, 2> v23)
					: mVector(v01.mData[0], v01.mData[1], v23.mData[0], v23.mData[1])
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(F32x4<Type, kAlignment, kLanes, Element, 3> v012, Element v3)
					: mVector(v012.mData[0], v012.mData[1], v012.mData[2], v3)
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(Element v0, F32x4<Type, kAlignment, kLanes, Element, 3> v123)
					: mVector(v0, v123.mData[0], v123.mData[1], v123.mData[2])
				{
				}

				explicit constexpr F32x4(Type value) : mVector(value) {}

				F32x4& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				template <typename = std::enable_if<std::equal_to<int>()(kCount, 1), Element>::type>
				operator const Element() const { return mVector.mData[0]; }

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
				template <int I0, int I1, int I2>
				Type GetLanes() const
				{
					Type result(mVector.mData[I0], mVector.mData[I1], mVector.mData[I2]);
					return result;
				}

				Type mVector;
			};

			template<int COUNT>
			using F32x4_ = F32x4<float4, 16, 4, float, COUNT>;

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
			CPF_FORCE_INLINE int operator == (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] == rhs.mVector.mData[i])
						result |= 1<<i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator != (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] != rhs.mVector.mData[i])
						result |= 1<<i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator < (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] < rhs.mVector.mData[i])
						result |= 1<<i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator <= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] <= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator > (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] > rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator >= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] >= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
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
			CPF_FORCE_INLINE F32x4_<COUNT> Clamp(const F32x4_<COUNT> value, typename F32x4_<COUNT>::Element low, typename F32x4_<COUNT>::Element high)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = (value.mVector.mData[i] <= low) ? low : value.mVector.mData[i] >= high ? high : value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::Element Dot(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				typename F32x4_<COUNT>::Element result = 0.0f;
				for (int i = 0; i < COUNT; ++i)
					result += lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::Element Magnitude(const F32x4_<COUNT> value)
			{
				return std::sqrt(Dot(value, value));
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::Element MagnitudeSq(const F32x4_<COUNT> value)
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

			CPF_FORCE_INLINE bool Near(const float lhs, const float rhs, float tolerance)
			{
				return std::fabs(lhs - rhs) <= tolerance;
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
			using F32x4_1 = F32x4<float4, 16, 4, float, 1>;
			using F32x4_2 = F32x4<float4, 16, 4, float, 2>;
			using F32x4_3 = F32x4<float4, 16, 4, float, 3>;
			using F32x4_4 = F32x4<float4, 16, 4, float, 4>;
		}
	}
}
