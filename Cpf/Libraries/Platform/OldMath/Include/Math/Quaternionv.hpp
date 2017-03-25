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
		class Quaternionv
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using ElementType = typename SIMD_TYPE::ElementType;
			using ValueType = typename SIMD_TYPE::ValueType;

			//////////////////////////////////////////////////////////////////////////
			Quaternionv();
			explicit Quaternionv(ElementType v);
			Quaternionv(const Vector3v<SIMD_TYPE>& xyz, ElementType _w);
			Quaternionv(ElementType _x, const Vector3v<SIMD_TYPE>& yzw);
			Quaternionv(const Vector2<ElementType>& xy, ElementType _z, ElementType _w);
			Quaternionv(ElementType _x, const Vector2<ElementType>& yz, ElementType _w);
			Quaternionv(ElementType _x, ElementType _y, const Vector2<ElementType>& zw);
			Quaternionv(const Vector2<ElementType>& xy, const Vector2<ElementType>& zw);
			Quaternionv(ElementType _x, ElementType _y, ElementType _z, ElementType _w);
			Quaternionv(const Quaternionv& rhs);
			Quaternionv(ValueType value);
			explicit Quaternionv(const Matrix33v<SIMD_TYPE>&);

			//////////////////////////////////////////////////////////////////////////
			ElementType operator [](int idx) const;
			float X() const;
			Quaternionv& X(float);
			float Y() const;
			Quaternionv& Y(float);
			float Z() const;
			Quaternionv& Z(float);
			float W() const;
			Quaternionv& W(float);

			//////////////////////////////////////////////////////////////////////////
			bool operator ==(const Quaternionv& rhs) const;
			bool operator !=(const Quaternionv& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Quaternionv operator -() const;
			Quaternionv operator +(const Quaternionv& rhs) const;
			Quaternionv operator -(const Quaternionv& rhs) const;
			Quaternionv operator *(const float rhs) const;
			Quaternionv operator *(const Quaternionv& rhs) const;
			Quaternionv operator /(const ElementType rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Quaternionv& operator +=(const Quaternionv& rhs);
			Quaternionv& operator -=(const Quaternionv& rhs);
			Quaternionv& operator *=(const ElementType rhs);
			Quaternionv& operator /=(const ElementType rhs);

			//////////////////////////////////////////////////////////////////////////
			operator ValueType() const;

			//////////////////////////////////////////////////////////////////////////
			static Quaternionv<SIMD_TYPE> AxisAngle(const Vector3fv& axis, ElementType angle);
			static Quaternionv<SIMD_TYPE> Identity();

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

		using Quaternionfv = Quaternionv<Simd::Float32x4>;
	}
}


#include <Math/Detail/Quaternionv.inl>
