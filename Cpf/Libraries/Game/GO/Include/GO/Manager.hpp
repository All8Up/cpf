//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/Types.hpp"
#include "UnorderedMap.hpp"
#include "RefCounted.hpp"
#include "Functional.hpp"


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
			using ObjectIDMap = UnorderedMap<ObjectID, IntrusivePtr<Object>>;
			using ObjectIDValue = ObjectIDMap::value_type;

			//
			Manager();
			~Manager() override;

			// Service interface.
			Object* CreateObject(ObjectID id = kInvalidObjectID);
			void Remove(Object*);
			void IterateObjects(Function<void (Object*)> cb);

		private:
			//
			static ObjectID mNextID;
			ObjectIDMap mObjectIDMap;
		};
	}
}
