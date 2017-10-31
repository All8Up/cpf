//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/SSE4_1/Bool4.hpp"

namespace CPF
{
	namespace SIMD
	{
		namespace SSE4_1
		{
#if 0
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator == (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpeq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator == (const F64x4_<1> lhs, const typename F64x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpeq_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator != (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpneq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator != (const F64x4_<1> lhs, const typename F64x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpneq_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator < (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmplt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator < (const F64x4_<1> lhs, const typename F64x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmplt_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
#endif
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator <= (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				auto m0 = _mm_movemask_pd(_mm_cmple_pd(lhs.mSIMD.mData[0], rhs.mSIMD.mData[0]));
				auto m1 = _mm_movemask_pd(_mm_cmple_pd(lhs.mSIMD.mData[1], rhs.mSIMD.mData[1]));
				auto mask = ((m0 << 2) + m1) & Bool4_<COUNT>::LaneMask;
				return Bool4_<COUNT>(_mm_set_epi32(
					(mask&8) ? -1 : 0,
					(mask&4) ? -1 : 0,
					(mask&2) ? -1 : 0,
					(mask&1) ? -1 : 0));
			}

#if 0
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator <= (const F64x4_<1> lhs, const typename F64x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmple_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator > (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpgt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator > (const F64x4_<1> lhs, const typename F64x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpgt_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE Bool4_<COUNT> CPF_VECTORCALL operator >= (const F64x4_<COUNT> lhs, const F64x4_<COUNT> rhs)
			{
				return Bool4_<COUNT>(_mm_castps_si128(
					_mm_cmpge_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs))));
			}
			CPF_FORCE_INLINE Bool4_<1> CPF_VECTORCALL operator >= (const F64x4_<1> lhs, const typename F64x4_<1>::LaneType rhs)
			{
				return Bool4_<1>(_mm_castps_si128(
					_mm_cmpge_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs))));
			}
#endif
		}
	}
}
