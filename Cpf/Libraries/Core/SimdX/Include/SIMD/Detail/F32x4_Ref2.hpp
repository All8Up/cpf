//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <int I0, int I1>
		class F32x4_Ref2
		{
		public:
			F32x4_Ref2& operator = (F32x4_2 value);
			constexpr operator F32x4_2() const;

		private:
			F32x4_4* _Data() { return reinterpret_cast<F32x4_4*>(mData); }
			const F32x4_4* _Data() const { return reinterpret_cast<const F32x4_4*>(mData); }

			uint8_t mData[1];
		};

		template <int I0, int I1>
		F32x4_Ref2<I0, I1>& F32x4_Ref2<I0, I1>::operator =(F32x4_2 value)
		{

			return *this;
		}

		template <int I0, int I1>
		constexpr F32x4_Ref2<I0, I1>::operator F32x4_2() const
		{
			return F32x4_2(_mm_shuffle_ps(static_cast<__m128>(*_Data()), static_cast<__m128>(*_Data()), _MM_SHUFFLE(0, 0, I1, I0)));
		}
	}
}


#define F32X4_2_SWIZZLE_(s, v)	\
	Cpf::SIMD::F32x4_Ref2<s, 0> v##x;	\
	Cpf::SIMD::F32x4_Ref2<s, 1> v##y;	\
	Cpf::SIMD::F32x4_Ref2<s, 2> v##z;	\
	Cpf::SIMD::F32x4_Ref2<s, 3> v##w

#define F32X4_2_SWIZZLE		\
	F32X4_2_SWIZZLE_(0, x);	\
	F32X4_2_SWIZZLE_(1, y);	\
	F32X4_2_SWIZZLE_(2, z);	\
	F32X4_2_SWIZZLE_(3, w);
