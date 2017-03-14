//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Float32x4.hpp"

// TODO: This is a temporary test.

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector3v
		{
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;

			Vector3v() {}
			Vector3v(typename TYPE::Element value)
				: mVector(value)
			{}
			Vector3v(Element v0, Element v1, Element v2)
				: mVector(v0, v1, v2)
			{}

			template <int I0, int I1, int I2>
			Vector3v(Cpf::SIMD::F32x4_Ref3<TYPE, I0, I1, I2>& ref) : mVector(ref) {}

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;

			F32X4_1_SWIZZLE(TYPE);
			F32X4_2_SWIZZLE(TYPE);
			F32X4_3_SWIZZLE(TYPE);
		};
	}
}
