//////////////////////////////////////////////////////////////////////////
#pragma once
#include <smmintrin.h>

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, typename ELEMENT, typename TAG>
		struct SimdType
		{
			constexpr SimdType() {}
			constexpr SimdType(TYPE value) : mData(value) {}
			constexpr SimdType(ELEMENT value) : mData{ value, value, value, value } {}

			using TypeTag = TAG;
			TYPE mData;
		};

		struct float32x1_tag;
		struct float32x2_tag;
		struct float32x3_tag;
		struct float32x4_tag;

		using float32x1 = SimdType<__m128, float, float32x1_tag>;
		using float32x2 = SimdType<__m128, float, float32x2_tag>;
		using float32x3 = SimdType<__m128, float, float32x3_tag>;
		using float32x4 = SimdType<__m128, float, float32x4_tag>;
	}
}

#include "Simd/Float32x1.hpp"
#include "Simd/Float32x2.hpp"
#include "Simd/Float32x3.hpp"
#include "Simd/Float32x4.hpp"
