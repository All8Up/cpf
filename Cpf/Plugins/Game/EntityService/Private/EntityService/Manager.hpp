//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "UnorderedMap.hpp"
#include "RefCounted.hpp"
#include "Functional.hpp"
#include "Plugin/iClassInstance.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "EntityService/Interfaces/iManager.hpp"

namespace CPF
{
	namespace EntityService
	{
		/*
		The Manager::Manager handles all the game objects within the environment.
		*/
		class Manager : public tRefCounted<iManager>
		{
		public:
			using EntityIDMap = UnorderedMap<uint64_t, IntrusivePtr<iEntity>>;
			using EntityIDValue = EntityIDMap::value_type;

			//
			Manager(iUnknown*);
			virtual ~Manager();

			//
			GOM::Result QueryInterface(uint64_t id, void**) override;

			// 
			MultiCore::iExecutionPlan* GetPipeline() const { return mpPipeline; }

			// Service interface.
			iEntity* CreateEntity(uint64_t id = uint64_t(-1));
			void Remove(iEntity*);
			void IterateEntities(Function<void (iEntity*)> cb);

		private:
			//
			static uint64_t mNextID;
			EntityIDMap mEntityIDMap;
			MultiCore::iExecutionPlan* mpPipeline;
		};
	}
}
