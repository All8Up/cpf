//////////////////////////////////////////////////////////////////////////
#include "EntityService.hpp"
#include "EntityService/Components/TransformComponent.hpp"
#include "EntityService/Manager.hpp"
#include "EntityService/Stages/EntityStage.hpp"
#include "MultiCore/System/iTimer.hpp"

using namespace Cpf;

namespace
{
	int s_RefCount = 0;
	Plugin::iRegistry* spRegistry = nullptr;
}

CPF_EXPORT_ENTITYSERVICE int EntityServiceInitializer::Install(Plugin::iRegistry* registry)
{
	if (++s_RefCount == 1)
	{
		CPF_ASSERT(spRegistry == nullptr);
		EntityService::TransformComponent::Install(registry);
		registry->Install(EntityService::kManagerCID, new EntityService::ManagerClass());
		registry->Install(EntityService::kEntityStageCID, new EntityService::EntityStageClass());
		spRegistry = registry;
	}
	return s_RefCount;
}

CPF_EXPORT_ENTITYSERVICE int EntityServiceInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		spRegistry->Remove(EntityService::kEntityStageCID);
		spRegistry->Remove(EntityService::kManagerCID);
		EntityService::TransformComponent::Remove(spRegistry);

		spRegistry = nullptr;
	}
	return s_RefCount;
}
