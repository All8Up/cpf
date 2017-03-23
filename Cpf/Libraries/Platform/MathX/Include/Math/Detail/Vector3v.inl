//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector2v.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		Vector3v<TYPE>::Vector3v() {}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(typename TYPE::Element value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(TYPE value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector3v<TYPE>::Vector3v(Element v0, Element v1, Element v2)
			: mVector(v0, v1, v2)
		{}

		template <typename TYPE>
		template <int I0, int I1, int I2>
		Vector3v<TYPE>::Vector3v(Cpf::SIMD::Ref32x4_3<TYPE, I0, I1, I2>& ref)
			: mVector(ref)
		{}

		template <typename TYPE>
		template <int I0, int I1>
		Vector3v<TYPE>::Vector3v(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref, Element v2)
			: mVector(typename TYPE::Lanes_2(ref), v2)
		{}

		template <typename TYPE>
		template <int I1, int I2>
		Vector3v<TYPE>::Vector3v(Element v0, Cpf::SIMD::Ref32x4_2<TYPE, I1, I2>& ref)
			: mVector(v0, typename TYPE::Lanes_2(ref))
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		template <typename RTYPE, int I0, int I1, int I2>
		Vector3v<TYPE>::Vector3v(const SIMD::Ref32x4_3<RTYPE, I0, I1, I2>& ref)
			: mVector(ref.GetLane(0), ref.GetLane(1), ref.GetLane(2))
		{}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Vector3v<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::Element CPF_VECTORCALL Vector3v<TYPE>::operator [](int idx) const
		{
			switch (idx)
			{
			case 0: return mVector.GetLane<0>();
			case 1: return mVector.GetLane<1>();
			case 2: return mVector.GetLane<2>();
			}
			CPF_ASSERT_ALWAYS;
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Cross(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Cross(lhs.mVector, rhs.mVector));
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator == (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mVector == rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator != (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mVector != rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator < (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mVector < rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mVector <= rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator > (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mVector > rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return lhs.mVector >= rhs.mVector;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator - (const Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(-value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator + (const Vector3v<TYPE> lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mVector + rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator - (const Vector3v<TYPE> lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mVector - rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator * (const Vector3v<TYPE> lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mVector * rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator * (const Vector3v<TYPE> lhs, typename TYPE::Element rhs)
		{
			return Vector3v<TYPE>(lhs.mVector * TYPE(rhs));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator * (typename TYPE::Element lhs, const Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(TYPE(lhs) * rhs.mVector);
		}


		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL operator / (const Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(lhs.mVector / rhs.mVector);
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
		Vector3v<TYPE>& CPF_VECTORCALL Vector3v<TYPE>::operator /= (const Vector3v<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Min(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Min(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector3v<TYPE> value)
		{
			return HMin(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Max(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Max(lhs.mVector, rhs.mVector));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector3v<TYPE> value)
		{
			return HMax(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Sqrt(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Sqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL RSqrt(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(RSqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Reciprocal(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Reciprocal(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Clamp(Vector3v<TYPE> value, typename TYPE::Element l, typename TYPE::Element h)
		{
			return Vector3v<TYPE>(Clamp(value.mVector, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Abs(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Abs(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::Element CPF_VECTORCALL Dot(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Dot(lhs.mVector, rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::Element CPF_VECTORCALL Magnitude(Vector3v<TYPE> value)
		{
			return Magnitude(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3v<TYPE>::Element CPF_VECTORCALL MagnitudeSq(Vector3v<TYPE> value)
		{
			return MagnitudeSq(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Normalize(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Normalize(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Reflect(Vector3v<TYPE> value, Vector3v<TYPE> norm)
		{
			const typename TYPE::Element dot2 = Dot(value, norm) * 2;
			return Vector3v<TYPE>(value.mVector * TYPE(dot2) - norm.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Ceil(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Ceil(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Floor(Vector3v<TYPE> value)
		{
			return Vector3v<TYPE>(Floor(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Round(Vector3v<TYPE> value, SIMD::Rounding mode)
		{
			return Vector3v<TYPE>(Round(value.mVector, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3v<TYPE> CPF_VECTORCALL Modulus(Vector3v<TYPE> lhs, Vector3v<TYPE> rhs)
		{
			return Vector3v<TYPE>(Modulus(lhs.mVector, rhs.mVector));
		}
	}
}
