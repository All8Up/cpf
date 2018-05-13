//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Concurrency/iScheduler.hpp"
#include "CPF/Platform/Concurrency/iThreadPool.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/iRefCounted.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/Platform/Concurrency/ThreadTimeInfo.hpp"
#include "CPF/GOM/ResultCodes.hpp"

namespace CPF
{
	namespace Platform
	{
		/** @brief A thread pool implementation based on the concurrency
		 * scheduler.  The scheduler handles the heavy lifting in terms
		 * of maintaining the threads and waking/sleeping the threads while
		 * this simply pushes work as first one instructions.
		 */
		class ThreadPool : public tRefCounted<iThreadPool>
		{
		public:
			ThreadPool(Plugin::iRegistry*);
			~ThreadPool();

			GOM::Result CPF_STDCALL QueryInterface(GOM::IID id, void** outIface) override;

			GOM::Result CPF_STDCALL Initialize(int threadCount) override;
			void CPF_STDCALL Shutdown() override;

			// TODO: Make this promise/future based, but it will need to be a
			// custom promise to make it actually useful, C++11 promises are
			// way too primitive.

            // iThreadPool overrides.
			void CPF_STDCALL Enqueue(WorkFunction, void* context) override;
			iScheduler* CPF_STDCALL GetScheduler() override { return mpScheduler; }

            // iThreadController overrides.
            int CPF_STDCALL GetMaxThreads() override { return mpScheduler->GetMaxThreads(); }
            GOM::Result CPF_STDCALL SetMaxThreads(int32_t count) override { (void)count; return GOM::kOK; }
            int CPF_STDCALL GetActiveThreads() override { return mpScheduler->GetActiveThreads(); }
            void CPF_STDCALL SetActiveThreads(int count) override { mpScheduler->SetActiveThreads(count); }
            void CPF_STDCALL CPF_STDCALL SetPriority(SchedulingPriority level) override { mpScheduler->SetPriority(level); }
            SchedulingPriority CPF_STDCALL GetPriority() override { return mpScheduler->GetPriority(); }
            float CPF_STDCALL GetUtilization() override { return 0.0f; }
            void CPF_STDCALL GetThreadTimeInfo(ThreadTimeInfo*) { }
            int32_t CPF_STDCALL GetDesiredThreadCount() override { return 0; }

		private:
            Plugin::iRegistry* mpRegistry;
			IntrusivePtr<iScheduler> mpScheduler;
			IntrusivePtr<iWorkBuffer> mpQueue;
		};
	}
}
