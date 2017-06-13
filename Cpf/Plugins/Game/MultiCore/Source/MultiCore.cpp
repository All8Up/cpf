//////////////////////////////////////////////////////////////////////////
#include "MultiCore.hpp"
#include "Logging/Logging.hpp"
#include "MultiCore/ExecutionPlan.hpp"
#include "MultiCore/System/Timer.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/System.hpp"

using namespace Cpf;

namespace
{
	int s_RefCount = 0;
	Plugin::iRegistry* spRegistry = nullptr;
}

int MultiCoreInitializer::Install(Plugin::iRegistry* registry)
{
	// TODO: Currently only exists in a single registry.
	// Will be fixed when this is a real plugin.
	CPF_ASSERT(spRegistry == nullptr);
	if (++s_RefCount == 1)
	{
		spRegistry = registry;
		CPF_INIT_LOG(MultiCore);
		CPF_LOG(MultiCore, Trace) << "Initialized multicore library.";
		spRegistry->Install(MultiCore::kExecutionPlanCID.GetID(), new Plugin::tClassInstance<MultiCore::ExecutionPlan>());
		spRegistry->Install(MultiCore::kTimerCID.GetID(), new Plugin::tClassInstance<MultiCore::Timer>());
		spRegistry->Install(MultiCore::kSingleUpdateStageCID.GetID(), new Plugin::tClassInstance<MultiCore::SingleUpdateStage>());
		spRegistry->Install(MultiCore::kStageListCID.GetID(), new Plugin::tClassInstance<MultiCore::StageList>());
	}
	return s_RefCount;
}

int MultiCoreInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		CPF_ASSERT(spRegistry != nullptr);
		spRegistry->Remove(MultiCore::kStageListCID.GetID());
		spRegistry->Remove(MultiCore::kSingleUpdateStageCID.GetID());
		spRegistry->Remove(MultiCore::kTimerCID.GetID());
		spRegistry->Remove(MultiCore::kExecutionPlanCID.GetID());
		CPF_LOG(MultiCore, Trace) << "Shutdown multicore library.";
		CPF_DROP_LOG(MultiCore);
		spRegistry = nullptr;
	}
	return s_RefCount;
}

#ifndef CPF_STATIC_MULTICORE
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (MultiCoreInitializer::Install(registry) > 0)
			return GOM::kOK;
		return GOM::kError;
	}
	return GOM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return s_RefCount == 0;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (MultiCoreInitializer::Remove() == 0)
			return GOM::kOK;
		return GOM::kInUse;
	}
	return GOM::kInvalidParameter;
}
#endif
