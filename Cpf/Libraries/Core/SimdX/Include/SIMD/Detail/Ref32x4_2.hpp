//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1>
		class Ref32x4_2
		{
		public:
			constexpr operator typename TYPE::Lanes_2() const;

		private:
			typename TYPE::Lanes_2* _Data() { return reinterpret_cast<typename TYPE::Lanes_2*>(mData); }
			const typename TYPE::Lanes_2* _Data() const { return reinterpret_cast<const typename TYPE::Lanes_2*>(mData); }

			uint8_t mData[1];
		};

		template <typename TYPE, int I0, int I1>
		constexpr Ref32x4_2<TYPE, I0, I1>::operator typename TYPE::Lanes_2() const
		{
			return TYPE::Lanes_2(_Data()->GetLanes<I0, I1>());
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		class Ref32x4_2<TYPE, 0, 1>
		{
		public:
			constexpr operator typename TYPE::Lanes_2() const { return *_Data(); }

		private:
			typename TYPE::Lanes_2* _Data() { return reinterpret_cast<typename TYPE::Lanes_2*>(mData); }
			const typename TYPE::Lanes_2* _Data() const { return reinterpret_cast<const typename TYPE::Lanes_2*>(mData); }

			uint8_t mData[1];
		};
	}
}


#define REF32X4_2_SWIZZLE_(t, s, v)		\
	Cpf::SIMD::Ref32x4_2<t, s, 0> v##x;	\
	Cpf::SIMD::Ref32x4_2<t, s, 1> v##y;	\
	Cpf::SIMD::Ref32x4_2<t, s, 2> v##z;	\
	Cpf::SIMD::Ref32x4_2<t, s, 3> v##w

#define REF32X4_2_SWIZZLE(type)		\
	REF32X4_2_SWIZZLE_(type, 0, x);	\
	REF32X4_2_SWIZZLE_(type, 1, y);	\
	REF32X4_2_SWIZZLE_(type, 2, z);	\
	REF32X4_2_SWIZZLE_(type, 3, w);
