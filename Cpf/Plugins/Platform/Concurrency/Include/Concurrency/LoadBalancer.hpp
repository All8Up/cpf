//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Scheduler.hpp"
#include "Concurrency/iLoadBalancer.hpp"
#include "Platform/Threading/CPU.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		/** @brief A very simple placeholder load balancer. */
		class LoadBalancer : public tRefCounted<iLoadBalancer>
		{
		public:
			static const int kUpdateRate = 1;

			LoadBalancer(iUnknown*);
			~LoadBalancer();

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;
			COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy, int count, iScheduler**) override;

			// TODO: Add policy information to each scheduler.
			// Policies should describe how the scheduler is being used.
			// So a primary loop scheduler will be balanced so that it
			// tries to accomplish all it's work in the minimum number
			// of threads but with say 15% overhead remaining for any
			// spikes in processing.  A scheduler used as a thread pool
			// on the other hand increases it's thread count based on the
			// number of waiting tasks and doesn't really pay too much
			// attention to it's actual utilization.
			void CPF_STDCALL Balance() override;

		private:
			using Schedulers = Vector<iScheduler*>;

			Schedulers mSchedulers;
			IntrusivePtr<iThreadTimes> mpDistTimeQuery;
			bool mQueryOutstanding = false;
			Time::Value mLastUpdate;
			Threading::CPUUsage mCPUUsage;
		};
	}
}
