//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Float32x4.hpp"

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
			Vector2v(typename TYPE::Element value)
				: mVector(value)
			{}
			Vector2v(Element v0, Element v1)
				: mVector(v0, v1)
			{}

			template <int I0, int I1>
			Vector2v(Cpf::SIMD::F32x4_Ref2<TYPE, I0, I1>& ref) : mVector(ref) {}

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;

			Cpf::SIMD::F32x4_Ref1<TYPE, 0> x;
			Cpf::SIMD::F32x4_Ref1<TYPE, 1> y;
		};
	}
}
