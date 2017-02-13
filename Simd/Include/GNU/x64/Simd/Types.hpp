//////////////////////////////////////////////////////////////////////////
#pragma once


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
#elif CPF_SIMD_SSE2 // || CPF_SIMD_SSE1
#	define SIMD_LEVEL Sse2
#elif CPF_SIMD_SSE1
#	define SIMD_LEVEL Sse1
// NOTE: Only here for debugging reasons, x64 guarantee's Sse2 availability.
// Remove this section and re-add the detection of sse1 above.
#elif CPF_SIMD_REFERENCE
#	define SIMD_LEVEL Reference
#else
#	pragma message( "Unknown Simd Level: Defaulting to reference." )
#	define SIMD_LEVEL Reference

#endif


typedef int8_t Int8x16_ValueType __attribute__((__vector_size__(16)));
typedef int8_t Int8x32_ValueType __attribute__((__vector_size__(32)));
typedef uint8_t Uint8x16_ValueType __attribute__((__vector_size__(16)));
typedef uint8_t Uint8x32_ValueType __attribute__((__vector_size__(32)));

typedef int16_t Int16x8_ValueType __attribute__((__vector_size__(16)));
typedef int16_t Int16x16_ValueType __attribute__((__vector_size__(32)));
typedef uint16_t Uint16x8_ValueType __attribute__((__vector_size__(16)));
typedef uint16_t Uint16x16_ValueType __attribute__((__vector_size__(32)));

typedef int32_t Int32x4_ValueType __attribute__((__vector_size__(16)));
typedef int32_t Int32x8_ValueType __attribute__((__vector_size__(32)));
typedef uint32_t Uint32x4_ValueType __attribute__((__vector_size__(16)));
typedef uint32_t Uint32x8_ValueType __attribute__((__vector_size__(32)));

typedef int64_t Int64x2_ValueType __attribute__((__vector_size__(16)));
typedef int64_t Int64x4_ValueType __attribute__((__vector_size__(32)));
typedef uint64_t Uint64x2_ValueType __attribute__((__vector_size__(16)));
typedef uint64_t Uint64x4_ValueType __attribute__((__vector_size__(32)));

typedef float Float32x4_ValueType __attribute__((__vector_size__(16)));
typedef float Float32x8_ValueType __attribute__((__vector_size__(32)));
typedef double Float64x2_ValueType __attribute__((__vector_size__(16)));
typedef double Float64x4_ValueType __attribute__((__vector_size__(32)));


//////////////////////////////////////////////////////////////////////////
#include <Simd/Detail/Sse/Avx2.hpp>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		using Int8x16 = Simd::SIMD_LEVEL::Int8x16;
		using Uint8x16 = Simd::SIMD_LEVEL::Uint8x16;
//		using Int16x8 = Simd::SIMD_LEVEL::Int16x8;
//		using Uint16x8 = Simd::SIMD_LEVEL::Uint16x8;
//		using Int32x4 = Simd::SIMD_LEVEL::Int32x4;
//		using Uint32x4 = Simd::SIMD_LEVEL::Uint32x4;
//		using Int64x2 = Simd::SIMD_LEVEL::Int64x2;
//		using Uint64x2 = Simd::SIMD_LEVEL::Uint64x2;

		using Float32x4 = Simd::SIMD_LEVEL::Float32x4;
		using Float32x8 = Simd::SIMD_LEVEL::Float32x8;
//		using Float64x2 = Simd::SIMD_LEVEL::Float64x2;
//		using Float64x4 = Simd::SIMD_LEVEL::Float64x4;
	}
}
