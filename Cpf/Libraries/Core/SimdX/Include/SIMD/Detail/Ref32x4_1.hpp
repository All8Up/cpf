//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int INDEX>
		class Ref32x4_1
		{
		public:
			Ref32x4_1& operator = (float value);
			operator float() const;

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mData); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mData); }

			uint8_t mData[1];
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>& Ref32x4_1<TYPE, INDEX>::operator =(float value)
		{
			SetLane<INDEX>(_Data(), value);
			return *this;
		}

		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>::operator float() const
		{
			float result = _Data()->GetLane<INDEX>();
			return result;
		}
	}
}

#define REF32X4_1_SWIZZLE(t)		\
	Cpf::SIMD::Ref32x4_1<t, 0> x;	\
	Cpf::SIMD::Ref32x4_1<t, 1> y;	\
	Cpf::SIMD::Ref32x4_1<t, 2> z;	\
	Cpf::SIMD::Ref32x4_1<t, 3> w;
