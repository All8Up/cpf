//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/Container.hpp"
#include "CPF/Plugin/iClassInstance.hpp"

namespace CPF
{
	namespace EntityService
	{
		struct iEntity;

		static constexpr GOM::ClassID kEntityStageCID = GOM::ClassID("EntityService::EntityStageClass"_crc64);

		struct iEntityStage : MultiCore::iStage
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("EntityService::iEntityStage"_crc64);

			using UpdateFunc = void(*)(MultiCore::iSystem*, iEntity*);

			// Interface.
			virtual void AddUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f) = 0;
			virtual void RemoveUpdate(MultiCore::iSystem* s, iEntity* o, UpdateFunc f) = 0;
		};
	}
}
