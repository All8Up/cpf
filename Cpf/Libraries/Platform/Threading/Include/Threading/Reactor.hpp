//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Export.hpp"
#include "Threading/Mutex.hpp"
#include "Threading/ConditionVariable.hpp"
#include "Queue.hpp"
#include "Functional.hpp"


namespace Cpf
{
	namespace Threading
	{
		/** @brief A reactor can be owned by a worker thread, other threads
		 *	can post work to a WorkQueue for the owner to execute.
		 */
		class CPF_EXPORT_THREADING Reactor
		{
		public:
			using WorkFunction = Function<void(void)>;
			class WorkQueue;

			Reactor();
			~Reactor();

			bool Run();
			bool RunOne();
			void Quit();

		private:
			Reactor(Reactor&&) = delete;
			Reactor(const Reactor&) = delete;
			Reactor& operator =(Reactor&&) = delete;
			Reactor& operator =(const Reactor&) = delete;

			bool mExit;
			Mutex mLock;
			ConditionVariable mCondition;
			CPF_DLL_SAFE_BEGIN;
			Queue<WorkFunction> mQueue;
			CPF_DLL_SAFE_END;
		};


		/** @brief The queue feeder.  Push work in here, it comes out in the reactor. */
		class CPF_EXPORT_THREADING Reactor::WorkQueue
		{
		public:
			WorkQueue();
			WorkQueue(Reactor*);

			void Initialize(Reactor*);

			void operator ()(WorkFunction&) const;
			void operator ()(WorkFunction&&) const;

		private:
			WorkQueue(const WorkQueue&) = delete;
			WorkQueue(WorkQueue&&) = delete;
			WorkQueue& operator = (const WorkQueue&) = delete;
			WorkQueue& operator = (WorkQueue&&) = delete;

			Reactor* mpReactor;
		};
	}
}
