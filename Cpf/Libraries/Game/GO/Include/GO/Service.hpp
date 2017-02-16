//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Types.hpp"
#include "IntrusivePtr.hpp"
#include "UnorderedMap.hpp"


namespace Cpf
{
	namespace GO
	{
		// TODO: This is a dirty first pass 'get it working' solution.

		// This is the overall GO service which integrates with the concurrency scheduler.
		// The similar "System" is intended for only items owned by this service.  So
		// the AwarenessSystem manages awareness for the GO::Service.
		class Service /* : public Cpf::Service */
		{
		public:
			// Stages within the service are update loops.  They work in a similar fashion to
			// 3D pipeline stages though Stages can be merged and/or executed in parallel
			// when there are no direct conflicts in data descriptions.
			class Stage /* : public Cpf::Stage */
			{
			};

			using ObjectIDMap = UnorderedMap<ObjectID, IntrusivePtr<Object>>;
			using ObjectIDValue = ObjectIDMap::value_type;

			Service();
			~Service();

			// Service interface.
			Object* CreateObject(ObjectID id = kInvalidObjectID);

			void Remove(Object*);

		private:
			static ObjectID mNextID;
			ObjectIDMap mObjectIDMap;
		};
	}
}
