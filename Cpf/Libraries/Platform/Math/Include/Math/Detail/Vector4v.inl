//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "Math/Vector4v.hpp"
#include <cmath>


namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>::Vector4v()
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(ElementType v)
			: mData(SIMD_TYPE::Create(v, v, v, v))
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(const Vector3v<SIMD_TYPE>& xyz, ElementType _w)
			: mData(SIMD_TYPE::Create(xyz.x, xyz.y, xyz.z, _w))
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(ElementType _x, const Vector3v<SIMD_TYPE>& yzw)
			: mData(SIMD_TYPE::Create(_x, yzw.x, yzw.y, yzw.z))
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(const Vector2<ElementType>& xy, const Vector2<ElementType>& zw)
			: mData(SIMD_TYPE::Create(xy.x, xy.y, zw.x, zw.y))
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(const Vector2<ElementType>& xy, ElementType _z, ElementType _w)
			: mData(SIMD_TYPE::Create(xy.x, xy.y, _z, _w))
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(ElementType _x, const Vector2<ElementType>& yz, ElementType _w)
			: mData(SIMD_TYPE::Create(_x, yz.x, yz.y, _w))
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(ElementType _x, ElementType _y, const Vector2<ElementType>& zw)
			: mData(SIMD_TYPE::Create(_x, _y, zw.x, zw.y))
		{}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::Vector4v(ElementType _x, ElementType _y, ElementType _z, ElementType _w)
			: mData(SIMD_TYPE::Create(_x, _y, _z, _w))
		{}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>::Vector4v(const Vector4v& rhs)
			: mData(rhs.mData)
		{
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>::Vector4v(typename SIMD_TYPE::ValueType value)
			: mData(value)
		{
		}

		template<typename SIMD_TYPE>
		typename Vector4v<SIMD_TYPE>::ElementType & Vector4v<SIMD_TYPE>::operator [](int idx)
		{
			return data[idx];
		}

		template<typename SIMD_TYPE>
		typename Vector4v<SIMD_TYPE>::ElementType Vector4v<SIMD_TYPE>::operator [](int idx) const
		{
			return data[idx];
		}

		template<typename SIMD_TYPE> float Vector4v<SIMD_TYPE>::X() const
		{
			return SIMD_TYPE::GetLane(mData, 0);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::X(float _x)
		{
			mData = SIMD_TYPE::SetLane(_x, mData, 0);
			return *this;
		}

		template<typename SIMD_TYPE> float Vector4v<SIMD_TYPE>::Y() const
		{
			return SIMD_TYPE::GetLane(mData, 1);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::Y(float _y)
		{
			mData = SIMD_TYPE::SetLane(_y, mData, 1);
			return *this;
		}

		template<typename SIMD_TYPE> float Vector4v<SIMD_TYPE>::Z() const
		{
			return SIMD_TYPE::GetLane(mData, 2);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::Z(float _z)
		{
			mData = SIMD_TYPE::SetLane(_z, mData, 2);
			return *this;
		}

		template<typename SIMD_TYPE> float Vector4v<SIMD_TYPE>::W() const
		{
			return SIMD_TYPE::GetLane(mData, 3);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::W(float _w)
		{
			mData = SIMD_TYPE::SetLane(_w, mData, 3);
			return *this;
		}

		template<typename SIMD_TYPE> bool Vector4v<SIMD_TYPE>::operator ==(const Vector4v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Equal(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> bool Vector4v<SIMD_TYPE>::operator !=(const Vector4v<SIMD_TYPE>& rhs) const
		{
			return !SIMD_TYPE::Equal(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::operator -() const
		{
			return Vector4v(SIMD_TYPE::Negate4(mData));
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::operator +(const Vector4v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Add4(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::operator -(const Vector4v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Sub4(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::operator *(const float rhs) const
		{
			typename SIMD_TYPE::ValueType temp = SIMD_TYPE::Create(rhs, rhs, rhs, rhs);
			return SIMD_TYPE::Mul4(mData, temp);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> operator *(const float lhs, const Vector4v<SIMD_TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::operator *(const Vector4v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Mul4(mData, rhs.mData);
		}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::operator /(const ElementType rhs) const
		{
			return SIMD_TYPE::Div4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, rhs));
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::operator +=(const Vector4v<SIMD_TYPE>& rhs)
		{
			mData = SIMD_TYPE::Add4(mData, rhs.mData);
			return *this;
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::operator -=(const Vector4v<SIMD_TYPE>& rhs)
		{
			mData = SIMD_TYPE::Sub4(mData, rhs.mData);
			return *this;
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::operator *=(const ElementType rhs)
		{
			mData = SIMD_TYPE::Mul4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, rhs));
			return *this;
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE>& Vector4v<SIMD_TYPE>::operator /=(const ElementType rhs)
		{
			mData = SIMD_TYPE::Div4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, rhs));
			return *this;
		}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE>::operator ValueType() const
		{
			return mData;
		}

		template<typename SIMD_TYPE> float Magnitude(const Vector4v<SIMD_TYPE>& rhs)
		{
			return std::sqrt(Dot(rhs, rhs));
		}

		template<typename SIMD_TYPE> float MagnitudeSquared(const Vector4v<SIMD_TYPE>& rhs)
		{
			return Dot(rhs, rhs);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Normalize(const Vector4v<SIMD_TYPE>& rhs)
		{
			float ooMag = typename SIMD_TYPE::ElementType(1) / Magnitude(rhs);
			return rhs * ooMag;
		}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE> NormalizeTo(const Vector4v<SIMD_TYPE>& rhs, const typename SIMD_TYPE::ElementType length)
		{
			typename SIMD_TYPE::ElementType ooMag = length / Magnitude(rhs);
			return rhs * ooMag;
		}

		template<typename SIMD_TYPE> float Dot(const Vector4v<SIMD_TYPE>& lhs, const Vector4v<SIMD_TYPE>& rhs)
		{
			return SIMD_TYPE::Dot4(lhs, rhs);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Cross(const Vector4v<SIMD_TYPE>& lhs, const Vector4v<SIMD_TYPE>& rhs)
		{
			return lhs ^ rhs;
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Reflect(const Vector4v<SIMD_TYPE>& incident, const Vector4v<SIMD_TYPE>& axis)
		{
			const float	dot2 = Dot(incident, axis) * 2.0f;
			return(dot2*axis - incident);
		}

		template<typename SIMD_TYPE> Vector4v<SIMD_TYPE> Refract(const Vector4v<SIMD_TYPE>& incident, const Vector4v<SIMD_TYPE>& normal, const float ior)
		{
			float cosI = Dot(-normal, incident);
			float sinT2 = ior*ior * (1.0f - cosI * cosI);
			if (sinT2 > 1.0f)
				return Vector4v<SIMD_TYPE>::kZero;
			return ior*incident - (ior + std::sqrt(1.0f - sinT2)) * -normal;
		}

		template<typename SIMD_TYPE> float Distance(const Vector4v<SIMD_TYPE>& lhs, const Vector4v<SIMD_TYPE>& rhs)
		{
			return Magnitude(rhs - lhs);
		}

		template<typename SIMD_TYPE> float DistanceSquared(const Vector4v<SIMD_TYPE>& lhs, const Vector4v<SIMD_TYPE>& rhs)
		{
			return MagnitudeSquared(rhs - lhs);
		}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::XAxis()
		{
			return Vector4v<SIMD_TYPE>(1, 0, 0, 0);
		}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::YAxis()
		{
			return Vector4v<SIMD_TYPE>(0, 1, 0, 0);
		}

		template<typename SIMD_TYPE>
		Vector4v<SIMD_TYPE> Vector4v<SIMD_TYPE>::ZAxis()
		{
			return Vector4v<SIMD_TYPE>(0, 0, 1, 0);
		}
	}
}
