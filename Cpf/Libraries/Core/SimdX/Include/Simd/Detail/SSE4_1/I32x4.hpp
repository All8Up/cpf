//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <immintrin.h>

namespace Cpf
{
	namespace SIMD
	{
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
				__m128i mVector;
			};


			template <typename TYPE, int ALIGNMENT, int LANES, typename ELEMENT, typename TAG, int COUNT>
			struct alignas(ALIGNMENT)I32x4;

			//////////////////////////////////////////////////////////////////////////
			template<typename TAG, int COUNT>
			struct alignas(16) I32x4<__m128i, 16, 4, int32_t, TAG, COUNT>
			{
				static constexpr int kAlignment = 16;
				using Type = __m128i;
				static constexpr int Lanes = 4;
				using Element = int32_t;
				static constexpr int kCount = COUNT;
				static constexpr int kCompareMask = (1 << kCount) - 1;

				constexpr I32x4() {}
				constexpr I32x4(Element value) : mVector(_mm_setr_epi32(value, value, value, value)) {}
				template <typename = std::enable_if<COUNT == 2, Element>::type>
				constexpr I32x4(Element v0, Element v1) : mVector(_mm_setr_epi32(v0, v1, 0, 0)) {}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				constexpr I32x4(Element v0, Element v1, Element v2) : mVector(_mm_setr_epi32(v0, v1, v2, 0)) {}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				constexpr I32x4(Element v0, Element v1, Element v2, Element v3) : mVector(_mm_setr_epi32(v0, v1, v2, v3)) {}

				explicit constexpr I32x4(Type value) : mVector(value) {}

				I32x4& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				template <typename = std::enable_if<std::equal_to<int>()(kCount, 1), Element>::type>
				operator const Element() const
				{
					return _mm_cvtsi128_si32(mVector);
				}

				Type mVector;
			};

			template<typename TAG, int COUNT>
			using I32x4_ = I32x4<__m128i, 16, 4, int32_t, TAG, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator == (const I32x4_<TAG, COUNT> lhs, const I32x4_<TAG, COUNT> rhs)
			{
				return TYPE::kCompareMask == (TYPE::kCompareMask & _mm_movemask_ps(_mm_cmpieq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
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
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL operator + (const I32x4_<TAG, COUNT> lhs, const I32x4_<TAG, COUNT> rhs)
			{
				return I32x4_<TAG, COUNT>(_mm_add_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL operator - (const I32x4_<TAG, COUNT> lhs, const I32x4_<TAG, COUNT> rhs)
			{
				return I32x4_<TAG, COUNT>(_mm_sub_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL operator * (const I32x4_<TAG, COUNT> lhs, const I32x4_<TAG, COUNT> rhs)
			{
				return I32x4_<TAG, COUNT>(_mm_mul_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL operator / (const I32x4_<TAG, COUNT> lhs, const I32x4_<TAG, COUNT> rhs)
			{
				// WTF, where is the instruction??
				// return I32x4_<TAG, COUNT><TAG, COUNT>(_mm_div_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
				// floating point based solution for the time being.
				auto l = _mm_cvtepi32_ps(static_cast<__m128i>(lhs));
				auto r = _mm_cvtepi32_ps(static_cast<__m128i>(rhs));
				return I32x4_<TAG, COUNT>(_mm_cvttps_epi32(_mm_div_ps(l, r)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL Min(const I32x4_<TAG, COUNT> lhs, const I32x4_<TAG, COUNT> rhs)
			{
				return I32x4_<TAG, COUNT>(_mm_min_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL Max(const I32x4_<TAG, COUNT> lhs, const I32x4_<TAG, COUNT> rhs)
			{
				return I32x4_<TAG, COUNT>(_mm_max_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL Clamp(const I32x4_<TAG, COUNT> value, const I32x4_<TAG, COUNT> low, const I32x4_<TAG, COUNT> high)
			{
				return I32x4_<TAG, COUNT>(_mm_min_epi32(static_cast<__m128>(high), _mm_max_epi32(static_cast<__m128i>(low), static_cast<__m128i>(value))));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE I32x4_<TAG, COUNT> CPF_VECTORCALL Abs(const I32x4_<TAG, COUNT> value)
			{
				static constexpr UInt32x4 kSignBits = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
				return TYPE(_mm_andnot_epi32(kSignBits.mVector, static_cast<__m128i>(value)));
			}

			//////////////////////////////////////////////////////////////////////////
			using I32x4_1 = I32x4<__m128i, 16, 4, int32_t, Count_1Tag, 1>;
			using I32x4_2 = I32x4<__m128i, 16, 4, int32_t, Count_2Tag, 2>;
			using I32x4_3 = I32x4<__m128i, 16, 4, int32_t, Count_3Tag, 3>;
			using I32x4_4 = I32x4<__m128i, 16, 4, int32_t, Count_4Tag, 4>;
		}
	}
}
