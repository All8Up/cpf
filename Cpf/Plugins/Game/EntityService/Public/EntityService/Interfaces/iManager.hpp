//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"

namespace CPF
{
	namespace MultiCore
	{
		struct iExecutionPlan;
	}

	namespace EntityService
	{
		struct iEntity;

		static constexpr GOM::ClassID kManagerCID = GOM::ClassID("EntityService::iManager"_crc64);

		struct iManager : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("EntityService::iManager"_crc64);

			virtual MultiCore::iExecutionPlan* GetPipeline() const = 0;

			virtual iEntity* CreateEntity(uint64_t id = uint64_t(-1)) = 0;
			virtual void Remove(iEntity*) = 0;
			virtual void IterateEntities(Function<void(iEntity*)> cb) = 0;
		};
	}
}
