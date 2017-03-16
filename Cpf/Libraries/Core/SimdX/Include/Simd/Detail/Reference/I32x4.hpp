//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		namespace Reference
		{
			struct int32x4
			{
				int32x4() {}
				int32x4(int32_t v0) : mData{ v0, v0, v0, v0 } {}
				int32x4(int32_t v0, int32_t v1) : mData{ v0, v1, v0, v0 } {}
				int32x4(int32_t v0, int32_t v1, int32_t v2) : mData{ v0, v1, v2, v0 } {}
				int32x4(int32_t v0, int32_t v1, int32_t v2, int32_t v3) : mData{ v0, v1, v2, v3 } {}

				int32_t mData[4];
			};

			template <typename TYPE, int ALIGNMENT, int LANES, typename ELEMENT, int COUNT>
			struct alignas(ALIGNMENT) I32x4;

			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(16) I32x4<int32x4, 16, 4, int32_t, COUNT>
			{
				static constexpr int kAlignment = 16;
				using Type = int32x4;
				static constexpr int kLanes = 4;
				using Element = int32_t;
				static constexpr int kCount = COUNT;
				static constexpr int kLaneMask = (1 << kCount) - 1;

				using Lanes_1 = I32x4<Type, 16, 4, int32_t, 1>;
				using Lanes_2 = I32x4<Type, 16, 4, int32_t, 2>;
				using Lanes_3 = I32x4<Type, 16, 4, int32_t, 3>;
				using Lanes_4 = I32x4<Type, 16, 4, int32_t, 4>;

				I32x4() {}
				I32x4(Element value) : mVector{ value, value, value, value } {}
				template <typename = std::enable_if<COUNT == 2, Element>::type>
				I32x4(Element v0, Element v1) : mVector(v0, v1) {}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				I32x4(Element v0, Element v1, Element v2) : mVector(v0, v1, v2) {}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Element v0, Element v1, Element v2, Element v3) : mVector(v0, v1, v2, v3) {}

				template <typename = std::enable_if<COUNT == 3, Element>::type>
				I32x4(I32x4<Type, kAlignment, kLanes, Element, 2> v01, Element v2)
					: mVector(v01.mData[0], v01.mData[1], v2)
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(I32x4<Type, kAlignment, kLanes, Element, 2> v01, Element v2, Element v3)
					: mVector(v01.mData[0], v01.mData[1], v2, v3)
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(float v0, I32x4<Type, kAlignment, kLanes, Element, 2> v12, Element v3)
					: mVector(v0, v12.mData[0], v12.mData[1], v3)
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(float v0, float v1, I32x4<Type, kAlignment, kLanes, Element, 2> v23)
					: mVector(v0, v1, v23.mData[0], v23.mData[1])
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(I32x4<Type, kAlignment, kLanes, Element, 2> v01, I32x4<Type, kAlignment, kLanes, Element, 2> v23)
					: mVector(v01.mData[0], v01.mData[1], v23.mData[0], v23.mData[1])
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(I32x4<Type, kAlignment, kLanes, Element, 3> v012, Element v3)
					: mVector(v012.mData[0], v012.mData[1], v012.mData[2], v3)
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Element v0, I32x4<Type, kAlignment, kLanes, Element, 3> v123)
					: mVector(v0, v123.mData[0], v123.mData[1], v123.mData[2])
				{
				}

				explicit constexpr I32x4(Type value) : mVector(value) {}

				I32x4& operator = (Type value) { mVector = value; return *this; }

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
			using I32x4_ = I32x4<int32x4, 16, 4, int32_t, COUNT>;


			//////////////////////////////////////////////////////////////////////////
			using I32x4_1 = I32x4<int32x4, 16, 4, int32_t, 1>;
			using I32x4_2 = I32x4<int32x4, 16, 4, int32_t, 2>;
			using I32x4_3 = I32x4<int32x4, 16, 4, int32_t, 3>;
			using I32x4_4 = I32x4<int32x4, 16, 4, int32_t, 4>;
		}
	}
}
