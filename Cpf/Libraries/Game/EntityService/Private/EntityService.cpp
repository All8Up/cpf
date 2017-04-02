//////////////////////////////////////////////////////////////////////////
#include "EntityService.hpp"
#include "EntityService/Components/TransformComponent.hpp"
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "MultiCore/System/iTimer.hpp"

using namespace Cpf;

namespace
{
	int s_RefCount = 0;
}

CPF_EXPORT_ENTITYSERVICE int EntityServiceInitializer::Install()
{
	if (++s_RefCount == 1)
	{
		EntityService::TransformComponent::Install();
		EntityService::EntityStage::Install();
	}
	return s_RefCount;
}

CPF_EXPORT_ENTITYSERVICE int EntityServiceInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		EntityService::EntityStage::Remove();
		EntityService::TransformComponent::Remove();
	}
	return s_RefCount;
}
