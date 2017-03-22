//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Detail/Swizzle2.hpp"
#include "Math/Detail/Swizzle3.hpp"
#include "Math/Detail/Swizzle4.hpp"

namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		class Vector3;
		class Half;

		//////////////////////////////////////////////////////////////////////////
		/// Base 4 unit vector.
		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		class Vector4
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using ElementType = TYPE;
			using ValueType = Vector4<TYPE>;

			//////////////////////////////////////////////////////////////////////////
			Vector4();
			Vector4(TYPE v);
			Vector4(const Vector3<TYPE>& v, TYPE _w);
			Vector4(TYPE _x, const Vector3<TYPE>& v);
			Vector4(const Vector2<TYPE>& v, TYPE _z, TYPE _w);
			Vector4(TYPE _x, const Vector2<TYPE>& v, TYPE _w);
			Vector4(TYPE _x, TYPE _y, const Vector2<TYPE>& v);
			Vector4(const Vector2<TYPE>& xy, const Vector2<TYPE>& zw);
			Vector4(TYPE _x, TYPE _y, TYPE _z, TYPE _w);
			Vector4(const Vector4& rhs);

			//////////////////////////////////////////////////////////////////////////
			Vector4& operator =(const Vector4& rhs);

			//////////////////////////////////////////////////////////////////////////
			TYPE& operator [](int idx);
			TYPE operator [](int idx) const;
			TYPE X() const;
			Vector4& X(TYPE);
			TYPE Y() const;
			Vector4& Y(TYPE);
			TYPE Z() const;
			Vector4& Z(TYPE);
			TYPE W() const;
			Vector4& W(TYPE);

			//////////////////////////////////////////////////////////////////////////
			bool operator ==(const Vector4& rhs) const;
			bool operator !=(const Vector4& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector4 operator -() const;
			Vector4 operator +(const Vector4& rhs) const;
			Vector4 operator -(const Vector4& rhs) const;
			Vector4 operator *(const TYPE rhs) const;
			Vector4 operator *(const Vector4& rhs) const;
			Vector4 operator /(const TYPE rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector4& operator +=(const Vector4& rhs);
			Vector4& operator -=(const Vector4& rhs);
			Vector4& operator *=(const TYPE rhs);
			Vector4& operator /=(const TYPE rhs);

			//////////////////////////////////////////////////////////////////////////
			static Vector4 XAxis();
			static Vector4 YAxis();
			static Vector4 ZAxis();
			static Vector4 WAxis();

			//////////////////////////////////////////////////////////////////////////
			union
			{
				struct
				{
					TYPE x, y, z, w;
				};
				TYPE data[4];

				// Swizzles
				SWIZZLE2_XYZW(TYPE);
				SWIZZLE3_XYZW(TYPE);
				SWIZZLE4_XYZW(TYPE);
			};
		};


		//////////////////////////////////////////////////////////////////////////
		typedef Vector4<Half> Vector4h;
		typedef Vector4<float> Vector4f;
		typedef Vector4<double> Vector4d;
	}
}


#include <Math/Detail/Vector4.inl>
