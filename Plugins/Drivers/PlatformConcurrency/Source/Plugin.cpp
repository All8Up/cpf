#include "CPF/Plugin/iRegistry.hpp"
#include "WorkBuffer.hpp"
#include "Scheduler.hpp"
#include "ThreadTimes.hpp"
#include "Fence.hpp"
#include "ThreadPool.hpp"
#include "LoadBalancer.hpp"
#include "CPF/Plugin/tClassFactory.hpp"
#include "CPF/Logging.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Plugin.hpp"

using namespace CPF;

//////////////////////////////////////////////////////////////////////////
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(Concurrency);
		CPF_LOG_LEVEL(Concurrency, Warn);

		registry->Install(Concurrency::iThreadTimes::kCID, new Plugin::tClassFactory<Concurrency::ThreadTimes>());
		registry->Install(Concurrency::iFence::kCID, new Plugin::tClassFactory<Concurrency::Fence>());
		registry->Install(Concurrency::iScheduler::kCID, new Plugin::tClassFactory<Concurrency::Scheduler>());
		registry->Install(Concurrency::iWorkBuffer::kCID, new Plugin::tClassFactory<Concurrency::WorkBuffer>());
		registry->Install(Concurrency::iThreadPool::kCID, new Plugin::tClassFactory<Concurrency::ThreadPool>());
		registry->Install(Concurrency::iLoadBalancer::kCID, new Plugin::tClassFactory<Concurrency::LoadBalancer>());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(Concurrency::iLoadBalancer::kCID);
		registry->Remove(Concurrency::iThreadPool::kCID);
		registry->Remove(Concurrency::iWorkBuffer::kCID);
		registry->Remove(Concurrency::iScheduler::kCID);
		registry->Remove(Concurrency::iFence::kCID);
		registry->Remove(Concurrency::iThreadTimes::kCID);

		CPF_DROP_LOG(Concurrency);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

CPF_REGISTER_PLUGIN(PlatformConcurrency)
	&Install,
	&Remove
};
