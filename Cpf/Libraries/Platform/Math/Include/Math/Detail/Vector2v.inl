//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		Vector2v<TYPE>::Vector2v()
		{}

		template <typename TYPE>
		Vector2v<TYPE>::Vector2v(typename TYPE::LaneType value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector2v<TYPE>::Vector2v(TYPE value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector2v<TYPE>::Vector2v(LaneType v0, LaneType v1)
			: mSIMD(v0, v1)
		{}

		template <typename TYPE>
		template <int I0, int I1>
		Vector2v<TYPE>::Vector2v(SIMD::LaneRef_2<TYPE, I0, I1>& ref)
			: mSIMD(ref)
		{}

		template <typename TYPE>
		Vector2v<TYPE>::operator typename TYPE::Lanes_2 () const
		{
			return static_cast<typename TYPE::Lanes_2>(mSIMD);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::LaneIndex<TYPE> CPF_VECTORCALL Vector2v<TYPE>::operator [](int idx)
		{
			return SIMD::LaneIndex<TYPE>(mSIMD, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::LaneType CPF_VECTORCALL Vector2v<TYPE>::operator [](int idx) const
		{
			switch (idx)
			{
			case 0: return mSIMD.GetLane(0);
			case 1: return mSIMD.GetLane(1);
			}
			CPF_ASSERT_ALWAYS;
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator == (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mSIMD == rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator != (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mSIMD != rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator < (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mSIMD < rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator <= (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mSIMD <= rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator > (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mSIMD > rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::BoolType CPF_VECTORCALL operator >= (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mSIMD >= rhs.mSIMD;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator - (Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(-value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator + (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mSIMD + rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator - (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mSIMD - rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator * (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mSIMD * rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator * (Vector2v<TYPE> lhs, typename TYPE::LaneType rhs)
		{
			return Vector2v<TYPE>(lhs.mSIMD * TYPE(rhs));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator * (typename TYPE::LaneType lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(TYPE(lhs) * rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator / (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mSIMD / rhs.mSIMD);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Vector2v<TYPE>& CPF_VECTORCALL Vector2v<TYPE>::operator += (const Vector2v<TYPE>& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		template <typename TYPE>
		Vector2v<TYPE>& CPF_VECTORCALL Vector2v<TYPE>::operator -= (const Vector2v<TYPE>& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		template <typename TYPE>
		Vector2v<TYPE>& CPF_VECTORCALL Vector2v<TYPE>::operator *= (const Vector2v<TYPE>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector2v<TYPE>& CPF_VECTORCALL Vector2v<TYPE>::operator /= (const Vector2v<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Min(Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(Min(lhs.mSIMD, rhs.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector2v<TYPE> value)
		{
			return HMin(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Max(Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(Max(lhs.mSIMD, rhs.mSIMD));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector2v<TYPE> value)
		{
			return HMax(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Sqrt(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Sqrt(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL RSqrt(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(RSqrt(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Reciprocal(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Reciprocal(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Clamp(Vector2v<TYPE> value, typename TYPE::LaneType l, typename TYPE::LaneType h)
		{
			return Vector2v<TYPE>(Clamp(value.mSIMD, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Abs(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Abs(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::LaneType CPF_VECTORCALL Dot(Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Dot(lhs.mSIMD, rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::LaneType CPF_VECTORCALL Magnitude(Vector2v<TYPE> value)
		{
			return Magnitude(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::LaneType CPF_VECTORCALL MagnitudeSq(Vector2v<TYPE> value)
		{
			return MagnitudeSq(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Normalize(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Normalize(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Reflect(Vector2v<TYPE> value, Vector2v<TYPE> norm)
		{
			const typename TYPE::LaneType dot2 = Dot(value, norm) * 2;
			return Vector2v<TYPE>(value.mSIMD * TYPE(dot2) - norm.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Ceil(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Ceil(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Floor(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Floor(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Round(Vector2v<TYPE> value, SIMD::Rounding mode)
		{
			return Vector2v<TYPE>(Round(value.mSIMD, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Modulus(Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(Modulus(lhs.mSIMD, rhs.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE bool CPF_VECTORCALL Near(TYPE a, TYPE b, typename TYPE::LaneType tolerance)
		{
			return Near(a.mSIMD, b.mSIMD, tolerance);
		}
	}
}
