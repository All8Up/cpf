//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <atomic>


namespace CPF
{
	//////////////////////////////////////////////////////////////////////////
	enum class MemoryOrder : int32_t
	{
		Relaxed = std::memory_order::memory_order_relaxed,
		Consume = std::memory_order::memory_order_consume,
		Acquire = std::memory_order::memory_order_acquire,
		Release = std::memory_order::memory_order_release,
		AcquireRelease = std::memory_order::memory_order_acq_rel,
		SequencialConsistency = std::memory_order::memory_order_seq_cst
	};
}
