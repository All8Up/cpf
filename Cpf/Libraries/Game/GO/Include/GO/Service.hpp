//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Types.hpp"
#include "IntrusivePtr.hpp"
#include "UnorderedMap.hpp"
#include "String.hpp"
#include "Vector.hpp"


namespace Cpf
{
	namespace GO
	{
		// TODO: This is a dirty first pass 'get it working' solution.

		// This is the overall GO service which integrates with the concurrency scheduler.
		// The similar "System" is intended only for items owned by this service.  So
		// the AwarenessSystem manages awareness for the GO::Service and objects can use it.
		class Service /* : public Cpf::Service */
		{
		public:
			using ObjectIDMap = UnorderedMap<ObjectID, IntrusivePtr<Object>>;
			using ObjectIDValue = ObjectIDMap::value_type;

			Service();
			~Service();

			// Service interface.
			Object* CreateObject(ObjectID id = kInvalidObjectID);
			void Remove(Object*);
			void IterateObjects(Function<void (Object*)> cb);

			// System management.
			bool Install(const String& name, System* system);
			bool Remove(const String& name);
			System* GetSystem(const String& name) const;
			template <typename TYPE>
			TYPE* GetSystem(const String& name) const { return static_cast<TYPE*>(GetSystem(name)); }

			// Integrate into scheduler.
			void Submit(Concurrency::Scheduler::Queue& q);

		private:
			//
			bool _InstallStages(System* system);

			//
			static ObjectID mNextID;
			ObjectIDMap mObjectIDMap;

			using SystemMap = UnorderedMap<String, IntrusivePtr<System>>;
			SystemMap mSystemMap;

			//
			using StageArray = Vector<IntrusivePtr<Stage>>;
			StageArray mStageArray;
		};
	}
}
