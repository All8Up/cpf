//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector3
		{
			//////////////////////////////////////////////////////////////////////////
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			//////////////////////////////////////////////////////////////////////////
			Vector3();
			explicit Vector3(typename TYPE::Element value);
			explicit Vector3(TYPE value);
			Vector3(Element v0, Element v1, Element v2);
			template <int I0, int I1, int I2>
			Vector3(Cpf::SIMD::Ref32x4_3<TYPE, I0, I1, I2>& ref);

			//////////////////////////////////////////////////////////////////////////
			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3& CPF_VECTORCALL operator += (const Vector3& rhs);
			Vector3& CPF_VECTORCALL operator -= (const Vector3& rhs);
			Vector3& CPF_VECTORCALL operator *= (const Vector3& rhs);
			Vector3& CPF_VECTORCALL operator /= (const Vector3& rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			//////////////////////////////////////////////////////////////////////////
			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
			REF32X4_3_SWIZZLE(TYPE);
		};
	}
}

#include "Math/Detail/Vector3.inl"
