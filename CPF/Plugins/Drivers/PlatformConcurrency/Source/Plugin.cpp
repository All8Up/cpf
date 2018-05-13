#include "CPF/Plugin.hpp"
#include "CPF/Logging.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Plugin/tClassFactory.hpp"
#include "Fence.hpp"
#include "Scheduler.hpp"
#include "WorkBuffer.hpp"
#include "ThreadPool.hpp"
#include "LoadBalancer.hpp"
#include "TimerService.hpp"

using namespace CPF;

namespace
{
    GOM::IID sPluginIID(GOM::IID("CPF::Concurrency"_crc64));
}

//////////////////////////////////////////////////////////////////////////
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
    int32_t references;
	if (registry && GOM::Succeeded(registry->Register(sPluginIID, &references)))
	{
        if (references == 1)
        {
            CPF_INIT_LOG(Concurrency);
            CPF_LOG_LEVEL(Concurrency, Warn);

		    registry->Install(Platform::iFence::kCID, new Plugin::tClassFactory<Platform::Fence>());
		    registry->Install(Platform::iScheduler::kCID, new Plugin::tClassFactory<Platform::Scheduler>());
		    registry->Install(Platform::iWorkBuffer::kCID, new Plugin::tClassFactory<Platform::WorkBuffer>());
		    registry->Install(Platform::iThreadPool::kCID, new Plugin::tClassFactory<Platform::ThreadPool>());
		    registry->Install(Platform::iLoadBalancer::kCIDLoadBalanceMinimize, new Plugin::tClassFactory<Platform::LoadBalanceMinimize>());
			registry->Install(Platform::iTimerService::kCID, new Plugin::tClassFactory<Platform::TimerService>());
		}
        return GOM::kOK;
    }
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
    int32_t references;
	if (registry && GOM::Succeeded(registry->Unregister(sPluginIID, &references)))
	{
        if (references == 0)
        {
			registry->Remove(Platform::iTimerService::kCID);
			registry->Remove(Platform::iLoadBalancer::kCIDLoadBalanceMinimize);
			registry->Remove(Platform::iThreadPool::kCID);
            registry->Remove(Platform::iWorkBuffer::kCID);
            registry->Remove(Platform::iScheduler::kCID);
            registry->Remove(Platform::iFence::kCID);

            CPF_DROP_LOG(Concurrency);
        }
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

CPF_REGISTER_PLUGIN(PlatformConcurrency)
	&Install,
	&Remove
};
