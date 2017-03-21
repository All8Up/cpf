//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		Vector3<TYPE>::Vector3() {}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(typename TYPE::Element value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(TYPE value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(Element v0, Element v1, Element v2)
			: mVector(v0, v1, v2)
		{}

		template <typename TYPE>
		template <int I0, int I1, int I2>
		Vector3<TYPE>::Vector3(Cpf::SIMD::Ref32x4_3<TYPE, I0, I1, I2>& ref)
			: mVector(ref)
		{}

		template <typename TYPE>
		template <int I0, int I1>
		Vector3<TYPE>::Vector3(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref, Element v2)
			: mVector(typename TYPE::Lanes_2(ref), v2)
		{}

		template <typename TYPE>
		template <int I1, int I2>
		Vector3<TYPE>::Vector3(Element v0, Cpf::SIMD::Ref32x4_2<TYPE, I1, I2>& ref)
			: mVector(v0, typename TYPE::Lanes_2(ref))
		{}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Vector3<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3<TYPE>::Element CPF_VECTORCALL Vector3<TYPE>::operator [](int idx) const
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
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Cross(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Cross(lhs.mVector, rhs.mVector));
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator == (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mVector == rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator != (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mVector != rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator < (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mVector < rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mVector <= rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator > (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mVector > rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return lhs.mVector >= rhs.mVector;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL operator - (Vector3<TYPE> value)
		{
			return Vector3<TYPE>(-value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL operator + (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mVector + rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL operator - (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mVector - rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL operator * (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mVector * rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL operator * (Vector3<TYPE> lhs, typename TYPE::Element rhs)
		{
			return Vector3<TYPE>(lhs.mVector * TYPE(rhs));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL operator * (typename TYPE::Element lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(TYPE(lhs) * rhs.mVector);
		}


		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL operator / (Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(lhs.mVector / rhs.mVector);
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
		Vector3<TYPE>& CPF_VECTORCALL Vector3<TYPE>::operator /= (const Vector3<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Min(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Min(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector3<TYPE> value)
		{
			return HMin(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Max(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Max(lhs.mVector, rhs.mVector));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector3<TYPE> value)
		{
			return HMax(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Sqrt(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Sqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL RSqrt(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(RSqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Reciprocal(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Reciprocal(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Clamp(Vector3<TYPE> value, typename TYPE::Element l, typename TYPE::Element h)
		{
			return Vector3<TYPE>(Clamp(value.mVector, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Abs(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Abs(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3<TYPE>::Element CPF_VECTORCALL Dot(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Dot(lhs.mVector, rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3<TYPE>::Element CPF_VECTORCALL Magnitude(Vector3<TYPE> value)
		{
			return Magnitude(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector3<TYPE>::Element CPF_VECTORCALL MagnitudeSq(Vector3<TYPE> value)
		{
			return MagnitudeSq(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Normalize(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Normalize(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Reflect(Vector3<TYPE> value, Vector3<TYPE> norm)
		{
			const typename TYPE::Element dot2 = Dot(value, norm) * 2;
			return Vector3<TYPE>(value.mVector * TYPE(dot2) - norm.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Ceil(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Ceil(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Floor(Vector3<TYPE> value)
		{
			return Vector3<TYPE>(Floor(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Round(Vector3<TYPE> value, SIMD::Rounding mode)
		{
			return Vector3<TYPE>(Round(value.mVector, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector3<TYPE> CPF_VECTORCALL Modulus(Vector3<TYPE> lhs, Vector3<TYPE> rhs)
		{
			return Vector3<TYPE>(Modulus(lhs.mVector, rhs.mVector));
		}
	}
}
