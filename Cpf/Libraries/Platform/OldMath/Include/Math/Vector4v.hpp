//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"
#include "Math/Detail/Swizzle2.hpp"
#include "Math/Detail/Swizzle3.hpp"
#include "Math/Detail/Swizzle4.hpp"

namespace Cpf
{
	namespace Math
	{
		template< typename SIMD_TYPE >
		class Vector4v
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using ElementType = typename SIMD_TYPE::ElementType;
			using ValueType = typename SIMD_TYPE::ValueType;

			//////////////////////////////////////////////////////////////////////////
			Vector4v();
			Vector4v(ElementType v);
			Vector4v(const Vector3v<SIMD_TYPE>& xyz, ElementType _w);
			Vector4v(ElementType _x, const Vector3v<SIMD_TYPE>& yzw);
			Vector4v(const Vector2<ElementType>& xy, ElementType _z, ElementType _w);
			Vector4v(ElementType _x, const Vector2<ElementType>& yz, ElementType _w);
			Vector4v(ElementType _x, ElementType _y, const Vector2<ElementType>& zw);
			Vector4v(const Vector2<ElementType>& xy, const Vector2<ElementType>& zw);
			Vector4v(ElementType _x, ElementType _y, ElementType _z, ElementType _w);
			Vector4v(const Vector4v& rhs);
			Vector4v(ValueType value);

			//////////////////////////////////////////////////////////////////////////
			ElementType& operator [](int idx);
			ElementType operator [](int idx) const;
			float X() const;
			Vector4v& X(float);
			float Y() const;
			Vector4v& Y(float);
			float Z() const;
			Vector4v& Z(float);
			float W() const;
			Vector4v& W(float);

			//////////////////////////////////////////////////////////////////////////
			bool operator ==(const Vector4v& rhs) const;
			bool operator !=(const Vector4v& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector4v operator -() const;
			Vector4v operator +(const Vector4v& rhs) const;
			Vector4v operator -(const Vector4v& rhs) const;
			Vector4v operator *(const float rhs) const;
			Vector4v operator *(const Vector4v& rhs) const;
			Vector4v operator /(const ElementType rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector4v& operator +=(const Vector4v& rhs);
			Vector4v& operator -=(const Vector4v& rhs);
			Vector4v& operator *=(const ElementType rhs);
			Vector4v& operator /=(const ElementType rhs);

			//////////////////////////////////////////////////////////////////////////
			operator ValueType() const;

			//////////////////////////////////////////////////////////////////////////
			static Vector4v<SIMD_TYPE> XAxis();
			static Vector4v<SIMD_TYPE> YAxis();
			static Vector4v<SIMD_TYPE> ZAxis();

			//////////////////////////////////////////////////////////////////////////
			union
			{
				ValueType mData;
				ElementType data[4];
				struct
				{
					ElementType x, y, z, w;
				};
				// Swizzles
				SWIZZLE2_XYZW(ElementType);
				SWIZZLE3_XYZW(ElementType);
				SWIZZLE4_XYZW(ElementType);
			};
		};
	}
}


#include <Math/Detail/Vector4v.inl>
