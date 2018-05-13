//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Backoff.hpp"
#include "Collections/RingBuffer.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Std/Deque.hpp"
#include "CPF/Threading/Thread.hpp"
#include "CPF/Threading/Mutex.hpp"
#include "CPF/Threading/Semaphore.hpp"
#include "CPF/Threading/ConditionVariable.hpp"
#include "CPF/Platform/Concurrency/iScheduler.hpp"
#include "CPF/Platform/Concurrency/ThreadTimeInfo.hpp"
#include <atomic>

namespace CPF
{
	namespace Platform
	{
		namespace Detail
		{
			struct Opcodes;
		}

		struct iWorkBuffer;
		struct iThreadTimes;

		/** @brief Scheduler for multi-core distribution. */
		class Scheduler : public GOM::tUnknown<iScheduler>
		{
		public:
			// Construction/Destruction.
			explicit Scheduler();
			~Scheduler();

			//
            static constexpr float kUtilizationSampleRate = 0.25f;
			static constexpr int kQueueSize = 4096;
			using InitOrShutdownFunc_t = WorkFunction;
			using OpcodeFunc_t = void(*)(Scheduler &vm, const WorkContext* context, int64_t index);
			struct Instruction
			{
				OpcodeFunc_t mpHandler;
				WorkFunction mpFunction;
				void* mpContext;
			};

            // iThreadController overrides.
            int CPF_STDCALL GetMaxThreads() override { return GetAvailableThreads(); }
            GOM::Result CPF_STDCALL SetMaxThreads(int32_t count) override { (void)count; return GOM::kOK; }
            int CPF_STDCALL GetActiveThreads() override { return GetCurrentThreads(); }
            void CPF_STDCALL SetActiveThreads(int count) override;
            void CPF_STDCALL SetPriority(SchedulingPriority level) override;
            SchedulingPriority CPF_STDCALL GetPriority() override;
            float CPF_STDCALL GetUtilization() override;
            void CPF_STDCALL GetThreadTimeInfo(ThreadTimeInfo* timeInfo) override;
            int32_t CPF_STDCALL GetDesiredThreadCount() override;

			// iScheduler overrides.
			GOM::Result CPF_STDCALL Initialize(int threadCount, WorkFunction init, WorkFunction shutdown, void* context) override;
			void CPF_STDCALL Shutdown() override;

			void CPF_STDCALL Execute(iWorkBuffer*) override;
			void CPF_STDCALL Submit(iFence*) override;

			//////////////////////////////////////////////////////////////////////////

			// Data access.
			int GetAvailableThreads() const;
			int GetCurrentThreads() const;
			void* GetContext() const;

		private:
			//////////////////////////////////////////////////////////////////////////
			friend struct Detail::Opcodes;
			CPF_DLL_SAFE_BEGIN;

			//////////////////////////////////////////////////////////////////////////
			static const int kMaxBackoff;

			// Internal implementation.
			void _Emit(OpcodeFunc_t, WorkFunction func, void* context);
			void _Worker(int index, InitOrShutdownFunc_t initFunc, InitOrShutdownFunc_t shutdownFunc, void* context);
			bool _StartMaster();
			void _EndMaster();
			bool _FetchWork();
            void _UpdateThreadTimes();

			// Spin lock variable for the thread fetching instructions.
			std::atomic<int32_t> mControlLock;
			int8_t pad0[64-sizeof(int32_t)];

			// External work queue.
			Threading::Mutex mWorkLock;
			STD::Deque<Instruction> mExternalQueue;

			// Active thread counts.
			std::atomic<int32_t> mTargetCount;
			int8_t pad1[64-sizeof(int32_t)];
			std::atomic<int32_t> mActiveCount;
			std::atomic<int32_t> mThreadCount;
			Threading::Thread::Group mThreads;

			// The internal instruction queue.
			// This is split into two pieces to avoid false sharing
			// between instructions and the predicate.
			Collections::RingBuffer<Instruction> mInstructionRing;
			Collections::RingBuffer<std::atomic<int64_t>> mPredicateRing;

			// Tracking for external queue size.
			int8_t pad2[64];
			std::atomic<size_t> mWorkCount;

			// Thread parking.
			Threading::Semaphore mActive;
			Threading::Mutex mActiveLock;
			Threading::ConditionVariable mActiveCondition;

			// System binding.
			void* mpOuterContext;

			// Queue size.
			const size_t mQueueSize;

			// Utility.
			Threading::Semaphore mWait;

			// Backoff primitive for the primary loop spin.
			Backoff mLoopBackoff[kMaxThreads];

			// Semaphore for the sleep opcodes.
			Threading::Semaphore mSleepOp;

            Threading::Mutex mTimeLock;
            std::atomic<int64_t> mLastUpdate;
            Time::Value mUpdateRate;

            ThreadTimeInfo mCurrentUtilization;
			ThreadTimeInfo mUpdatedUtilization;
			ThreadTimeInfo mLastTimeInfo;

			CPF_DLL_SAFE_END;
		};
	}
}
