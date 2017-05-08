//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Scheduler.hpp"


namespace Cpf
{
	namespace Concurrency
	{
		namespace Detail
		{
			/** @brief Opcodes for the scheduler. */
			struct Opcodes
			{
			private:
				friend class Scheduler;
				friend class Queue;

				static void Wait(Scheduler &vm, int64_t index);

				static void FirstOne(Scheduler &vm, const WorkContext* context, int64_t index);
				static void FirstOneBarrier(Scheduler &vm, const WorkContext* context, int64_t index);
				static void LastOne(Scheduler &vm, const WorkContext* context, int64_t index);
				static void LastOneBarrier(Scheduler &vm, const WorkContext* context, int64_t index);
				static void All(Scheduler &vm, const WorkContext* context, int64_t index);
				static void AllBarrier(Scheduler &vm, const WorkContext* context, int64_t index);
				static void Barrier(Scheduler &vm, const WorkContext* context, int64_t index);

				static void TLD(Scheduler&, const WorkContext*, int64_t);
				static void TLA(Scheduler&, const WorkContext*, int64_t);
				static void SD(Scheduler&, const WorkContext*, int64_t);
				static void SA(Scheduler&, const WorkContext*, int64_t);


				static void ActiveThreads(Scheduler &vm, const WorkContext* context, int64_t index);
				static void HeadMinimize(Scheduler &vm, const WorkContext* context, int64_t index);
			};
		}
	}
}
