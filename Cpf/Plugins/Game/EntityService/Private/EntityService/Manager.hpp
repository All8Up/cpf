//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "UnorderedMap.hpp"
#include "RefCounted.hpp"
#include "Functional.hpp"
#include "Plugin/iClassInstance.hpp"
#include "MultiCore/iPipeline.hpp"
#include "EntityService/Interfaces/iManager.hpp"

namespace Cpf
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
			Manager(iBase*);
			virtual ~Manager();

			//
			GOM::Result Cast(uint64_t id, void**) override;

			// 
			MultiCore::iPipeline* GetPipeline() const { return mpPipeline; }

			// Service interface.
			iEntity* CreateEntity(uint64_t id = uint64_t(-1));
			void Remove(iEntity*);
			void IterateEntities(Function<void (iEntity*)> cb);

		private:
			//
			static uint64_t mNextID;
			EntityIDMap mEntityIDMap;
			MultiCore::iPipeline* mpPipeline;
		};
	}
}
