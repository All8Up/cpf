//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

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

				using F32x4_1 = F32x4<Type, 16, 4, float, 1>;
				using F32x4_2 = F32x4<Type, 16, 4, float, 2>;
				using F32x4_3 = F32x4<Type, 16, 4, float, 3>;
				using F32x4_4 = F32x4<Type, 16, 4, float, 4>;

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
			CPF_FORCE_INLINE int operator == (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] != rhs.mVector.mData[i])
						result |= 1<<i;
				return ~result;
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
			CPF_FORCE_INLINE bool operator < (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] < rhs.mVector.mData[i])
						result |= 1<<i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE bool operator <= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] <= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE bool operator > (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] > rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE bool operator >= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] >= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
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
					result.mVector.mData[i] = std::min(lhs.mVector.mData[i], rhs.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE float HMin(const F32x4_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = std::min(result, value.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> Max(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::max(lhs.mVector.mData[i], rhs.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE float CPF_VECTORCALL HMax(const F32x4_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = std::max(result, value.mVector.mData[i]);
				return result;
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
			CPF_FORCE_INLINE F32x4_<COUNT> Clamp(const F32x4_<COUNT> value, const F32x4_<COUNT> low, const F32x4_<COUNT> high)
			{
				F32x4_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = value.mVector.mData[i] >= high.mVector.mData[i] ? high.mVector.mData[i]
						: (value.mVector.mData[i] <= low.mVector.mData[i]) ? low.mVector.mData[i] : value.mVector.mData[i];
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
				return Abs(lhs - rhs) <= F32x4_<COUNT>(tolerance);
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Valid(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> test(value * F32x4_<COUNT>{ 0.0f });
				return test == F32x4_<COUNT>{0.0f};
			}

			//////////////////////////////////////////////////////////////////////////
			using F32x4_1 = F32x4<float4, 16, 4, float, 1>;
			using F32x4_2 = F32x4<float4, 16, 4, float, 2>;
			using F32x4_3 = F32x4<float4, 16, 4, float, 3>;
			using F32x4_4 = F32x4<float4, 16, 4, float, 4>;
		}
	}
}
