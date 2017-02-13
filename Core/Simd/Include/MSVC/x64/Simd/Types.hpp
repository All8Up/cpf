//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#include <Simd/Detail/Reference/All.hpp>


//////////////////////////////////////////////////////////////////////////
// Msvc lets you use any of the intrinsics even if the compiler is not
// setup for it.  As such, we just define all the types needed even if they
// will not be used.
#include <immintrin.h>

typedef __m128i Int8x16_ValueType;
typedef __m256i Int8x32_ValueType;
typedef __m128i Uint8x16_ValueType;
typedef __m256i Uint8x32_ValueType;

typedef __m128i Int16x8_ValueType;
typedef __m256i Int16x16_ValueType;
typedef __m128i Uint16x8_ValueType;
typedef __m256i Uint16x16_ValueType;

typedef __m128i Int32x4_ValueType;
typedef __m256i Int32x8_ValueType;
typedef __m128i Uint32x4_ValueType;
typedef __m256i Uint32x8_ValueType;

typedef __m128i Int64x2_ValueType;
typedef __m256i Int64x4_ValueType;
typedef __m128i Uint64x2_ValueType;
typedef __m256i Uint64x4_ValueType;

typedef __m128 Float32x4_ValueType;
typedef __m256 Float32x8_ValueType;
typedef __m128 Float64x2_ValueType;
typedef __m256 Float64x4_ValueType;


//////////////////////////////////////////////////////////////////////////
#include <Simd/Detail/Sse/Avx2.hpp>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		enum : int32_t
		{
			eX,
			eY,
			eZ,
			eW
		};
		struct Elements2
		{
			int32_t _0 : 4;
			int32_t _1 : 4;
		};
		struct Elements3
		{
			int32_t _0 : 4;
			int32_t _1 : 4;
			int32_t _2 : 4;
		};
		struct Elements4
		{
			int32_t _0 : 4;
			int32_t _1 : 4;
			int32_t _2 : 4;
			int32_t _4 : 4;
		};

		using Int8x16 = CPF_SIMD_LEVEL::Int8x16;
		using Uint8x16 = CPF_SIMD_LEVEL::Uint8x16;
//		using Int16x8 = CPF_SIMD_LEVEL::Int16x8;
//		using Uint16x8 = CPF_SIMD_LEVEL::Uint16x8;
//		using Int32x4 = CPF_SIMD_LEVEL::Int32x4;
//		using Uint32x4 = CPF_SIMD_LEVEL::Uint32x4;
//		using Int64x2 = CPF_SIMD_LEVEL::Int64x2;
//		using Uint64x2 = CPF_SIMD_LEVEL::Uint64x2;

		using Float32x4 = CPF_SIMD_LEVEL::Float32x4;
		using Float32x8 = CPF_SIMD_LEVEL::Float32x8;
//		using Float64x2 = CPF_SIMD_LEVEL::Float64x2;
		using Float64x4 = CPF_SIMD_LEVEL::Float64x4;
	}
}
