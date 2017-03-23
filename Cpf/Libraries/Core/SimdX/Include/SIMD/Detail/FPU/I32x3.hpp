//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/FPU/FPU.hpp"

namespace Cpf
{
	namespace SIMD
	{
		namespace FPU
		{
			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(4) I32x3<int3, 4, 3, int32_t, COUNT>
			{
				static constexpr int kAlignment = 4;
				using Type = int3;
				static constexpr int kLanes = 3;
				using Element = int32_t;
				static constexpr int kCount = COUNT;
				static constexpr int kLaneMask = (1 << kCount) - 1;

				using Lanes_1 = I32x3<Type, 4, 3, int32_t, 1>;
				using Lanes_2 = I32x3<Type, 4, 3, int32_t, 2>;
				using Lanes_3 = I32x3<Type, 4, 3, int32_t, 3>;

				I32x3() {}
				I32x3(Element value) : mVector{ value, value, value } {}
				template <typename = std::enable_if<COUNT == 2, Element>::type>
				I32x3(Element v0, Element v1) : mVector(v0, v1) {}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				I32x3(Element v0, Element v1, Element v2) : mVector(v0, v1, v2) {}

				template <typename = std::enable_if<COUNT == 3, Element>::type>
				I32x3(Lanes_2 v01, Element v2)
					: mVector(v01.mVector.mData[0], v01.mVector.mData[1], v2)
				{
				}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				I32x3(Element v0, Lanes_2 v12)
					: mVector(v0, v12.mVector.mData[0], v12.mVector.mData[1])
				{
				}

				explicit constexpr I32x3(Type value) : mVector(value) {}

				I32x3& operator = (Type value) { mVector = value; return *this; }

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
				void SetLane(int index, int32_t value)
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
			using I32x3_ = I32x3<int3, 4, 3, int32_t, COUNT>;

			//////////////////////////////////////////////////////////////////////////

			template <int COUNT>
			CPF_FORCE_INLINE int operator == (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mVector.mData[i] == rhs.mVector.mData[i])
						result |= 1 << i;
				}
				return result & I32x3_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE int operator != (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mVector.mData[i] != rhs.mVector.mData[i])
						result |= 1 << i;
				}
				return result & I32x3_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE int operator < (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mVector.mData[i] < rhs.mVector.mData[i])
						result |= 1 << i;
				}
				return result & I32x3_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE int operator <= (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mVector.mData[i] <= rhs.mVector.mData[i])
						result |= 1 << i;
				}
				return result & I32x3_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE int operator > (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mVector.mData[i] > rhs.mVector.mData[i])
						result |= 1 << i;
				}
				return result & I32x3_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE int operator >= (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
				{
					if (lhs.mVector.mData[i] >= rhs.mVector.mData[i])
						result |= 1 << i;
				}
				return result & I32x3_<COUNT>::kLaneMask;
			}

			//////////////////////////////////////////////////////////////////////////

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> operator - (const I32x3_<COUNT> value)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = -value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> operator + (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] + rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> operator - (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] - rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> operator * (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> operator / (const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] / rhs.mVector.mData[i];
				return result;
			}

			//////////////////////////////////////////////////////////////////////////

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> Min(const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] <= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<1> HMin(const I32x3_<COUNT> value)
			{
				int32_t result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result <= value.mVector.mData[i] ? result : value.mVector.mData[i];
				return I32x3_<1>(result);
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> Max(const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] >= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<1> HMax(const I32x3_<COUNT> value)
			{
				int32_t result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result >= value.mVector.mData[i] ? result : value.mVector.mData[i];
				return I32x3_<1>(result);
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> Sqrt(const I32x3_<COUNT> value)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = int32_t(std::sqrt(value.mVector.mData[i]));
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> Clamp(const I32x3_<COUNT> value, typename I32x3_<COUNT>::Element l, typename I32x3_<COUNT>::Element h)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
				{
					result.mVector.mData[i] = value.mVector.mData[i] <= l ? l : value.mVector.mData[i] >= h ? h : value.mVector.mData[i];
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> Modulus(const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
				{
					result.mVector.mData[i] = lhs.mVector.mData[i] % rhs.mVector.mData[i];
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x3_<COUNT> Abs(const I32x3_<COUNT> value)
			{
				I32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = value.mVector.mData[i] >= 0 ? value.mVector.mData[i] : -value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Near(const I32x3_<COUNT> lhs, const I32x3_<COUNT> rhs, int32_t tolerance)
			{
				return (Abs(lhs - rhs) <= I32x3_<COUNT>(tolerance)) == I32x3_<COUNT>::kLaneMask;
			}

			//////////////////////////////////////////////////////////////////////////
			using I32x3_3 = I32x3<int3, 4, 3, int32_t, 3>;
		}
	}
}
