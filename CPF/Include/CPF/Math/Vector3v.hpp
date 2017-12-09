//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include "SIMD/Detail/LaneRef.hpp"
#include "SIMD/Detail/LaneIndex.hpp"
#include "SIMD/Detail/Swizzles.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		union Vector3
		{
			//////////////////////////////////////////////////////////////////////////
			using Type = TYPE;
			using StorageType = typename TYPE::StorageType;
			using LaneType = typename TYPE::LaneType;
			static constexpr int LaneMask = TYPE::LaneMask;

			//////////////////////////////////////////////////////////////////////////
			Vector3();
			explicit Vector3(typename TYPE::LaneType value);
			Vector3(const Vector3& rhs);
			Vector3(TYPE value);
			Vector3(StorageType value);
			Vector3(LaneType v0, LaneType v1, LaneType v2);
			template <int I0, int I1, int I2>
			Vector3(const SIMD::LaneRef_3<TYPE, I0, I1, I2>& ref);
			template <int I0, int I1>
			Vector3(const SIMD::LaneRef_2<TYPE, I0, I1>& ref, LaneType v2);
			template <int I1, int I2>
			Vector3(LaneType v0, const SIMD::LaneRef_2<TYPE, I1, I2>& ref);
			explicit Vector3(const LaneType* data);

			template <typename RTYPE>
			explicit Vector3(const Vector3<RTYPE>& rhs);

			template <typename RTYPE, int I0, int I1, int I2>
			explicit Vector3(const SIMD::LaneRef_3<RTYPE, I0, I1, I2>& ref);

			// Accepting bool4 for integral vectors is needed for predicated equations.
			template <typename = std::enable_if_t<std::is_integral<LaneType>::value>>
			Vector3(typename TYPE::BoolType rhs) : mSIMD(rhs.mVector) {}

			//////////////////////////////////////////////////////////////////////////
			SIMD::LaneIndex<TYPE> CPF_VECTORCALL operator [](int idx);
			LaneType CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector3& CPF_VECTORCALL operator += (const Vector3& rhs);
			Vector3& CPF_VECTORCALL operator -= (const Vector3& rhs);
			Vector3& CPF_VECTORCALL operator *= (const Vector3& rhs);
			Vector3& CPF_VECTORCALL operator *= (LaneType rhs);
			Vector3& CPF_VECTORCALL operator /= (const Vector3& rhs);
			Vector3& CPF_VECTORCALL operator /= (LaneType rhs);

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

namespace CPF
{
	namespace Math
	{
		using Vector3f = Vector3<SIMD::FPU::F32x3_3>;
//		using Vector3d = Vector3v<SIMD::FPU::F64x3_3>;
		using Vector3fv = Vector3<SIMD::F32x4_3>;
		using Vector3dv = Vector3<SIMD::F64x4_3>;
		using Vector3iv = Vector3<SIMD::I32x4_3>;
	}
}
