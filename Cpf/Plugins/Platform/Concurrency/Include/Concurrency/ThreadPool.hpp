//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iThreadPool.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		/** @brief A thread pool implementation based on the concurrency
		 * scheduler.  The scheduler handles the heavy lifting in terms
		 * of maintaining the threads and waking/sleeping the threads while
		 * this simply pushes work as first one instructions.
		 */
		class ThreadPool : public tRefCounted<iThreadPool>
		{
		public:
			ThreadPool(iUnknown*);
			~ThreadPool();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			bool CPF_STDCALL Initialize(Plugin::iRegistry* regy, int threadCount) override;
			void CPF_STDCALL Shutdown() override;

			// TODO: Make this promise/future based, but it will need to be a
			// custom promise to make it actually useful, C++11 promises are
			// way too primitive.

			void CPF_STDCALL Enqueue(WorkFunction, void* context) override;

			int CPF_STDCALL GetAvailableThreads() override;
			void CPF_STDCALL SetActiveThreads(int count) override;
			int CPF_STDCALL GetActiveThreads() override;

			iScheduler* CPF_STDCALL GetScheduler() override { return mpScheduler; }

		private:
			IntrusivePtr<iScheduler> mpScheduler;
			IntrusivePtr<iWorkBuffer> mpQueue;
		};
	}
}
