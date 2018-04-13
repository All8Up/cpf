//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Concurrency/iScheduler.hpp"
#include "CPF/Platform/Concurrency/iThreadPool.hpp"
#include "CPF/iRefCounted.hpp"
#include "CPF/IntrusivePtr.hpp"

namespace CPF
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
			ThreadPool(Plugin::iRegistry*, iUnknown*);
			~ThreadPool();

			GOM::Result CPF_STDCALL QueryInterface(GOM::IID id, void** outIface) override;

			GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy, int threadCount) override;
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
