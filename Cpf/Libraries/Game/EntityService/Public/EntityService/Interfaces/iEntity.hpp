//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/iManager.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iComponent;

		static constexpr COM::ClassID kEntityCID = COM::ClassID("EntityService::EntityClass"_crc64);

		struct iEntity : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("EntityService::iEntity"_crc64);

			virtual void Initialize(iManager*) = 0;
			virtual void Shutdown() = 0;

			virtual iManager* GetManager() = 0;

			virtual void Activate() = 0;
			virtual void Deactivate() = 0;

			virtual const EntityID& GetID() const = 0;

			virtual void AddComponent(COM::InterfaceID id, iComponent* component) = 0;
			virtual iComponent* GetComponent(COM::InterfaceID id) = 0;
			virtual const iComponent* GetComponent(COM::InterfaceID id) const = 0;

			// Utilities.
			template <typename TYPE>
			TYPE* CreateComponent(Plugin::iRegistry*, const COM::ClassID id, MultiCore::iSystem* system);

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


		template <typename TYPE>
		TYPE* iEntity::AddComponent(TYPE* component)
		{
			AddComponent(TYPE::kIID, reinterpret_cast<iComponent*>(component));
			return component;
		}

		template <typename TYPE>
		TYPE* iEntity::CreateComponent(Plugin::iRegistry* regy, const COM::ClassID id, MultiCore::iSystem* system)
		{
			IntrusivePtr<TYPE> created;
			regy->Create(nullptr, id, TYPE::kIID, created.AsVoidPP());
			if (created)
			{
				created->SetOwner(system);
				AddComponent<TYPE>(created);
			}
			return created;
		}


		template <typename TYPE>
		TYPE* iEntity::GetComponent()
		{
			return static_cast<TYPE*>(GetComponent(TYPE::kIID));
		}

		template <typename TYPE>
		const TYPE* iEntity::GetComponent() const
		{
			return static_cast<const TYPE*>(GetComponent(TYPE::kIID));
		}
	}
}
