//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"


namespace Cpf
{
	//////////////////////////////////////////////////////////////////////////
	enum class MemoryOrder : int32_t
	{
		Relaxed = __ATOMIC_RELAXED,
		Consume = __ATOMIC_CONSUME,
		Acquire = __ATOMIC_ACQUIRE,
		Release = __ATOMIC_RELEASE,
		AcquireRelease = __ATOMIC_ACQ_REL,
		SequencialConsistency = __ATOMIC_SEQ_CST
	};
}
