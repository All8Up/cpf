//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Export.hpp"
#include "EntityService/Types.hpp"
#include "RefCount.hpp"
#include "UnorderedMap.hpp"
#include "Pair.hpp"
#include "String.hpp"
#include "MultiCore/System.hpp"


namespace Cpf
{
	namespace EntityService
	{
		struct iEntity : public iUnknown
		{
			virtual void Initialize(iEntityService* owner) = 0;
			virtual void Shutdown() = 0;

			virtual iEntityService* GetService() = 0;

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

		class Entity : public tRefCounted<iEntity>
		{
		public:
			static constexpr int kMaxComponents = 32;
			using ComponentPair = Pair<InterfaceID, IntrusivePtr<iComponent>>;

			// iUnknown interface.
			bool QueryInterface(InterfaceID id, void**) override;

			// Object interface.
			static bool Create(EntityID id, iEntity**);

			void Initialize(iEntityService* owner) override;
			void Shutdown() override;

			iEntityService* GetService() override { return mpService; }

			void Activate() override;
			void Deactivate() override;

			const EntityID& GetID() const override;

			void AddComponent(InterfaceID id, iComponent* component) override;
			iComponent* GetComponent(InterfaceID id) override;
			const iComponent* GetComponent(InterfaceID id) const override;
		
			using ComponentCreator = iComponent* (*)(MultiCore::System*);
			static bool Install(InterfaceID iid, ComponentCreator creator);
			static bool Remove(InterfaceID iid);
			static iComponent* CreateComponent(InterfaceID iid, MultiCore::System*);

		private:
			// Not intended for direct creation.
			Entity();
			~Entity();

			//
			int _GetComponentIndex(InterfaceID id) const;

			// Implementation data.
			iEntityService* mpService;
			EntityID mID;
			int mComponentCount;
			ComponentPair mComponents[kMaxComponents];
			bool mActive;

			using ComponentMap = UnorderedMap<InterfaceID, ComponentCreator>;
			static ComponentMap mComponentCreators;
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
			iComponent* created = Object::CreateComponent(TYPE::kIID, system);
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
