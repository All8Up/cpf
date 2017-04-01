//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		struct iPipeline;
	}

	namespace EntityService
	{
		struct iEntity;

		struct iManager : COM::iUnknown
		{
			virtual MultiCore::iPipeline* GetPipeline() const = 0;

			virtual iEntity* CreateEntity(EntityID id = kInvalidEntityID) = 0;
			virtual void Remove(iEntity*) = 0;
			virtual void IterateEntities(Function<void(iEntity*)> cb) = 0;
		};

		iManager* CreateManager();
	}
}
