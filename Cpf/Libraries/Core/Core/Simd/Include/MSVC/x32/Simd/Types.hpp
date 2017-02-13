//////////////////////////////////////////////////////////////////////////
#pragma once
#pragma message( "Msvc x32 Simd Types.hpp" )


//////////////////////////////////////////////////////////////////////////
#include <Simd/Detail/Reference/All.hpp>


//////////////////////////////////////////////////////////////////////////
#if CPF_SIMD_AVX2
#	define SIMD_LEVEL Avx2
#elif CPF_SIMD_AVX
#	define SIMD_LEVEL Avx
#elif CPF_SIMD_SSE4a
#	define SIMD_LEVEL Sse4a
#elif CPF_SIMD_SSE4_2
#	define SIMD_LEVEL Sse4_2
#elif CPF_SIMD_SSE4_1
#	define SIMD_LEVEL Sse4_1
#elif CPF_SIMD_SSE3
#	define SIMD_LEVEL Sse3
#elif CPF_SIMD_SSE2
#	define SIMD_LEVEL Sse2
#elif CPF_SIMD_SSE1
#	define SIMD_LEVEL Sse1
#elif CPF_SIMD_REFERENCE
#	define SIMD_LEVEL Reference
#else
#	pragma message( "Unknown Simd Level: Defaulting to reference." )
#	define SIMD_LEVEL Reference
#endif


//////////////////////////////////////////////////////////////////////////
#include <Simd/Detail/Sse/Avx2.hpp>


//////////////////////////////////////////////////////////////////////////
namespace Simd
{
	using Int8x16 = Simd::SIMD_LEVEL::Int8x16;
	using Uint8x16 = Simd::SIMD_LEVEL::Uint8x16;
//	using Int16x8 = Simd::SIMD_LEVEL::Int16x8;
//	using Uint16x8 = Simd::SIMD_LEVEL::Uint16x8;
//	using Int32x4 = Simd::SIMD_LEVEL::Int32x4;
//	using Uint32x4 = Simd::SIMD_LEVEL::Uint32x4;
//	using Int64x2 = Simd::SIMD_LEVEL::Int64x2;
//	using Uint64x2 = Simd::SIMD_LEVEL::Uint64x2;

	using Float32x4 = Simd::SIMD_LEVEL::Float32x4;
	using Float32x8 = Simd::SIMD_LEVEL::Float32x8;
//	using Float64x2 = Simd::SIMD_LEVEL::Float64x2;
//	using Float64x4 = Simd::SIMD_LEVEL::Float64x4;
}
