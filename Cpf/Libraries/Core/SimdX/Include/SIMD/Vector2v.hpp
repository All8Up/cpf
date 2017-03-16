//////////////////////////////////////////////////////////////////////////
#pragma once
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

			Vector2v() {}
			explicit Vector2v(typename TYPE::Element value)
				: mVector(value)
			{}
			Vector2v(Element v0, Element v1)
				: mVector(v0, v1)
			{}

			template <int I0, int I1>
			explicit Vector2v(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref) : mVector(ref) {}

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
		};
	}
}
