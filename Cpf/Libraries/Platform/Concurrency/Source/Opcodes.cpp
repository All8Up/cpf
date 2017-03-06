//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Opcodes.hpp"
#include "Concurrency/Backoff.hpp"

using namespace Cpf;
using namespace Concurrency;


/**
* @brief Wait for the opcode execution to complete.
* @param [in,out] vm The virtual machine.
* @param index		  Index into the predicate ring (wrapped).
*/
void Detail::Opcodes::Wait(Scheduler &vm, int64_t index)
{
	Backoff<4096, 0> backoff;
	for (; Atomic::Load(vm.mPredicateRing[index]) >= 0;)
		backoff();
}


/**
* @brief Opcode which makes the first thread to arrive consume the payload, other threads pass over this instruction.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::FirstOne(Scheduler &vm, ThreadContext& tc, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count<1000);

	// If this is the first thread into the instruction, execute.
	if (count == Atomic::Load(vm.mActiveCount) - 1)
	{
		auto context = vm.mInstructionRing[index].mpContext;
		(*vm.mInstructionRing[index].mpFunction)(tc, context);
	}
}


/**
* @brief Opcode which makes the first thread to arrive consume the payload, other threads wail until the payload completes before moving along.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::FirstOneBarrier(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= -Atomic::Load(vm.mActiveCount) && count<1000);

	// If this is the first thread into the instruction, execute.
	if (count == Atomic::Load(vm.mActiveCount) - 1)
	{
		auto context = vm.mInstructionRing[index].mpContext;
		(*vm.mInstructionRing[index].mpFunction)(tc, context);
		Atomic::Store(vm.mPredicateRing[index], -1);
	}
	else
		Wait(vm, index);
}


/**
* @brief Opcode which makes the last thread to arrive consume the payload, other threads continue on to the next instruction.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::LastOne(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count<1000);

	// If this is the last thread to arrive, execute.
	if (count == 0)
	{
		(*vm.mInstructionRing[index].mpFunction)(tc, vm.mInstructionRing[index].mpContext);
	}
}


/**
* @brief Opcode which makes the last thread to arrive consume the payload, other threads wait till the payload completes before moving to the next instruction.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::LastOneBarrier(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count<1000);

	// If this is the last thread to arrive, execute.
	if (count == 0)
	{
		(*vm.mInstructionRing[index].mpFunction)(tc, vm.mInstructionRing[index].mpContext);
		Atomic::Store(vm.mPredicateRing[index], -1);
	}
	else
		Wait(vm, index);
}


/**
* @brief All threads execute the payload, no conditions involved.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::All(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	// First/Last, who cares, execute!
	CPF_ASSERT(Atomic::Load(vm.mPredicateRing[index]) == Atomic::Load(vm.mActiveCount));
	(*vm.mInstructionRing[index].mpFunction)(tc, vm.mInstructionRing[index].mpContext);
}


/**
* @brief All threads execute the payload but they do not move to the next instruction until all have completed.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::AllBarrier(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	// All threads execute.
	(*vm.mInstructionRing[index].mpFunction)(tc, vm.mInstructionRing[index].mpContext);

	// Last thread consumes, others wait.
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count < 1000);
	if (count == 0)
	{
		Atomic::Store(vm.mPredicateRing[index], -1);
	}
	else
		Wait(vm, index);
}


/**
* @brief Synchronize the threads.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::Barrier(Scheduler &vm, ThreadContext&, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count < 1000);

	// If this is the last thread, let everything continue.
	if (count == 0)
	{
		Atomic::Store(vm.mPredicateRing[index], -1);
	}
	else
		Wait(vm, index);
}


/**
 * @brief Assign a thread local data register.
 * @param [in,out] vm The scheduler we are running under.
 * @param [in,out] tc The thread context of who is running this.
 * @param index The instruction index, not wrapped to ring buffer size.
 */
void Detail::Opcodes::TLD(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count < 1000);

	intptr_t iidx = (intptr_t)vm.mInstructionRing[index].mpFunction;
	intptr_t ival = (intptr_t)vm.mInstructionRing[index].mpContext;
	if (count == 0)
	{
		// Last thread changes any sleeping thread registers so they stay in sync.
		for (int i = vm.mActiveCount; i < vm.mThreadCount; ++i)
			vm._TLD(i, int(iidx)) = int32_t(ival);
	}

	vm._TLD(tc.GetThreadIndex(), int(iidx)) = int32_t(ival);
}

/**
 * @brief Assign a thread local address register.
 * @param [in,out] vm The scheduler we are running under.
 * @param [in,out] tc The thread context of who is running this.
 * @param index The instruction index, not wrapped to ring buffer size.
 */
