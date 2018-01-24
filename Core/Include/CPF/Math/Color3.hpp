//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		class Color3
		{
		public:
			using Type = TYPE;
			using StorageType = typename TYPE::StorageType;
			using LaneType = typename TYPE::LaneType;
			static constexpr int LaneMask = TYPE::LaneMask;

			Color3() {}
			Color3(const Color3& rhs);
			explicit Color3(LaneType v);
			explicit Color3(StorageType v);

		private:
			StorageType mData;
		};
	}
}

#include "CPF/SIMD/Types.hpp"
#include "CPF/SIMD/Detail/FPU/F32x3.hpp"
#include "CPF/SIMD/Detail/FPU/I32x3.hpp"

namespace CPF
{
	namespace Math
	{
		using Color3f = Color3<SIMD::FPU::F32x3_3>;
		using Color3i = Color3<SIMD::FPU::I32x3_3>;

		using Color3fv = Color3<SIMD::F32x4_3>;
		using Color3dv = Color3<SIMD::F64x4_3>;
		using Color3iv = Color3<SIMD::I32x4_3>;
	}
}
