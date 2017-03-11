//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1, int I2>
		class F32x4_Ref3
		{
		public:
			F32x4_Ref3& operator = (typename TYPE::F32x4_3 value);
			constexpr operator typename TYPE::F32x4_3() const;

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mData); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mData); }

			uint8_t mData[1];
		};

		template <typename TYPE, int I0, int I1, int I2>
		F32x4_Ref3<TYPE, I0, I1, I2>& F32x4_Ref3<TYPE, I0, I1, I2>::operator =(typename TYPE::F32x4_3 value)
		{

			return *this;
		}

		template <typename TYPE, int I0, int I1, int I2>
		constexpr F32x4_Ref3<TYPE, I0, I1, I2>::operator typename TYPE::F32x4_3() const
		{
			return typename TYPE::F32x4_3(_mm_shuffle_ps(static_cast<__m128>(*_Data()), static_cast<__m128>(*_Data()), _MM_SHUFFLE(0, I2, I1, I0)));
		}
	}
}


#define F32X4_3_SWIZZLE_3(t, a, an, b, bn)			\
	Cpf::SIMD::F32x4_Ref3<t, a, b, 0> an##bn##x;	\
	Cpf::SIMD::F32x4_Ref3<t, a, b, 1> an##bn##y;	\
	Cpf::SIMD::F32x4_Ref3<t, a, b, 2> an##bn##z;	\
	Cpf::SIMD::F32x4_Ref3<t, a, b, 3> an##bn##w;

#define F32X4_3_SWIZZLE_2(t, a, an)	\
	F32X4_3_SWIZZLE_3(t, a, an, 0, x)	\
	F32X4_3_SWIZZLE_3(t, a, an, 1, y)	\
	F32X4_3_SWIZZLE_3(t, a, an, 2, z)	\
	F32X4_3_SWIZZLE_3(t, a, an, 3, w)

#define F32X4_3_SWIZZLE(t)		\
	F32X4_3_SWIZZLE_2(t, 0, x)	\
	F32X4_3_SWIZZLE_2(t, 1, y)	\
	F32X4_3_SWIZZLE_2(t, 2, z)	\
	F32X4_3_SWIZZLE_2(t, 3, w)
