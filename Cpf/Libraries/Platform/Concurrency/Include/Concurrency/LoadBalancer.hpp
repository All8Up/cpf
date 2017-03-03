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

			void SetSchedulers(Schedulers&&);
			void Balance();

		private:
			Schedulers mSchedulers;
			Platform::Time::Value mLastUpdate;
		};
	}
}
