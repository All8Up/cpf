//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"
#include "SIMD/Detail/Ref32x4_4.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector4
		{
			//////////////////////////////////////////////////////////////////////////
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			using Lanes_1 = typename TYPE::Lanes_1;
			using Lanes_2 = typename TYPE::Lanes_2;
			using Lanes_3 = typename TYPE::Lanes_3;
			using Lanes_4 = typename TYPE::Lanes_4;

			//////////////////////////////////////////////////////////////////////////
			Vector4();
			explicit Vector4(typename TYPE::Element value);
			explicit Vector4(TYPE value);
			Vector4(Element v0, Element v1, Element v2, Element v3);
			template <int I0, int I1, int I2, int I3>
			Vector4(Cpf::SIMD::Ref32x4_4<TYPE, I0, I1, I2, I3>& ref);

			explicit Vector4(Lanes_2 v01, Element v2, Element v3);
			explicit Vector4(Element v0, Lanes_2 v12, Element v3);
			explicit Vector4(Element v0, Element v1, Lanes_2 v23);
			explicit Vector4(Lanes_2 v01, Lanes_2 v23);

			explicit Vector4(Lanes_3 v012, Element v3);
			explicit Vector4(Element v0, Lanes_3 v123);

			//////////////////////////////////////////////////////////////////////////
			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector4& CPF_VECTORCALL operator += (const Vector4& rhs);
			Vector4& CPF_VECTORCALL operator -= (const Vector4& rhs);
			Vector4& CPF_VECTORCALL operator *= (const Vector4& rhs);
			Vector4& CPF_VECTORCALL operator /= (const Vector4& rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			//////////////////////////////////////////////////////////////////////////
			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
			REF32X4_3_SWIZZLE(TYPE);
			REF32X4_4_SWIZZLE(TYPE);
		};
	}
}

#include "Math/Detail/Vector4.inl"
