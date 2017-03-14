//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Float32x4.hpp"

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

			Vector4v() {}
			Vector4v(typename TYPE::Element value)
				: mVector(value)
			{}
			Vector4v(Element v0, Element v1, Element v2, Element v3)
				: mVector(v0, v1, v2, v3)
			{}

			template <int I0, int I1, int I2, int I3>
			Vector4v(Cpf::SIMD::F32x4_Ref4<TYPE, I0, I1, I2, I3>& ref) : mVector(ref) {}

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;

			F32X4_1_SWIZZLE(TYPE);
			F32X4_2_SWIZZLE(TYPE);
			F32X4_3_SWIZZLE(TYPE);
		};
	}
}
