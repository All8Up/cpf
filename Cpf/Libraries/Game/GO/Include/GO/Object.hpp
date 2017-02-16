//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/Export.hpp"
#include "RefCount.hpp"
#include "GO/Types.hpp"
#include "UnorderedMap.hpp"
#include "Pair.hpp"
#include "String.hpp"


namespace Cpf
{
	namespace GO
	{
		class Object : public tRefCounted<iRefCounted>
		{
		public:
			using ComponentMap = UnorderedMultiMap<ComponentID, IntrusivePtr<Component>>;
			using ComponentEntry = ComponentMap::value_type;
			using ComponentRange = Pair<ComponentMap::const_iterator, ComponentMap::const_iterator>;

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
		
			System* GetSystem(const String& name) const;

			// Utilities.
			template <typename TYPE>
			TYPE* AddComponent(TYPE* component);
			template <typename TYPE>
			TYPE* GetComponent();
			template <typename TYPE>
			const TYPE* GetComponent() const;
			template <typename TYPE>
			TYPE* GetSystem(const String& name) const
			{
				return static_cast<TYPE*>(GetSystem(name));
			}

		private:
			// Not intended for direct creation.
			Object();
			~Object();

			// Implementation data.
			Service* mpOwner;
			ObjectID mID;
			ComponentMap mComponents;
			bool mActive;
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