void Detail::Opcodes::TLA(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count < 1000);

	intptr_t iidx = (intptr_t)vm.mInstructionRing[index].mpFunction;
	void* ival = vm.mInstructionRing[index].mpContext;
	if (count == 0)
	{
		// Last thread changes any sleeping thread registers so they stay in sync.
		for (int i = vm.mActiveCount; i < vm.mThreadCount; ++i)
			vm._TLA(i, int(iidx)) = ival;
	}

	vm._TLA(tc.GetThreadIndex(), int(iidx)) = ival;
}

/**
 * @brief Assign a shared data register.
 * @param [in,out] vm The scheduler we are running under.
 * @param [in,out] tc The thread context of who is running this.
 * @param index The instruction index, not wrapped to ring buffer size.
 */
void Detail::Opcodes::SD(Scheduler& vm, ThreadContext&, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count < 1000);

	intptr_t ival = (intptr_t)vm.mInstructionRing[index].mpContext;
	if (count == 0)
	{
		// Last thread changes makes the changes.
		intptr_t iidx = (intptr_t)vm.mInstructionRing[index].mpFunction;
		vm._SD(int(iidx)) = int32_t(ival);
		Atomic::Store(vm.mPredicateRing[index], -1);
	}
	else
		Wait(vm, index);
}

/**
 * @brief Assign a shared data address register.
 * @param [in,out] vm The scheduler we are running under.
 * @param [in,out] tc The thread context of who is running this.
 * @param index The instruction index, not wrapped to ring buffer size.
 */
void Detail::Opcodes::SA(Scheduler& vm, ThreadContext&, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count < 1000);

	void* ival = vm.mInstructionRing[index].mpContext;
	if (count == 0)
	{
		// Last thread changes any sleeping thread registers so they stay in sync.
		intptr_t iidx = (intptr_t)vm.mInstructionRing[index].mpFunction;
		vm._SA(int(iidx)) = ival;
		Atomic::Store(vm.mPredicateRing[index], -1);
	}
	else
		Wait(vm, index);
}


/**
* @brief Change the number of active threads in the system.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::ActiveThreads(Scheduler& vm, ThreadContext& tc, int64_t index)
{
	// NOTE: Only one of these instructions can be in flight at any give time.
	auto count = Atomic::Dec(vm.mPredicateRing[index]);
	CPF_ASSERT(count >= 0 && count<1000);

	// Last thread to arrive performs the actual change.
	if (count == 0)
	{
		auto target = Atomic::Load(vm.mTargetCount);
		auto active = Atomic::Load(vm.mActiveCount);
		if (target != active)
		{
			// Make the actual change by acquiring the condition lock and then storing the new value.
			// This guarantee's no thread is sporadically woken and misses the changed active count.
			vm.mActiveLock.Acquire();
			Atomic::Store(vm.mActiveCount, target);

			// Modify each threads head index in the ring buffer so they come out
			// of here with the intended state.
			for (auto i = 0; i < vm.mThreadCount; ++i)
			{
				vm.mInstructionRing.ThreadHead(i, index);
			}

			// Wake the currently parked threads.
			vm.mActiveCondition.ReleaseAll();
			vm.mActiveLock.Release();
		}
		// Let the threads which were already awake continue into the park code
		// where they will figure out if they should go back to work or not.
		vm.mActive.Release(active);
	}

	// Wait here for the thread change to take place.
	vm.mActive.Acquire();

	// Only the threads supposed to be active will leave here.
	// Parked threads will block in the condition variable.
	// All active threads will pop out.
	for (;;)
	{
		vm.mActiveLock.Acquire();
		if (tc.GetThreadIndex() >= Atomic::Load(vm.mActiveCount))
		{
			vm.mActiveCondition.Acquire(vm.mActiveLock);
			vm.mActiveLock.Release();

			// Reset thread time so it is accurate for load balancing.
			Threading::Thread::GetThreadTimes(
				vm.mTimeInfo.mUserTime[tc.GetThreadIndex()],
				vm.mTimeInfo.mKernelTime[tc.GetThreadIndex()]
			);
		}
		else
		{
			vm.mActiveLock.Release();
			return;
		}
	}
}


/**
* @brief Opcode that resets all head indices to minimal values.
* @param vm The virtual machine.
* @param context Thread context information.
* @param index Threads current instruction index.
*/
void Detail::Opcodes::HeadMinimize(Scheduler &vm, ThreadContext&, int64_t index)
{
	auto count = Atomic::Dec(vm.mPredicateRing[index]);

	if (count == 0)
		vm.mInstructionRing.Minimize();
	else
		Wait(vm, index);
}
