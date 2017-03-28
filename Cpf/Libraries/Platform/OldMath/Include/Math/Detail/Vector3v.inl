//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"


namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v()
		{}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v(ElementType v)
			: mData(SIMD_TYPE::Create(v, v, v, ElementType(0)))
		{}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v(const Vector2<ElementType>& xy, ElementType _z)
			: mData(SIMD_TYPE::Create(xy.x, xy.y, _z, ElementType(0)))
		{}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v(ElementType _x, const Vector2<ElementType>& yz)
			: mData(SIMD_TYPE::Create(_x, yz.x, yz.y, ElementType(0)))
		{}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v(ElementType _x, ElementType _y, ElementType _z)
			: mData(SIMD_TYPE::Create(_x, _y, _z, ElementType(0)))
		{
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v(const Vector3<ElementType>& rhs)
			: mData(SIMD_TYPE::Create(rhs.x, rhs.y, rhs.z, ElementType(0)))
		{}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v(const Vector3v& rhs)
			: mData(rhs.mData)
		{
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::Vector3v(DataType value)
			: mData(value)
		{
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType Vector3v<SIMD_TYPE>::operator [](int idx) const
		{
			return data[idx];
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType Vector3v<SIMD_TYPE>::X() const
		{
			return SIMD_TYPE::GetLane(mData, 0);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::X(ElementType _x)
		{
			mData = SIMD_TYPE::SetLane(_x, mData, 0);
			return *this;
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType Vector3v<SIMD_TYPE>::Y() const
		{
			return SIMD_TYPE::GetLane(mData, 1);
		}

		template<typename SIMD_TYPE>  Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::Y(ElementType _y)
		{
			mData = SIMD_TYPE::SetLane(_y, mData, 1);
			return *this;
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType Vector3v<SIMD_TYPE>::Z() const
		{
			return SIMD_TYPE::GetLane(mData, 2);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::Z(ElementType _z)
		{
			mData = SIMD_TYPE::SetLane(_z, mData, 2);
			return *this;
		}

		template<typename SIMD_TYPE>
		bool Vector3v<SIMD_TYPE>::operator ==(const Vector3v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Equal(mData, rhs.mData);
		}

		template<typename SIMD_TYPE>
		bool Vector3v<SIMD_TYPE>::operator !=(const Vector3v<SIMD_TYPE>& rhs) const
		{
			return !SIMD_TYPE::Equal(mData, rhs.mData);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::operator -() const
		{
			return Vector3v(SIMD_TYPE::Negate3(mData));
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::operator +(const Vector3v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Add3(mData, rhs.mData);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::operator -(const Vector3v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Sub3(mData, rhs.mData);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::operator *(const ElementType rhs) const
		{
			typename SIMD_TYPE::ValueType temp = SIMD_TYPE::Create(rhs, rhs, rhs, ElementType(0));
			return SIMD_TYPE::Mul4(mData, temp);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> operator *(const typename SIMD_TYPE::ElementType lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::operator *(const Vector3v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Mul4(mData, rhs.mData);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::operator /(const ElementType rhs) const
		{
			return SIMD_TYPE::Div4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, ElementType(1)));
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::operator ^(const Vector3v<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Cross3(mData, rhs.mData);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::operator +=(const Vector3v<SIMD_TYPE>& rhs)
		{
			mData = SIMD_TYPE::Add3(mData, rhs.mData);
			return *this;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::operator -=(const Vector3v<SIMD_TYPE>& rhs)
		{
			mData = SIMD_TYPE::Sub3(mData, rhs.mData);
			return *this;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::operator *=(const ElementType rhs)
		{
			mData = SIMD_TYPE::Mul4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, ElementType(0)));
			return *this;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::operator /=(const ElementType rhs)
		{
			mData = SIMD_TYPE::Div4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, ElementType(1)));
			return *this;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>& Vector3v<SIMD_TYPE>::operator ^=(const Vector3v& rhs)
		{
			mData = SIMD_TYPE::Cross3(mData, rhs.mData);
			return *this;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Rotate(const Vector3v<SIMD_TYPE>& incident, const Vector3v<SIMD_TYPE>& axis, const typename SIMD_TYPE::ElementType angle)
		{
			typename SIMD_TYPE::ElementType s = std::sin(angle);
			typename SIMD_TYPE::ElementType c = std::cos(angle);

			Vector3v<SIMD_TYPE> result;
			result.X((incident.X()*(axis.X()*axis.X()*(1 - c) + c) + incident.Y()*(axis.X()*axis.Y()*(1 - c) - axis.Z()*s) + incident.Z()*(axis.X()*axis.Z()*(1 - c) + axis.Y()*s)));
			result.Y((incident.X()*(axis.Y()*axis.X()*(1 - c) + axis.Z()*s) + incident.Y()*(axis.Y()*axis.Y()*(1 - c) + c) + incident.Z()*(axis.Y()*axis.Z()*(1 - c) - axis.X()*s)));
			result.Z((incident.X()*(axis.X()*axis.Z()*(1 - c) - axis.Y()*s) + incident.Y()*(axis.Y()*axis.Z()*(1 - c) + axis.X()*s) + incident.Z()*(axis.Z()*axis.Z()*(1 - c) + c)));

			return result;
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType Magnitude(const Vector3v<SIMD_TYPE>& rhs)
		{
			return std::sqrt(Dot(rhs, rhs));
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType MagnitudeSquared(const Vector3v<SIMD_TYPE>& rhs)
		{
			return Dot(rhs, rhs);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Mod(const Vector3v<SIMD_TYPE>& lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return SIMD_TYPE::Mod3(lhs.mData, rhs.mData);
		}
		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Normalize(const Vector3v<SIMD_TYPE>& rhs)
		{
			typename SIMD_TYPE::ElementType ooMag = typename SIMD_TYPE::ElementType(1) / Magnitude(rhs);
			return rhs * ooMag;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> NormalizeTo(const Vector3v<SIMD_TYPE>& rhs, const typename SIMD_TYPE::ElementType length)
		{
			typename SIMD_TYPE::ElementType ooMag = length / Magnitude(rhs);
			return rhs * ooMag;
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType Dot(const Vector3v<SIMD_TYPE>& lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return SIMD_TYPE::Dot3(lhs, rhs);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Cross(const Vector3v<SIMD_TYPE>& lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return lhs ^ rhs;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Reflect(const Vector3v<SIMD_TYPE>& incident, const Vector3v<SIMD_TYPE>& axis)
		{
			const typename SIMD_TYPE::ElementType dot2 = Dot(incident, axis) * 2;
			return(dot2*axis - incident);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Refract(const Vector3v<SIMD_TYPE>& incident, const Vector3v<SIMD_TYPE>& normal, const typename SIMD_TYPE::ElementType ior)
		{
			typename SIMD_TYPE::ElementType cosI = Dot(-normal, incident);
			typename SIMD_TYPE::ElementType sinT2 = ior*ior * (1 - cosI * cosI);
			if (sinT2 > 1)
				return Vector3v<SIMD_TYPE>::kZero;
			return ior*incident - (ior + std::sqrt(1 - sinT2)) * -normal;
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType Distance(const Vector3v<SIMD_TYPE>& lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return Magnitude(rhs - lhs);
		}

		template<typename SIMD_TYPE>
		typename SIMD_TYPE::ElementType DistanceSquared(const Vector3v<SIMD_TYPE>& lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return MagnitudeSquared(rhs - lhs);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE>::operator DataType() const
		{
			return mData;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::Zero()
		{
			return Vector3v<SIMD_TYPE>(0, 0, 0);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::XAxis()
		{
			return Vector3v<SIMD_TYPE>(1, 0, 0);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::YAxis()
		{
			return Vector3v<SIMD_TYPE>(0, 1, 0);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Vector3v<SIMD_TYPE>::ZAxis()
		{
			return Vector3v<SIMD_TYPE>(0, 0, 1);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Min(const Vector3v<SIMD_TYPE>& lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return SIMD_TYPE::Min3(lhs, rhs);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Max(const Vector3v<SIMD_TYPE>& lhs, const Vector3v<SIMD_TYPE>& rhs)
		{
			return SIMD_TYPE::Max3(lhs, rhs);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> Clamp(const Vector3v<SIMD_TYPE>& v, const Vector3v<SIMD_TYPE>& l, const Vector3v<SIMD_TYPE>& h)
		{
			return SIMD_TYPE::Clamp3(v, l, h);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> operator /(const typename SIMD_TYPE::ElementType rhs, const Vector3v<SIMD_TYPE>& v)
		{
			return SIMD_TYPE::Div4(SIMD_TYPE::Create(rhs, rhs, rhs, typename SIMD_TYPE::ElementType(1)), v.mData);
		}
	}
}
