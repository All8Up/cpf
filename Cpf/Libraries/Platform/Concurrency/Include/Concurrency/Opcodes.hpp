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
				using ThreadContext = Scheduler::ThreadContext;

				static void Wait(Scheduler &vm, int64_t index);

				static void FirstOne(Scheduler &vm, ThreadContext& context, int64_t index);
				static void FirstOneBarrier(Scheduler &vm, ThreadContext& context, int64_t index);
				static void LastOne(Scheduler &vm, ThreadContext& context, int64_t index);
				static void LastOneBarrier(Scheduler &vm, ThreadContext& context, int64_t index);
				static void All(Scheduler &vm, ThreadContext& context, int64_t index);
				static void AllBarrier(Scheduler &vm, ThreadContext& context, int64_t index);
				static void Barrier(Scheduler &vm, ThreadContext& context, int64_t index);

				static void TLD(Scheduler&, ThreadContext&, int64_t);
				static void TLA(Scheduler&, ThreadContext&, int64_t);
				static void SD(Scheduler&, ThreadContext&, int64_t);
				static void SA(Scheduler&, ThreadContext&, int64_t);


				static void ActiveThreads(Scheduler &vm, ThreadContext& context, int64_t index);
				static void HeadMinimize(Scheduler &vm, ThreadContext& context, int64_t index);
			};
		}
	}
}
