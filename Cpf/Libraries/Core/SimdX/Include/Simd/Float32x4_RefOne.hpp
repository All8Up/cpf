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
		class RefOne
		{
		public:
			operator ELEMENTTYPE () const;
			RefOne& operator = (ELEMENTTYPE value);

		private:
			const SIMDTYPE* _GetData() const { reinterpret_cast<const SIMDTYPE*>(mData); }
			uint8_t mData[1];
		};


		//////////////////////////////////////////////////////////////////////////
		template <>
		class RefOne <__m128, float, 0>
		{
		public:
			operator float() const
			{
				float result;
				_mm_store_ss(&result, *_GetData());
				return result;
			}
			RefOne& operator = (float value)
			{
				*_GetData() = _mm_insert_ps(*_GetData(), { value, value, value, value }, _MM_MK_INSERTPS_NDX(0, 0, 0));
				return *this;
			}

		private:
			__m128* _GetData() { return reinterpret_cast<__m128*>(mData); }
			const __m128* _GetData() const { return reinterpret_cast<const __m128*>(mData); }
			uint8_t mData[1];
		};
		//////////////////////////////////////////////////////////////////////////
		template <>
		class RefOne <__m128, float, 1>
		{
		public:
			operator float() const
			{
				float result;
				_MM_EXTRACT_FLOAT(result, *_GetData(), 1);
				return result;
			}
			RefOne& operator = (float value)
			{
				*_GetData() = _mm_insert_ps(*_GetData(), { value, value, value, value }, _MM_MK_INSERTPS_NDX(0, 1, 0));
				return *this;
			}

		private:
			__m128* _GetData() { return reinterpret_cast<__m128*>(mData); }
			const __m128* _GetData() const { return reinterpret_cast<const __m128*>(mData); }
			uint8_t mData[1];
		};
		//////////////////////////////////////////////////////////////////////////
		template <>
		class RefOne <__m128, float, 2>
		{
		public:
			operator float() const
			{
				float result;
				_MM_EXTRACT_FLOAT(result, *_GetData(), 2);
				return result;
			}
			RefOne& operator = (float value)
			{
				*_GetData() = _mm_insert_ps(*_GetData(), { value, value, value, value }, _MM_MK_INSERTPS_NDX(0, 2, 0));
				return *this;
			}

		private:
			__m128* _GetData() { return reinterpret_cast<__m128*>(mData); }
			const __m128* _GetData() const { return reinterpret_cast<const __m128*>(mData); }
			uint8_t mData[1];
		};
		//////////////////////////////////////////////////////////////////////////
		template <>
		class RefOne <__m128, float, 3>
		{
		public:
			operator float() const
			{
				float result;
				_MM_EXTRACT_FLOAT(result, *_GetData(), 3);
				return result;
			}
			RefOne& operator = (float value)
			{
				*_GetData() = _mm_insert_ps(*_GetData(), { value, value, value, value }, _MM_MK_INSERTPS_NDX(0, 3, 0));
				return *this;
			}

		private:
			__m128* _GetData() { return reinterpret_cast<__m128*>(mData); }
			const __m128* _GetData() const { return reinterpret_cast<const __m128*>(mData); }
			uint8_t mData[1];
		};
	}
}
