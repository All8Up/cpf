//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Platform/Atomic/MemoryOrder.hpp"


namespace Cpf
{
	namespace Atomic
	{
		//////////////////////////////////////////////////////////////////////////
		struct IntPtrPair_t
		{
			intptr_t mFirst;
			intptr_t mSecond;
		};
		static_assert(sizeof(IntPtrPair_t) == 2 * sizeof(void*), "Should be equivalent.");


		//////////////////////////////////////////////////////////////////////////
		using SizeType1_t = uint8_t;
		using SizeType2_t = uint16_t;
		using SizeType4_t = uint32_t;
		using SizeType8_t = uint64_t;
#if CPF_TARGET_CPU_64
		using SizeType16_t = IntPtrPair_t;
#endif

		template<const size_t SIZE> struct SizeType;
		template<> struct SizeType<1> { using ValueType_t = SizeType1_t; };
		template<> struct SizeType<2> { using ValueType_t = SizeType2_t; };
		template<> struct SizeType<4> { using ValueType_t = SizeType4_t; };
		template<> struct SizeType<8> { using ValueType_t = SizeType8_t; };
#if CPF_TARGET_CPU_64
		template<> struct SizeType<16> { using ValueType_t = SizeType16_t; };
#endif


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		typename SizeType<SIZE>::ValueType_t LoadSizeType(volatile typename SizeType<SIZE>::ValueType_t* value, MemoryOrder mo);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		inline TYPE Load(const TYPE& value, MemoryOrder mo=MemoryOrder::SequencialConsistency)
		{
			return static_cast<TYPE>(
				LoadSizeType<sizeof(TYPE)>(
					reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(const_cast<TYPE*>(&value)),
					mo
				));
		}


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		void StoreSizeType(volatile typename SizeType<SIZE>::ValueType_t* target, typename SizeType<SIZE>::ValueType_t value, MemoryOrder mo);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE, typename RHS>
		inline void Store(TYPE& target, RHS value, MemoryOrder mo = MemoryOrder::SequencialConsistency)
		{
			StoreSizeType<sizeof(TYPE)>(
				reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(&target),
					static_cast<TYPE>(value),
					mo
				);
		}


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		typename SizeType<SIZE>::ValueType_t IncSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			MemoryOrder mo
		);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		inline TYPE Inc(TYPE& target, MemoryOrder mo = MemoryOrder::SequencialConsistency)
		{
			return static_cast<TYPE>(IncSizeType<sizeof(TYPE)>(
				reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(&target),
				mo
			));
		};


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		typename SizeType<SIZE>::ValueType_t DecSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			MemoryOrder mo
		);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		inline TYPE Dec(TYPE& target, MemoryOrder mo = MemoryOrder::SequencialConsistency)
		{
			return static_cast<TYPE>(DecSizeType<sizeof(TYPE)>(
				reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(&target),
				mo
			));
		};


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		typename SizeType<SIZE>::ValueType_t AddSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t addend,
			MemoryOrder mo
		);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE, typename RHS>
		inline TYPE Add(TYPE& target, RHS addend, MemoryOrder mo = MemoryOrder::SequencialConsistency)
		{
			return static_cast<TYPE>(AddSizeType<sizeof(TYPE)>(
				reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(&target),
				static_cast<typename SizeType<sizeof(TYPE)>::ValueType_t>(addend),
				mo
			));
		};


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		typename SizeType<SIZE>::ValueType_t SubSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t addend,
			MemoryOrder mo
		);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE, typename RHS>
		inline TYPE Sub(TYPE& target, RHS value, MemoryOrder mo = MemoryOrder::SequencialConsistency)
		{
			return static_cast<TYPE>(SubSizeType<sizeof(TYPE)>(
				reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(&target),
				static_cast<typename SizeType<sizeof(TYPE)>::ValueType_t>(value),
				mo
			));
		};


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		typename SizeType<SIZE>::ValueType_t ExchangeSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t value,
			MemoryOrder mo
		);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE, typename RHS>
		inline TYPE Exchange(TYPE& target, RHS value, MemoryOrder mo = MemoryOrder::SequencialConsistency)
		{
			return static_cast<TYPE>(ExchangeSizeType<sizeof(TYPE)>(
				reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(&target),
				static_cast<typename SizeType<sizeof(TYPE)>::ValueType_t>(value),
				mo
			));
		};


		//////////////////////////////////////////////////////////////////////////
		template<const size_t SIZE>
		bool CompareExchangeSizeType(
			volatile typename SizeType<SIZE>::ValueType_t* target,
			typename SizeType<SIZE>::ValueType_t value,
			typename SizeType<SIZE>::ValueType_t comparand,
			MemoryOrder mo
		);

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE, typename LHS, typename RHS>
		inline bool CompareExchange(TYPE& target, LHS value, RHS comparand, MemoryOrder mo = MemoryOrder::SequencialConsistency)
		{
			return static_cast<TYPE>(CompareExchangeSizeType<sizeof(TYPE)>(
				reinterpret_cast<volatile typename SizeType<sizeof(TYPE)>::ValueType_t*>(&target),
				static_cast<typename SizeType<sizeof(TYPE)>::ValueType_t>(value),
				static_cast<typename SizeType<sizeof(TYPE)>::ValueType_t>(comparand),
				mo
			));
		};
	}
}


//////////////////////////////////////////////////////////////////////////
#include <Platform/Atomic/Operations.hpp>
