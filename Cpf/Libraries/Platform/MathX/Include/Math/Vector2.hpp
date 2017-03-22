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
		/// Base 2 unit vector.
		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		class Vector2
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using ElementType = TYPE;
			using ValueType = Vector2<TYPE>;

			//////////////////////////////////////////////////////////////////////////
			Vector2();
			explicit Vector2(TYPE v);
			explicit Vector2(TYPE x, TYPE y);
			Vector2(const ValueType& rhs);

			//////////////////////////////////////////////////////////////////////////
			ValueType& operator =(const ValueType& rhs);

			//////////////////////////////////////////////////////////////////////////
			TYPE operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			bool operator ==(const ValueType& rhs) const;
			bool operator !=(const ValueType& rhs) const;

			//////////////////////////////////////////////////////////////////////////
			ValueType operator -() const;
			ValueType operator +(const ValueType& rhs) const;
			ValueType operator -(const ValueType& rhs) const;
			template<typename RHSTYPE>
			ValueType operator *(const RHSTYPE rhs) const;
			ValueType operator *(const ValueType& rhs) const;
			ValueType operator /(const TYPE rhs) const;

			//////////////////////////////////////////////////////////////////////////
			ValueType& operator +=(const ValueType& rhs);
			ValueType& operator -=(const ValueType& rhs);
			ValueType& operator *=(const TYPE rhs);
			ValueType& operator /=(const TYPE rhs);

			//////////////////////////////////////////////////////////////////////////
			static Vector2<TYPE> Zero() { return Vector2<TYPE>(TYPE(0), TYPE(0)); }

			//////////////////////////////////////////////////////////////////////////
			union
			{
				struct
				{
					TYPE x, y;
				};
				TYPE data[2];

				// Swizzles
				SWIZZLE2_XY(TYPE);
				SWIZZLE3_XY(TYPE);
				SWIZZLE4_XY(TYPE);
			};
		};
		static_assert(sizeof(Vector2f)==sizeof(float)*2, "Incorrect size.");
	}
}

//////////////////////////////////////////////////////////////////////////
#include "Math/Detail/Vector2.inl"
#include "Math/Detail/Swizzle2.inl"
#include "Math/Detail/Swizzle3.inl"
#include "Math/Detail/Swizzle4.inl"
