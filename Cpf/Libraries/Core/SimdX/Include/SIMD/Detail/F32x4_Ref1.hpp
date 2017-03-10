//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		template <int INDEX>
		class F32x4_Ref1
		{
		public:
			F32x4_Ref1& operator = (float value);
			operator float() const;

		private:
			F32x4_4* _Data() { return reinterpret_cast<F32x4_4*>(mData); }
			const F32x4_4* _Data() const { return reinterpret_cast<const F32x4_4*>(mData); }

			uint8_t mData[1];
		};

		template <int INDEX>
		F32x4_Ref1<INDEX>& F32x4_Ref1<INDEX>::operator =(float value)
		{
			__m128 insert = {value, value, value, value};
			*_Data() = _mm_insert_ps(*_Data(), insert, _MM_MK_INSERTPS_NDX(0, INDEX, 0));
			return *this;
		}

		template <int INDEX>
		F32x4_Ref1<INDEX>::operator float() const
		{
			float result;
			_MM_EXTRACT_FLOAT(result, static_cast<__m128>(*_Data()), INDEX);
			return result;
		}
	}
}
