//////////////////////////////////////////////////////////////////////////
#include "Scheduler.hpp"
#include "Backoff.hpp"
#include "WorkBuffer.hpp"
#include "Opcodes.hpp"
#include "CPF/Platform/Concurrency/WorkContext.hpp"
#include "CPF/Threading/ScopedLock.hpp"
#include "CPF/Performance/VTune.hpp"
#include <string>
#include <CPF/Std/String.hpp>
#include "CPF/GOM/ResultCodes.hpp"

#include "Fence.hpp"
#include "CPF/CSTD/Memory.hpp"
#include "CPF/Math/Algorithm.hpp"

using namespace CPF;
using namespace Platform;


//////////////////////////////////////////////////////////////////////////
VTune::Domain* gSchedulerDomain = VTune::DomainCreate("Scheduler");


//////////////////////////////////////////////////////////////////////////
const int Scheduler::kMaxBackoff = 4096;


/** @brief Default constructor. */
Scheduler::Scheduler()
    : mControlLock(0)
    , mTargetCount(0)
    , mActiveCount(0)
    , mThreadCount(0)
    , mInstructionRing(kQueueSize)
    , mPredicateRing(kQueueSize)
    , mWorkCount(0)
    , mQueueSize(kQueueSize)
    , mLastUpdate(Time::Now().GetTicks())
    , mUpdateRate(Time::Seconds(kUtilizationSampleRate))
{
	CSTD::MemSet(&mCurrentUtilization, 0, sizeof(mCurrentUtilization));
	CSTD::MemSet(&mLastTimeInfo, 0, sizeof(mLastTimeInfo));
	mCurrentUtilization.mDuration = Time::Now();
    mLastTimeInfo.mDuration = Time::Now();
}

/** @brief Destructor. */
Scheduler::~Scheduler()
{
	// Check that we were shut down.
	CPF_ASSERT(mThreadCount.load() == 0);
}

/**
 @brief Initializes the scheduler.
 @param          threadCount Number of threads to initialize with.
 @param          init The initialize function per thread.
 @param          shutdown The shutdown function per thread.
 @param [in,out] context If non-null, the context.
 @return A GOM result.
 */
