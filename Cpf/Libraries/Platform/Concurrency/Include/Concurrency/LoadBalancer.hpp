//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Scheduler.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		/** @brief A very simple placeholder load balancer. */
		class LoadBalancer
		{
		public:
			static const int kUpdateRate = 1;

			LoadBalancer();
			~LoadBalancer();

			using Schedulers = Vector<Scheduler*>;

			// TODO: Add policy information to each scheduler.
			// Policies should describe how the scheduler is being used.
			// So a primary loop scheduler will be balanced so that it
			// tries to accomplish all it's work in the minimum number
			// of threads but with say 15% overhead remaining for any
			// spikes in processing.  A scheduler used as a thread pool
			// on the other hand increases it's thread count based on the
			// number of waiting tasks and doesn't really pay too much
			// attention to it's actual utilization.
			void SetSchedulers(Schedulers&&);
			void Balance();

		private:
			Schedulers mSchedulers;
			Scheduler::ThreadTimes mDistTimeQuery;
			bool mQueryOutstanding = false;
			Platform::Time::Value mLastUpdate;
		};
	}
}
