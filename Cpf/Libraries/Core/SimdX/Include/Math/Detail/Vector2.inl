//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		Vector2<TYPE>::Vector2()
		{}

		template <typename TYPE>
		Vector2<TYPE>::Vector2(typename TYPE::Element value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector2<TYPE>::Vector2(TYPE value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector2<TYPE>::Vector2(Element v0, Element v1)
			: mVector(v0, v1)
		{}

		template <typename TYPE>
		template <int I0, int I1>
		Vector2<TYPE>::Vector2(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref)
			: mVector(ref)
		{}

		template <typename TYPE>
		Vector2<TYPE>::operator Storage () const
		{
			return static_cast<Storage>(mVector);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Vector2<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2<TYPE>::Element CPF_VECTORCALL Vector2<TYPE>::operator [](int idx) const
		{
			switch (idx)
			{
			case 0: return mVector.GetLane<0>();
			case 1: return mVector.GetLane<1>();
			}
			CPF_ASSERT_ALWAYS;
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator == (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return lhs.mVector == rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator != (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return lhs.mVector != rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator < (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return lhs.mVector < rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return lhs.mVector <= rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator > (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return lhs.mVector > rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return lhs.mVector >= rhs.mVector;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL operator - (Vector2<TYPE> value)
		{
			return Vector2<TYPE>(-value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL operator + (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(lhs.mVector + rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL operator - (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(lhs.mVector - rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL operator * (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(lhs.mVector * rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL operator * (Vector2<TYPE> lhs, typename TYPE::Element rhs)
		{
			return Vector2<TYPE>(lhs.mVector * TYPE(rhs));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL operator * (typename TYPE::Element lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(TYPE(lhs) * rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL operator / (Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(lhs.mVector / rhs.mVector);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Vector2<TYPE>& CPF_VECTORCALL Vector2<TYPE>::operator += (const Vector2<TYPE>& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		template <typename TYPE>
		Vector2<TYPE>& CPF_VECTORCALL Vector2<TYPE>::operator -= (const Vector2<TYPE>& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		template <typename TYPE>
		Vector2<TYPE>& CPF_VECTORCALL Vector2<TYPE>::operator *= (const Vector2<TYPE>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector2<TYPE>& CPF_VECTORCALL Vector2<TYPE>::operator /= (const Vector2<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Min(Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(Min(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector2<TYPE> value)
		{
			return HMin(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Max(Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(Max(lhs.mVector, rhs.mVector));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector2<TYPE> value)
		{
			return HMax(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Sqrt(Vector2<TYPE> value)
		{
			return Vector2<TYPE>(Sqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL RSqrt(Vector2<TYPE> value)
		{
			return Vector2<TYPE>(RSqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Reciprocal(Vector2<TYPE> value)
		{
			return Vector2<TYPE>(Reciprocal(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Clamp(Vector2<TYPE> value, typename TYPE::Element l, typename TYPE::Element h)
		{
			return Vector2<TYPE>(Clamp(value.mVector, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Abs(Vector2<TYPE> value)
		{
			return Vector2<TYPE>(Abs(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2<TYPE>::Element CPF_VECTORCALL Dot(Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Dot(lhs.mVector, rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2<TYPE>::Element CPF_VECTORCALL Magnitude(Vector2<TYPE> value)
		{
			return Magnitude(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2<TYPE>::Element CPF_VECTORCALL MagnitudeSq(Vector2<TYPE> value)
		{
			return MagnitudeSq(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Normalize(Vector2<TYPE> value)
		{
			return Vector2<TYPE>(Normalize(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Reflect(Vector2<TYPE> value, Vector2<TYPE> norm)
		{
			const typename TYPE::Element dot2 = Dot(value, norm) * 2;
			return Vector2<TYPE>(value.mVector * TYPE(dot2) - norm.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Ceil(Vector2<TYPE> value)
		{
			return Vector2<TYPE>(Ceil(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Floor(Vector2<TYPE> value)
		{
			return Vector2<TYPE>(Floor(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Round(Vector2<TYPE> value, SIMD::Rounding mode)
		{
			return Vector2<TYPE>(Round(value.mVector, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2<TYPE> CPF_VECTORCALL Modulus(Vector2<TYPE> lhs, Vector2<TYPE> rhs)
		{
			return Vector2<TYPE>(Modulus(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE bool CPF_VECTORCALL Near(TYPE a, TYPE b, typename TYPE::Element tolerance)
		{
			return Near(a.mVector, b.mVector, tolerance);
		}
	}
}
