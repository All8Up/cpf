//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Vector2.hpp"
#include <cmath>


namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Vector2<TYPE>::Vector2()
		{}

		template<typename TYPE>
		Vector2<TYPE>::Vector2(TYPE v)
			: x(v), y(v)
		{}

		template<typename TYPE>
		Vector2<TYPE>::Vector2(TYPE _x, TYPE _y)
			: x(_x), y(_y)
		{}

		template<typename TYPE>
		Vector2<TYPE>::Vector2(const ValueType& rhs)
			: x(rhs.x), y(rhs.y)
		{}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType& Vector2<TYPE>::operator =(const ValueType& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		template<typename TYPE>
		TYPE Vector2<TYPE>::operator [](int idx) const
		{
			return reinterpret_cast<const TYPE* const>(this)[idx];
		}

		template<typename TYPE>
		bool Vector2<TYPE>::operator ==(const ValueType& rhs) const
		{
			return (x == rhs.x && y == rhs.y);
		}

		template<typename TYPE>
		bool Vector2<TYPE>::operator !=(const ValueType& rhs) const
		{
			return (x != rhs.x || y != rhs.y);
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType Vector2<TYPE>::operator -() const
		{
			return Vector2(-x, -y);
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType Vector2<TYPE>::operator +(const ValueType& rhs) const
		{
			return Vector2(
				x + rhs.x,
				y + rhs.y
			);
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType Vector2<TYPE>::operator -(const ValueType& rhs) const
		{
			return Vector2<TYPE>(
				x - rhs.x,
				y - rhs.y
				);
		}

		template<typename TYPE>
		template<typename RHSTYPE>
		typename Vector2<TYPE>::ValueType Vector2<TYPE>::operator *(const RHSTYPE rhs) const
		{
			return Vector2<TYPE>(
				TYPE(x*rhs),
				TYPE(y*rhs)
				);
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType operator * (const TYPE lhs, const Vector2<TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType Vector2<TYPE>::operator *(const ValueType& rhs) const
		{
			return Vector2<TYPE>(
				x * rhs.x,
				y * rhs.y
				);
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType Vector2<TYPE>::operator /(const TYPE rhs) const
		{
			return Vector2(
				x / rhs,
				y / rhs
			);
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType& Vector2<TYPE>::operator +=(const ValueType& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType& Vector2<TYPE>::operator -=(const ValueType& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType& Vector2<TYPE>::operator *=(const TYPE rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}

		template<typename TYPE>
		typename Vector2<TYPE>::ValueType& Vector2<TYPE>::operator /=(const TYPE rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}

		template<typename TYPE>
		TYPE Magnitude(const Vector2<TYPE>& rhs)
		{
			return std::sqrt(
				rhs.X()*rhs.X() +
				rhs.Y()*rhs.Y()
			);
		}

		template<typename TYPE>
		TYPE MagnitudeSquared(const Vector2<TYPE>& rhs)
		{
			return
				rhs.X()*rhs.X() +
				rhs.Y()*rhs.Y();
		}

		template<typename TYPE>
		Vector2<TYPE> Normalize(const Vector2<TYPE>& rhs)
		{
			TYPE ooMag = 1.0f / Magnitude(rhs);
			return Vector2<TYPE>(
				rhs.X() * ooMag,
				rhs.Y() * ooMag
				);
		}

		template<typename TYPE, typename LENGTH_TYPE = TYPE>
		Vector2<TYPE> NormalizeTo(const Vector2<TYPE>& rhs, const LENGTH_TYPE length)
		{
			LENGTH_TYPE ooMag = length / Magnitude(rhs);
			return Vector2<TYPE>(
				rhs.X() * ooMag,
				rhs.Y() * ooMag
				);
		}

		template<typename TYPE>
		TYPE Dot(const Vector2<TYPE>& lhs, const Vector2<TYPE>& rhs)
		{
			return lhs * rhs;
		}

		template<typename TYPE>
		Vector2<TYPE> Reflect(const Vector2<TYPE>& incident, const Vector2<TYPE>& axis)
		{
			const TYPE	dot2 = incident * axis * 2.0f;
			return(dot2*axis - incident);
		}

		template<typename TYPE>
		TYPE Distance(const Vector2<TYPE>& lhs, const Vector2<TYPE>& rhs)
		{
			return Magnitude(rhs - lhs);
		}

		template<typename TYPE>
		TYPE DistanceSquared(const Vector2<TYPE>& lhs, const Vector2<TYPE>& rhs)
		{
			return MagnitudeSquared(rhs - lhs);
		}

		template<typename TYPE>
		Vector2<TYPE> ElementMultiply(const Vector2<TYPE>& lhs, const Vector2<TYPE>& rhs)
		{
			return Vector2<TYPE>(
				lhs.X() * rhs.X(),
				lhs.Y() * rhs.Y()
				);
		}
	}
}
