//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Collections/RingBuffer.hpp"
#include "Deque.hpp"
#include "Threading/Thread.hpp"
#include "Threading/Mutex.hpp"
#include "Threading/Semaphore.hpp"
#include "Threading/ConditionVariable.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Plugin/iRegistry.hpp"


extern "C" Cpf::COM::Result CPF_EXPORT Install(Cpf::Plugin::iRegistry* registry);

namespace Cpf
{
	namespace Concurrency
	{
		static constexpr int kMaxThreads = 64;

		namespace Detail
		{
			struct Opcodes;
		}

		class Semaphore;
		class ThreadTimes;
		class Queue;

		using PayloadFunc_t = void(*)(const WorkContext*, void*);

		struct ThreadTimeInfo
		{
			int mThreadCount;
			Time::Value mDuration;
			Time::Value mUserTime[kMaxThreads];
			Time::Value mKernelTime[kMaxThreads];
		};

		/** @brief Scheduler for multi-core distribution. */
		class CPF_EXPORT_CONCURRENCY Scheduler : public tRefCounted<iScheduler>
		{
		public:
			// TODO: Temporary hack to setup for moving over to plugin.
			static void Install(Plugin::iRegistry* regy) { ::Install(regy); }

			//
			static constexpr int kRegisterCount = 16;
			static constexpr int kQueueSize = 4096;
			using InitOrShutdownFunc_t = PayloadFunc_t;
			using OpcodeFunc_t = void(*)(Scheduler &vm, const WorkContext* context, int64_t index);
			struct Instruction
			{
				OpcodeFunc_t mpHandler;
				PayloadFunc_t mpFunction;
				void* mpContext;
			};


			// Construction/Destruction.
			explicit Scheduler(iUnknown*);
			~Scheduler();

			// iUnkown overrides.
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			// iScheduler overrides.
			COM::Result CPF_STDCALL Initialize(int threadCount, WorkFunction init, WorkFunction shutdown, void* context) override;
			void CPF_STDCALL Shutdown() override;

			int CPF_STDCALL GetMaxThreads() override { return GetAvailableThreads(); }
			int CPF_STDCALL GetActiveThreads() override { return GetCurrentThreads(); }

			void CPF_STDCALL Execute(iQueue*, bool clear = true) override;
			void Submit(Semaphore*) override;

			//////////////////////////////////////////////////////////////////////////

			// Data access.
			int GetAvailableThreads() const;
			void SetActiveThreads(int count);
			int GetCurrentThreads() const;
			void* GetContext() const;

			//
			void Submit(ThreadTimes&);
			void Execute(Queue&, bool clear=true);

		private:
			//////////////////////////////////////////////////////////////////////////
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
		PayloadFunc_t ThreadedCall(void(TYPE::*function)(const WorkContext*))
		{
			using FunctionType = void(TYPE::*)(const WorkContext*);
			static FunctionType func = function;
			struct Caller
			{
				static void Call(const WorkContext* tc, void* context)
				{
					TYPE* type = reinterpret_cast<TYPE*>(context);
					(type->*func)(tc);
				}
			};
			return &Caller::Call;
		}
#define SCHEDULED_CALL(t, f) Cpf::Concurrency::ThreadedCall<t, __COUNTER__>(f)


		class CPF_EXPORT_CONCURRENCY Semaphore
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

		class ThreadTimes : Semaphore
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
