//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "EntityService/Types.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iEntity;

		struct iComponent : COM::iUnknown
		{
			static constexpr auto kIID = COM::InterfaceID("EntityService::iComponent"_crc64);

			virtual void SetSystem(MultiCore::iSystem*) = 0;
			virtual MultiCore::iSystem* GetSystem() = 0;

			virtual iEntity* GetEntity() const = 0;
			virtual void SetEntity(iEntity* entity) = 0;

			virtual void Initialize() = 0;
			virtual void Shutdown() = 0;

			virtual void Activate() = 0;
			virtual void Deactivate() = 0;
		};
	}
}
