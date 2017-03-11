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
		template <typename TYPE>
		union Float32x4
		{
			Float32x4();
			Float32x4(float _0123);
			Float32x4(float _0, float _1, float _2, float _3);

			Float32x4(typename TYPE::F32x4_2 _01, float _2, float _3);
			Float32x4(float _0, typename TYPE::F32x4_2 _12, float _3);
			Float32x4(float _0, float _1, typename TYPE::F32x4_2 _23);
			Float32x4(typename TYPE::F32x4_2 _01, typename TYPE::F32x4_2 _23);

			Float32x4(typename TYPE::F32x4_3 _012, float _3);
			Float32x4(float _0, typename TYPE::F32x4_3 _123);

			Float32x4(typename TYPE::F32x4_4 _0123);

			TYPE mVector;
			F32x4_Ref1<TYPE, 0> x;
			F32x4_Ref1<TYPE, 1> y;
			F32x4_Ref1<TYPE, 2> z;
			F32x4_Ref1<TYPE, 3> w;

			F32X4_2_SWIZZLE(TYPE);
			F32X4_3_SWIZZLE(TYPE);
			F32X4_4_SWIZZLE(TYPE);
		};

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4() {}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(float _0123) : mVector(_0123) {}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(float _0, float _1, float _2, float _3)
			: mVector{ _0, _1, _2, _3 }
		{}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(typename TYPE::F32x4_2 _01, float _2, float _3)
			: mVector(_01, _2, _3)
		{}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(float _0, typename TYPE::F32x4_2 _12, float _3)
			: mVector(_0, _12, _3)
		{}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(float _0, float _1, typename TYPE::F32x4_2 _23)
			: mVector(_0, _1, _23)
		{}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(typename TYPE::F32x4_2 _01, typename TYPE::F32x4_2 _23)
			: mVector(_01, _23)
		{}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(typename TYPE::F32x4_3 _012, float _3)
			: mVector(_012, _3)
		{}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(float _0, typename TYPE::F32x4_3 _123)
			: mVector(_0, _123)
		{}

		template <typename TYPE>
		inline Float32x4<TYPE>::Float32x4(typename TYPE::F32x4_4 _0123)
			: mVector(_0123)
		{}

		template <typename TYPE>
		CPF_FORCE_INLINE Float32x4<TYPE> CPF_VECTORCALL operator - (const Float32x4<TYPE> lhs, const Float32x4<TYPE> rhs) { return lhs.mVector - rhs.mVector; }
		template <typename TYPE>
		CPF_FORCE_INLINE Float32x4<TYPE> CPF_VECTORCALL operator * (const Float32x4<TYPE> lhs, const Float32x4<TYPE> rhs) { return lhs.mVector * rhs.mVector; }

		template <typename TYPE>
		CPF_FORCE_INLINE Float32x4<TYPE> CPF_VECTORCALL Min(const Float32x4<TYPE> lhs, const Float32x4<TYPE> rhs) { return Min(lhs.mVector, rhs.mVector); }
		template <typename TYPE>
		CPF_FORCE_INLINE Float32x4<TYPE> CPF_VECTORCALL Max(const Float32x4<TYPE> lhs, const Float32x4<TYPE> rhs) { return Max(lhs.mVector, rhs.mVector); }

		template <typename TYPE>
		CPF_FORCE_INLINE float CPF_VECTORCALL HMin(const Float32x4<TYPE> value) { return HMin(value.mVector); }
		template <typename TYPE>
		CPF_FORCE_INLINE float CPF_VECTORCALL HMax(const Float32x4<TYPE> value) { return HMax(value.mVector); }
	}
}
