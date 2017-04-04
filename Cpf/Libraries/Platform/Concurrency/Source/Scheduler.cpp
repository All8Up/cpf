//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Backoff.hpp"
#include "Concurrency/Queue.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"
#include "Atomic/Fence.hpp"
#include "Threading/ScopedLock.hpp"
#include "VTune/VTune.hpp"
#include <algorithm>
#include <string>
#include <String.hpp>


using namespace Cpf;
using namespace Concurrency;


//////////////////////////////////////////////////////////////////////////
VTune::Domain* gSchedulerDomain = VTune::DomainCreate("Scheduler");


//////////////////////////////////////////////////////////////////////////
Scheduler::Semaphore::Semaphore(int32_t value)
	: mSemaphore(value)
{
}

void Scheduler::Semaphore::Acquire()
{
	mSemaphore.Acquire();
}

void Scheduler::Semaphore::Release()
{
	mSemaphore.Release();
}


//////////////////////////////////////////////////////////////////////////
const int Scheduler::kMaxBackoff = 4096;


/** @brief Default constructor. */
Scheduler::Scheduler(void* outerContext, size_t queueSize)
	: mControlLock(0)
	, mTargetCount(0)
	, mActiveCount(0)
	, mThreadCount(0)
	, mInstructionRing(queueSize)
	, mPredicateRing(queueSize)
	, mpOuterContext(outerContext)
	, mQueueSize(queueSize)
{
	// Queue must be power of 2.
	CPF_ASSERT((queueSize&(queueSize - 1)) == 0);
	_ClearRegisters();
	TimeInitializer::Install();
}


/** @brief Destructor. */
Scheduler::~Scheduler()
{
	// Check that we were shut down.
	CPF_ASSERT(Atomic::Load(mThreadCount) == 0);
	TimeInitializer::Remove();
}


void Scheduler::_ClearRegisters()
{
	for (auto i = 0; i < kRegisterCount; ++i)
	{
		for (auto j = 0; j < kMaxThreads; ++j)
		{
			mThreadLocalDataRegister[j][i] = 0;
			mThreadLocalAddressRegister[j][i] = nullptr;
		}
		mSharedDataRegister[i] = 0;
		mSharedAddressRegister[i] = nullptr;
	}
}



/**
 * @brief Initializes the thread team by creating the given number of threads.
 * @param count Number of threads to allocate.
 * @param init A function for each thread to call to setup any custom data required.
 * @param shutdown A function for each thread to call on shutdown to free up any custom data..
 * @param context If non-null, context for the shutdown.
 * @return true if it succeeds, false if it fails.
 */
bool Scheduler::Initialize(Threading::Thread::Group&& threads, InitOrShutdownFunc_t init, InitOrShutdownFunc_t shutdown, void* context)
{
	if (threads)
	{
		mThreads = std::move(threads);
		if (mInstructionRing.Initialize(mThreads.Size()))
		{
			// Setup to start with all threads active.
			mThreadCount = mTargetCount = mActiveCount = int(mThreads.Size());

			for(int i=0; i<mThreadCount; ++i)
				mThreads(i, std::bind(&Scheduler::_Worker, this, i, init, shutdown, context));

			mTimeInfo.mThreadCount = mThreadCount;
			mTimeInfo.mDuration = Time::Value::Zero();
			for (int i = 0; i < mThreadCount; ++i)
			{
				mTimeInfo.mUserTime[i] = Time::Value::Zero();
				mTimeInfo.mKernelTime[i] = Time::Value::Zero();
			}
			return true;
		}
		mThreadCount = mTargetCount = mActiveCount = 0;
	}
	return false;
}


/** @brief Shuts down this object and frees any resources it is using. */
void Scheduler::Shutdown()
{
	if (mThreads)
	{
		// Activate all threads in the system.
		// Pass in the exit opcode.
		SetActiveThreads(mThreadCount);
		_Emit(nullptr, nullptr, nullptr);

		mThreads.Join();
		mThreadCount = mTargetCount = mActiveCount = 0;
	}
}


int Scheduler::GetAvailableThreads() const
{
	return mThreadCount;
}

int Scheduler::GetActiveThreads() const
{
	return mActiveCount;
}

void Scheduler::SetActiveThreads(int count)
{
	CPF_ASSERT(count > 0);
	CPF_ASSERT(count <= mThreadCount);

	_Emit(Detail::Opcodes::AllBarrier, [](ThreadContext&, void* context) {
		reinterpret_cast<Threading::Semaphore*>(context)->Release();
	}, &mWait);
	mWait.Acquire();

	// Issue the change.
	if (count != Atomic::Load(mActiveCount)) {
		intptr_t intCount = intptr_t(count);
		_Emit(Detail::Opcodes::ActiveThreads, nullptr, reinterpret_cast<void *>(intCount));
	}
}


