//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/SSE4_1/Bool4.hpp"

namespace Cpf
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator == (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpeq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator == (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpeq_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator != (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpneq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator != (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpneq_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator < (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmplt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator < (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmplt_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator <= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmple_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator <= (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmple_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator > (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpgt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator > (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpgt_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator >= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpge_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator >= (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpge_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
		}
	}
}
