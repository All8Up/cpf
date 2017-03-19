//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Types.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

namespace Cpf
{
	namespace Math
	{
		using float2 = Vector2<SIMD::F32x4_2>;
		using float3 = Vector3<SIMD::F32x4_3>;
		using float4 = Vector4<SIMD::F32x4>;

		using int2 = Vector2<SIMD::I32x4_2>;
		using int3 = Vector2<SIMD::I32x4_3>;
		using int4 = Vector2<SIMD::I32x4>;

		// Eventual types.
		// For purposes of things which don't use vectorized types (networking, file formats etc)
		// a set of types need to exist which don't use 4 unit types.  Need to decide on how
		// that will be named.  The problem is what's a good naming scheme given I want to maintain
		// the hlsl names?  Or perhaps drop that and go back to post fixing?
		/*
		using float2x2 = Math::Matrix2x2<F32x4_2>;
		using float3x3 = Math::Matrix3x3<F32x4_3>;
		using float4x4 = Math::Matrix4x4<F32x4_4>;

		using int2x2 = Math::Matrix2x2<I32x4_2>;
		using int3x3 = Math::Matrix2x2<I32x4_3>;
		using int4x4 = Math::Matrix2x2<I32x4_4>;
		*/
	}
}
