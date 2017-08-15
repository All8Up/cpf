//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator == (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::LaneMask & _mm_movemask_ps(_mm_cmpeq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator == (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return (F32x4_<1>::LaneMask & _mm_movemask_ps(_mm_cmpeq_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs)))) == F32x4_<1>::LaneMask;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator != (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::LaneMask & _mm_movemask_ps(_mm_cmpneq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator != (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return (F32x4_<1>::LaneMask & _mm_movemask_ps(_mm_cmpneq_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs)))) == F32x4_<1>::LaneMask;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator < (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::LaneMask & _mm_movemask_ps(_mm_cmplt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator < (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return (F32x4_<1>::LaneMask & _mm_movemask_ps(_mm_cmplt_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs)))) == F32x4_<1>::LaneMask;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::LaneMask & _mm_movemask_ps(_mm_cmple_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator <= (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return (F32x4_<1>::LaneMask & _mm_movemask_ps(_mm_cmple_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs)))) == F32x4_<1>::LaneMask;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator > (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::LaneMask & _mm_movemask_ps(_mm_cmpgt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator > (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return (F32x4_<1>::LaneMask & _mm_movemask_ps(_mm_cmpgt_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs)))) == F32x4_<1>::LaneMask;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::LaneMask & _mm_movemask_ps(_mm_cmpge_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			CPF_FORCE_INLINE bool CPF_VECTORCALL operator >= (const F32x4_<1> lhs, const typename F32x4_<1>::LaneType rhs)
			{
				return (F32x4_<1>::LaneMask & _mm_movemask_ps(_mm_cmpge_ps(static_cast<__m128>(lhs), _mm_set1_ps(rhs)))) == F32x4_<1>::LaneMask;
			}
		}
	}
}
