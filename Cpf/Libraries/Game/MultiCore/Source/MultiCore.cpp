//////////////////////////////////////////////////////////////////////////
#include "MultiCore.hpp"
#include "Logging/Logging.hpp"
#include "MultiCore/Pipeline.hpp"

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
		spRegistry->Install(MultiCore::kPipelineCID, new MultiCore::PipelineClass());
	}
	return s_RefCount;
}

CPF_EXPORT_MULTICORE int MultiCoreInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		CPF_ASSERT(spRegistry != nullptr);
		spRegistry->Remove(MultiCore::kPipelineCID);
		CPF_LOG(MultiCore, Trace) << "Shutdown multicore library.";
		CPF_DROP_LOG(MultiCore);
	}
	return s_RefCount;
}
