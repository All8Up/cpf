//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Scheduler.hpp"


namespace CPF
{
	namespace Platform
	{
		namespace Detail
		{
			/** @brief Opcodes for the scheduler. */
			struct Opcodes
			{
				static void Wait(Scheduler &vm, const WorkContext* context, int64_t index);

				static void FirstOne(Scheduler &vm, const WorkContext* context, int64_t index);
				static void FirstOneBarrier(Scheduler &vm, const WorkContext* context, int64_t index);
				static void LastOne(Scheduler &vm, const WorkContext* context, int64_t index);
				static void LastOneBarrier(Scheduler &vm, const WorkContext* context, int64_t index);
				static void All(Scheduler &vm, const WorkContext* context, int64_t index);
				static void AllBarrier(Scheduler &vm, const WorkContext* context, int64_t index);
				static void Barrier(Scheduler &vm, const WorkContext* context, int64_t index);

				static void LastOneSleep(Scheduler &vm, const WorkContext* context, int64_t index);

				static void ActiveThreads(Scheduler &vm, const WorkContext* context, int64_t index);
			};
		}
	}
}
