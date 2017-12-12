//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/SIMD/Rounding.hpp"
#include "CPF/SIMD/Detail/LaneRef.hpp"
#include "CPF/SIMD/Detail/LaneIndex.hpp"
#include "CPF/SIMD/Detail/Swizzles.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		union Vector2v
		{
			//////////////////////////////////////////////////////////////////////////
			using LaneType = typename TYPE::LaneType;
			static constexpr int LaneMask = TYPE::LaneMask;

			//////////////////////////////////////////////////////////////////////////
			Vector2v();
			
			explicit Vector2v(typename TYPE::LaneType value);
			explicit Vector2v(TYPE value);
			Vector2v(LaneType v0, LaneType v1);
			template <int I0, int I1>
			explicit Vector2v(SIMD::LaneRef_2<TYPE, I0, I1>& ref);

			//////////////////////////////////////////////////////////////////////////
			SIMD::LaneIndex<TYPE> CPF_VECTORCALL operator [](int idx);
			LaneType CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector2v& CPF_VECTORCALL operator += (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator -= (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator *= (const Vector2v& rhs);
			Vector2v& CPF_VECTORCALL operator /= (const Vector2v& rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator typename TYPE::Lanes_2() const;

			//////////////////////////////////////////////////////////////////////////
			TYPE mSIMD;
			LANEREF_1_SWIZZLE(TYPE);
			LANEREF_2_SWIZZLE(TYPE);
		};
	}
}

#include "CPF/Math/Detail/Vector2v.inl"
#include "CPF/SIMD/Types.hpp"

namespace CPF
{
	namespace Math
	{
		using Vector2i = Vector2v<SIMD::I32x4_2>;
		using Vector2fv = Vector2v<SIMD::F32x4_2>;
	}
}
