//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Vector3.hpp"
#include <cmath>


namespace Cpf
{
	namespace Math
	{
		template<typename TYPE>
		Vector3<TYPE>::Vector3()
		{}

		template<typename TYPE>
		Vector3<TYPE>::Vector3(TYPE v)
			: x(v), y(v), z(v)
		{}

		template<typename TYPE>
		Vector3<TYPE>::Vector3(const Vector2<TYPE>& xy, TYPE _z)
			: x(xy.x), y(xy.y), z(_z)
		{}

		template<typename TYPE>
		Vector3<TYPE>::Vector3(TYPE _x, const Vector2<TYPE>& yz)
			: x(_x), y(yz.x), z(yz.y)
		{}

		template<typename TYPE>
		Vector3<TYPE>::Vector3(TYPE x, TYPE y, TYPE z)
			: x(x), y(y), z(z)
		{}

		template<typename TYPE>
		Vector3<TYPE>::Vector3(const Vector3<TYPE>& rhs)
			: x(rhs.x), y(rhs.y), z(rhs.z)
		{}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::operator =(const Vector3<TYPE>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		template<typename TYPE>
		TYPE Vector3<TYPE>::operator [](int idx) const
		{
			return reinterpret_cast<const TYPE* const>(this)[idx];
		}

		template<typename TYPE>
		TYPE Vector3<TYPE>::X() const
		{
			return x;
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::X(TYPE _x)
		{
			x = _x;
			return *this;
		}

		template<typename TYPE>
		TYPE Vector3<TYPE>::Y() const
		{
			return y;
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::Y(TYPE _y)
		{
			y = _y;
			return *this;
		}

		template<typename TYPE>
		TYPE Vector3<TYPE>::Z() const
		{
			return z;
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::Z(TYPE _z)
		{
			z = _z;
			return *this;
		}

		template<typename TYPE>
		bool Vector3<TYPE>::operator ==(const Vector3<TYPE>& rhs) const
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z);
		}

		template<typename TYPE>
		bool Vector3<TYPE>::operator !=(const Vector3<TYPE>& rhs) const
		{
			return (x != rhs.x || y != rhs.y || z != rhs.z);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::operator -() const
		{
			return Vector3(-x, -y, -z);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::operator +(const Vector3& rhs) const
		{
			return Vector3(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z
			);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::operator -(const Vector3<TYPE>& rhs) const
		{
			return Vector3<TYPE>(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z
				);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::operator *(const TYPE rhs) const
		{
			return Vector3<TYPE>(
				x*rhs,
				y*rhs,
				z*rhs
				);
		}

		template<typename TYPE>
		Vector3<TYPE> operator * (const TYPE lhs, const Vector3<TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::operator *(const Vector3<TYPE>& rhs) const
		{
			return Vector3<TYPE>(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z
				);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::operator /(const TYPE rhs) const
		{
			return Vector3(
				x / rhs,
				y / rhs,
				z / rhs
			);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::operator ^(const Vector3<TYPE>& rhs) const
		{
			return Vector3<TYPE>(
				y * rhs.z - rhs.y * z,
				z * rhs.x - rhs.z * x,
				x * rhs.y - rhs.x * y);
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::operator +=(const Vector3<TYPE>& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::operator -=(const Vector3<TYPE>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::operator *=(const TYPE rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::operator /=(const TYPE rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		template<typename TYPE>
		Vector3<TYPE>& Vector3<TYPE>::operator ^=(const Vector3<TYPE>& rhs)
		{
			*this = Vector3<TYPE>(
				y * rhs.z - z * rhs.y,
				z * rhs.x - x * rhs.z,
				x * rhs.y - y * rhs.x
				);
			return *this;
		}

		template<typename TYPE>
		Vector3<TYPE> Rotate(const Vector3<TYPE>& incident, const Vector3<TYPE>& axis, const TYPE angle)
		{
			TYPE	s = std::sin(angle);
			TYPE	c = std::cos(angle);

			Vector3<TYPE>	result;
			result.X((incident.X()*(axis.X()*axis.X()*(1 - c) + c) + incident.Y()*(axis.X()*axis.Y()*(1 - c) - axis.Z()*s) + incident.Z()*(axis.X()*axis.Z()*(1 - c) + axis.Y()*s)));
			result.Y((incident.X()*(axis.Y()*axis.X()*(1 - c) + axis.Z()*s) + incident.Y()*(axis.Y()*axis.Y()*(1 - c) + c) + incident.Z()*(axis.Y()*axis.Z()*(1 - c) - axis.X()*s)));
			result.Z((incident.X()*(axis.X()*axis.Z()*(1 - c) - axis.Y()*s) + incident.Y()*(axis.Y()*axis.Z()*(1 - c) + axis.X()*s) + incident.Z()*(axis.Z()*axis.Z()*(1 - c) + c)));

			return result;
		}

		template<typename TYPE>
		TYPE Magnitude(const Vector3<TYPE>& rhs)
		{
			return std::sqrt(
				rhs.X()*rhs.X() +
				rhs.Y()*rhs.Y() +
				rhs.Z()*rhs.Z()
			);
		}

		template<typename TYPE>
		TYPE MagnitudeSquared(const Vector3<TYPE>& rhs)
		{
			return
				rhs.X()*rhs.X() +
				rhs.Y()*rhs.Y() +
				rhs.Z()*rhs.Z();
		}

		template<typename TYPE>
		Vector3<TYPE> Normalize(const Vector3<TYPE>& rhs)
		{
			TYPE ooMag = 1.0f / Magnitude(rhs);
			return Vector3<TYPE>(
				rhs.X() * ooMag,
				rhs.Y() * ooMag,
				rhs.Z() * ooMag
				);
		}

		template<typename TYPE, typename LENGTH_TYPE = TYPE>
		Vector3<TYPE> NormalizeTo(const Vector3<TYPE>& rhs, const LENGTH_TYPE length)
		{
			LENGTH_TYPE ooMag = length / Magnitude(rhs);
			return Vector3<TYPE>(
				rhs.X() * ooMag,
				rhs.Y() * ooMag,
				rhs.Z() * ooMag
				);
		}

		template<typename TYPE>
		TYPE Dot(const Vector3<TYPE>& lhs, const Vector3<TYPE>& rhs)
		{
			return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
		}

		template<typename TYPE>
		Vector3<TYPE> Cross(const Vector3<TYPE>& lhs, const Vector3<TYPE>& rhs)
		{
			return lhs ^ rhs;
		}

		template<typename TYPE>
		Vector3<TYPE> Reflect(const Vector3<TYPE>& incident, const Vector3<TYPE>& axis)
		{
			const TYPE	dot2 = Dot(incident, axis) * 2.0f;
			return(dot2*axis - incident);
		}

		template<typename TYPE>
		Vector3<TYPE> Refract(const Vector3<TYPE>& incident, const Vector3<TYPE>& normal, const TYPE ior)
		{
			TYPE cosI = Dot(-normal, incident);
			TYPE sinT2 = ior*ior * (TYPE(1) - cosI * cosI);
			if (sinT2 > TYPE(1))
				return Vector3<TYPE>::kZero;
			return ior*incident - (ior + std::sqrt(TYPE(1) - sinT2)) * -normal;
		}

		template<typename TYPE>
		TYPE Distance(const Vector3<TYPE>& lhs, const Vector3<TYPE>& rhs)
		{
			return Magnitude(rhs - lhs);
		}

		template<typename TYPE>
		TYPE DistanceSquared(const Vector3<TYPE>& lhs, const Vector3<TYPE>& rhs)
		{
			return MagnitudeSquared(rhs - lhs);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::Zero()
		{
			return Vector3<TYPE>(0, 0, 0);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::XAxis()
		{
			return Vector3<TYPE>(1, 0, 0);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::YAxis()
		{
			return Vector3<TYPE>(0, 1, 0);
		}

		template<typename TYPE>
		Vector3<TYPE> Vector3<TYPE>::ZAxis()
		{
			return Vector3<TYPE>(0, 0, 1);
		}
	}
}
