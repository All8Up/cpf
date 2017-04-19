//////////////////////////////////////////////////////////////////////////
#include "MultiCore.hpp"
#include "Logging/Logging.hpp"
#include "MultiCore/Pipeline.hpp"
#include "MultiCore/System/Timer.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/System.hpp"

using namespace Cpf;

namespace
{
	int s_RefCount = 0;
	Plugin::iRegistry* spRegistry = nullptr;
}

CPF_EXPORT_MULTICORE int MultiCoreInitializer::Install(Plugin::iRegistry* registry)
{
	// TODO: Currently only exists in a single registry.
	// Will be fixed when this is a real plugin.
	CPF_ASSERT(spRegistry == nullptr);
	if (++s_RefCount == 1)
	{
		spRegistry = registry;
		CPF_INIT_LOG(MultiCore);
		CPF_LOG(MultiCore, Trace) << "Initialized multicore library.";
		spRegistry->Install(MultiCore::kPipelineCID, new Plugin::tClassInstance<MultiCore::Pipeline>());
		spRegistry->Install(MultiCore::kTimerCID, new Plugin::tClassInstance<MultiCore::Timer>());
		spRegistry->Install(MultiCore::kSingleUpdateStageCID, new Plugin::tClassInstance<MultiCore::SingleUpdateStage>());
		spRegistry->Install(MultiCore::kStageListCID, new Plugin::tClassInstance<MultiCore::StageList>());
	}
	return s_RefCount;
}

CPF_EXPORT_MULTICORE int MultiCoreInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		CPF_ASSERT(spRegistry != nullptr);
		spRegistry->Remove(MultiCore::kStageListCID);
		spRegistry->Remove(MultiCore::kSingleUpdateStageCID);
		spRegistry->Remove(MultiCore::kTimerCID);
		spRegistry->Remove(MultiCore::kPipelineCID);
		CPF_LOG(MultiCore, Trace) << "Shutdown multicore library.";
		CPF_DROP_LOG(MultiCore);
		spRegistry = nullptr;
	}
	return s_RefCount;
}

#ifndef CPF_STATIC_MULTICORE
extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (MultiCoreInitializer::Install(registry) > 0)
			return COM::kOK;
		return COM::kError;
	}
	return COM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return s_RefCount == 0;
}

extern "C"
COM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (MultiCoreInitializer::Remove() == 0)
			return COM::kOK;
		return COM::kInUse;
	}
	return COM::kInvalidParameter;
}
#endif
