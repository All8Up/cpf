//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Pipeline;
	}

	namespace EntityService
	{
		struct iEntity;

		struct iManager : COM::iUnknown
		{
			virtual MultiCore::Pipeline* GetPipeline() const = 0;

			virtual iEntity* CreateEntity(EntityID id = kInvalidEntityID) = 0;
			virtual void Remove(iEntity*) = 0;
			virtual void IterateEntities(Function<void(iEntity*)> cb) = 0;
		};

		iManager* CreateManager();
	}
}
