//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#include <Simd/Detail/Sse/Sse1.hpp>
#if CPF_SIMD_SSE2
#	include <emmintrin.h>
#	include <Simd/Detail/Sse/Sse2/Int8x16.hpp>
#	include <Simd/Detail/Sse/Sse2/Float32x4.hpp>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Sse2
		{
			using Uint8x16 = Simd::Sse1::Uint8x16;
			using Int16x8 = Simd::Sse1::Int16x8;
//			using Uint16x8 = Simd::Sse1::Uint16x8;
			using Int32x4 = Simd::Sse1::Int32x4;
//			using Uint32x4 = Simd::Sse1::Uint32x4;

			using Float32x8 = Sse1::Float32x8;
			using Float64x4 = Sse1::Float64x4;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
#endif
