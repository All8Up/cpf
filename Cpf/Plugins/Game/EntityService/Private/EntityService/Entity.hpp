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
			using ComponentPair = Pair<uint64_t, IntrusivePtr<iComponent>>;

			// iBase interface.
			GOM::Result QueryInterface(uint64_t id, void**) override;

			// Object interface.
			static bool Create(uint64_t id, iEntity**);

			void Initialize(iManager* owner) override;
			void Shutdown() override;

			iManager* GetManager() override { return mpManager; }

			void Activate() override;
			void Deactivate() override;

			const uint64_t GetID() const override;

			void AddComponent(uint64_t id, iComponent* component) override;
			iComponent* GetComponent(uint64_t id) override;
			const iComponent* GetComponent(uint64_t id) const override;
		
		private:
			// Not intended for direct creation.
			Entity();
			~Entity();

			//
			int _GetComponentIndex(uint64_t id) const;

			// Implementation data.
			iManager* mpManager;
			uint64_t mID;
			int mComponentCount;
			ComponentPair mComponents[kMaxComponents];
			bool mActive;
		};
	}
}
