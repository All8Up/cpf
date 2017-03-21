//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"
#include "SIMD/Detail/Ref32x4_4.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector3;

		template <typename TYPE>
		union Quaternion
		{
			//////////////////////////////////////////////////////////////////////////
			using Type = TYPE;
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;
			static constexpr int kLaneMask = TYPE::kLaneMask;

			//////////////////////////////////////////////////////////////////////////
			Quaternion();
			explicit Quaternion(typename TYPE::Element value);
			explicit Quaternion(TYPE value);
			Quaternion(Element v0, Element v1, Element v2, Element v3);
			template <int I0, int I1, int I2, int I3>
			constexpr Quaternion(Cpf::SIMD::Ref32x4_4<TYPE, I0, I1, I2, I3>& ref);
			Quaternion(typename TYPE::Lanes_3, Element);

			//////////////////////////////////////////////////////////////////////////
			SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Quaternion& CPF_VECTORCALL operator += (const Quaternion& rhs);
			Quaternion& CPF_VECTORCALL operator -= (const Quaternion& rhs);
			Quaternion& CPF_VECTORCALL operator *= (const Quaternion& rhs);
			Quaternion& CPF_VECTORCALL operator /= (const Quaternion& rhs);

			//////////////////////////////////////////////////////////////////////////
			static Quaternion CPF_VECTORCALL Identity();
			template<typename ATYPE>
			static Quaternion CPF_VECTORCALL AxisAngle(ATYPE axis, Element radians);

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

#include "Math/Detail/Quaternion.inl"
