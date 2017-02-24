//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "EntityService/Interfaces/iManager.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iComponent;

		using ComponentCreator = iComponent* (*)(MultiCore::System*);
		bool ComponentFactoryInstall(InterfaceID iid, ComponentCreator creator);
		bool ComponentFactoryRemove(InterfaceID iid);
		iComponent* ComponentFactoryCreate(InterfaceID iid, MultiCore::System*);

		struct iEntity : public iUnknown
		{
			virtual void Initialize(iManager*) = 0;
			virtual void Shutdown() = 0;

			virtual iManager* GetManager() = 0;

			virtual void Activate() = 0;
			virtual void Deactivate() = 0;

			virtual const EntityID& GetID() const = 0;

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


		template <typename TYPE>
		TYPE* iEntity::AddComponent(TYPE* component)
		{
			AddComponent(TYPE::kIID, reinterpret_cast<iComponent*>(component));
			return component;
		}

		template <typename TYPE>
		TYPE* iEntity::CreateComponent(MultiCore::System* system)
		{
			iComponent* created = ComponentFactoryCreate(TYPE::kIID, system);
			TYPE* result = nullptr;
			if (created)
			{
				if (created->QueryInterface(TYPE::kIID, reinterpret_cast<void**>(&result)))
					AddComponent<TYPE>(result);
				created->Release();
			}
			return result;
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
