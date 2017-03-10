//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <int I0, int I1, int I2>
		class F32x4_Ref3
		{
		public:
			F32x4_Ref3& operator = (F32x4_3 value);
			constexpr operator F32x4_3() const;

		private:
			F32x4_4* _Data() { return reinterpret_cast<F32x4_4*>(mData); }
			const F32x4_4* _Data() const { return reinterpret_cast<const F32x4_4*>(mData); }

			uint8_t mData[1];
		};

		template <int I0, int I1, int I2>
		F32x4_Ref3<I0, I1, I2>& F32x4_Ref3<I0, I1, I2>::operator =(F32x4_3 value)
		{

			return *this;
		}

		template <int I0, int I1, int I2>
		constexpr F32x4_Ref3<I0, I1, I2>::operator F32x4_3() const
		{
			return F32x4_3(_mm_shuffle_ps(static_cast<__m128>(*_Data()), static_cast<__m128>(*_Data()), _MM_SHUFFLE(0, I2, I1, I0)));
		}
	}
}


#define F32X4_3_SWIZZLE_3(a, an, b, bn)			\
	Cpf::SIMD::F32x4_Ref3<a, b, 0> an##bn##x;	\
	Cpf::SIMD::F32x4_Ref3<a, b, 1> an##bn##y;	\
	Cpf::SIMD::F32x4_Ref3<a, b, 2> an##bn##z;	\
	Cpf::SIMD::F32x4_Ref3<a, b, 3> an##bn##w;

#define F32X4_3_SWIZZLE_2(a, an)	\
	F32X4_3_SWIZZLE_3(a, an, 0, x)	\
	F32X4_3_SWIZZLE_3(a, an, 1, y)	\
	F32X4_3_SWIZZLE_3(a, an, 2, z)	\
	F32X4_3_SWIZZLE_3(a, an, 3, w)

#define F32X4_3_SWIZZLE		\
	F32X4_3_SWIZZLE_2(0, x)	\
	F32X4_3_SWIZZLE_2(1, y)	\
	F32X4_3_SWIZZLE_2(2, z)	\
	F32X4_3_SWIZZLE_2(3, w)
