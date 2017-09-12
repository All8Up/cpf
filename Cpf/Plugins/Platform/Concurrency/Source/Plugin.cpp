#include "Plugin/iRegistry.hpp"
#include "Concurrency/WorkBuffer.hpp"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/ThreadTimes.hpp"
#include "Concurrency/Fence.hpp"
#include "Concurrency/ThreadPool.hpp"
#include "Concurrency/LoadBalancer.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;

extern "C" void CPF_EXPORT InstallScheduler(Plugin::iRegistry* registry)
{
	CPF_INIT_LOG(Concurrency);
	CPF_LOG_LEVEL(Concurrency, Warn);

	registry->Install(Concurrency::kThreadTimeCID.GetID(), new Plugin::tClassInstance<Concurrency::ThreadTimes>());
	registry->Install(Concurrency::kFenceCID.GetID(), new Plugin::tClassInstance<Concurrency::Fence>());
	registry->Install(Concurrency::kSchedulerCID.GetID(), new Plugin::tClassInstance<Concurrency::Scheduler>());
	registry->Install(Concurrency::kWorkBufferCID.GetID(), new Plugin::tClassInstance<Concurrency::WorkBuffer>());
	registry->Install(kThreadPoolCID.GetID(), new Plugin::tClassInstance<Concurrency::ThreadPool>());
	registry->Install(Concurrency::kLoadBalancerCID.GetID(), new Plugin::tClassInstance<Concurrency::LoadBalancer>());
}

extern "C" void CPF_EXPORT RemoveScheduler(Plugin::iRegistry* registry)
{
	registry->Remove(Concurrency::kLoadBalancerCID.GetID());
	registry->Remove(kThreadPoolCID.GetID());
	registry->Remove(Concurrency::kWorkBufferCID.GetID());
	registry->Remove(Concurrency::kSchedulerCID.GetID());
	registry->Remove(Concurrency::kFenceCID.GetID());
	registry->Remove(Concurrency::kThreadTimeCID.GetID());

	CPF_DROP_LOG(Concurrency);
}

//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		InstallScheduler(registry);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		RemoveScheduler(registry);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
