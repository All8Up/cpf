//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Detail/Swizzle2.hpp"
#include "Math/Detail/Swizzle3.hpp"
#include "Math/Detail/Swizzle4.hpp"
#include "Math/Detail/SwizzleMacros.hpp"

namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		class Vector4;
		class Half;

		//////////////////////////////////////////////////////////////////////////
		/// Base 3 unit vector.
		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		class Vector3
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using ElementType = TYPE;
			using ValueType = Vector3<TYPE>;

			//////////////////////////////////////////////////////////////////////////
			Vector3();
			explicit Vector3(TYPE v);
			explicit Vector3(const Vector2<TYPE>& xy, TYPE _z);
			explicit Vector3(TYPE _x, const Vector2<TYPE>& yz);
			Vector3(TYPE _x, TYPE _y, TYPE _z);
			Vector3(const Vector3& rhs);

			//////////////////////////////////////////////////////////////////////////
			Vector3& operator =(const Vector3& rhs);

			//////////////////////////////////////////////////////////////////////////
			TYPE operator [](int idx) const;
			TYPE X() const;
			Vector3& X(TYPE);
			TYPE Y() const;
			Vector3& Y(TYPE);
			TYPE Z() const;
			Vector3& Z(TYPE);

			//////////////////////////////////////////////////////////////////////////
			bool operator ==(const Vector3& rhs) const;
			bool operator !=(const Vector3& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3 operator -() const;
			Vector3 operator +(const Vector3& rhs) const;
			Vector3 operator -(const Vector3& rhs) const;
			Vector3 operator *(const TYPE rhs) const;
			Vector3 operator *(const Vector3& rhs) const;
			Vector3 operator /(const TYPE rhs) const;
			Vector3 operator ^(const Vector3& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3& operator +=(const Vector3& rhs);
			Vector3& operator -=(const Vector3& rhs);
			Vector3& operator *=(const TYPE rhs);
			Vector3& operator /=(const TYPE rhs);
			Vector3& operator ^=(const Vector3& rhs);

			//////////////////////////////////////////////////////////////////////////
			static Vector3 Zero();
			static Vector3 XAxis();
			static Vector3 YAxis();
			static Vector3 ZAxis();

			//////////////////////////////////////////////////////////////////////////
			union
			{
				struct
				{
					TYPE x, y, z;
				};
				TYPE data[3];

				// Swizzles
				SWIZZLE2_XYZ(TYPE);
				SWIZZLE3_XYZ(TYPE);
				SWIZZLE4_XYZ(TYPE);
			};
		};


		//////////////////////////////////////////////////////////////////////////
		using Vector3h = Vector3<Half>;
		using Vector3f = Vector3<float>;
		using Vector3d = Vector3<double>;
		using Vector3i = Vector3<int32_t>;
	}
}

#include <Math/Detail/Vector3.inl>
