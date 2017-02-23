//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "EntityService/Interfaces/iEntityService.hpp"

namespace Cpf
{
	namespace EntityService
	{
		class iEntity : public iUnknown
		{
		public:
			virtual void Initialize(iEntityService* owner) = 0;
			virtual void Shutdown() = 0;

			virtual iEntityService* GetService() = 0;

			virtual void Activate() = 0;
			virtual void Deactivate() = 0;

			virtual const ObjectID& GetID() const = 0;

			virtual void AddComponent(InterfaceID id, iComponent* component) = 0;
			virtual iComponent* GetComponent(InterfaceID id) = 0;
			virtual const iComponent* GetComponent(InterfaceID id) const = 0;

			// Utilities.
			template <typename TYPE>
			TYPE* CreateComponent(MultiCore::System*);

			template <typename TYPE>
			TYPE* GetComponent();

			template <typename TYPE>
			const TYPE* GetComponent() const;

			template <typename TYPE>
			TYPE* GetSystem(MultiCore::SystemID id) const
			{
				return static_cast<TYPE*>(GetSystem(id));
			}

			template <typename TYPE>
			TYPE* AddComponent(TYPE* component);
		};
	}
}
