//////////////////////////////////////////////////////////////////////////
#pragma once
#include <atomic>


namespace Cpf
{
	namespace Fence
	{
		inline void Consume() { std::atomic_thread_fence(std::memory_order_consume); }
		inline void Acquire() { std::atomic_thread_fence(std::memory_order_acquire); }
		inline void Release() { std::atomic_thread_fence(std::memory_order_release); }
		inline void AcquireRelease() { std::atomic_thread_fence(std::memory_order_acq_rel); }
		inline void SequencialConsistency() { std::atomic_thread_fence(std::memory_order_seq_cst); }
	}
}