void* Scheduler::GetContext() const
{
	return mpOuterContext;
}


/**
 * @brief Pushes an opcode into the scheduler.
 * @param opcode The opcode.
 * @param func The payload to be called.
 * @param context Opaque data to go with the function pointer payload.
 */
void Scheduler::_Emit(OpcodeFunc_t opcode, PayloadFunc_t func, void* context)
{
	// NOTE: It may be tempting to make this a lockless queue but
	// generally speaking this mutex should be low contention given
	// how the internals work.  The exception is if multiple threads
	// attempt to push work which really is not intended usage at this
	// level of the system.
	{
		Threading::ScopedLock<Threading::Mutex> lock(mWorkLock);
		mExternalQueue.push_back({opcode, func, context});
	}
}

void Scheduler::Submit(Scheduler::Semaphore& semaphore)
{
	_Emit(Detail::Opcodes::LastOne, [](ThreadContext&, void* context)
	{
		reinterpret_cast<Scheduler::Semaphore*>(context)->Release();
	}, &semaphore);
}

void Scheduler::Submit(ThreadTimes& times)
{
	_Emit(Detail::Opcodes::All, [](ThreadContext& tc, void* context)
	{
		ThreadTimes* times = reinterpret_cast<ThreadTimes*>(context);
		Threading::Thread::GetThreadTimes(
			times->mTimeResult.mUserTime[tc.GetThreadIndex()],
			times->mTimeResult.mKernelTime[tc.GetThreadIndex()]
		);
	}, &times);
	_Emit(Detail::Opcodes::LastOne, [](ThreadContext& tc, void* context)
	{
		auto now = Time::Now();
		ThreadTimes* times = reinterpret_cast<ThreadTimes*>(context);
		times->mTimeResult.mThreadCount = tc.GetThreadCount();
		times->mTimeResult.mDuration = now;
		auto temp = times->mTimeResult;

		// Make the times relative.
		times->mTimeResult.mDuration -= tc.GetScheduler().mTimeInfo.mDuration;
		for (int i=0; i<tc.GetThreadCount(); ++i)
		{
			times->mTimeResult.mUserTime[i] -= tc.GetScheduler().mTimeInfo.mUserTime[i];
			times->mTimeResult.mKernelTime[i] -= tc.GetScheduler().mTimeInfo.mKernelTime[i];
		}
		tc.GetScheduler().mTimeInfo = temp;
	}, &times);
	Submit(*static_cast<Semaphore*>(&times));
}

void Scheduler::Execute(Queue& q, bool clear)
{
	Threading::ScopedLock<Threading::Mutex> lock(mWorkLock);
	mExternalQueue.insert(mExternalQueue.end(), q.begin(), q.end());
	if (clear)
		q.Discard();
}


/**
 * @brief The primary worker function for threads.  This is actually modeled as a spin lock so it can perform exponential backoff.
 * @param index A internally assigned, incrementing index for each thread.
 * @param initFunc Pass through from initialize which is called by each thread.
 * @param initContext Pass through of the opaque data pointer for the initialization/shutdown function.
 */
void Scheduler::_Worker(int index, InitOrShutdownFunc_t initFunc, InitOrShutdownFunc_t shutdownFunc, void* ctx)
{
	// Setup the thread name for debugging.
	Threading::Thread::SetName((std::string("Scheduler thread: ") + std::to_string(index)).c_str());

	// Setup the thread context for calling opcodes.
	ThreadContext context{*this, index, nullptr};

	// Run the optional initialization function.
	if (initFunc)
		initFunc(context, ctx);

	// Setup performance profiling.
	String threadNumber("Thread(");
	threadNumber += std::to_string(index).c_str();
	threadNumber += ")";
	String threadWork = threadNumber + " work";
	VTUNE_EVENT_CREATE(workEvent);
	String threadMaster = threadNumber + " master";
	VTUNE_EVENT_CREATE(masterEvent);

	// Begin the core loop.
	Backoff<> backoff;
	for (;;)
	{
		VTUNE_EVENT_START(workEvent);

		//////////////////////////////////////////////////////////////////////////
		// Check for available work.
		Instruction work;
		checkWork:
		{
			int64_t workIndex = mInstructionRing.Fetch(index, work);
			if (workIndex != mInstructionRing.InvalidIndex)
			{
				if (work.mpHandler)
				{
					work.mpHandler(*this, context, workIndex);

					// Mark the instruction consumed.
					mInstructionRing.Consume(index, mInstructionRing.ThreadHead(index));
				}
				else
					break;

				// When we get something to execute, reset our backoff.
				backoff.Reset();

				goto checkWork;
			}
		}
		VTUNE_EVENT_END(workEvent);


		//////////////////////////////////////////////////////////////////////////
		// Attempt to take control and fetch more work.
		if (_StartMaster())
		{
			VTUNE_EVENT_START(masterEvent);
			auto more = _FetchWork();
			_EndMaster();
			VTUNE_EVENT_END(masterEvent);
			if (more)
				continue;
		}


		//////////////////////////////////////////////////////////////////////////
		// Perform exponential backoff.
		// NOTE: This entire loop is setup to work like a spin lock such that
		// when there is no work we don't burn the CPU's for no reason.
		// This does mean that if the work is sporadic, there is likely going to
		// be >1ms latency between receiving new instructions and executing them.
		backoff();
	}

	// Call the optional shutdown function.
	if (shutdownFunc)
		shutdownFunc(context, ctx);
}

