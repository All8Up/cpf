//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1, int I2>
		class Ref32x4_3
		{
		public:
			constexpr operator typename TYPE::Lanes_3() const;
			
			typename TYPE::LaneType GetLane(int idx) const;

		private:
			TYPE* _Data();
			const TYPE* _Data() const;

			uint8_t mData[1];
		};
	}
}

#include "Ref32x4_3.inl"

#define F32X4_3_SWIZZLE_3(t, a, an, b, bn)		\
	Cpf::SIMD::Ref32x4_3<t, a, b, 0> an##bn##x;	\
	Cpf::SIMD::Ref32x4_3<t, a, b, 1> an##bn##y;	\
	Cpf::SIMD::Ref32x4_3<t, a, b, 2> an##bn##z;	\
	Cpf::SIMD::Ref32x4_3<t, a, b, 3> an##bn##w;

#define F32X4_3_SWIZZLE_2(t, a, an)		\
	F32X4_3_SWIZZLE_3(t, a, an, 0, x)	\
	F32X4_3_SWIZZLE_3(t, a, an, 1, y)	\
	F32X4_3_SWIZZLE_3(t, a, an, 2, z)	\
	F32X4_3_SWIZZLE_3(t, a, an, 3, w)

#define REF32X4_3_SWIZZLE(t)	\
	F32X4_3_SWIZZLE_2(t, 0, x)	\
	F32X4_3_SWIZZLE_2(t, 1, y)	\
	F32X4_3_SWIZZLE_2(t, 2, z)	\
	F32X4_3_SWIZZLE_2(t, 3, w)
