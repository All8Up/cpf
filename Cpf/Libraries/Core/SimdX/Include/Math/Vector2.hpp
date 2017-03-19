//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector2
		{
			//////////////////////////////////////////////////////////////////////////
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			//////////////////////////////////////////////////////////////////////////
			Vector2();
			explicit Vector2(typename TYPE::Element value);
			explicit Vector2(TYPE value);
			Vector2(Element v0, Element v1);
			template <int I0, int I1>
			explicit Vector2(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref);

			//////////////////////////////////////////////////////////////////////////
			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector2& CPF_VECTORCALL operator += (const Vector2& rhs);
			Vector2& CPF_VECTORCALL operator -= (const Vector2& rhs);
			Vector2& CPF_VECTORCALL operator *= (const Vector2& rhs);
			Vector2& CPF_VECTORCALL operator /= (const Vector2& rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator Storage () const;

			//////////////////////////////////////////////////////////////////////////
			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
		};
	}
}

#include "Math/Detail/Vector2.inl"
