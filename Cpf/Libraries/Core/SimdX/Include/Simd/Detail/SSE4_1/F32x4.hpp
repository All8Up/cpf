//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

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
			union alignas(16) F32x4_UInt324
			{
				uint32_t UInt32[4];
				__m128 mVector;
			};


			template <typename TYPE, int ALIGNMENT, int LANES, typename ELEMENT, typename TAG, int COUNT>
			struct alignas(ALIGNMENT)F32x4;

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

				F32x4& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				template <typename = std::enable_if<std::equal_to<int>()(kCount, 1), Element>::type>
				operator const Element() const { Element result; _mm_store_ss(&result, mVector); return result; }

				Type mVector;
			};

			//////////////////////////////////////////////////////////////////////////
			template<typename TAG, int COUNT>
			using F32x4_ = F32x4<__m128, 16, 4, float, TAG, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator == (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>::kCompareMask ==
					(F32x4_<TAG, COUNT>::kCompareMask & _mm_movemask_ps(_mm_cmpeq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator != (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>::kCompareMask == (F32x4_<TAG, COUNT>::kCompareMask & _mm_movemask_ps(_mm_cmpneq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator < (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>::kCompareMask == (F32x4_<TAG, COUNT>::kCompareMask & _mm_movemask_ps(_mm_cmplt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator <= (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>::kCompareMask == (F32x4_<TAG, COUNT>::kCompareMask & _mm_movemask_ps(_mm_cmple_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator > (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>::kCompareMask == (F32x4_<TAG, COUNT>::kCompareMask & _mm_movemask_ps(_mm_cmpgt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator >= (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>::kCompareMask == (F32x4_<TAG, COUNT>::kCompareMask & _mm_movemask_ps(_mm_cmpge_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}

			//////////////////////////////////////////////////////////////////////////
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL operator + (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>(_mm_add_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL operator - (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>(_mm_sub_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL operator * (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>(_mm_mul_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL operator / (const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>(_mm_div_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL Min(const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>(_mm_min_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL Max(const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs)
			{
				return F32x4_<TAG, COUNT>(_mm_max_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL Sqrt(const F32x4_<TAG, COUNT> value)
			{
				return F32x4_<TAG, COUNT>(_mm_sqrt_ps(static_cast<__m128>(value)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL Reciprocal(const F32x4_<TAG, COUNT> value)
			{
				return F32x4_<TAG, COUNT>(_mm_rcp_ps(static_cast<__m128>(value)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL RSqrt(const F32x4_<TAG, COUNT> value)
			{
				return F32x4_<TAG, COUNT>(_mm_rsqrt_ps(static_cast<__m128>(value)));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL Clamp(const F32x4_<TAG, COUNT> value, const F32x4_<TAG, COUNT> low, const F32x4_<TAG, COUNT> high)
			{
				return F32x4_<TAG, COUNT>(_mm_min_ps(static_cast<__m128>(high), _mm_max_ps(static_cast<__m128>(low), static_cast<__m128>(value))));
			}
			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE F32x4_<TAG, COUNT> CPF_VECTORCALL Abs(const F32x4_<TAG, COUNT> value)
			{
				static constexpr F32x4_UInt324 kSignBits = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
				return F32x4_<TAG, COUNT>(_mm_andnot_ps(kSignBits.mVector, static_cast<__m128>(value)));
			}

			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const float lhs, const float rhs, float tolerance)
			{
				return std::fabs(lhs - rhs) <= tolerance;
			}

			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const F32x4_<TAG, COUNT> lhs, const F32x4_<TAG, COUNT> rhs, float tolerance)
			{
				return Abs(lhs - rhs) <= F32x4_<TAG, COUNT>(tolerance);
			}

			template <typename TAG, int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Valid(const F32x4_<TAG, COUNT> value)
			{
				F32x4_<TAG, COUNT> test(_mm_mul_ps(static_cast<__m128>(value), _mm_setzero_ps()));
				test = _mm_cmpeq_ps(static_cast<__m128>(test), _mm_setzero_ps());
				int mask = _mm_movemask_ps(static_cast<__m128>(test));
				return(F32x4_<TAG, COUNT>::kCompareMask == (mask & F32x4_<TAG, COUNT>::kCompareMask));
			}

			//////////////////////////////////////////////////////////////////////////
			using F32x4_1 = F32x4<__m128, 16, 4, float, Count_1Tag, 1>;
			using F32x4_2 = F32x4<__m128, 16, 4, float, Count_2Tag, 2>;
			using F32x4_3 = F32x4<__m128, 16, 4, float, Count_3Tag, 3>;
			using F32x4_4 = F32x4<__m128, 16, 4, float, Count_4Tag, 4>;
		}
	}
}
