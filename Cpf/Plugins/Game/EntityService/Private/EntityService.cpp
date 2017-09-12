//////////////////////////////////////////////////////////////////////////
#include "EntityService.hpp"
#include "EntityService/Components/TransformComponent.hpp"
#include "EntityService/Manager.hpp"
#include "EntityService/Stages/EntityStage.hpp"
#include "MultiCore/System/iTimer.hpp"

using namespace CPF;

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
		registry->Install(EntityService::kManagerCID.GetID(), new Plugin::tClassInstance<EntityService::Manager>());
		registry->Install(EntityService::kEntityStageCID.GetID(), new Plugin::tClassInstance<EntityService::EntityStage>());
		spRegistry = registry;
	}
	return s_RefCount;
}

int EntityServiceInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		spRegistry->Remove(EntityService::kEntityStageCID.GetID());
		spRegistry->Remove(EntityService::kManagerCID.GetID());
		EntityService::TransformComponent::Remove(spRegistry);

		spRegistry = nullptr;
	}
	return s_RefCount;
}



#ifndef CPF_STATIC_ENTITYSERVICE
#include "Plugin/iRegistry.hpp"
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (EntityServiceInitializer::Install(registry) > 0)
			return GOM::kOK;
		return GOM::kError;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (EntityServiceInitializer::Remove() == 0)
		{
			return GOM::kOK;
		}
		return GOM::kInUse;
	}
	return GOM::kInvalidParameter;
}
#endif
