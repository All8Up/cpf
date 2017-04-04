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

int EntityServiceInitializer::Install(Plugin::iRegistry* registry)
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

int EntityServiceInitializer::Remove()
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



#ifndef CPF_STATIC_ENTITYSERVICE
#include "Plugin/iRegistry.hpp"
extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		TimeInitializer::Install();
		if (EntityServiceInitializer::Install(registry) > 0)
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
		if (EntityServiceInitializer::Remove() == 0)
		{
			TimeInitializer::Remove();
			return COM::kOK;
		}
		return COM::kInUse;
	}
	return COM::kInvalidParameter;
}
#endif
