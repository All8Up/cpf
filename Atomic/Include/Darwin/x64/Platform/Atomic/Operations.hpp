//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"


namespace Cpf
{
	namespace Atomic
	{
		template<const size_t SIZE>
		inline typename SizeType<SIZE>::ValueType_t LoadSizeType(volatile typename SizeType<SIZE>::ValueType_t* value, MemoryOrder mo)
		{
			(void)mo;
			return __sync_add_and_fetch(value, 0);
		}

		template<>
		inline typename SizeType<16>::ValueType_t LoadSizeType<16>(volatile typename SizeType<16>::ValueType_t* value, MemoryOrder mo)
		{
			(void)mo;
			CPF_ASSERT(reinterpret_cast<intptr_t>(value) % 16 == 0);
			__m128i temp = _mm_load_si128((__m128i*)value);
			return *reinterpret_cast<SizeType<16>::ValueType_t*>(&temp);
		}


		//////////////////////////////////////////////////////////////////////////

		template<const size_t SIZE>
		inline void StoreSizeType(volatile typename SizeType<SIZE>::ValueType_t* target, typename SizeType<SIZE>::ValueType_t value, MemoryOrder mo)
		{
			(void)mo;
			*target = value;
		}

		template<>
		inline void StoreSizeType<16>(volatile typename SizeType<16>::ValueType_t* target, typename SizeType<16>::ValueType_t value, MemoryOrder mo)
		{
			(void)mo;
			CPF_ASSERT(reinterpret_cast<intptr_t>(target) % 16 == 0);
			const __m128i* v = reinterpret_cast<const __m128i*>(&value);
			_mm_store_si128((__m128i*)target, _mm_loadu_si128(v));
		}


		//////////////////////////////////////////////////////////////////////////

		template<const size_t SIZE>
		inline typename SizeType<SIZE>::ValueType_t IncSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			MemoryOrder mo
		)
		{
			(void)mo;
			__sync_synchronize();
			return __sync_add_and_fetch(target, 1);
		}

		//////////////////////////////////////////////////////////////////////////

		template<const size_t SIZE>
		inline typename SizeType<SIZE>::ValueType_t DecSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			MemoryOrder mo
		)
		{
			(void)mo;
			__sync_synchronize();
			return __sync_sub_and_fetch(target, 1);
		}


		//////////////////////////////////////////////////////////////////////////

		template<const size_t SIZE>
		inline typename SizeType<SIZE>::ValueType_t AddSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t addend,
			MemoryOrder mo
		)
		{
			(void)mo;
			return __sync_add_and_fetch(target, addend);
		}

		//////////////////////////////////////////////////////////////////////////

		template<const size_t SIZE>
		inline typename SizeType<SIZE>::ValueType_t SubSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t value,
			MemoryOrder mo
		)
		{
			(void)mo;
			return __sync_sub_and_fetch(target, value);
		}


		//////////////////////////////////////////////////////////////////////////

		template<const size_t SIZE>
		inline typename SizeType<SIZE>::ValueType_t ExchangeSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t value,
			MemoryOrder mo
		)
		{
			(void)mo;
			__sync_synchronize();
			return __sync_swap(target, value);
		}


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		inline bool CompareExchangeSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t value,
			typename SizeType<SIZE>::ValueType_t comparand,
			MemoryOrder mo
		)
		{
			(void)mo;
			return __sync_bool_compare_and_swap(target, comparand, value);
		}
	}
}
