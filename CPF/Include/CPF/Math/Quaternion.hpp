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
		union Vector3;

		template <typename TYPE>
		union Quaternion
		{
			//////////////////////////////////////////////////////////////////////////
			using Type = TYPE;
			using Storage = typename TYPE::StorageType;
			using Element = typename TYPE::LaneType;
			static constexpr int LaneMask = TYPE::LaneMask;

			//////////////////////////////////////////////////////////////////////////
			Quaternion();
			explicit Quaternion(typename TYPE::LaneType value);
			Quaternion(TYPE value);
			Quaternion(Element v0, Element v1, Element v2, Element v3);
			template <int I0, int I1, int I2, int I3>
			constexpr Quaternion(SIMD::LaneRef_4<TYPE, I0, I1, I2, I3>& ref);
			Quaternion(typename TYPE::Lanes_3, Element);

			//////////////////////////////////////////////////////////////////////////
			SIMD::LaneIndex<TYPE> CPF_VECTORCALL operator [](int idx);
			Element CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			/*
			Quaternion& CPF_VECTORCALL operator += (const Quaternion& rhs);
			Quaternion& CPF_VECTORCALL operator -= (const Quaternion& rhs);
			Quaternion& CPF_VECTORCALL operator *= (const Quaternion& rhs);
			Quaternion& CPF_VECTORCALL operator /= (const Quaternion& rhs);
			*/

			//////////////////////////////////////////////////////////////////////////
			static Quaternion CPF_VECTORCALL Zero();
			static Quaternion CPF_VECTORCALL Identity();
			template<typename ATYPE>
			static Quaternion CPF_VECTORCALL AxisAngle(ATYPE axis, Element radians);

			//////////////////////////////////////////////////////////////////////////
			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			//////////////////////////////////////////////////////////////////////////
			TYPE mVector;
			LANEREF_1_SWIZZLE(TYPE);
			LANEREF_2_SWIZZLE(TYPE);
			LANEREF_3_SWIZZLE(TYPE);
			LANEREF_4_SWIZZLE(TYPE);
		};
	}
}

#include "CPF/Math/Detail/Quaternion.inl"
#include "CPF/SIMD/Types.hpp"

namespace CPF
{
	namespace Math
	{
		using Quaternionf = Quaternion<SIMD::FPU::F32x4_4>;
//		using Quaterniond = tQuaternion<SIMD::FPU::F64x4_4>;

		// The base type is chosen at compile time.
		using Quaternionfv = Quaternion<SIMD::F32x4>;
		using Quaterniondv = Quaternion<SIMD::F64x4>;
	}
}
