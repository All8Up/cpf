//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <int I0, int I1, int I2, int I3>
		class F32x4_Ref4
		{
		public:
			F32x4_Ref4& operator = (F32x4_4 value);
			constexpr operator F32x4_4() const;

		private:
			F32x4_4* _Data() { return reinterpret_cast<F32x4_4*>(mData); }
			const F32x4_4* _Data() const { return reinterpret_cast<const F32x4_4*>(mData); }

			uint8_t mData[1];
		};

		template <int I0, int I1, int I2, int I3>
		F32x4_Ref4<I0, I1, I2, I3>& F32x4_Ref4<I0, I1, I2, I3>::operator =(F32x4_4 value)
		{

			return *this;
		}

		template <int I0, int I1, int I2, int I3>
		constexpr F32x4_Ref4<I0, I1, I2, I3>::operator F32x4_4() const
		{
			return F32x4_4(_mm_shuffle_ps(static_cast<__m128>(*_Data()), static_cast<__m128>(*_Data()), _MM_SHUFFLE(I3, I2, I1, I0)));
		}
	}
}


#define F32X4_4_SWIZZLE_4(a, an, b, bn, c, cn)			\
	Cpf::SIMD::F32x4_Ref4<a, b, c, 0> an##bn##cn##x;	\
	Cpf::SIMD::F32x4_Ref4<a, b, c, 1> an##bn##cn##y;	\
	Cpf::SIMD::F32x4_Ref4<a, b, c, 2> an##bn##cn##z;	\
	Cpf::SIMD::F32x4_Ref4<a, b, c, 3> an##bn##cn##w;

#define F32X4_4_SWIZZLE_3(a, an, b, bn)		\
	F32X4_4_SWIZZLE_4(a, an, b, bn, 0, x)	\
	F32X4_4_SWIZZLE_4(a, an, b, bn, 1, y)	\
	F32X4_4_SWIZZLE_4(a, an, b, bn, 2, z)	\
	F32X4_4_SWIZZLE_4(a, an, b, bn, 3, w)

#define F32X4_4_SWIZZLE_2(a, an)	\
	F32X4_4_SWIZZLE_3(a, an, 0, x)	\
	F32X4_4_SWIZZLE_3(a, an, 1, y)	\
	F32X4_4_SWIZZLE_3(a, an, 2, z)	\
	F32X4_4_SWIZZLE_3(a, an, 3, w)

#define F32X4_4_SWIZZLE		\
	F32X4_4_SWIZZLE_2(0, x)	\
	F32X4_4_SWIZZLE_2(1, y)	\
	F32X4_4_SWIZZLE_2(2, z)	\
	F32X4_4_SWIZZLE_2(3, w)
