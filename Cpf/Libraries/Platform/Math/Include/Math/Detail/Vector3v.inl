//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector2v.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		Vector3<TYPE>::Vector3() {}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(const Vector3& rhs)
			: mSIMD(rhs.mSIMD)
		{}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(typename TYPE::LaneType value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(TYPE value)
			: mSIMD(value)
		{}
		
		template <typename TYPE>
		Vector3<TYPE>::Vector3(typename TYPE::StorageType value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(LaneType v0, LaneType v1, LaneType v2)
			: mSIMD{ v0, v1, v2 }
		{}

		template <typename TYPE>
		template <int I0, int I1, int I2>
		Vector3<TYPE>::Vector3(const SIMD::LaneRef_3<TYPE, I0, I1, I2>& ref)
			: mSIMD(typename TYPE::Lanes_3(ref))
		{}

		template <typename TYPE>
		template <int I0, int I1>
		Vector3<TYPE>::Vector3(const SIMD::LaneRef_2<TYPE, I0, I1>& ref, LaneType v2)
			: mSIMD(typename TYPE::Lanes_2(ref), v2)
		{}

		template <typename TYPE>
		template <int I1, int I2>
		Vector3<TYPE>::Vector3(LaneType v0, const SIMD::LaneRef_2<TYPE, I1, I2>& ref)
			: mSIMD(v0, typename TYPE::Lanes_2(ref))
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		template <typename RTYPE, int I0, int I1, int I2>
		Vector3<TYPE>::Vector3(const SIMD::LaneRef_3<RTYPE, I0, I1, I2>& ref)
			: mSIMD(LaneType(ref.GetLane<I0>()), LaneType(ref.GetLane<I1>()), LaneType(ref.GetLane<I2>()))
		{
		}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(const LaneType* data)
			: mSIMD(data[0], data[1], data[2])
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::LaneIndex<TYPE> CPF_VECTORCALL Vector3<TYPE>::operator [](int idx)
		{
			return SIMD::LaneIndex<TYPE>(mSIMD, idx);
		}

		template <typename TYPE>
		inline typename Vector3<TYPE>::LaneType CPF_VECTORCALL Vector3<TYPE>::operator [](int idx) const
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
		inline Vector3<TYPE> CPF_VECTORCALL Cross(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Cross(lhs.mSIMD, rhs.mSIMD));
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		inline typename TYPE::BoolType CPF_VECTORCALL operator == (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mSIMD == rhs.mSIMD;
		}

		template <typename TYPE>
		inline typename TYPE::BoolType CPF_VECTORCALL operator != (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mSIMD != rhs.mSIMD;
		}

		template <typename TYPE>
		inline typename TYPE::BoolType CPF_VECTORCALL operator < (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mSIMD < rhs.mSIMD;
		}

		template <typename TYPE>
		inline typename TYPE::BoolType CPF_VECTORCALL operator <= (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mSIMD <= rhs.mSIMD;
		}

		template <typename TYPE>
		inline typename TYPE::BoolType CPF_VECTORCALL operator > (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mSIMD > rhs.mSIMD;
		}

		template <typename TYPE>
		inline typename TYPE::BoolType CPF_VECTORCALL operator >= (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mSIMD >= rhs.mSIMD;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL operator - (const Vector3<TYPE> value)
		{
			return Vector3<TYPE>(-value.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL operator + (const Vector3<TYPE> lhs, const Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mSIMD + rhs.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL operator - (const Vector3<TYPE> lhs, const Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mSIMD - rhs.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL operator * (const Vector3<TYPE> lhs, const Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mSIMD * rhs.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL operator * (const Vector3<TYPE> lhs, typename TYPE::LaneType rhs)
		{
			return Vector3<TYPE>(lhs.mSIMD * TYPE(rhs));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL operator * (typename TYPE::LaneType lhs, const Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(TYPE(lhs) * rhs.mSIMD);
		}


		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL operator / (const Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mSIMD / rhs.mSIMD);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Vector3<TYPE>& CPF_VECTORCALL Vector3<TYPE>::operator += (const Vector3<TYPE>& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3<TYPE>& CPF_VECTORCALL Vector3<TYPE>::operator -= (const Vector3<TYPE>& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3<TYPE>& CPF_VECTORCALL Vector3<TYPE>::operator *= (const Vector3<TYPE>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3<TYPE>& CPF_VECTORCALL Vector3<TYPE>::operator *= (typename Vector3<TYPE>::LaneType rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3<TYPE>& CPF_VECTORCALL Vector3<TYPE>::operator /= (const Vector3<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		template <typename TYPE>
		Vector3<TYPE>& CPF_VECTORCALL Vector3<TYPE>::operator /= (typename Vector3<TYPE>::LaneType rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Min(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Min(lhs.mSIMD, rhs.mSIMD));
		}

		template <typename TYPE>
		inline typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector3<TYPE> value)
		{
			return HMin(value.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Max(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Max(lhs.mSIMD, rhs.mSIMD));
		}
		template <typename TYPE>
		inline typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector3<TYPE> value)
		{
			return HMax(value.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Sqrt(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Sqrt(value.mSIMD));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL RSqrt(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(RSqrt(value.mSIMD));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Reciprocal(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Reciprocal(value.mSIMD));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Clamp(Vector3<TYPE> value, typename TYPE::LaneType l, typename TYPE::LaneType h)
		{
			return Vector3<TYPE>(Clamp(value.mSIMD, l, h));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Abs(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Abs(value.mSIMD));
		}

		template <typename TYPE>
		inline typename Vector3<TYPE>::LaneType CPF_VECTORCALL Dot(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Dot(lhs.mSIMD, rhs.mSIMD);
		}

		template <typename TYPE>
		inline typename Vector3<TYPE>::LaneType CPF_VECTORCALL Magnitude(Vector3<TYPE> value)
		{
			return Magnitude(value.mSIMD);
		}

		template <typename TYPE>
		inline typename Vector3<TYPE>::LaneType CPF_VECTORCALL MagnitudeSq(Vector3<TYPE> value)
		{
			return MagnitudeSq(value.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Normalize(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Normalize(value.mSIMD));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Reflect(Vector3<TYPE> value, Vector3<TYPE> norm)
		{
			const typename TYPE::LaneType dot2 = Dot(value, norm) * 2;
			return Vector3<TYPE>(value.mSIMD * TYPE(dot2) - norm.mSIMD);
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Ceil(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Ceil(value.mSIMD));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Floor(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Floor(value.mSIMD));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Round(Vector3<TYPE> value, SIMD::Rounding mode)
		{
			return Vector3<TYPE>(Round(value.mSIMD, mode));
		}

		template <typename TYPE>
		inline Vector3<TYPE> CPF_VECTORCALL Modulus(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Modulus(lhs.mSIMD, rhs.mSIMD));
		}
	}
}
