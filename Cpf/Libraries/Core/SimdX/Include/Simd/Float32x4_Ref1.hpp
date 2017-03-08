//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <smmintrin.h>

namespace Cpf
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename SIMDTYPE, typename ELEMENTTYPE, int INDEX>
		class Ref1
		{
		public:
			operator ELEMENTTYPE () const { ELEMENTTYPE result;  _mm_store_ss(&result, _mm_shuffle_ps(*_GetData(), *_GetData(), _MM_SHUFFLE(0, 0, 0, INDEX))); return result; }
			operator float32x1 () const { return _mm_extract_ps(*_GetData(), INDEX); }
			Ref1& operator = (float32x1 value) { *_GetData() = _mm_insert_ps(*_GetData(), value.mData, _MM_MK_INSERTPS_NDX(INDEX, 0, 0)); return *this; }
			Ref1& operator = (float value) { *_GetData() = _mm_insert_ps(*_GetData(), { value, value, value, value }, _MM_MK_INSERTPS_NDX(INDEX, 0, 0)); return *this; }

		private:
			SIMDTYPE* _GetData() { return reinterpret_cast<SIMDTYPE*>(mData); }
			const SIMDTYPE* _GetData() const { return reinterpret_cast<const SIMDTYPE*>(mData); }

			uint8_t mData[1];
		};
	}
}
