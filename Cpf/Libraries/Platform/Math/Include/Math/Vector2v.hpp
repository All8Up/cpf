//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector2v
		{
			//////////////////////////////////////////////////////////////////////////
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			//////////////////////////////////////////////////////////////////////////
			Vector2v();
			explicit Vector2v(typename TYPE::Element value);
			explicit Vector2v(TYPE value);
			Vector2v(Element v0, Element v1);
			template <int I0, int I1>
			explicit Vector2v(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref);

			//////////////////////////////////////////////////////////////////////////
			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector2v& CPF_VECTORCALL operator += (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator -= (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator *= (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator /= (const Vector2v& rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator Storage () const;

			//////////////////////////////////////////////////////////////////////////
			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
		};
	}
}

#include "Math/Detail/Vector2v.inl"
#include "SIMD/Types.hpp"

namespace Cpf
{
	namespace Math
	{
		using Vector2i = Vector2v<SIMD::I32x4_2>;
		using Vector2fv = Vector2v<SIMD::F32x4_2>;
	}
}
