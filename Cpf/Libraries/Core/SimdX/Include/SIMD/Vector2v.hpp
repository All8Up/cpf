//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"

// TODO: This is a temporary test.

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector2v
		{
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			Vector2v() {}
			explicit Vector2v(typename TYPE::Element value)
				: mVector(value)
			{}
			explicit Vector2v(TYPE value)
				: mVector(value)
			{}
			Vector2v(Element v0, Element v1)
				: mVector(v0, v1)
			{}

			template <int I0, int I1>
			explicit Vector2v(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref) : mVector(ref) {}

			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			Vector2v& CPF_VECTORCALL operator += (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator -= (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator *= (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator /= (const Vector2v& rhs);

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Vector2v<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::Element CPF_VECTORCALL Vector2v<TYPE>::operator [](int idx) const
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
		CPF_FORCE_INLINE int CPF_VECTORCALL operator == (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mVector == rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator != (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mVector != rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator < (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mVector < rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mVector <= rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator > (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mVector > rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return lhs.mVector >= rhs.mVector;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator - (Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(-value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator + (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mVector + rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator - (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mVector - rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator * (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mVector * rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL operator / (Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(lhs.mVector / rhs.mVector);
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
			return Vector2v<TYPE>(Min(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL HMin(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(HMin(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Max(Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(Max(lhs.mVector, rhs.mVector));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL HMax(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(HMax(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Sqrt(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Sqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL RSqrt(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(RSqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Reciprocal(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Reciprocal(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Clamp(Vector2v<TYPE> value, typename TYPE::Element l, typename TYPE::Element h)
		{
			return Vector2v<TYPE>(Clamp(value.mVector, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Abs(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Abs(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::Element CPF_VECTORCALL Dot(Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Dot(lhs.mVector, rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::Element CPF_VECTORCALL Magnitude(Vector2v<TYPE> value)
		{
			return Magnitude(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector2v<TYPE>::Element CPF_VECTORCALL MagnitudeSq(Vector2v<TYPE> value)
		{
			return MagnitudeSq(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Normalize(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Normalize(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Reflect(Vector2v<TYPE> value, Vector2v<TYPE> norm)
		{
			const typename TYPE::Element dot2 = Dot(value, norm) * 2;
			return Vector2v<TYPE>(value.mVector * TYPE(dot2) - norm.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Ceil(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Ceil(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Floor(Vector2v<TYPE> value)
		{
			return Vector2v<TYPE>(Floor(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Round(Vector2v<TYPE> value, SIMD::Rounding mode)
		{
			return Vector2v<TYPE>(Round(value.mVector, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector2v<TYPE> CPF_VECTORCALL Modulus(Vector2v<TYPE> lhs, Vector2v<TYPE> rhs)
		{
			return Vector2v<TYPE>(Modulus(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE bool CPF_VECTORCALL Near(TYPE a, TYPE b, typename TYPE::Element tolerance)
		{
			return Near(a.mVector, b.mVector, tolerance);
		}
	}
}
