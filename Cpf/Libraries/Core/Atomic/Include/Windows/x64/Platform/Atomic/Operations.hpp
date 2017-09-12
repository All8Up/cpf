//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <atomic>


namespace CPF
{
	namespace Atomic
	{
		//////////////////////////////////////////////////////////////////////////
		template<>
		inline typename SizeType<1>::ValueType_t LoadSizeType<1>(volatile typename SizeType<1>::ValueType_t* value, MemoryOrder mo)
		{
			return std::_Atomic_load_1(
				reinterpret_cast<volatile std::_Uint1_t*>(value),
				static_cast<std::memory_order>(mo));
		}
		template<>
		inline typename SizeType<2>::ValueType_t LoadSizeType<2>(volatile typename SizeType<2>::ValueType_t* value, MemoryOrder mo)
		{
			return std::_Atomic_load_2(
				reinterpret_cast<volatile std::_Uint2_t*>(value),
				static_cast<std::memory_order>(mo));
		}
		template<>
		inline typename SizeType<4>::ValueType_t LoadSizeType<4>(volatile typename SizeType<4>::ValueType_t* value, MemoryOrder mo)
		{
			return std::_Atomic_load_4(
				reinterpret_cast<volatile std::_Uint4_t*>(value),
				static_cast<std::memory_order>(mo));
		}
		template<>
		inline typename SizeType<8>::ValueType_t LoadSizeType<8>(volatile typename SizeType<8>::ValueType_t* value, MemoryOrder mo)
		{
			return std::_Atomic_load_8(
				reinterpret_cast<volatile std::_Uint8_t*>(value),
				static_cast<std::memory_order>(mo));
		}
#if CPF_TARGET_CPU_64
		template<>
		inline typename SizeType<16>::ValueType_t LoadSizeType<16>(volatile typename SizeType<16>::ValueType_t* value, MemoryOrder mo)
		{
			(void)mo;
			CPF_ASSERT(reinterpret_cast<intptr_t>(value) % 16 == 0);
			__m128i temp = _mm_load_si128((__m128i*)value);
			return *reinterpret_cast<IntPtrPair_t*>(&temp);
		}
#endif


		//////////////////////////////////////////////////////////////////////////

		template<>
		inline void StoreSizeType<1>(volatile typename SizeType<1>::ValueType_t* target, typename SizeType<1>::ValueType_t value, MemoryOrder mo)
		{
			std::_Atomic_store_1((volatile std::_Uint1_t*)target, (std::_Uint1_t)value, (std::memory_order)mo);
		}
		template<>
		inline void StoreSizeType<2>(volatile typename SizeType<2>::ValueType_t* target, typename SizeType<2>::ValueType_t value, MemoryOrder mo)
		{
			std::_Atomic_store_2((volatile std::_Uint2_t*)target, (std::_Uint2_t)value, (std::memory_order)mo);
		}
		template<>
		inline void StoreSizeType<4>(volatile typename SizeType<4>::ValueType_t* target, typename SizeType<4>::ValueType_t value, MemoryOrder mo)
		{
			std::_Atomic_store_4((volatile std::_Uint4_t*)target, (std::_Uint4_t)value, (std::memory_order)mo);
		}
		template<>
		inline void StoreSizeType<8>(volatile typename SizeType<8>::ValueType_t* target, typename SizeType<8>::ValueType_t value, MemoryOrder mo)
		{
			std::_Atomic_store_8((volatile std::_Uint8_t*)target, (std::_Uint8_t)value, (std::memory_order)mo);
		}
		template<>
		inline void StoreSizeType<16>(volatile typename SizeType<16>::ValueType_t* target, typename SizeType<16>::ValueType_t value, MemoryOrder mo)
		{
			(void)mo;
			CPF_ASSERT(reinterpret_cast<intptr_t>(target) % 16 == 0);
			const __m128i* v = reinterpret_cast<const __m128i*>(&value);
			_mm_store_si128((__m128i*)target, _mm_load_si128(v));
		}


		//////////////////////////////////////////////////////////////////////////
		template<>
		inline typename SizeType<1>::ValueType_t IncSizeType<1>(
			volatile typename SizeType<1>::ValueType_t* target,
			MemoryOrder mo
		)
		{
			return std::_Atomic_fetch_add_1((volatile std::_Uint1_t*)target, (std::_Uint1_t)1, (std::memory_order)mo) + (std::_Uint1_t)1;
		}

