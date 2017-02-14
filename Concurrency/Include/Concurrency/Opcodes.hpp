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
				friend class Cpf::Concurrency::Scheduler;

				static void Wait(Scheduler &vm, int64_t index);

				static void FirstOne(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
				static void FirstOneBarrier(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
				static void LastOne(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
				static void LastOneBarrier(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
				static void All(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
				static void AllBarrier(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
				static void Barrier(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);

				static void TLD(Scheduler&, Scheduler::ThreadContext&, int64_t);
				static void TLA(Scheduler&, Scheduler::ThreadContext&, int64_t);
				static void SD(Scheduler&, Scheduler::ThreadContext&, int64_t);
				static void SA(Scheduler&, Scheduler::ThreadContext&, int64_t);


				static void ActiveThreads(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
				static void HeadMinimize(Scheduler &vm, Scheduler::ThreadContext& context, int64_t index);
			};
		}
	}
}
