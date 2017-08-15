//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		Vector4v<TYPE>::Vector4v()
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(typename Vector4v<TYPE>::LaneType value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(TYPE value)
			: mSIMD(value)
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(LaneType v0, LaneType v1, LaneType v2, LaneType v3)
			: mSIMD{ v0, v1, v2, v3 }
		{}

		template <typename TYPE>
		template <int I0, int I1, int I2, int I3>
		Vector4v<TYPE>::Vector4v(Cpf::SIMD::Ref32x4_4<TYPE, I0, I1, I2, I3>& ref) : mSIMD(ref) {}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(Lanes_2 v01, LaneType v2, LaneType v3)
			: mSIMD{ v01, v2, v3 }
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(LaneType v0, Lanes_2 v12, LaneType v3)
			: mSIMD{ v0, v12, v3 }
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(LaneType v0, LaneType v1, Lanes_2 v23)
			: mSIMD{ v0, v1, v23 }
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(Lanes_2 v01, Lanes_2 v23)
			: mSIMD{ v01, v23 }
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(Lanes_3 v012, LaneType v3)
			: mSIMD{ v012, v3 }
		{}

		template <typename TYPE>
		Vector4v<TYPE>::Vector4v(LaneType v0, Lanes_3 v123)
			: mSIMD{ v0, v123 }
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Vector4v<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mSIMD, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::LaneType CPF_VECTORCALL Vector4v<TYPE>::operator [](int idx) const
		{
			switch (idx)
			{
			case 0: return mSIMD.GetLane<0>();
			case 1: return mSIMD.GetLane<1>();
			case 2: return mSIMD.GetLane<2>();
			case 3: return mSIMD.GetLane<3>();
			}
			CPF_ASSERT_ALWAYS;
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Cross(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Cross(lhs.mSIMD, rhs.mSIMD));
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator == (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mSIMD == rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator != (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mSIMD != rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator < (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mSIMD < rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mSIMD <= rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator > (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mSIMD > rhs.mSIMD;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mSIMD >= rhs.mSIMD;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator - (Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(-value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator + (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mSIMD + rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator - (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mSIMD - rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator * (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mSIMD * rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator * (const Vector4v<TYPE> lhs, typename TYPE::LaneType rhs)
		{
			return Vector4v<TYPE>(lhs.mSIMD * TYPE(rhs));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator * (typename TYPE::Element lhs, const Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(TYPE(lhs) * rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator / (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mSIMD / rhs.mSIMD);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Vector4v<TYPE>& CPF_VECTORCALL Vector4v<TYPE>::operator += (const Vector4v<TYPE>& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4v<TYPE>& CPF_VECTORCALL Vector4v<TYPE>::operator -= (const Vector4v<TYPE>& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4v<TYPE>& CPF_VECTORCALL Vector4v<TYPE>::operator *= (const Vector4v<TYPE>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4v<TYPE>& CPF_VECTORCALL Vector4v<TYPE>::operator *= (typename Vector4v<TYPE>::LaneType rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4v<TYPE>& CPF_VECTORCALL Vector4v<TYPE>::operator /= (const Vector4v<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4v<TYPE>& CPF_VECTORCALL Vector4v<TYPE>::operator /= (typename Vector4v<TYPE>::LaneType rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Min(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Min(lhs.mSIMD, rhs.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector4v<TYPE> value)
		{
			return HMin(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Max(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Max(lhs.mSIMD, rhs.mSIMD));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector4v<TYPE> value)
		{
			return HMax(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Sqrt(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Sqrt(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL RSqrt(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(RSqrt(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Reciprocal(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Reciprocal(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Clamp(Vector4v<TYPE> value, typename TYPE::LaneType l, typename TYPE::LaneType h)
		{
			return Vector4v<TYPE>(Clamp(value.mSIMD, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Abs(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Abs(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::LaneType CPF_VECTORCALL Dot(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Dot(lhs.mSIMD, rhs.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::LaneType CPF_VECTORCALL Magnitude(Vector4v<TYPE> value)
		{
			return Magnitude(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::LaneType CPF_VECTORCALL MagnitudeSq(Vector4v<TYPE> value)
		{
			return MagnitudeSq(value.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Normalize(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Normalize(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Reflect(Vector4v<TYPE> value, Vector4v<TYPE> norm)
		{
			const typename TYPE::LaneType dot2 = Dot(value, norm) * 2;
			return Vector4v<TYPE>(value.mSIMD * TYPE(dot2) - norm.mSIMD);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Ceil(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Ceil(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Floor(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Floor(value.mSIMD));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Round(Vector4v<TYPE> value, SIMD::Rounding mode)
		{
			return Vector4v<TYPE>(Round(value.mSIMD, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Modulus(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Modulus(lhs.mSIMD, rhs.mSIMD));
		}
	}
}
