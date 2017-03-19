//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"
#include "SIMD/Detail/Ref32x4_4.hpp"

// TODO: This is a temporary test.

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector4v
		{
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			Vector4v() {}
			explicit Vector4v(typename TYPE::Element value)
				: mVector(value)
			{}
			explicit Vector4v(TYPE value)
				: mVector(value)
			{}
			Vector4v(Element v0, Element v1, Element v2, Element v3)
				: mVector(v0, v1, v2, v3)
			{}

			template <int I0, int I1, int I2, int I3>
			Vector4v(Cpf::SIMD::Ref32x4_4<TYPE, I0, I1, I2, I3>& ref) : mVector(ref) {}

			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			Vector4v& CPF_VECTORCALL operator += (const Vector4v& rhs);
			Vector4v& CPF_VECTORCALL operator -= (const Vector4v& rhs);
			Vector4v& CPF_VECTORCALL operator *= (const Vector4v& rhs);
			Vector4v& CPF_VECTORCALL operator /= (const Vector4v& rhs);

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
			REF32X4_3_SWIZZLE(TYPE);
			REF32X4_4_SWIZZLE(TYPE);
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Vector4v<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::Element CPF_VECTORCALL Vector4v<TYPE>::operator [](int idx) const
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
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Cross(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Cross(lhs.mVector, rhs.mVector));
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator == (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mVector == rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator != (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mVector != rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator < (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mVector < rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mVector <= rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator > (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mVector > rhs.mVector;
		}

		template <typename TYPE>
		CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return lhs.mVector >= rhs.mVector;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator - (Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(-value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator + (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mVector + rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator - (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mVector - rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator * (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mVector * rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL operator / (Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(lhs.mVector / rhs.mVector);
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
		Vector4v<TYPE>& CPF_VECTORCALL Vector4v<TYPE>::operator /= (const Vector4v<TYPE>& rhs)
		{
			*this = *this / rhs;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Min(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Min(lhs.mVector, rhs.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMin(Vector4v<TYPE> value)
		{
			return HMin(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Max(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Max(lhs.mVector, rhs.mVector));
		}
		template <typename TYPE>
		CPF_FORCE_INLINE typename TYPE::Lanes_1 CPF_VECTORCALL HMax(Vector4v<TYPE> value)
		{
			return HMax(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Sqrt(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Sqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL RSqrt(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(RSqrt(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Reciprocal(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Reciprocal(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Clamp(Vector4v<TYPE> value, typename TYPE::Element l, typename TYPE::Element h)
		{
			return Vector4v<TYPE>(Clamp(value.mVector, l, h));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Abs(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Abs(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::Element CPF_VECTORCALL Dot(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Dot(lhs.mVector, rhs.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::Element CPF_VECTORCALL Magnitude(Vector4v<TYPE> value)
		{
			return Magnitude(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Vector4v<TYPE>::Element CPF_VECTORCALL MagnitudeSq(Vector4v<TYPE> value)
		{
			return MagnitudeSq(value.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Normalize(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Normalize(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Reflect(Vector4v<TYPE> value, Vector4v<TYPE> norm)
		{
			const typename TYPE::Element dot2 = Dot(value, norm) * 2;
			return Vector4v<TYPE>(value.mVector * TYPE(dot2) - norm.mVector);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Ceil(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Ceil(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Floor(Vector4v<TYPE> value)
		{
			return Vector4v<TYPE>(Floor(value.mVector));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Round(Vector4v<TYPE> value, SIMD::Rounding mode)
		{
			return Vector4v<TYPE>(Round(value.mVector, mode));
		}

		template <typename TYPE>
		CPF_FORCE_INLINE Vector4v<TYPE> CPF_VECTORCALL Modulus(Vector4v<TYPE> lhs, Vector4v<TYPE> rhs)
		{
			return Vector4v<TYPE>(Modulus(lhs.mVector, rhs.mVector));
		}
	}
}
