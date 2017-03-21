//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		Vector4<TYPE>::Vector4()
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(typename TYPE::Element value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(TYPE value)
			: mVector(value)
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(Element v0, Element v1, Element v2, Element v3)
			: mVector(v0, v1, v2, v3)
		{}

		template <typename TYPE>
		template <int I0, int I1, int I2, int I3>
		Vector4<TYPE>::Vector4(Cpf::SIMD::Ref32x4_4<TYPE, I0, I1, I2, I3>& ref) : mVector(ref) {}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(Lanes_2 v01, Element v2, Element v3)
			: mVector(v01, v2, v3)
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(Element v0, Lanes_2 v12, Element v3)
			: mVector(v0, v12, v3)
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(Element v0, Element v1, Lanes_2 v23)
			: mVector(v0, v1, v23)
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(Lanes_2 v01, Lanes_2 v23)
			: mVector(v01, v23)
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(Lanes_3 v012, Element v3)
			: mVector(v012, v3)
		{}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(Element v0, Lanes_3 v123)
			: mVector(v0, v123)
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Vector4<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4<TYPE>::Element CPF_VECTORCALL Vector4<TYPE>::operator [](int idx) const
		{
			switch (idx)
			{
			case 0: return mVector.GetLane<0>();
			case 1: return mVector.GetLane<1>();
			case 2: return mVector.GetLane<2>();
			case 3: return mVector.GetLane<3>();
			}
			CPF_ASSERT_ALWAYS;
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Cross(Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(Cross(lhs.mVector, rhs.mVector));
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator == (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return lhs.mVector == rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator != (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return lhs.mVector != rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator < (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return lhs.mVector < rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return lhs.mVector <= rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator > (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return lhs.mVector > rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return lhs.mVector >= rhs.mVector;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL operator - (Vector4<TYPE> value)
		{
			return Vector4<TYPE>(-value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL operator + (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(lhs.mVector + rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL operator - (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(lhs.mVector - rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL operator * (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(lhs.mVector * rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL operator / (Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(lhs.mVector / rhs.mVector);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Vector4<TYPE>& CPF_VECTORCALL Vector4<TYPE>::operator += (const Vector4<TYPE>& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4<TYPE>& CPF_VECTORCALL Vector4<TYPE>::operator -= (const Vector4<TYPE>& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4<TYPE>& CPF_VECTORCALL Vector4<TYPE>::operator *= (const Vector4<TYPE>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		template <typename TYPE>
		Vector4<TYPE>& CPF_VECTORCALL Vector4<TYPE>::operator /= (const Vector4<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Min(Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(Min(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector4<TYPE> value)
		{
			return HMin(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Max(Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(Max(lhs.mVector, rhs.mVector));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector4<TYPE> value)
		{
			return HMax(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Sqrt(Vector4<TYPE> value)
		{
			return Vector4<TYPE>(Sqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL RSqrt(Vector4<TYPE> value)
		{
			return Vector4<TYPE>(RSqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Reciprocal(Vector4<TYPE> value)
		{
			return Vector4<TYPE>(Reciprocal(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Clamp(Vector4<TYPE> value, typename TYPE::Element l, typename TYPE::Element h)
		{
			return Vector4<TYPE>(Clamp(value.mVector, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Abs(Vector4<TYPE> value)
		{
			return Vector4<TYPE>(Abs(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4<TYPE>::Element CPF_VECTORCALL Dot(Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Dot(lhs.mVector, rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4<TYPE>::Element CPF_VECTORCALL Magnitude(Vector4<TYPE> value)
		{
			return Magnitude(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4<TYPE>::Element CPF_VECTORCALL MagnitudeSq(Vector4<TYPE> value)
		{
			return MagnitudeSq(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Normalize(Vector4<TYPE> value)
		{
			return Vector4<TYPE>(Normalize(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Reflect(Vector4<TYPE> value, Vector4<TYPE> norm)
		{
			const typename TYPE::Element dot2 = Dot(value, norm) * 2;
			return Vector4<TYPE>(value.mVector * TYPE(dot2) - norm.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Ceil(Vector4<TYPE> value)
		{
			return Vector4<TYPE>(Ceil(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Floor(Vector4<TYPE> value)
		{
			return Vector4<TYPE>(Floor(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Round(Vector4<TYPE> value, SIMD::Rounding mode)
		{
			return Vector4<TYPE>(Round(value.mVector, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4<TYPE> CPF_VECTORCALL Modulus(Vector4<TYPE> lhs, Vector4<TYPE> rhs)
		{
			return Vector4<TYPE>(Modulus(lhs.mVector, rhs.mVector));
		}
	}
}
