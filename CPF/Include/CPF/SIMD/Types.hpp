//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/SIMD/Detail/FPU/F32x4.hpp"
#include "CPF/SIMD/Detail/FPU/I32x4.hpp"
#include "CPF/SIMD/Detail/Reference/F32x4.hpp"
#include "CPF/SIMD/Detail/Reference/F64x4.hpp"
#include "CPF/SIMD/Detail/Reference/I32x4.hpp"
#include "CPF/SIMD/Detail/SSE4_1/F32x4.hpp"
#include "CPF/SIMD/Detail/SSE4_1/F64x4.hpp"
#include "CPF/SIMD/Detail/SSE4_1/I32x4.hpp"

namespace CPF
{
	namespace SIMD
	{
#if CPF_SIMD_AVX2 || CPF_SIMD_AVX || CPF_SIMD_SSE4a || CPF_SIMD_SSE4_2 || CPF_SIMD_SSE4_1 || CPF_SIMD_SSE3
		//////////////////////////////////////////////////////////////////////////
		using F32x4_1 = SSE4_1::F32x4_1;
		using F32x4_2 = SSE4_1::F32x4_2;
		using F32x4_3 = SSE4_1::F32x4_3;
		using F32x4 = SSE4_1::F32x4_4;

		using F64x4_1 = SSE4_1::F64x4_1;
		using F64x4_2 = SSE4_1::F64x4_2;
		using F64x4_3 = SSE4_1::F64x4_3;
		using F64x4 = SSE4_1::F64x4_4;

		using I32x4_1 = SSE4_1::I32x4_1;
		using I32x4_2 = SSE4_1::I32x4_2;
		using I32x4_3 = SSE4_1::I32x4_3;
		using I32x4 = SSE4_1::I32x4_4;
#else
		//////////////////////////////////////////////////////////////////////////
		using F32x4_1 = Reference::F32x4_1;
		using F32x4_2 = Reference::F32x4_2;
		using F32x4_3 = Reference::F32x4_3;
		using F32x4 = Reference::F32x4_4;

		using F64x4_1 = Reference::F64x4_1;
		using F64x4_2 = Reference::F64x4_2;
		using F64x4_3 = Reference::F64x4_3;
		using F64x4 = Reference::F64x4_4;

		using I32x4_1 = Reference::I32x4_1;
		using I32x4_2 = Reference::I32x4_2;
		using I32x4_3 = Reference::I32x4_3;
		using I32x4 = Reference::I32x4_4;
#endif
	}
}
