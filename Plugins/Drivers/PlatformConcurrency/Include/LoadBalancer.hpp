//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Scheduler.hpp"
#include "CPF/Platform/Concurrency/iLoadBalancer.hpp"
#include "CPF/Threading/CPU.hpp"
#include "CPF/IntrusivePtr.hpp"

namespace CPF
{
	namespace Platform
	{
		/** @brief A very simple placeholder load balancer. */
		class LoadBalanceMinimize : public GOM::tUnknown<iLoadBalancer>
		{
		public:
			static const int kUpdateRate = 1;

            LoadBalanceMinimize(Plugin::iRegistry*, iUnknown*);
			~LoadBalanceMinimize() = default;

            // Overrides from iThreadController.
            int32_t CPF_STDCALL GetMaxThreads() override;
            GOM::Result CPF_STDCALL SetMaxThreads(int32_t count) override;
            int32_t CPF_STDCALL GetActiveThreads() override;
            void CPF_STDCALL SetActiveThreads(int32_t count) override;
            void CPF_STDCALL SetPriority(SchedulingPriority level) override;
            SchedulingPriority CPF_STDCALL GetPriority() override;
            float CPF_STDCALL GetUtilization() override;
            void CPF_STDCALL GetThreadTimeInfo(ThreadTimeInfo* timeInfo) override;
            int32_t CPF_STDCALL GetDesiredThreadCount() override;

            // Overrides from iLoadBalancer.
            GOM::Result CPF_STDCALL SetControllers(int32_t count, iThreadController** controllers) override;
            GOM::Result CPF_STDCALL GetControllers(int32_t* count, iThreadController** controllers) override;
            GOM::Result CPF_STDCALL RebalanceThreads() override;

		private:
			using Controllers = STD::Vector<IntrusivePtr<iThreadController>>;

            Plugin::iRegistry* mpRegistry;
            Controllers mControllers;
            int32_t mMaxUsableThreads;
		};
	}
}
