//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#include <Simd/Detail/Sse/Sse2.hpp>
#if CPF_SIMD_SSE3
#include <Simd/Detail/Sse/Sse3/Float32x4.hpp>

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Sse3
		{
			using Int8x16 = Simd::Sse2::Int8x16;
			using Uint8x16 = Simd::Sse2::Uint8x16;
			using Int16x8 = Simd::Sse2::Int16x8;
//			using Uint16x8 = Simd::Sse2::Uint16x8;
			using Int32x4 = Simd::Sse2::Int32x4;
//			using Uint32x4 = Simd::Sse2::Uint32x4;

			using Float32x8 = Sse2::Float32x8;
			using Float64x4 = Sse2::Float64x4;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
#endif
