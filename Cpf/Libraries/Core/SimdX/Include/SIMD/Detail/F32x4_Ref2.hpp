//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1>
		class F32x4_Ref2
		{
		public:
			constexpr operator typename TYPE::F32x4_2() const;

		private:
			typename TYPE::F32x4_4* _Data() { return reinterpret_cast<typename TYPE::F32x4_4*>(mData); }
			const typename TYPE::F32x4_4* _Data() const { return reinterpret_cast<const typename TYPE::F32x4_4*>(mData); }

			uint8_t mData[1];
		};

		template <typename TYPE, int I0, int I1>
		constexpr F32x4_Ref2<TYPE, I0, I1>::operator typename TYPE::F32x4_2() const
		{
			return typename TYPE::F32x4_2(_mm_shuffle_ps(static_cast<__m128>(*_Data()), static_cast<__m128>(*_Data()), _MM_SHUFFLE(0, 0, I1, I0)));
		}
	}
}


#define F32X4_2_SWIZZLE_(t, s, v)			\
	Cpf::SIMD::F32x4_Ref2<t, s, 0> v##x;	\
	Cpf::SIMD::F32x4_Ref2<t, s, 1> v##y;	\
	Cpf::SIMD::F32x4_Ref2<t, s, 2> v##z;	\
	Cpf::SIMD::F32x4_Ref2<t, s, 3> v##w

#define F32X4_2_SWIZZLE(type)		\
	F32X4_2_SWIZZLE_(type, 0, x);	\
	F32X4_2_SWIZZLE_(type, 1, y);	\
	F32X4_2_SWIZZLE_(type, 2, z);	\
	F32X4_2_SWIZZLE_(type, 3, w);
