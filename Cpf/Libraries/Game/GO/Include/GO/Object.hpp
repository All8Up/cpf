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
			static constexpr int kMaxComponents = 32;
			using ComponentPair = Pair<ComponentID, IntrusivePtr<Component>>;

			// Object interface.
			static bool Create(int64_t id, Object**);

			void Initialize(Service* owner);
			void Shutdown();

			void Activate();
			void Deactivate();

			ObjectID GetID() const;

			Component* GetComponent(ComponentID id);
			const Component* GetComponent(ComponentID id) const;
		
			System* GetSystem(SystemID id) const;

			// Utilities.
			template <typename TYPE, typename... ARGS>
			TYPE* CreateComponent(ARGS...);
			template <typename TYPE>
			TYPE* GetComponent();
			template <typename TYPE>
			const TYPE* GetComponent() const;
			template <typename TYPE>
			TYPE* GetSystem(SystemID id) const
			{
				return static_cast<TYPE*>(GetSystem(id));
			}

		private:
			// Not intended for direct creation.
			Object();
			~Object();

			//
			void AddComponent(ComponentID id, Component* component);
			template <typename TYPE>
			TYPE* AddComponent(TYPE* component);
			int _GetComponentIndex(ComponentID id) const;

			// Implementation data.
			Service* mpOwner;
			ObjectID mID;
			int mComponentCount;
			ComponentPair mComponents[kMaxComponents];
			bool mActive;
		};


		template <typename TYPE>
		TYPE* Object::AddComponent(TYPE* component)
		{
			AddComponent(TYPE::kID, component);
			return component;
		}

		template <typename TYPE, typename... ARGS>
		TYPE* Object::CreateComponent(ARGS... args)
		{
			// TODO: This is for future factory based components.
			TYPE* result = new TYPE(args...);
			AddComponent<TYPE>(result);
			return result;
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
