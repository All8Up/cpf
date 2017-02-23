//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "MultiCore/Pipeline.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iEntityService : iUnknown
		{
			virtual MultiCore::Pipeline* GetPipeline() const = 0;

			virtual iEntity* CreateObject(EntityID id = kInvalidEntityID) = 0;
			virtual void Remove(iEntity*) = 0;
			virtual void IterateObjects(Function<void(iEntity*)> cb) = 0;
		};
	}
}
