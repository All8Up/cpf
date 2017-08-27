//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/LaneRef.hpp"
#include "SIMD/Detail/LaneIndex.hpp"
#include "SIMD/Detail/Swizzles.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector3v
		{
			//////////////////////////////////////////////////////////////////////////
			using StorageType = typename TYPE::StorageType;
			using LaneType = typename TYPE::LaneType;
			static constexpr int LaneMask = TYPE::LaneMask;

			//////////////////////////////////////////////////////////////////////////
			Vector3v();
			explicit Vector3v(typename TYPE::LaneType value);
			Vector3v(TYPE value);
			Vector3v(StorageType value);
			Vector3v(LaneType v0, LaneType v1, LaneType v2);
			template <int I0, int I1, int I2>
			Vector3v(const SIMD::LaneRef_3<TYPE, I0, I1, I2>& ref);
			template <int I0, int I1>
			Vector3v(const SIMD::LaneRef_2<TYPE, I0, I1>& ref, LaneType v2);
			template <int I1, int I2>
			Vector3v(LaneType v0, const SIMD::LaneRef_2<TYPE, I1, I2>& ref);
			explicit Vector3v(const LaneType* data);

			template <typename RTYPE, int I0, int I1, int I2>
			explicit Vector3v(const SIMD::LaneRef_3<RTYPE, I0, I1, I2>& ref);

			//////////////////////////////////////////////////////////////////////////
			SIMD::LaneIndex<TYPE> CPF_VECTORCALL operator [](int idx);
			LaneType CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3v& CPF_VECTORCALL operator += (const Vector3v& rhs);
			Vector3v& CPF_VECTORCALL operator -= (const Vector3v& rhs);
			Vector3v& CPF_VECTORCALL operator *= (const Vector3v& rhs);
			Vector3v& CPF_VECTORCALL operator *= (LaneType rhs);
			Vector3v& CPF_VECTORCALL operator /= (const Vector3v& rhs);
			Vector3v& CPF_VECTORCALL operator /= (LaneType rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator typename TYPE::Lanes_3 () const { return static_cast<typename TYPE::Lanes_3>(mSIMD); }
			explicit operator StorageType () const { return StorageType(mSIMD); }

			//////////////////////////////////////////////////////////////////////////
			TYPE mSIMD;
			LANEREF_1_SWIZZLE(TYPE);
			LANEREF_2_SWIZZLE(TYPE);
			LANEREF_3_SWIZZLE(TYPE);
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
