//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Float32x2.hpp"
#include <smmintrin.h>

namespace Cpf
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename SIMDTYPE, typename ELEMENTTYPE, int I0, int I1>
		class Ref2
		{
		public:
			operator ELEMENTTYPE () const;
			Ref2& operator = (ELEMENTTYPE value);

		private:
			const SIMDTYPE* _GetData() const { reinterpret_cast<const SIMDTYPE*>(mData); }
			uint8_t mData[1];
		};


		//////////////////////////////////////////////////////////////////////////
		template <>
		class Ref2 <__m128, float, 0, 0>
		{
		public:
			operator __m128() const
			{
				// TODO: There are faster methods for various combinations.
				return _mm_shuffle_ps(*_GetData(), *_GetData(), _MM_SHUFFLE(0, 0, 0, 0));
			}
			Ref2& operator = (__m128 value)
			{
				*_GetData() = _mm_shuffle_ps(*_GetData(), value, _MM_SHUFFLE(1, 0, 3, 2));
				return *this;
			}

		private:
			__m128* _GetData() { return reinterpret_cast<__m128*>(mData); }
			const __m128* _GetData() const { return reinterpret_cast<const __m128*>(mData); }
			uint8_t mData[1];
		};
	}
}
