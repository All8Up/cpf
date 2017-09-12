//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector2v.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		Vector3v<TYPE>::Vector3v() {}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(const Vector3v& rhs)
			: mSIMD(rhs.mSIMD)
		{}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(typename TYPE::LaneType value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(TYPE value)
			: mSIMD(value)
		{}
		
		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(typename TYPE::StorageType value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(LaneType v0, LaneType v1, LaneType v2)
			: mSIMD{ v0, v1, v2 }
		{}

		template <typename TYPE>
		template <int I0, int I1, int I2>
		Vector3v<TYPE>::Vector3v(const SIMD::LaneRef_3<TYPE, I0, I1, I2>& ref)
			: mSIMD(typename TYPE::Lanes_3(ref))
		{}

		template <typename TYPE>
		template <int I0, int I1>
		Vector3v<TYPE>::Vector3v(const SIMD::LaneRef_2<TYPE, I0, I1>& ref, LaneType v2)
			: mSIMD(typename TYPE::Lanes_2(ref), v2)
		{}

		template <typename TYPE>
		template <int I1, int I2>
		Vector3v<TYPE>::Vector3v(LaneType v0, const SIMD::LaneRef_2<TYPE, I1, I2>& ref)
			: mSIMD(v0, typename TYPE::Lanes_2(ref))
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		template <typename RTYPE, int I0, int I1, int I2>
		Vector3v<TYPE>::Vector3v(const SIMD::LaneRef_3<RTYPE, I0, I1, I2>& ref)
			: mSIMD(ref.GetLane<I0>(), ref.GetLane<I1>(), ref.GetLane<I2>())
		{
		}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(const LaneType* data)
			: mSIMD(data[0], data[1], data[2])
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::LaneIndex<TYPE> CPF_VECTORCALL Vector3v<TYPE>::operator [](int idx)
		{
			return SIMD::LaneIndex<TYPE>(mSIMD, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::LaneType CPF_VECTORCALL Vector3v<TYPE>::operator [](int idx) const
		{
			switch (idx)
			{
			case 0: return mSIMD.GetLane<0>();
			case 1: return mSIMD.GetLane<1>();
			case 2: return mSIMD.GetLane<2>();
			}
			CPF_ASSERT_ALWAYS;
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Cross(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Cross(lhs.mSIMD, rhs.mSIMD));
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator == (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mSIMD == rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator != (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mSIMD != rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator < (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mSIMD < rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator <= (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mSIMD <= rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator > (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mSIMD > rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator >= (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mSIMD >= rhs.mSIMD;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator - (const Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(-value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator + (const Vector3v<TYPE> lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mSIMD + rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator - (const Vector3v<TYPE> lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mSIMD - rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator * (const Vector3v<TYPE> lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mSIMD * rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator * (const Vector3v<TYPE> lhs, typename TYPE::LaneType rhs)
		{
			return Vector3v<TYPE>(lhs.mSIMD * TYPE(rhs));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator * (typename TYPE::LaneType lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(TYPE(lhs) * rhs.mSIMD);
		}


		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator / (const Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mSIMD / rhs.mSIMD);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Vector3v<TYPE>& CPF_VECTORCALL Vector3v<TYPE>::operator += (const Vector3v<TYPE>& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3v<TYPE>& CPF_VECTORCALL Vector3v<TYPE>::operator -= (const Vector3v<TYPE>& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3v<TYPE>& CPF_VECTORCALL Vector3v<TYPE>::operator *= (const Vector3v<TYPE>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3v<TYPE>& CPF_VECTORCALL Vector3v<TYPE>::operator *= (typename Vector3v<TYPE>::LaneType rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3v<TYPE>& CPF_VECTORCALL Vector3v<TYPE>::operator /= (const Vector3v<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3v<TYPE>& CPF_VECTORCALL Vector3v<TYPE>::operator /= (typename Vector3v<TYPE>::LaneType rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Min(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Min(lhs.mSIMD, rhs.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector3v<TYPE> value)
		{
			return HMin(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Max(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Max(lhs.mSIMD, rhs.mSIMD));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector3v<TYPE> value)
		{
			return HMax(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Sqrt(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Sqrt(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL RSqrt(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(RSqrt(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Reciprocal(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Reciprocal(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Clamp(Vector3v<TYPE> value, typename TYPE::LaneType l, typename TYPE::LaneType h)
		{
			return Vector3v<TYPE>(Clamp(value.mSIMD, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Abs(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Abs(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::LaneType CPF_VECTORCALL Dot(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Dot(lhs.mSIMD, rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::LaneType CPF_VECTORCALL Magnitude(Vector3v<TYPE> value)
		{
			return Magnitude(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::LaneType CPF_VECTORCALL MagnitudeSq(Vector3v<TYPE> value)
		{
			return MagnitudeSq(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Normalize(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Normalize(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Reflect(Vector3v<TYPE> value, Vector3v<TYPE> norm)
		{
			const typename TYPE::LaneType dot2 = Dot(value, norm) * 2;
			return Vector3v<TYPE>(value.mSIMD * TYPE(dot2) - norm.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Ceil(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Ceil(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Floor(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Floor(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Round(Vector3v<TYPE> value, SIMD::Rounding mode)
		{
			return Vector3v<TYPE>(Round(value.mSIMD, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Modulus(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Modulus(lhs.mSIMD, rhs.mSIMD));
		}
	}
}
