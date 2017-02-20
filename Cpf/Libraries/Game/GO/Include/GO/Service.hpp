//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"
#include "GO/Types.hpp"
#include "MultiCore/Service.hpp"
#include "UnorderedMap.hpp"


namespace Cpf
{
	namespace GO
	{
		// TODO: This is a dirty first pass 'get it working' solution.

		// This is the overall GO service which integrates with the concurrency scheduler.
		// The similar "System" is intended only for items owned by this service.  So
		// the AwarenessSystem manages awareness for the GO::Service and objects can use it.
		class Service : public MultiCore::Service
		{
		public:
			using ObjectIDMap = UnorderedMap<ObjectID, IntrusivePtr<Object>>;
			using ObjectIDValue = ObjectIDMap::value_type;

			//
			Service();
			~Service() override;

			//
			void Activate();
			void Deactivate();

			//
			bool GetStagesChanged() const;
			const StageVector& GetStages() const { return mStageArray; }

			// Service interface.
			Object* CreateObject(ObjectID id = kInvalidObjectID);
			void Remove(Object*);
			void IterateObjects(Function<void (Object*)> cb);

			// System management.
			bool Install(SystemID, System* system);
			bool Remove(SystemID);
			System* GetSystem(SystemID) const;
			template <typename TYPE>
			TYPE* GetSystem(SystemID id) const { return static_cast<TYPE*>(GetSystem(id)); }

			// Integrate into scheduler.
			void Submit(Concurrency::Scheduler::Queue& q);

		private:
			//
			bool _InstallStages(System* system);

			//
			static ObjectID mNextID;
			ObjectIDMap mObjectIDMap;

			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<System>>;
			SystemMap mSystemMap;

			//
			StageVector mStageArray;
			bool mStagesChanged;
		};
	}
}
