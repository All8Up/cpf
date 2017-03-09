//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		/*
		Let's get the bit WTF question out of the way, why wrap up a
		vector 4 to be representable as a 1 through 4 sized vector?
		Later, in the actual vector math classes there needs to be
		consistent handling of 1-4 sizes so the various accessors such
		as v.x, v.xy, v.xyz are still represented by registers in order
		to prevent spilling to memory and breaking pipelining.
		*/

		// Tags to allow the same primitive type, __m128 in VC, to represent
		// more fine grained divisions in a type safe manner.
		struct F32x4_1Tag;
		struct F32x4_2Tag;
		struct F32x4_3Tag;
		struct F32x4_4Tag;

		/*
		This layer is intended to provide a type safe abstraction on top
		of the simd types.  While this is implemented in terms of VC it
		is intended to extend over to GCC/Clang and wrap the vector types
		there, which should be a bit easier.
		*/
		inline namespace SSE4_1
		{
			union alignas(16) UInt32x4
			{
				uint32_t UInt32[4];
				__m128 mVector;
			};


			template <typename TYPE, int ALIGNMENT, int LANES, typename ELEMENT, typename TAG, int COUNT>
			struct alignas(ALIGNMENT) F32x4;

			//////////////////////////////////////////////////////////////////////////
			template<typename TAG, int COUNT>
			struct alignas(16) F32x4<__m128, 16, 4, float, TAG, COUNT>
			{
				static constexpr int kAlignment = 16;
				using Type = __m128;
				static constexpr int Lanes = 4;
				using Element = float;
				static constexpr int kCount = COUNT;
				static constexpr int kCompareMask = (1 << kCount) - 1;

				constexpr F32x4() {}
				constexpr F32x4(Element value) : mVector{ value, value, value, value } {}
				template <typename = std::enable_if<COUNT == 2, Element>::type>
				constexpr F32x4(Element v0, Element v1) : mVector{ v0, v1, 0.0f, 0.0f } {}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				constexpr F32x4(Element v0, Element v1, Element v2) : mVector{ v0, v1, v2, 0.0f } {}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				constexpr F32x4(Element v0, Element v1, Element v2, Element v3) : mVector{ v0, v1, v2, v3 } {}

				explicit constexpr F32x4(Type value) : mVector(value) {}

				constexpr F32x4& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				template <typename = std::enable_if<std::equal_to<int>()(kCount, 1), Element>::type>
				operator const Element () const { Element result; _mm_store_ss(&result, mVector); return result; }

				Type mVector;
			};

			//////////////////////////////////////////////////////////////////////////
			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator == (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kCompareMask == (TYPE::kCompareMask & _mm_movemask_ps(_mm_cmpeq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator != (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kCompareMask == (TYPE::kCompareMask & _mm_movemask_ps(_mm_cmpneq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator < (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kCompareMask == (TYPE::kCompareMask & _mm_movemask_ps(_mm_cmplt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator <= (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kCompareMask == (TYPE::kCompareMask & _mm_movemask_ps(_mm_cmple_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator > (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kCompareMask == (TYPE::kCompareMask & _mm_movemask_ps(_mm_cmpgt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator >= (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kCompareMask == (TYPE::kCompareMask & _mm_movemask_ps(_mm_cmpge_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}

			//////////////////////////////////////////////////////////////////////////
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL operator + (const TYPE lhs, const TYPE rhs)
			{
				return TYPE(_mm_add_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL operator - (const TYPE lhs, const TYPE rhs)
			{
				return TYPE(_mm_sub_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL operator * (const TYPE lhs, const TYPE rhs)
			{
				return TYPE(_mm_mul_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL operator / (const TYPE lhs, const TYPE rhs)
			{
				return TYPE(_mm_div_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL Min(const TYPE lhs, const TYPE rhs)
			{
				return TYPE(_mm_min_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL Max(const TYPE lhs, const TYPE rhs)
			{
				return TYPE(_mm_max_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL Sqrt(const TYPE value)
			{
				return TYPE(_mm_sqrt_ps(static_cast<__m128>(value)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL Reciprocal(const TYPE value)
			{
				return TYPE(_mm_rcp_ps(static_cast<__m128>(value)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL RSqrt(const TYPE value)
			{
				return TYPE(_mm_rsqrt_ps(static_cast<__m128>(value)));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL Clamp(const TYPE value, const TYPE low, const TYPE high)
			{
				return TYPE(_mm_min_ps(static_cast<__m128>(high), _mm_max_ps(static_cast<__m128>(low), static_cast<__m128>(value))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE TYPE CPF_VECTORCALL Abs(const TYPE value)
			{
				static constexpr UInt32x4 kSignBits = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
				return TYPE(_mm_andnot_ps(kSignBits.mVector, static_cast<__m128>(value)));
			}

			// TODO: This is used right now to avoid ambiguity given needs of the x1 type.
			// Should be possible to prevent instantiation of the other near to prevent conversions to float in x1 types.
			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const float lhs, const float rhs, float tolerance)
			{
				// TODO: Should probably leave this in registers.
				return std::abs(lhs - rhs) <= tolerance;
			}

			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const TYPE lhs, const TYPE rhs, float tolerance)
			{
				return Abs(lhs - rhs) <= TYPE(tolerance);
			}

			template <typename TYPE>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Valid(const TYPE value)
			{
				TYPE test(_mm_mul_ps(static_cast<__m128>(value), _mm_setzero_ps()));
				test = _mm_cmpeq_ps(static_cast<__m128>(test), _mm_setzero_ps());
				int mask = _mm_movemask_ps(static_cast<__m128>(test));
				return(TYPE::kCompareMask == (mask & TYPE::kCompareMask));
			}

			//////////////////////////////////////////////////////////////////////////
			using F32x4_1 = F32x4<__m128, 16, 4, float, F32x4_1Tag, 1>;
			using F32x4_2 = F32x4<__m128, 16, 4, float, F32x4_2Tag, 2>;
			using F32x4_3 = F32x4<__m128, 16, 4, float, F32x4_3Tag, 3>;
			using F32x4_4 = F32x4<__m128, 16, 4, float, F32x4_4Tag, 4>;
		}

		using F32x1 = SSE4_1::F32x4_1;
		using F32x2 = SSE4_1::F32x4_2;
		using F32x3 = SSE4_1::F32x4_3;
		using F32x4 = SSE4_1::F32x4_4;
	}
}
