//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1, int I2, int I3>
		class F32x4_Ref4
		{
		public:
			F32x4_Ref4& operator = (typename TYPE::F32x4_4 value);
			constexpr operator typename TYPE::F32x4_4() const;

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mData); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mData); }

			uint8_t mData[1];
		};

		template <typename TYPE, int I0, int I1, int I2, int I3>
		F32x4_Ref4<TYPE, I0, I1, I2, I3>& F32x4_Ref4<TYPE, I0, I1, I2, I3>::operator =(typename TYPE::F32x4_4 value)
		{

			return *this;
		}

		template <typename TYPE, int I0, int I1, int I2, int I3>
		constexpr F32x4_Ref4<TYPE, I0, I1, I2, I3>::operator typename TYPE::F32x4_4() const
		{
			return typename TYPE::F32x4_4(_mm_shuffle_ps(static_cast<__m128>(*_Data()), static_cast<__m128>(*_Data()), _MM_SHUFFLE(I3, I2, I1, I0)));
		}
	}
}


#define F32X4_4_SWIZZLE_4(t, a, an, b, bn, c, cn)		\
	Cpf::SIMD::F32x4_Ref4<t, a, b, c, 0> an##bn##cn##x;	\
	Cpf::SIMD::F32x4_Ref4<t, a, b, c, 1> an##bn##cn##y;	\
	Cpf::SIMD::F32x4_Ref4<t, a, b, c, 2> an##bn##cn##z;	\
	Cpf::SIMD::F32x4_Ref4<t, a, b, c, 3> an##bn##cn##w;

#define F32X4_4_SWIZZLE_3(t, a, an, b, bn)		\
	F32X4_4_SWIZZLE_4(t, a, an, b, bn, 0, x)	\
	F32X4_4_SWIZZLE_4(t, a, an, b, bn, 1, y)	\
	F32X4_4_SWIZZLE_4(t, a, an, b, bn, 2, z)	\
	F32X4_4_SWIZZLE_4(t, a, an, b, bn, 3, w)

#define F32X4_4_SWIZZLE_2(t, a, an)		\
	F32X4_4_SWIZZLE_3(t, a, an, 0, x)	\
	F32X4_4_SWIZZLE_3(t, a, an, 1, y)	\
	F32X4_4_SWIZZLE_3(t, a, an, 2, z)	\
	F32X4_4_SWIZZLE_3(t, a, an, 3, w)

#define F32X4_4_SWIZZLE(t)		\
	F32X4_4_SWIZZLE_2(t, 0, x)	\
	F32X4_4_SWIZZLE_2(t, 1, y)	\
	F32X4_4_SWIZZLE_2(t, 2, z)	\
	F32X4_4_SWIZZLE_2(t, 3, w)
