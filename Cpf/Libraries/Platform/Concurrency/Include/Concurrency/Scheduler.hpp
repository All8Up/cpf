//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Collections/RingBuffer.hpp"
#include "Deque.hpp"
#include "Threading/Thread.hpp"
#include "Threading/Mutex.hpp"
#include "Threading/Semaphore.hpp"
#include "Threading/ConditionVariable.hpp"


namespace Cpf
{
	namespace Concurrency
	{
		class ThreadContext;
		namespace Detail
		{
			struct Opcodes;
		}


		/** @brief Scheduler for multi-core distribution. */
		class CPF_EXPORT_CONCURRENCY Scheduler
		{
		public:
			//
			static const int kMaxThreads = 64;
			static const int kRegisterCount = 16;
			using ThreadContext = ThreadContext;
			using PayloadFunc_t = void(*)(ThreadContext&, void*);
			using InitOrShutdownFunc_t = PayloadFunc_t;
			using OpcodeFunc_t = void(*)(Scheduler &vm, ThreadContext& context, int64_t index);
			struct Instruction
			{
				OpcodeFunc_t mpHandler;
				PayloadFunc_t mpFunction;
				void* mpContext;
			};
			struct ThreadTimeInfo
			{
				int mThreadCount;
				Time::Value mDuration;
				Time::Value mUserTime[kMaxThreads];
				Time::Value mKernelTime[kMaxThreads];
			};


			class Queue;
			class Semaphore;
			class ThreadTimes;

			// Construction/Destruction.
			explicit Scheduler(void* outerContext = nullptr, size_t queueSize=4096);
			~Scheduler();

			//
			bool Initialize(Threading::Thread::Group&&, InitOrShutdownFunc_t init = nullptr, InitOrShutdownFunc_t shutdown = nullptr, void* context = nullptr);
			void Shutdown();

			// Data access.
			int GetAvailableThreads() const;
			void SetActiveThreads(int count);
			int GetActiveThreads() const;
			void* GetContext() const;

			//
			void Submit(Semaphore&);
			void Submit(ThreadTimes&);
			void Execute(Queue&, bool clear=true);

		private:
			//////////////////////////////////////////////////////////////////////////
			friend class Concurrency::ThreadContext;
			friend struct Detail::Opcodes;
			CPF_DLL_SAFE_BEGIN;

			//////////////////////////////////////////////////////////////////////////
			static const int kMaxBackoff;

			// Internal implementation.
			void _Emit(OpcodeFunc_t, PayloadFunc_t func, void* context);
			void _Worker(int index, InitOrShutdownFunc_t initFunc, InitOrShutdownFunc_t shutdownFunc, void* context);
			bool _StartMaster();
			void _EndMaster();
			bool _FetchWork();
			void _ClearRegisters();

			// Spin lock variable for the thread fetching instructions.
			int32_t mControlLock;
			int8_t pad0[64-sizeof(int32_t)];

			// External work queue.
			Threading::Mutex mWorkLock;
			Deque<Instruction> mExternalQueue;

			// Active thread counts.
			int32_t mTargetCount;
			int8_t pad1[64-sizeof(int32_t)];
			int32_t mActiveCount;
			int32_t mThreadCount;
			Threading::Thread::Group mThreads;

			// The internal instruction queue.
			// This is split into two pieces to avoid false sharing
			// between instructions and the predicate.
			Collections::RingBuffer<Instruction> mInstructionRing;
			Collections::RingBuffer<int64_t> mPredicateRing;

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

			// Register access, used only via the ThreadContext.
			int32_t& _TLD(int tid, int index);
			void*& _TLA(int tid, int index);
			int32_t& _SD(int index);
			void*& _SA(int index);

			// Control registers.
			int32_t mThreadLocalDataRegister[kMaxThreads][kRegisterCount];
			void* mThreadLocalAddressRegister[kMaxThreads][kRegisterCount];

			int32_t mSharedDataRegister[kRegisterCount];
			void* mSharedAddressRegister[kRegisterCount];

			ThreadTimeInfo mTimeInfo;
			CPF_DLL_SAFE_END;
		};

		//////////////////////////////////////////////////////////////////////////
		// Helper utility for payload functions.  This is a nasty little thing
		// since it relies on a unique instantiation of the template for each
		// specific member it will call.  The macro wrapper takes care of the unique
		// identifier via the macro counter.  In most cases, the benefits out weight the
		// evil inherent.
		template<typename TYPE, int UNIQUE>
		Scheduler::PayloadFunc_t ThreadedCall(void(TYPE::*function)(ThreadContext&))
		{
			using FunctionType = void(TYPE::*)(ThreadContext&);
			static FunctionType func = function;
			struct Caller
			{
				static void Call(ThreadContext& tc, void* context)
				{
					TYPE* type = reinterpret_cast<TYPE*>(context);
					(type->*func)(tc);
				}
			};
			return &Caller::Call;
		}
#define SCHEDULED_CALL(t, f) ThreadedCall<t, __COUNTER__>(f)


		class CPF_EXPORT_CONCURRENCY Scheduler::Semaphore
		{
		public:
			Semaphore(int32_t value=0);
			void Acquire();
			void Release();

		private:
			CPF_DLL_SAFE_BEGIN;
			Threading::Semaphore mSemaphore;
			CPF_DLL_SAFE_END;
		};

		class Scheduler::ThreadTimes : private Semaphore
		{
		public:
			ThreadTimes() {}

			ThreadTimeInfo GetResult() { Acquire(); return mTimeResult; }

		private:
			friend class Scheduler;

			ThreadTimeInfo mTimeResult;
		};
	}
}


//
#include <Concurrency/Queue.hpp>
#include <Concurrency/ThreadContext.hpp>
