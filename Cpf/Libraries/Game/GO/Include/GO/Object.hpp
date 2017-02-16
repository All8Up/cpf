//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/Export.hpp"
#include "RefCount.hpp"
#include "GO/Types.hpp"
#include "UnorderedMap.hpp"
#include "Pair.hpp"


namespace Cpf
{
	namespace GO
	{
		class Object : public iRefCounted
		{
		public:
			using ComponentMap = UnorderedMultiMap<ComponentID, IntrusivePtr<Component>>;
			using ComponentEntry = ComponentMap::value_type;
			using ComponentRange = Pair<ComponentMap::const_iterator, ComponentMap::const_iterator>;

			// iRefCounted.
			int32_t AddRef() override;
			int32_t Release() override;

			// Object interface.
			static bool Create(int64_t id, Object**);

			void Initialize(Service* owner);
			void Shutdown();

			void Activate();
			void Deactivate();

			ObjectID GetID() const;

			void AddComponent(ComponentID id, Component* component);
			Component* GetComponent(ComponentID id);
			const Component* GetComponent(ComponentID id) const;
			ComponentRange GetComponents(ComponentID id);
		
			// Utilities.
			template <typename TYPE>
			TYPE* AddComponent(TYPE* component);
			template <typename TYPE>
			TYPE* GetComponent();
			template <typename TYPE>
			const TYPE* GetComponent() const;

		private:
			// Not intended for direct creation.
			Object();
			~Object();

			// Implementation data.
			int32_t mRefCount;
			Service* mpOwner;
			ObjectID mID;
			ComponentMap mComponents;
		};


		template <typename TYPE>
		TYPE* Object::AddComponent(TYPE* component)
		{
			AddComponent(TYPE::kID, component);
			return component;
		}

		template <typename TYPE>
		TYPE* Object::GetComponent()
		{
			return static_cast<TYPE*>(GetComponent(TYPE::kID));
		}

		template <typename TYPE>
		const TYPE* Object::GetComponent() const
		{
			return static_cast<const TYPE*>(GetComponent(TYPE::kID));
		}
	}
}
