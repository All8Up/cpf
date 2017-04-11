//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/Container.hpp"
#include "Plugin/iClassInstance.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iEntity;

		static constexpr COM::ClassID kEntityStageCID = COM::ClassID("EntityService::EntityStageClass"_crc64);

		struct iEntityStage : MultiCore::iStage
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("EntityService::iEntityStage"_crc64);

			using UpdateFunc = void(*)(MultiCore::iSystem*, iEntity*);

			// Interface.
			virtual void AddUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f) = 0;
			virtual void RemoveUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f) = 0;
		};
	}
}