		template<>
		inline typename SizeType<2>::ValueType_t IncSizeType<2>(
			volatile typename SizeType<2>::ValueType_t* target,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_add_2((volatile std::_Uint2_t*)target, (std::_Uint2_t)1, (std::memory_order)mo) + (std::_Uint1_t)1;
		}

		template<>
		inline typename SizeType<4>::ValueType_t IncSizeType<4>(
			volatile typename SizeType<4>::ValueType_t* target,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_add_4((volatile std::_Uint4_t*)target, (std::_Uint4_t)1, (std::memory_order)mo) + (std::_Uint1_t)1;
		}

		template<>
		inline typename SizeType<8>::ValueType_t IncSizeType<8>(
			volatile typename SizeType<8>::ValueType_t* target,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_add_8((volatile std::_Uint8_t*)target, (std::_Uint8_t)1, (std::memory_order)mo) + (std::_Uint1_t)1;
		}

		//////////////////////////////////////////////////////////////////////////
		template<>
		inline typename SizeType<1>::ValueType_t DecSizeType<1>(
			volatile typename SizeType<1>::ValueType_t* target,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_1((volatile std::_Uint1_t*)target, (std::_Uint1_t)1, (std::memory_order)mo) - (std::_Uint1_t)1;
		}

		template<>
		inline typename SizeType<2>::ValueType_t DecSizeType<2>(
			volatile typename SizeType<2>::ValueType_t* target,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_2((volatile std::_Uint2_t*)target, (std::_Uint2_t)1, (std::memory_order)mo) - (std::_Uint1_t)1;
		}

		template<>
		inline typename SizeType<4>::ValueType_t DecSizeType<4>(
			volatile typename SizeType<4>::ValueType_t* target,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_4((volatile std::_Uint4_t*)target, (std::_Uint4_t)1, (std::memory_order)mo) - (std::_Uint1_t)1;
		}

		template<>
		inline typename SizeType<8>::ValueType_t DecSizeType<8>(
			volatile typename SizeType<8>::ValueType_t* target,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_8((volatile std::_Uint8_t*)target, (std::_Uint8_t)1, (std::memory_order)mo) - (std::_Uint1_t)1;
		}


		//////////////////////////////////////////////////////////////////////////
		template<>
		inline typename SizeType<1>::ValueType_t AddSizeType<1>(
			volatile typename SizeType<1>::ValueType_t* target,
			typename SizeType<1>::ValueType_t addend,
			MemoryOrder mo
		)
		{
			return std::_Atomic_fetch_add_1((volatile std::_Uint1_t*)target, (std::_Uint1_t)addend, (std::memory_order)mo) + (std::_Uint1_t)addend;
		}

		template<>
		inline typename SizeType<2>::ValueType_t AddSizeType<2>(
			volatile typename SizeType<2>::ValueType_t* target,
			typename SizeType<2>::ValueType_t addend,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_add_2((volatile std::_Uint2_t*)target, (std::_Uint2_t)addend, (std::memory_order)mo) + (std::_Uint1_t)addend;
		}

		template<>
		inline typename SizeType<4>::ValueType_t AddSizeType<4>(
			volatile typename SizeType<4>::ValueType_t* target,
			typename SizeType<4>::ValueType_t addend,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_add_4((volatile std::_Uint4_t*)target, (std::_Uint4_t)addend, (std::memory_order)mo) + (std::_Uint1_t)addend;
		}

		template<>
		inline typename SizeType<8>::ValueType_t AddSizeType<8>(
			volatile typename SizeType<8>::ValueType_t* target,
			typename SizeType<8>::ValueType_t addend,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_add_8((volatile std::_Uint8_t*)target, (std::_Uint8_t)addend, (std::memory_order)mo) + (std::_Uint1_t)addend;
		}


		//////////////////////////////////////////////////////////////////////////
		template<>
		inline typename SizeType<1>::ValueType_t SubSizeType<1>(
			volatile typename SizeType<1>::ValueType_t* target,
			typename SizeType<1>::ValueType_t addend,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_1((volatile std::_Uint1_t*)target, (std::_Uint1_t)addend, (std::memory_order)mo) - (std::_Uint1_t)addend;
		}

		template<>
		inline typename SizeType<2>::ValueType_t SubSizeType<2>(
			volatile typename SizeType<2>::ValueType_t* target,
			typename SizeType<2>::ValueType_t addend,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_2((volatile std::_Uint2_t*)target, (std::_Uint2_t)addend, (std::memory_order)mo) - (std::_Uint1_t)addend;
		}

