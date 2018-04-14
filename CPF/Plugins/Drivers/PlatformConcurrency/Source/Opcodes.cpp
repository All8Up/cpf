//////////////////////////////////////////////////////////////////////////
#include "Opcodes.hpp"
#include "Backoff.hpp"
#include "CPF/Platform/Concurrency/WorkContext.hpp"

using namespace CPF;
using namespace Concurrency;

/**
* @brief Wait for the opcode execution to complete.
* @param [in,out] vm The virtual machine.
* @param index Index into the predicate ring (wrapped).
*/
void Detail::Opcodes::Wait(Scheduler &vm, const WorkContext* context, int64_t index)
{
	vm.mWorkBackoff[context->mThreadID].Reset();
	for (; vm.mPredicateRing[index].load() >= 0;)
		vm.mWorkBackoff[context->mThreadID]();
}

/**
* @brief Opcode which makes the first thread to arrive consume the payload, other threads pass over this instruction.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::FirstOne(Scheduler &vm, const WorkContext* tc, int64_t index)
{
	auto count = vm.mPredicateRing[index].fetch_sub(1)-1;
	CPF_ASSERT(count >= 0 && count<1000);

	// If this is the first thread into the instruction, execute.
	if (count == vm.mActiveCount.load() - 1)
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
void Detail::Opcodes::FirstOneBarrier(Scheduler& vm, const WorkContext* tc, int64_t index)
{
	auto count = vm.mPredicateRing[index].fetch_sub(1)-1;
	CPF_ASSERT(count >= -vm.mActiveCount.load() && count<1000);

	// If this is the first thread into the instruction, execute.
	if (count == vm.mActiveCount.load() - 1)
	{
		auto context = vm.mInstructionRing[index].mpContext;
		(*vm.mInstructionRing[index].mpFunction)(tc, context);
		vm.mPredicateRing[index].store(-1);
	}
	else
		Wait(vm, tc, index);
}

/**
* @brief Opcode which makes the last thread to arrive consume the payload, other threads continue on to the next instruction.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::LastOne(Scheduler& vm, const WorkContext* tc, int64_t index)
{
	auto count = vm.mPredicateRing[index].fetch_sub(1)-1;
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
void Detail::Opcodes::LastOneBarrier(Scheduler& vm, const WorkContext* tc, int64_t index)
{
	auto count = vm.mPredicateRing[index].fetch_sub(1)-1;
	CPF_ASSERT(count >= 0 && count<1000);

	// If this is the last thread to arrive, execute.
	if (count == 0)
	{
		(*vm.mInstructionRing[index].mpFunction)(tc, vm.mInstructionRing[index].mpContext);
		vm.mPredicateRing[index].store(-1);
	}
	else
		Wait(vm, tc, index);
}

/**
* @brief All threads execute the payload, no conditions involved.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::All(Scheduler& vm, const WorkContext* tc, int64_t index)
{
	// First/Last, who cares, execute!
	CPF_ASSERT(vm.mPredicateRing[index].load() == vm.mActiveCount.load());
	(*vm.mInstructionRing[index].mpFunction)(tc, vm.mInstructionRing[index].mpContext);
}

/**
* @brief All threads execute the payload but they do not move to the next instruction until all have completed.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::AllBarrier(Scheduler& vm, const WorkContext* tc, int64_t index)
{
	// All threads execute.
	(*vm.mInstructionRing[index].mpFunction)(tc, vm.mInstructionRing[index].mpContext);

	// Last thread consumes, others wait.
	auto count = vm.mPredicateRing[index].fetch_sub(1)-1;
	CPF_ASSERT(count >= 0 && count < 1000);
	if (count == 0)
	{
		vm.mPredicateRing[index].store(-1);
	}
	else
		Wait(vm, tc, index);
}

/**
* @brief Synchronize the threads.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::Barrier(Scheduler &vm, const WorkContext* tc, int64_t index)
{
	auto count = vm.mPredicateRing[index].fetch_sub(1)-1;
	CPF_ASSERT(count >= 0 && count < 1000);

	// If this is the last thread, let everything continue.
	if (count == 0)
	{
		vm.mPredicateRing[index].store(-1);
	}
	else
		Wait(vm, tc, index);
}

/**
* @brief Change the number of active threads in the system.
* @param [in,out] vm The scheduler we are running under.
* @param [in,out] tc The thread context of who is running this.
* @param index The instruction index, not wrapped to ring buffer size.
*/
void Detail::Opcodes::ActiveThreads(Scheduler& vm, const WorkContext* tc, int64_t index)
{
	// NOTE: Only one of these instructions can be in flight at any give time.
	auto count = vm.mPredicateRing[index].fetch_sub(1)-1;
	CPF_ASSERT(count >= 0 && count<1000);

	// Last thread to arrive performs the actual change.
	if (count == 0)
	{
		auto target = vm.mTargetCount.load();
		auto active = vm.mActiveCount.load();
		if (target != active)
		{
			// Make the actual change by acquiring the condition lock and then storing the new value.
			// This guarantee's no thread is sporadically woken and misses the changed active count.
			vm.mActiveLock.Acquire();
			vm.mActiveCount.store(target);

			// Modify each threads head index in the ring buffer so they come out
			// of here with the intended state.
			for (auto i = 0; i < vm.mThreadCount; ++i)
			{
				vm.mInstructionRing.SetThreadHead(i, index);
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
		if (tc->mThreadID >= vm.mActiveCount.load())
		{
			vm.mActiveCondition.Acquire(vm.mActiveLock);
			vm.mActiveLock.Release();

			// Reset thread time so it is accurate for load balancing.
			Threading::Thread::GetThreadTimes(
				vm.mTimeInfo.mUserTime[tc->mThreadID],
				vm.mTimeInfo.mKernelTime[tc->mThreadID]
			);
		}
		else
		{
			vm.mActiveLock.Release();
			return;
		}
	}
}

void Detail::Opcodes::LastOneSleep(Scheduler &vm, const WorkContext* context, int64_t index)
{
	auto count = vm.mPredicateRing[index].fetch_sub(1) - 1;
	CPF_ASSERT(count >= 0 && count<1000);

	// If this is the last thread to arrive, execute.
	if (count == 0)
	{
		(*vm.mInstructionRing[index].mpFunction)(context, vm.mInstructionRing[index].mpContext);
		vm.mSleepOp.Release(vm.mActiveCount - 1);
	}
	else
		vm.mSleepOp.Acquire();
}
