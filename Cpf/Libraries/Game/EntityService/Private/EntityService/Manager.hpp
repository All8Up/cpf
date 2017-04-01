//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "UnorderedMap.hpp"
#include "RefCounted.hpp"
#include "Functional.hpp"
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
			using EntityIDMap = UnorderedMap<EntityID, IntrusivePtr<iEntity>>;
			using EntityIDValue = EntityIDMap::value_type;

			//
			Manager();
			~Manager() override;

			//
			COM::Result QueryInterface(COM::InterfaceID id, void**) override;

			// 
			MultiCore::iPipeline* GetPipeline() const { return mpPipeline; }

			// Service interface.
			iEntity* CreateEntity(EntityID id = kInvalidEntityID);
			void Remove(iEntity*);
			void IterateEntities(Function<void (iEntity*)> cb);

		private:
			//
			static EntityID mNextID;
			EntityIDMap mEntityIDMap;
			MultiCore::iPipeline* mpPipeline;
		};
	}
}