		template<>
		inline typename SizeType<4>::ValueType_t SubSizeType<4>(
			volatile typename SizeType<4>::ValueType_t* target,
			typename SizeType<4>::ValueType_t addend,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_4((volatile std::_Uint4_t*)target, (std::_Uint4_t)addend, (std::memory_order)mo) - (std::_Uint1_t)addend;
		}

		template<>
		inline typename SizeType<8>::ValueType_t SubSizeType<8>(
			volatile typename SizeType<8>::ValueType_t* target,
			typename SizeType<8>::ValueType_t addend,
			MemoryOrder mo
			)
		{
			return std::_Atomic_fetch_sub_8((volatile std::_Uint8_t*)target, (std::_Uint8_t)addend, (std::memory_order)mo) - (std::_Uint1_t)addend;
		}


		//////////////////////////////////////////////////////////////////////////
		template<>
		inline typename SizeType<1>::ValueType_t ExchangeSizeType<1>(
			volatile typename SizeType<1>::ValueType_t* target,
			typename SizeType<1>::ValueType_t value,
			MemoryOrder mo
			)
		{
			return std::_Atomic_exchange_1((volatile std::_Uint1_t*)target, (std::_Uint1_t)value, (std::memory_order)mo);
		}

		template<>
		inline typename SizeType<2>::ValueType_t ExchangeSizeType<2>(
			volatile typename SizeType<2>::ValueType_t* target,
			typename SizeType<2>::ValueType_t value,
			MemoryOrder mo
			)
		{
			return std::_Atomic_exchange_2((volatile std::_Uint2_t*)target, (std::_Uint2_t)value, (std::memory_order)mo);
		}

		template<>
		inline typename SizeType<4>::ValueType_t ExchangeSizeType<4>(
			volatile typename SizeType<4>::ValueType_t* target,
			typename SizeType<4>::ValueType_t value,
			MemoryOrder mo
			)
		{
			return std::_Atomic_exchange_4((volatile std::_Uint4_t*)target, (std::_Uint4_t)value, (std::memory_order)mo);
		}

		template<>
		inline typename SizeType<8>::ValueType_t ExchangeSizeType<8>(
			volatile typename SizeType<8>::ValueType_t* target,
			typename SizeType<8>::ValueType_t value,
			MemoryOrder mo
			)
		{
			return std::_Atomic_exchange_8((volatile std::_Uint8_t*)target, (std::_Uint8_t)value, (std::memory_order)mo);
		}


		//////////////////////////////////////////////////////////////////////////
		template<>
		inline bool CompareExchangeSizeType<1>(
			volatile typename SizeType<1>::ValueType_t* target,
			typename SizeType<1>::ValueType_t value,
			typename SizeType<1>::ValueType_t comparand,
			MemoryOrder mo
			)
		{
			return std::_Atomic_compare_exchange_strong_1(
				(volatile std::_Uint1_t*)target,
				(std::_Uint1_t*)&comparand,
				(std::_Uint1_t)value,
				(std::memory_order)mo,
				(std::memory_order)mo)==TRUE;
		}

		template<>
		inline bool CompareExchangeSizeType<2>(
			volatile typename SizeType<2>::ValueType_t* target,
			typename SizeType<2>::ValueType_t value,
			typename SizeType<2>::ValueType_t comparand,
			MemoryOrder mo
			)
		{
			(void)mo;
			return _InterlockedCompareExchange16((volatile short*)target, (short)value, comparand) == (short)comparand;
		}

		template<>
		inline bool CompareExchangeSizeType<4>(
			volatile typename SizeType<4>::ValueType_t* target,
			typename SizeType<4>::ValueType_t value,
			typename SizeType<4>::ValueType_t comparand,
			MemoryOrder mo
			)
		{
			(void)mo;
			return _InterlockedCompareExchange((volatile unsigned*)target, (unsigned)value, comparand) == (unsigned)comparand;
		}

		template<>
		inline bool CompareExchangeSizeType<8>(
			volatile typename SizeType<8>::ValueType_t* target,
			typename SizeType<8>::ValueType_t value,
			typename SizeType<8>::ValueType_t comparand,
			MemoryOrder mo
			)
		{
			(void)mo;
			return _InterlockedCompareExchange64((volatile LONG64*)target, (LONG64)value, comparand) == (LONG64)comparand;
		}
	}
}
