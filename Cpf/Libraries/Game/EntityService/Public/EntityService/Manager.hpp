//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/Types.hpp"
#include "UnorderedMap.hpp"
#include "RefCounted.hpp"
#include "Functional.hpp"
#include "MultiCore/Pipeline.hpp"


namespace Cpf
{
	namespace GO
	{
		/*
		The GO::Manager handles all the game objects within the environment.
		*/
		class Manager : public tRefCounted<iRefCounted>
		{
		public:
			using ObjectIDMap = UnorderedMap<ObjectID, IntrusivePtr<iEntity>>;
			using ObjectIDValue = ObjectIDMap::value_type;

			//
			Manager();
			~Manager() override;

			// 
			MultiCore::Pipeline* GetPipeline() const { return mpPipeline; }

			// Service interface.
			iEntity* CreateObject(ObjectID id = kInvalidObjectID);
			void Remove(iEntity*);
			void IterateObjects(Function<void (iEntity*)> cb);

		private:
			//
			static ObjectID mNextID;
			ObjectIDMap mObjectIDMap;
			MultiCore::Pipeline* mpPipeline;
		};
	}
}
