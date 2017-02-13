//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#if CPF_SIMD_SSE1==1
#	include <Configuration/Configuration.hpp>
#	include <xmmintrin.h>
#	include <Simd/Detail/Sse/Sse1/Float32x4.hpp>
#	include <Simd/Detail/Sse/Sse1/Float32x8.hpp>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Sse1
		{
			using Int8x16 = Simd::Reference::Int8x16;
			using Uint8x16 = Simd::Reference::Uint8x16;
			using Int16x8 = Simd::Reference::Int16x8;
//			using Uint16x8 = Simd::Reference::Uint16x8;
			using Int32x4 = Simd::Reference::Int32x4;
//			using Uint32x4 = Simd::Reference::Uint32x4;
//			using Int64x2 = Simd::Reference::Int64x2;
//			using Uint64x4 = Simd::Reference::Uint64x4;

			using Float64x4 = Simd::Reference::Float64x4;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
#endif
