//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "RefCount.hpp"
#include "UnorderedMap.hpp"
#include "Pair.hpp"
#include "MultiCore/iSystem.hpp"
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
			using ComponentPair = Pair<GOM::InterfaceID, IntrusivePtr<iComponent>>;

			// iBase interface.
			GOM::Result Cast(GOM::InterfaceID id, void**) override;

			// Object interface.
			static bool Create(EntityID id, iEntity**);

			void Initialize(iManager* owner) override;
			void Shutdown() override;

			iManager* GetManager() override { return mpManager; }

			void Activate() override;
			void Deactivate() override;

			const EntityID& GetID() const override;

			void AddComponent(GOM::InterfaceID id, iComponent* component) override;
			iComponent* GetComponent(GOM::InterfaceID id) override;
			const iComponent* GetComponent(GOM::InterfaceID id) const override;
		
		private:
			// Not intended for direct creation.
			Entity();
			~Entity();

			//
			int _GetComponentIndex(GOM::InterfaceID id) const;

			// Implementation data.
			iManager* mpManager;
			EntityID mID;
			int mComponentCount;
			ComponentPair mComponents[kMaxComponents];
			bool mActive;
		};
	}
}
