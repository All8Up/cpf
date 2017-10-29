//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Collections/RingBuffer.hpp"
#include "Deque.hpp"
#include "Threading/Thread.hpp"
#include "Threading/Mutex.hpp"
#include "Threading/Semaphore.hpp"
#include "Threading/ConditionVariable.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Plugin/tClassInstance.hpp"
#include "Concurrency/ThreadTimeInfo.hpp"
#include <atomic>

namespace CPF
{
	namespace Concurrency
	{
		namespace Detail
		{
			struct Opcodes;
		}

		struct iThreadTimes;
		struct iWorkBuffer;
		struct iThreadTimes;

		/** @brief Scheduler for multi-core distribution. */
		class Scheduler : public tRefCounted<iScheduler>
		{
		public:
			//
			static constexpr int kQueueSize = 4096;
			using InitOrShutdownFunc_t = WorkFunction;
			using OpcodeFunc_t = void(*)(Scheduler &vm, const WorkContext* context, int64_t index);
			struct Instruction
			{
				OpcodeFunc_t mpHandler;
				WorkFunction mpFunction;
				void* mpContext;
			};

			// iUnkown overrides.
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			// iScheduler overrides.
			GOM::Result CPF_STDCALL Initialize(int threadCount, WorkFunction init, WorkFunction shutdown, void* context) override;
			void CPF_STDCALL Shutdown() override;

			int CPF_STDCALL GetMaxThreads() override { return GetAvailableThreads(); }
			int CPF_STDCALL GetActiveThreads() override { return GetCurrentThreads(); }
			void CPF_STDCALL SetActiveThreads(int count) override;

			void CPF_STDCALL Execute(iWorkBuffer*, bool clear = true) override;
			void CPF_STDCALL Submit(iFence*) override;

			//////////////////////////////////////////////////////////////////////////

			// Data access.
			int GetAvailableThreads() const;
			int GetCurrentThreads() const;
			void* GetContext() const;

			//
			void Submit(iThreadTimes*);

		private:
			// Construction/Destruction.
			explicit Scheduler(Plugin::iRegistry*, iUnknown*);
			~Scheduler();

			template <typename TYPE>
			friend struct Plugin::tClassInstance;

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

			// Spin lock variable for the thread fetching instructions.
			std::atomic<int32_t> mControlLock;
			int8_t pad0[64-sizeof(int32_t)];

			// External work queue.
			Threading::Mutex mWorkLock;
			Deque<Instruction> mExternalQueue;

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

			ThreadTimeInfo mTimeInfo;
			CPF_DLL_SAFE_END;
		};
	}
}