/**
 * @brief Attempt to take control of the instruction ring buffer tail.
 * @return true if it succeeds, false if it fails.
 */
bool Scheduler::_StartMaster()
{
	// Simply attempt to poke a 1 into the lock, we are
	// control if that happens.
	return Atomic::CompareExchange(mControlLock, 1, 0);
}


/** @brief Release access to the ring buffer tail pointer. */
void Scheduler::_EndMaster()
{
	// Restore the lock to 0.
	Atomic::Store(mControlLock, 0);
}


/**
 * @brief Attempts to move instructions off the external queue into the internal ring buffer.
 * @return true if it pulls any instructions, false if there was nothing to fetch.
 */
bool Scheduler::_FetchWork()
{
	// NOTE: This mutex may seem like a bad thing but it actually does not
	// impact overall performance due to it being rarely called from this side.
	Threading::ScopedLock<Threading::Mutex> lock(mWorkLock);

	// We try to pull as many instructions off the external queue as possible.
	auto externalCount = mExternalQueue.size();
	if (externalCount > 0)
	{
		auto pullCount = mInstructionRing.Reserve(Atomic::Load(mActiveCount), std::min(mQueueSize-1, externalCount));
		if (pullCount == 0)
			return false;

		auto start = mInstructionRing.Tail();

		// Move instructions off the external and into the internal.
		for (auto i = 0; i<pullCount; ++i)
		{
			// TODO: It would be better to perform a memcpy here except the need to look
			// for thread count changes is preventing it.  Might want to consider experimenting
			// with having the opcode re-adjust the predicates instead of performing the checks
			// here.  It would make the change instruction slower but allow this loop to be
			// even tighter.

			// Copy each instruction.
			auto& inst = mExternalQueue[i];
			mInstructionRing[start + i] = inst;

			// Setup the predicate ring so threads can track entry/exit.
			mPredicateRing[start + i] = Atomic::Load(mTargetCount);

			// If this is changing the thread count, apply the change so subsequent
			// instructions will have a proper predicate setup.
			if (inst.mpHandler== Detail::Opcodes::ActiveThreads) {
				int target = int(reinterpret_cast<intptr_t>(inst.mpContext));
				CPF_ASSERT(target>0 && target <= mThreadCount);
				Atomic::Store(mTargetCount, target);
			}
		}
		mExternalQueue.erase(mExternalQueue.begin(), mExternalQueue.begin() + pullCount);

		// Update the tail with new instructions.
		Fence::Release();
		mInstructionRing.Commit(pullCount);
		return true;
	}
	return false;
}


int32_t& Scheduler::_TLD(int tid, int index)
{
	CPF_ASSERT(tid >= 0 && tid < mThreadCount);
	CPF_ASSERT(index >= 0 && index < kRegisterCount);
	return mThreadLocalDataRegister[tid][index];
}


void*& Scheduler::_TLA(int tid, int index)
{
	CPF_ASSERT(tid >= 0 && tid < mThreadCount);
	CPF_ASSERT(index >= 0 && index < kRegisterCount);
	return mThreadLocalAddressRegister[tid][index];
}


int32_t& Scheduler::_SD(int index)
{
	CPF_ASSERT(index >= 0 && index < kRegisterCount);
	return mSharedDataRegister[index];
}


void*& Scheduler::_SA(int index)
{
	CPF_ASSERT(index >= 0 && index < kRegisterCount);
	return mSharedAddressRegister[index];
}
