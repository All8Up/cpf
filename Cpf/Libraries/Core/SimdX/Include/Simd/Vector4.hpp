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
		union Vector4
		{
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			Vector4() {}
			explicit Vector4(typename TYPE::Element value)
				: mVector(value)
			{}
			explicit Vector4(TYPE value)
				: mVector(value)
			{}
			Vector4(Element v0, Element v1, Element v2, Element v3)
				: mVector(v0, v1, v2, v3)
			{}

			template <int I0, int I1, int I2, int I3>
			Vector4(Cpf::SIMD::Ref32x4_4<TYPE, I0, I1, I2, I3>& ref) : mVector(ref) {}

			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			Vector4& CPF_VECTORCALL operator += (const Vector4& rhs);
			Vector4& CPF_VECTORCALL operator -= (const Vector4& rhs);
			Vector4& CPF_VECTORCALL operator *= (const Vector4& rhs);
			Vector4& CPF_VECTORCALL operator /= (const Vector4& rhs);

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
			REF32X4_3_SWIZZLE(TYPE);
			REF32X4_4_SWIZZLE(TYPE);
		};

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
