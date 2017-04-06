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

		static constexpr COM::ClassID kManagerCID = COM::ClassID("EntityService::iManager"_crc64);

		struct iManager : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("EntityService::iManager"_crc64);

			virtual MultiCore::iPipeline* GetPipeline() const = 0;

			virtual iEntity* CreateEntity(EntityID id = kInvalidEntityID) = 0;
			virtual void Remove(iEntity*) = 0;
			virtual void IterateEntities(Function<void(iEntity*)> cb) = 0;
		};
	}
}
