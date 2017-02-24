//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "Concurrency/Scheduler.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iStage : iUnknown
		{
			virtual void Emit(Concurrency::Scheduler::Queue*) = 0;
		};
	}
}
