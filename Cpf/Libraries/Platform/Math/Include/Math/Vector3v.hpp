//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector3v
		{
			//////////////////////////////////////////////////////////////////////////
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			//////////////////////////////////////////////////////////////////////////
			Vector3v();
			explicit Vector3v(typename TYPE::Element value);
			Vector3v(TYPE value);
			Vector3v(Element v0, Element v1, Element v2);
			template <int I0, int I1, int I2>
			Vector3v(Cpf::SIMD::Ref32x4_3<TYPE, I0, I1, I2>& ref);
			template <int I0, int I1>
			Vector3v(Cpf::SIMD::Ref32x4_2<TYPE, I0, I1>& ref, Element v2);
			template <int I1, int I2>
			Vector3v(Element v0, Cpf::SIMD::Ref32x4_2<TYPE, I1, I2>& ref);
			explicit Vector3v(const Element* data);

			template <typename RTYPE, int I0, int I1, int I2>
			explicit Vector3v(const SIMD::Ref32x4_3<RTYPE, I0, I1, I2>& ref);

			//////////////////////////////////////////////////////////////////////////
			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3v& CPF_VECTORCALL operator += (const Vector3v& rhs);
			Vector3v& CPF_VECTORCALL operator -= (const Vector3v& rhs);
			Vector3v& CPF_VECTORCALL operator *= (const Vector3v& rhs);
			Vector3v& CPF_VECTORCALL operator /= (const Vector3v& rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator Storage () const { return static_cast<Storage>(mVector); }
			operator typename TYPE::Lanes_3() const { return mVector; }

			//////////////////////////////////////////////////////////////////////////
			TYPE mVector;
			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
			REF32X4_3_SWIZZLE(TYPE);
		};
	}
}

#include "Math/Detail/Vector3v.inl"
#include "SIMD/Types.hpp"
#include "SIMD/Detail/FPU/F32x3.hpp"

namespace Cpf
{
	namespace Math
	{
		using Vector3fv = Vector3v<SIMD::F32x4_3>;
		using Vector3f = Vector3v<SIMD::FPU::F32x3_3>;
	}
}
