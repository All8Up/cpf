//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Scheduler.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		/** @brief A thread pool implementation based on the concurrency
		 * scheduler.  The scheduler handles the heavy lifting in terms
		 * of maintaining the threads and waking/sleeping the threads while
		 * this simply pushes work as first one instructions.
		 */
		class CPF_EXPORT_CONCURRENCY ThreadPool
		{
		public:
			ThreadPool();
			~ThreadPool();

			bool Initialize(Plugin::iRegistry* regy, int threadCount);
			void Shutdown();

			// TODO: Make this promise/future based, but it will need to be a
			// custom promise to make it actually useful, C++11 promises are
			// way too primitive.

			using Task = PayloadFunc_t;
			void Enqueue(Task, void* context);

			int GetAvailableThreads() const;
			void SetActiveThreads(int count);
			int GetActiveThreads() const;

			iScheduler* GetScheduler() { return mpScheduler; }

		private:
			IntrusivePtr<iScheduler> mpScheduler;
			Queue mQueue;
		};
	}
}
