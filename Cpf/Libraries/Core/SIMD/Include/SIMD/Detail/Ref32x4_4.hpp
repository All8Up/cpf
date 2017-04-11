//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1, int I2, int I3>
		class Ref32x4_4
		{
		public:
			constexpr operator typename TYPE::Lanes_4() const;

		private:
			TYPE* _Data();
			const TYPE* _Data() const;

			uint8_t mData[1];
		};
	}
}

#include "Ref32x4_4.inl"

#define F32X4_4_SWIZZLE_4(t, a, an, b, bn, c, cn)		\
	Cpf::SIMD::Ref32x4_4<t, a, b, c, 0> an##bn##cn##x;	\
	Cpf::SIMD::Ref32x4_4<t, a, b, c, 1> an##bn##cn##y;	\
	Cpf::SIMD::Ref32x4_4<t, a, b, c, 2> an##bn##cn##z;	\
	Cpf::SIMD::Ref32x4_4<t, a, b, c, 3> an##bn##cn##w;

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

#define REF32X4_4_SWIZZLE(t)	\
	F32X4_4_SWIZZLE_2(t, 0, x)	\
	F32X4_4_SWIZZLE_2(t, 1, y)	\
	F32X4_4_SWIZZLE_2(t, 2, z)	\
	F32X4_4_SWIZZLE_2(t, 3, w)