GOM::Result CPF_STDCALL Scheduler::Initialize(int threadCount, WorkFunction init, WorkFunction shutdown, void* context)
{
	if (threadCount > 0)
	{
        SetPriority(SchedulingPriority::eNormal);
        mThreads = STD::Move(Threading::Thread::Group(threadCount));
		if (mInstructionRing.Initialize(mThreads.Size()))
		{
			// Setup to start with all threads active.
			mThreadCount = mTargetCount = mActiveCount = int(mThreads.Size());

			for (int i = 0; i < mThreadCount; ++i)
				mThreads(i, std::bind(&Scheduler::_Worker, this, i, init, shutdown, context));

			mLastTimeInfo.mThreadCount = mThreadCount;
            mLastTimeInfo.mDuration = Time::Value::Zero();
			for (int i = 0; i < mThreadCount; ++i)
			{
                mLastTimeInfo.mUserTime[i] = Time::Value::Zero();
                mLastTimeInfo.mKernelTime[i] = Time::Value::Zero();
            }

			return GOM::kOK;
		}
		mThreadCount = mTargetCount = mActiveCount = 0;
	}

	return GOM::kInvalidParameter;
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

/**
 @brief Gets available threads the scheduler was initialized with.
 @return The available threads.
 */
int Scheduler::GetAvailableThreads() const
{
	return mThreadCount;
}

/**
 @brief Gets current thread count in use.
 @return The current threads.
 */
int Scheduler::GetCurrentThreads() const
{
	return mActiveCount;
}

/**
 @brief Sets the number of active threads.  Only one set can be happening at
 a given time, if an outstanding change is already in flight, nothing will be
 done.
 @param count Number of.
 */
void Scheduler::SetActiveThreads(int count)
{
	CPF_ASSERT(count > 0);
	CPF_ASSERT(count <= mThreadCount);

	_Emit(Detail::Opcodes::AllBarrier, [](const WorkContext*, void* context) {
		reinterpret_cast<Threading::Semaphore*>(context)->Release();
	}, &mWait);
	mWait.Acquire();

	// Issue the change.
	if (count != mActiveCount.load()) {
		const auto intCount = intptr_t(count);
		_Emit(Detail::Opcodes::ActiveThreads, nullptr, reinterpret_cast<void *>(intCount));
	}
}

struct PriorityData
{
	int mSpinCount;
	int mSleepMS;
};
PriorityData sLoopPriorityData[]
{
	{ 8, 1 },
	{ 16, 1 },
	{ 256, 1 },
	{ 64, 1 },
	{ 16, 0 }
};

/**
 @brief Set the priority of this scheduler.
 @param level The level.
 */
void CPF_STDCALL Scheduler::SetPriority(SchedulingPriority level)
{
	// This is not atomic or protected in any manner but it won't much
	// matter, eventually the various threads will pick up the change
	// and putting locks on this would be horrible.  Making them atomic
	// on processors with issues of split writes may be needed but
	// arm and intel are fine since 32/64 bit writes are atomic already.
	for (int i=0; i<kMaxThreads; ++i)
	{
		mLoopBackoff[i].SetMaxSpin(sLoopPriorityData[int(level)].mSpinCount);
		mLoopBackoff[i].SetSleepMS(sLoopPriorityData[int(level)].mSleepMS);
	}
}

/**
 @brief Gets the priority applied to this scheduler.
 @return The priority.
 */
SchedulingPriority Scheduler::GetPriority()
{
	for (int i=0; i<5; ++i)
	{
		if (mLoopBackoff[0].GetMaxSpin() == sLoopPriorityData[i].mSpinCount &&
			mLoopBackoff[0].GetSleepMS() == sLoopPriorityData[i].mSleepMS)
			return SchedulingPriority(i);
	}
	return SchedulingPriority(0);
}

/**
 @brief Gets the utilization of this scheduler.  This is a 0+ value
 describing how many threads (cores) worth of work are being performed.
 @return The utilization value.
 */
float CPF_STDCALL Scheduler::GetUtilization()
{
    ThreadTimeInfo info;
    GetThreadTimeInfo(&info);
    float result = 0.0f;
    for (int i = 0; i < info.mThreadCount; ++i)
    {
        result += float(Time::Seconds(info.mUserTime[i]));
        result += float(Time::Seconds(info.mKernelTime[i]));
    }
    const auto duration = float(Time::Seconds(info.mDuration));
    if (duration > 0.5f * kUtilizationSampleRate)
        return result / float(Time::Seconds(info.mDuration));
    return 1.0f;
}

/**
 @brief Gets thread time information which represents current utilization by this scheduler.
 @param [in,out] timeInfo If non-null, information describing the time.
 @return The thread time information.
 */
void CPF_STDCALL Scheduler::GetThreadTimeInfo(ThreadTimeInfo* timeInfo)
{
    Threading::ScopedLock<Threading::Mutex> lock(mTimeLock);
    timeInfo->mThreadCount = mCurrentUtilization.mThreadCount;
    timeInfo->mDuration = mCurrentUtilization.mDuration - mLastTimeInfo.mDuration;
    const float timeAdjustment = float(Time::Seconds(timeInfo->mDuration)) / kUtilizationSampleRate;
    for (int i = 0; i<kMaxThreads; ++i)
    {
        if (i >= timeInfo->mThreadCount)
        {
            timeInfo->mUserTime[i] = Time::Value();
            timeInfo->mKernelTime[i] = Time::Value();
        }
        else
        {
            const float userTime = float(Time::Seconds(mCurrentUtilization.mUserTime[i] - mLastTimeInfo.mUserTime[i])) * timeAdjustment;
            timeInfo->mUserTime[i] = Time::Seconds(userTime);
            const float kernelTime = float(Time::Seconds(mCurrentUtilization.mKernelTime[i] - mLastTimeInfo.mKernelTime[i])) * timeAdjustment;
            timeInfo->mKernelTime[i] = Time::Seconds(kernelTime);
        }
    }
}

/**
 @brief Gets desired thread count for this thread controller.
 @return The desired thread count.
 */
int32_t CPF_STDCALL Scheduler::GetDesiredThreadCount()
{
    const auto utilization = std::ceilf(GetUtilization() + 0.5f);
    const auto target = int32_t(utilization);
    return Math::Min(Math::Max(1, target), GetMaxThreads());
}

/**
 @brief Gets the context associated with this scheduler.  This is
 intended to be used when multiple schedulers are working together
 and need association with each other.  As this is not common though,
 it is not a formalized portion of the scheduler.  For the most part
 it will likely be used to associate a thread pool with the scheduler
 such that long running work knows which pool to use.
 @return Null if it fails, else the context.
 */
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
void Scheduler::_Emit(OpcodeFunc_t opcode, WorkFunction func, void* context)
{
	// NOTE: It may be tempting to make this a lockless queue but
	// generally speaking this mutex should be low contention given
	// how the internals work.  The exception is if multiple threads
	// attempt to push work which really is not intended usage at this
	// level of the system.
	{
		Threading::ScopedLock<Threading::Mutex> lock(mWorkLock);
		mExternalQueue.push_back({opcode, func, context});
		mWorkCount.fetch_add(1);
	}
}

/**
 @brief Submits the fence to the scheduler.
 @param [in,out] fence If non-null, the semaphore.
 */
void Scheduler::Submit(iFence* fence)
{
	_Emit(Detail::Opcodes::LastOne, [](const WorkContext*, void* context)
	{
		reinterpret_cast<iFence*>(context)->Signal();
	}, fence);
}

/** @brief Internal function to insert instructions to update thread utilization information. */
void Scheduler::_UpdateThreadTimes()
{
    _Emit(Detail::Opcodes::All, [](const WorkContext* tc, void* context)
    {
        auto* times = reinterpret_cast<ThreadTimeInfo*>(context);
        Threading::Thread::GetThreadTimes(
            times->mUserTime[tc->mThreadID],
            times->mKernelTime[tc->mThreadID]
        );
	}, &mUpdatedUtilization);
    _Emit(Detail::Opcodes::LastOne, [](const WorkContext* tc, void* context)
    {
        Threading::ScopedLock<Threading::Mutex> lock(reinterpret_cast<Scheduler*>(tc->mpScheduler)->mTimeLock);
        auto scheduler = static_cast<Scheduler*>(tc->mpScheduler);
        auto* times = reinterpret_cast<ThreadTimeInfo*>(context);

		// TODO: This is a hack to prevent overshort samples when
		// they happen, though I'm not currently sure why..
		if (float(Time::Seconds(Time::Now() - scheduler->mCurrentUtilization.mDuration))
			< 0.8f * float(Time::Seconds(scheduler->mUpdateRate)))
		{
			return;
		}

		// Move current to last.
		scheduler->mLastTimeInfo = scheduler->mCurrentUtilization;
		// Move the new sample to the current utilization.
		scheduler->mCurrentUtilization = *times;
		scheduler->mCurrentUtilization.mThreadCount = tc->mpScheduler->GetActiveThreads();
		scheduler->mCurrentUtilization.mDuration = Time::Now();

		// If we added threads since last sample, make sure
		// the samples will end up as zero.
		for (int i= scheduler->mLastTimeInfo.mThreadCount;
			i<scheduler->mCurrentUtilization.mThreadCount;
			++i)
		{
			scheduler->mLastTimeInfo.mUserTime[i] = scheduler->mCurrentUtilization.mUserTime[i];
			scheduler->mLastTimeInfo.mKernelTime[i] = scheduler->mCurrentUtilization.mKernelTime[i];
		}
	}, &mUpdatedUtilization);
}

/**
 * @brief Executes.
 * @param [in,out] queue If non-null, the queue.
 * @param clear True to clear.
 */
void CPF_STDCALL Scheduler::Execute(iWorkBuffer* queue)
{
	Threading::ScopedLock<Threading::Mutex> lock(mWorkLock);
	const auto q = static_cast<WorkBuffer*>(queue);
	mExternalQueue.insert(mExternalQueue.end(), q->begin(), q->end());
	mWorkCount.fetch_sub(mExternalQueue.size());
}

/**
 * @brief The primary worker function for threads.  This is actually modeled as a spin lock so it can perform exponential backoff.
 * @param index An internally assigned, incrementing index for each thread.
 * @param initFunc Pass through from initialize which is called by each thread.
 * @param initContext Pass through of the opaque data pointer for the initialization/shutdown function.
 */
void Scheduler::_Worker(int index, InitOrShutdownFunc_t initFunc, InitOrShutdownFunc_t shutdownFunc, void* ctx)
{
	// Setup the thread name for debugging.
	Threading::Thread::SetName((std::string("Scheduler thread: ") + std::to_string(index)).c_str());

	// Setup the thread context for calling opcodes.
	WorkContext context{this, index, nullptr};

	// Run the optional initialization function.
	if (initFunc)
		initFunc(&context, ctx);

	// Setup performance profiling.
	STD::String threadNumber("Thread(");
	threadNumber += std::to_string(index).c_str();
	threadNumber += ")";
	STD::String threadWork = threadNumber + " work";
	VTUNE_EVENT_CREATE(workEvent);
	STD::String threadMaster = threadNumber + " master";
	VTUNE_EVENT_CREATE(masterEvent);

	// Begin the core loop.
    mLastUpdate.store(Time::Now().GetTicks());
	for (;;)
	{
        VTUNE_EVENT_START(workEvent);

		//////////////////////////////////////////////////////////////////////////
		// Check for available work.
        {
            Instruction work;
        checkWork:
            {
                const int64_t workIndex = mInstructionRing.Fetch(index, work);
                if (workIndex != Collections::RingBuffer<Instruction>::kInvalidIndex)
                {
                    if (work.mpHandler)
                    {
                        work.mpHandler(*this, &context, workIndex);

                        // Mark the instruction consumed.
                        mInstructionRing.ConsumeThreadHead(index);
                    }
                    else
                        break;

                    // When we get something to execute, reset our backoff.
                    mLoopBackoff[index].Reset();

                    goto checkWork;
                }
            }
            VTUNE_EVENT_END(workEvent);
		}


		//////////////////////////////////////////////////////////////////////////
		// Attempt to take control and fetch more work.
		if (_StartMaster())
		{
            const auto now = Time::Now();
			const auto lastUpdate = mLastUpdate.load();
            if (now.GetTicks() - lastUpdate >= mUpdateRate.GetTicks())
            {
                mLastUpdate.store(lastUpdate + mUpdateRate.GetTicks());
                _UpdateThreadTimes();
            }

			VTUNE_EVENT_START(masterEvent);
			const auto more = _FetchWork();
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
		// be latency between receiving new instructions and executing them.
		mLoopBackoff[index]();
	}

	// Call the optional shutdown function.
	if (shutdownFunc)
		shutdownFunc(&context, ctx);
}

/**
 * @brief Attempt to take control of the instruction ring buffer tail.
 * @return true if it succeeds, false if it fails.
 */
bool Scheduler::_StartMaster()
{
	// Simply attempt to poke a 1 into the lock, we are
	// control if that happens.
	if (mWorkCount.load() > 0)
	{
		auto oldValue = mControlLock.load();
		return mControlLock.compare_exchange_weak(oldValue, 1);
	}
	return false;
}

/** @brief Release access to the ring buffer tail pointer. */
void Scheduler::_EndMaster()
{
	// Restore the lock to 0.
	mControlLock.store(0, std::memory_order::memory_order_release);
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
	const auto externalCount = mExternalQueue.size();
	if (externalCount > 0)
	{
		const auto pullCount = mInstructionRing.Reserve(mActiveCount.load(), mQueueSize-1 < externalCount ? mQueueSize - 1 : externalCount);
		if (pullCount == 0)
			return false;
		mWorkCount.fetch_sub(pullCount);

		const auto start = mInstructionRing.GetTail();

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
			mPredicateRing[start + i] = mTargetCount.load();

			// If this is changing the thread count, apply the change so subsequent
			// instructions will have a proper predicate setup.
			if (inst.mpHandler== Detail::Opcodes::ActiveThreads) {
				const auto target = int(reinterpret_cast<intptr_t>(inst.mpContext));
				CPF_ASSERT(target>0 && target <= mThreadCount);
				mTargetCount.store(target);
			}
		}
		mExternalQueue.erase(mExternalQueue.begin(), mExternalQueue.begin() + pullCount);

		// Update the tail with new instructions.
		std::atomic_thread_fence(std::memory_order_release);
		mInstructionRing.Commit(pullCount);
		return true;
	}
	return false;
}
