//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/F32x4_Ref1.hpp"
#include "SIMD/Detail/F32x4_Ref2.hpp"
#include "SIMD/Detail/F32x4_Ref3.hpp"
#include "SIMD/Detail/F32x4_Ref4.hpp"

namespace Cpf
{
	namespace SIMD
	{
		union Float32x4
		{
			Float32x4();
			Float32x4(float _0123);
			Float32x4(float _0, float _1, float _2, float _3);

			Float32x4(F32x4_2 _01, float _2, float _3);
			Float32x4(float _0, F32x4_2 _12, float _3);
			Float32x4(float _0, float _1, F32x4_2 _23);
			Float32x4(F32x4_2 _01, F32x4_2 _23);

			Float32x4(F32x4_3 _012, float _3);
			Float32x4(float _0, F32x4_3 _123);

			Float32x4(F32x4_4 _0123);

			F32x4_4 mVector;
			F32x4_Ref1<0> x;
			F32x4_Ref1<1> y;
			F32x4_Ref1<2> z;
			F32x4_Ref1<3> w;

			F32X4_2_SWIZZLE;
			F32X4_3_SWIZZLE;
			F32X4_4_SWIZZLE;
		};

		inline Float32x4::Float32x4() {}

		inline Float32x4::Float32x4(float _0123) : mVector(_0123) {}

		inline Float32x4::Float32x4(float _0, float _1, float _2, float _3)
			: mVector{ _0, _1, _2, _3 }
		{}

		inline Float32x4::Float32x4(F32x4_2 _01, float _2, float _3)
			: mVector(_01, _2, _3)
		{}

		inline Float32x4::Float32x4(float _0, F32x4_2 _12, float _3)
			: mVector(_0, _12, _3)
		{}

		inline Float32x4::Float32x4(float _0, float _1, F32x4_2 _23)
			: mVector(_0, _1, _23)
		{}

		inline Float32x4::Float32x4(F32x4_2 _01, F32x4_2 _23)
			: mVector(_01, _23)
		{}

		inline Float32x4::Float32x4(F32x4_3 _012, float _3)
			: mVector(_012, _3)
		{}

		inline Float32x4::Float32x4(float _0, F32x4_3 _123)
			: mVector(_0, _123)
		{}

		inline Float32x4::Float32x4(F32x4_4 _0123)
			: mVector(_0123)
		{}
	}
}
