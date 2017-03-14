//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int INDEX>
		class F32x4_Ref1
		{
		public:
			F32x4_Ref1& operator = (float value);
			operator float() const;

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mData); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mData); }

			uint8_t mData[1];
		};

		template <typename TYPE, int INDEX>
		F32x4_Ref1<TYPE, INDEX>& F32x4_Ref1<TYPE, INDEX>::operator =(float value)
		{
			SetLane<INDEX>(_Data(), value);
//			__m128 insert = {value, value, value, value};
//			*_Data() = _mm_insert_ps(*_Data(), insert, _MM_MK_INSERTPS_NDX(0, INDEX, 0));
			return *this;
		}

		template <typename TYPE, int INDEX>
		F32x4_Ref1<TYPE, INDEX>::operator float() const
		{
			float result = _Data()->GetLane<INDEX>();
//			_MM_EXTRACT_FLOAT(result, static_cast<__m128>(*_Data()), INDEX);
			return result;
		}
	}
}

#define F32X4_1_SWIZZLE(t)	\
	Cpf::SIMD::F32x4_Ref1<t, 0> x;	\
	Cpf::SIMD::F32x4_Ref1<t, 1> y;	\
	Cpf::SIMD::F32x4_Ref1<t, 2> z;	\
	Cpf::SIMD::F32x4_Ref1<t, 3> w
