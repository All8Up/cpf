//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "Math/Quaternionv.hpp"
#include "Math/Vector3v.hpp"
#include <cmath>


namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>::Quaternionv()
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(ElementType v)
			: mData(SIMD_TYPE::Create(v, v, v, v))
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(const Vector3v<SIMD_TYPE>& xyz, ElementType _w)
			: mData(SIMD_TYPE::Create(xyz.x, xyz.y, xyz.z, _w))
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(ElementType _x, const Vector3v<SIMD_TYPE>& yzw)
			: mData(SIMD_TYPE::Create(_x, yzw.x, yzw.y, yzw.z))
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(const Vector2<ElementType>& xy, const Vector2<ElementType>& zw)
			: mData(SIMD_TYPE::Create(xy.x, xy.y, zw.x, zw.y))
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(const Vector2<ElementType>& xy, ElementType _z, ElementType _w)
			: mData(SIMD_TYPE::Create(xy.x, xy.y, _z, _w))
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(ElementType _x, const Vector2<ElementType>& yz, ElementType _w)
			: mData(SIMD_TYPE::Create(_x, yz.x, yz.y, _w))
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(ElementType _x, ElementType _y, const Vector2<ElementType>& zw)
			: mData(SIMD_TYPE::Create(_x, _y, zw.x, zw.y))
		{}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(ElementType _x, ElementType _y, ElementType _z, ElementType _w)
			: mData(SIMD_TYPE::Create(_x, _y, _z, _w))
		{}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>::Quaternionv(const Quaternionv& rhs)
			: mData(rhs.mData)
		{
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>::Quaternionv(typename SIMD_TYPE::ValueType value)
			: mData(value)
		{
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::Quaternionv(const Matrix33v<SIMD_TYPE>& r)
		{
			using type = ElementType;
			Matrix33v<SIMD_TYPE> rhs = Transpose(r);
			type trace = rhs[0][0] + rhs[1][1] + rhs[2][2];
			if (trace > type(0))
			{
				type s = type(0.5) / sqrtf(trace + type(1));
				w = type(0.25) / s;
				x = (rhs[2][1] - rhs[1][2]) * s;
				y = (rhs[0][2] - rhs[2][0]) * s;
				z = (rhs[1][0] - rhs[0][1]) * s;
			}
			else if ((rhs[0][0] > rhs[1][1]) && (rhs[0][0] > rhs[2][2]))
			{
				type s = type(2) * sqrtf(type(1) + rhs[0][0] - rhs[1][1] - rhs[2][2]);
				x = type(0.25) * s;
				w = (rhs[2][1] - rhs[1][2]) / s;
				y = (rhs[0][1] + rhs[1][0]) / s;
				z = (rhs[0][2] + rhs[2][0]) / s;
			}
			else if (rhs[1][1] > rhs[2][2])
			{
				type s = type(2) * sqrtf(type(1) + rhs[1][1] - rhs[0][0] - rhs[2][2]);
				w = (rhs[0][2] - rhs[2][0]) / s;
				x = (rhs[0][1] + rhs[1][0]) / s;
				z = (rhs[1][2] + rhs[2][1]) / s;
				y = type(0.25) * s;
			}
			else
			{
				type s = type(2) * sqrtf(type(1) + rhs[2][2] - rhs[0][0] - rhs[1][1]);
				w = (rhs[1][0] - rhs[0][1]) / s;
				x = (rhs[0][2] + rhs[2][0]) / s;
				y = (rhs[1][2] + rhs[2][1]) / s;
				z = type(0.25) * s;
			}
		}

		template<typename SIMD_TYPE>
		typename Quaternionv<SIMD_TYPE>::ElementType Quaternionv<SIMD_TYPE>::operator [](int idx) const
		{
			return data[idx];
		}

		template<typename SIMD_TYPE> float Quaternionv<SIMD_TYPE>::X() const
		{
			return SIMD_TYPE::GetLane(mData, 0);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::X(float _x)
		{
			mData = SIMD_TYPE::SetLane(_x, mData, 0);
			return *this;
		}

		template<typename SIMD_TYPE> float Quaternionv<SIMD_TYPE>::Y() const
		{
			return SIMD_TYPE::GetLane(mData, 1);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::Y(float _y)
		{
			mData = SIMD_TYPE::SetLane(_y, mData, 1);
			return *this;
		}

		template<typename SIMD_TYPE> float Quaternionv<SIMD_TYPE>::Z() const
		{
			return SIMD_TYPE::GetLane(mData, 2);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::Z(float _z)
		{
			mData = SIMD_TYPE::SetLane(_z, mData, 2);
			return *this;
		}

		template<typename SIMD_TYPE> float Quaternionv<SIMD_TYPE>::W() const
		{
			return SIMD_TYPE::GetLane(mData, 3);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::W(float _w)
		{
			mData = SIMD_TYPE::SetLane(_w, mData, 3);
			return *this;
		}

		template<typename SIMD_TYPE> bool Quaternionv<SIMD_TYPE>::operator ==(const Quaternionv<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Equal(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> bool Quaternionv<SIMD_TYPE>::operator !=(const Quaternionv<SIMD_TYPE>& rhs) const
		{
			return !SIMD_TYPE::Equal(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::operator -() const
		{
			return Quaternionv(SIMD_TYPE::Negate4(mData));
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::operator +(const Quaternionv<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Add4(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::operator -(const Quaternionv<SIMD_TYPE>& rhs) const
		{
			return SIMD_TYPE::Sub4(mData, rhs.mData);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::operator *(const float rhs) const
		{
			typename SIMD_TYPE::ValueType temp = SIMD_TYPE::Create(rhs, rhs, rhs, rhs);
			return SIMD_TYPE::Mul4(mData, temp);
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE> operator *(const float lhs, const Quaternionv<SIMD_TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::operator *(const Quaternionv<SIMD_TYPE>& rhs) const
		{
			return Quaternionv<SIMD_TYPE>(
				+(*this)[0] * rhs[3] + (*this)[1] * rhs[2] - (*this)[2] * rhs[1] + (*this)[3] * rhs[0],
				-(*this)[0] * rhs[2] + (*this)[1] * rhs[3] + (*this)[2] * rhs[0] + (*this)[3] * rhs[1],
				+(*this)[0] * rhs[1] - (*this)[1] * rhs[0] + (*this)[2] * rhs[3] + (*this)[3] * rhs[2],
				-(*this)[0] * rhs[0] - (*this)[1] * rhs[1] - (*this)[2] * rhs[2] + (*this)[3] * rhs[3]);
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::operator /(const ElementType rhs) const
		{
			return SIMD_TYPE::Div4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, rhs));
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::operator +=(const Quaternionv<SIMD_TYPE>& rhs)
		{
			mData = SIMD_TYPE::Add4(mData, rhs.mData);
			return *this;
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::operator -=(const Quaternionv<SIMD_TYPE>& rhs)
		{
			mData = SIMD_TYPE::Sub4(mData, rhs.mData);
			return *this;
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::operator *=(const ElementType rhs)
		{
			mData = SIMD_TYPE::Mul4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, rhs));
			return *this;
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE>& Quaternionv<SIMD_TYPE>::operator /=(const ElementType rhs)
		{
			mData = SIMD_TYPE::Div4(mData, SIMD_TYPE::Create(rhs, rhs, rhs, rhs));
			return *this;
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE>::operator ValueType() const
		{
			return mData;
		}

		template<typename SIMD_TYPE> float Magnitude(const Quaternionv<SIMD_TYPE>& rhs)
		{
			return std::sqrt(Dot(rhs, rhs));
		}

		template<typename SIMD_TYPE> float MagnitudeSquared(const Quaternionv<SIMD_TYPE>& rhs)
		{
			return rhs * rhs;
		}

		template<typename SIMD_TYPE> Quaternionv<SIMD_TYPE> Normalize(const Quaternionv<SIMD_TYPE>& rhs)
		{
			float ooMag = typename SIMD_TYPE::ElementType(1) / Magnitude(rhs);
			return rhs * ooMag;
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE> NormalizeTo(const Quaternionv<SIMD_TYPE>& rhs, const typename SIMD_TYPE::ElementType length)
		{
			typename SIMD_TYPE::ElementType ooMag = length / Magnitude(rhs);
			return rhs * ooMag;
		}

		template<typename SIMD_TYPE> float Dot(const Quaternionv<SIMD_TYPE>& lhs, const Quaternionv<SIMD_TYPE>& rhs)
		{
			return SIMD_TYPE::Dot4(lhs, rhs);
		}

		template<typename SIMD_TYPE> float Distance(const Quaternionv<SIMD_TYPE>& lhs, const Quaternionv<SIMD_TYPE>& rhs)
		{
			return Magnitude(rhs - lhs);
		}

		template<typename SIMD_TYPE> float DistanceSquared(const Quaternionv<SIMD_TYPE>& lhs, const Quaternionv<SIMD_TYPE>& rhs)
		{
			return MagnitudeSquared(rhs - lhs);
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::AxisAngle(const Vector3fv& axis, ElementType angle)
		{
			const float a = angle * 0.5f;
			const float s = sin(a);
			return Quaternionv<SIMD_TYPE>(axis.x * s, axis.y * s, axis.z * s, cos(a));
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE> Quaternionv<SIMD_TYPE>::Identity()
		{
			return Quaternionv<SIMD_TYPE>(0, 0, 0, 1);
		}

		template<typename SIMD_TYPE>
		Quaternionv<SIMD_TYPE> Inverse(const Quaternionv<SIMD_TYPE>& q)
		{
			Quaternionv<SIMD_TYPE> result(
				-q.x,
				-q.y,
				-q.z,
				q.w
			);
			return result;
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> operator * (const Vector3fv& lhs, const Quaternionv<SIMD_TYPE>& rhs)
		{
			Vector3fv u(rhs.xyz);
			float s = rhs.w;
			return Vector3v<SIMD_TYPE>(
				2 * Dot(u, lhs) * u +
				(s*s - Dot(u, u)) * lhs +
				2 * s * Cross(u, lhs)
				);
		}

		template<typename SIMD_TYPE>
		Vector3v<SIMD_TYPE> operator * (const Quaternionv<SIMD_TYPE>& lhs, const Vector3fv& rhs)
		{
			Vector3fv u(lhs.xyz);
			float s = lhs.w;
			return Vector3v<SIMD_TYPE>(
				2 * Dot(u, rhs) * u +
				(s*s - Dot(u, u)) * rhs +
				2 * s * Cross(u, rhs)
				);
		}
	}
}
