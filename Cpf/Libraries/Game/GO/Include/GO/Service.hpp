//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"
#include "GO/Types.hpp"
#include "MultiCore/Service.hpp"
#include "UnorderedMap.hpp"
#include "Hash/Crc.hpp"


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
			bool Install(System* system);
			bool Remove(SystemID);
			System* GetSystem(SystemID) const;
			System* GetSystem(const String& name) const { return GetSystem(Platform::Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1))); }
			template <typename TYPE>
			TYPE* GetSystem(SystemID id) const { return static_cast<TYPE*>(GetSystem(id)); }

			// Integrate into scheduler.
			void Submit(Concurrency::Scheduler::Queue& q);

		private:
			//
			bool _InstallStages(System* system);
			bool _ResolveOutstanding();

			//
			static ObjectID mNextID;
			ObjectIDMap mObjectIDMap;

			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<System>>;
			SystemMap mSystemMap;

			//
			StageVector mStageArray;
			bool mStagesChanged;

			//
			StageVector mOutstanding;
		};
	}
}
