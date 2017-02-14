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
		class Vector3v
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using ElementType = typename SIMD_TYPE::ElementType;
			using DataType = typename SIMD_TYPE::ValueType;

			//////////////////////////////////////////////////////////////////////////
			Vector3v();
			explicit Vector3v(ElementType v);
			explicit Vector3v(const Vector2<ElementType>& xy, ElementType z);
			explicit Vector3v(ElementType x, const Vector2<ElementType>& yz);
			explicit Vector3v(ElementType x, ElementType y, ElementType z);
			Vector3v(const Vector3<ElementType>& rhs);
			Vector3v(const Vector3v& rhs);
			Vector3v(DataType value);

			//////////////////////////////////////////////////////////////////////////
			ElementType operator [](int idx) const;
			ElementType X() const;
			Vector3v& X(ElementType);
			ElementType Y() const;
			Vector3v& Y(ElementType);
			ElementType Z() const;
			Vector3v& Z(ElementType);

			//////////////////////////////////////////////////////////////////////////
			bool operator ==(const Vector3v& rhs) const;
			bool operator !=(const Vector3v& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3v operator -() const;
			Vector3v operator +(const Vector3v& rhs) const;
			Vector3v operator -(const Vector3v& rhs) const;
			Vector3v operator *(const ElementType rhs) const;
			Vector3v operator *(const Vector3v& rhs) const;
			Vector3v operator /(const ElementType rhs) const;
			Vector3v operator ^(const Vector3v& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3v& operator +=(const Vector3v& rhs);
			Vector3v& operator -=(const Vector3v& rhs);
			Vector3v& operator *=(const ElementType rhs);
			Vector3v& operator /=(const ElementType rhs);
			Vector3v& operator ^=(const Vector3v& rhs);

			//////////////////////////////////////////////////////////////////////////
			operator DataType() const;

			//////////////////////////////////////////////////////////////////////////
			static Vector3v<SIMD_TYPE> Zero();
			static Vector3v<SIMD_TYPE> XAxis();
			static Vector3v<SIMD_TYPE> YAxis();
			static Vector3v<SIMD_TYPE> ZAxis();

			//////////////////////////////////////////////////////////////////////////
			union
			{
				DataType mData;
				ElementType data[3];
				struct
				{
					ElementType x, y, z;
				};

				// Swizzles
				SWIZZLE2_XYZ(ElementType);
				SWIZZLE3_XYZ(ElementType);
				SWIZZLE4_XYZ(ElementType);
			};
		};

		//////////////////////////////////////////////////////////////////////////
		static_assert(sizeof(Vector3fv) == 4*sizeof(float), "Size of Vector4fv should be a simd vector.");
	}
}

#include <Math/Detail/Vector3v.inl>
