//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "RefCount.hpp"
#include "UnorderedMap.hpp"
#include "Pair.hpp"
#include "MultiCore/System.hpp"
#include "Manager.hpp"
#include "EntityService/Interfaces/iEntity.hpp"


namespace Cpf
{
	namespace EntityService
	{
		class Entity : public tRefCounted<iEntity>
		{
		public:
			static constexpr int kMaxComponents = 32;
			using ComponentPair = Pair<InterfaceID, IntrusivePtr<iComponent>>;

			// iUnknown interface.
			bool QueryInterface(InterfaceID id, void**) override;

			// Object interface.
			static bool Create(EntityID id, iEntity**);

			void Initialize(iManager* owner) override;
			void Shutdown() override;

			iManager* GetManager() override { return mpManager; }

			void Activate() override;
			void Deactivate() override;

			const EntityID& GetID() const override;

			void AddComponent(InterfaceID id, iComponent* component) override;
			iComponent* GetComponent(InterfaceID id) override;
			const iComponent* GetComponent(InterfaceID id) const override;
		
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
			iManager* mpManager;
			EntityID mID;
			int mComponentCount;
			ComponentPair mComponents[kMaxComponents];
			bool mActive;

			using ComponentMap = UnorderedMap<InterfaceID, ComponentCreator>;
			static ComponentMap mComponentCreators;
		};
	}
}
