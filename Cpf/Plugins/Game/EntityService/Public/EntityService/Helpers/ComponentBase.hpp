//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "EntityService/Types.hpp"

namespace CPF
{
	namespace EntityService
	{
		//
		struct iEntity;

		// Helper template.
		template <typename BASE>
		struct ComponentBase : public tRefCounted<BASE>
		{
			//
			ComponentBase() : mpEntity(nullptr) {}
			virtual ~ComponentBase() {}

			// Component interface.
			virtual iEntity* GetEntity() const { return mpEntity; }
			virtual void SetEntity(iEntity* entity) { mpEntity = entity; }

			virtual ComponentID GetID() const = 0;

			virtual void Initialize() {}
			virtual void Shutdown() {}

			virtual void Activate() {}
			virtual void Deactivate() {}


		private:
			iEntity* mpEntity;
		};
	}
}
