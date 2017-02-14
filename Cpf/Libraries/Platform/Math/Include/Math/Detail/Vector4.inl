//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Vector4.hpp"
#include <cmath>


namespace Cpf
{
	namespace Math
	{
		template<typename TYPE>
		Vector4<TYPE>::Vector4()
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(TYPE v)
			: x(v), y(v), z(v), w(v)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(TYPE _x, TYPE _y, TYPE _z, TYPE _w)
			: x(_x), y(_y), z(_z), w(_w)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(const Vector3<TYPE>& v, TYPE _w)
			: x(v.X()), y(v.Y()), z(v.Z()), w(_w)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(TYPE _x, const Vector3<TYPE>& v)
			: x(_x), y(v.x), z(v.y), w(v.z)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(const Vector2<TYPE>& v, TYPE _z, TYPE _w)
			: x(v.x), y(v.y), z(_z), w(_w)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(TYPE _x, const Vector2<TYPE>& v, TYPE _w)
			: x(_x), y(v.x), z(v.y), w(_w)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(TYPE _x, TYPE _y, const Vector2<TYPE>& v)
			: x(_x), y(_y), z(v.x), w(v.y)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(const Vector2<TYPE>& xy, const Vector2<TYPE>& zw)
			: x(xy.x), y(xy.y), z(zw.x), w(zw.y)
		{}

		template<typename TYPE>
		Vector4<TYPE>::Vector4(const Vector4<TYPE>& rhs)
			: x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
		{}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::operator =(const Vector4<TYPE>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}

		template<typename TYPE>
		TYPE& Vector4<TYPE>::operator [](int idx)
		{
			return reinterpret_cast<TYPE*>(this)[idx];
		}

		template<typename TYPE>
		TYPE Vector4<TYPE>::operator [](int idx) const
		{
			return reinterpret_cast<const TYPE* const>(this)[idx];
		}

		template<typename TYPE>
		TYPE Vector4<TYPE>::X() const
		{
			return x;
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::X(TYPE _x)
		{
			x = _x;
			return *this;
		}

		template<typename TYPE>
		TYPE Vector4<TYPE>::Y() const
		{
			return y;
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::Y(TYPE _y)
		{
			y = _y;
			return *this;
		}

		template<typename TYPE>
		TYPE Vector4<TYPE>::Z() const
		{
			return z;
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::Z(TYPE _z)
		{
			z = _z;
			return *this;
		}

		template<typename TYPE>
		TYPE Vector4<TYPE>::W() const
		{
			return w;
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::W(TYPE _w)
		{
			w = _w;
			return *this;
		}

		template<typename TYPE>
		bool Vector4<TYPE>::operator ==(const Vector4<TYPE>& rhs) const
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
		}

		template<typename TYPE>
		bool Vector4<TYPE>::operator !=(const Vector4<TYPE>& rhs) const
		{
			return (x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::operator -() const
		{
			return Vector4(-x, -y, -z, -w);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::operator +(const Vector4& rhs) const
		{
			return Vector4(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z,
				w + rhs.w
			);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::operator -(const Vector4<TYPE>& rhs) const
		{
			return Vector4<TYPE>(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z,
				w - rhs.w
				);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::operator *(const TYPE rhs) const
		{
			return Vector4<TYPE>(
				x*rhs,
				y*rhs,
				z*rhs,
				w*rhs
				);
		}

		template<typename TYPE>
		Vector4<TYPE> operator * (const TYPE lhs, const Vector4<TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::operator *(const Vector4<TYPE>& rhs) const
		{
			return Vector4<TYPE>(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z,
				w * rhs.w);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::operator /(const TYPE rhs) const
		{
			return Vector4(
				x / rhs,
				y / rhs,
				z / rhs,
				w / rhs
			);
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::operator +=(const Vector4<TYPE>& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::operator -=(const Vector4<TYPE>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::operator *=(const TYPE rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;
			return *this;
		}

		template<typename TYPE>
		Vector4<TYPE>& Vector4<TYPE>::operator /=(const TYPE rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
			return *this;
		}

		template<typename TYPE>
		TYPE Magnitude(const Vector4<TYPE>& rhs)
		{
			return std::sqrt(
				rhs.X()*rhs.X() +
				rhs.Y()*rhs.Y() +
				rhs.Z()*rhs.Z() +
				rhs.W()*rhs.W()
			);
		}

		template<typename TYPE>
		TYPE MagnitudeSquared(const Vector4<TYPE>& rhs)
		{
			return
				rhs.X()*rhs.X() +
				rhs.Y()*rhs.Y() +
				rhs.Z()*rhs.Z() +
				rhs.W()*rhs.W();
		}

		template<typename TYPE>
		Vector4<TYPE> Normalize(const Vector4<TYPE>& rhs)
		{
			TYPE ooMag = 1.0f / Magnitude(rhs);
			return Vector4<TYPE>(
				rhs.X() * ooMag,
				rhs.Y() * ooMag,
				rhs.Z() * ooMag,
				rhs.W() * ooMag
				);
		}

		template<typename TYPE, typename LENGTH_TYPE = TYPE>
		Vector4<TYPE> NormalizeTo(const Vector4<TYPE>& rhs, const LENGTH_TYPE length)
		{
			LENGTH_TYPE ooMag = length / Magnitude(rhs);
			return Vector4<TYPE>(
				rhs.X() * ooMag,
				rhs.Y() * ooMag,
				rhs.Z() * ooMag,
				rhs.W() * ooMag
				);
		}

		template<typename TYPE>
		TYPE Dot(const Vector4<TYPE>& lhs, const Vector4<TYPE>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}

		template<typename TYPE>
		Vector4<TYPE> Reflect(const Vector4<TYPE>& incident, const Vector4<TYPE>& axis)
		{
			const TYPE	dot2 = Dot(incident, axis) * 2.0f;
			return(dot2*axis - incident);
		}

		template<typename TYPE>
		Vector4<TYPE> Refract(const Vector4<TYPE>& incident, const Vector4<TYPE>& normal, const TYPE ior)
		{
			TYPE cosI = Dot(-normal, incident);
			TYPE sinT2 = ior*ior * (TYPE(1) - cosI * cosI);
			if (sinT2 > TYPE(1))
				return Vector4<TYPE>::kZero;
			return ior*incident - (ior + std::sqrt(TYPE(1) - sinT2)) * -normal;
		}

		template<typename TYPE>
		TYPE Distance(const Vector4<TYPE>& lhs, const Vector4<TYPE>& rhs)
		{
			return Magnitude(rhs - lhs);
		}

		template<typename TYPE>
		TYPE DistanceSquared(const Vector4<TYPE>& lhs, const Vector4<TYPE>& rhs)
		{
			return MagnitudeSquared(rhs - lhs);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::XAxis()
		{
			return Vector4<TYPE>(1, 0, 0, 0);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::YAxis()
		{
			return Vector4<TYPE>(0, 1, 0, 0);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::ZAxis()
		{
			return Vector4<TYPE>(0, 0, 1, 0);
		}

		template<typename TYPE>
		Vector4<TYPE> Vector4<TYPE>::WAxis()
		{
			return Vector4<TYPE>(0, 0, 0, 1);
		}
	}
}
