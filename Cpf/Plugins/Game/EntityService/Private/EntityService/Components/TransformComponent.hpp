//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/iComponent.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "EntityService/Helpers/ComponentBase.hpp"
#include "MultiCore/iSystem.hpp"

namespace CPF
{
	namespace EntityService
	{
		class TransformComponent : public ComponentBase<iTransformComponent>
		{
		public:
			static constexpr auto kID = ComponentID("iTransformComponent"_crc64);

			static GOM::Result Install(Plugin::iRegistry*);
			static GOM::Result Remove(Plugin::iRegistry*);

			TransformComponent(GOM::iUnknown*);
			~TransformComponent() override;

			//
			GOM::Result QueryInterface(uint64_t id, void**) override;

			// Component overrides.
			ComponentID GetID() const override;

			void Shutdown() override;

			void SetSystem(MultiCore::iSystem*) override {}
			MultiCore::iSystem* GetSystem() override { return nullptr; }

			// Local transform interface.
			iTransformComponent* GetParent() const;
			void SetParent(iTransformComponent* transform, bool maintainRelative = false);

			void AddChild(iTransformComponent*);
			void RemoveChild(iTransformComponent*);

			Math::Matrix44fv GetMatrix() const;
			Math::Matrix44fv GetWorldMatrix() const;

			Math::Transform& GetTransform();
			const Math::Transform& GetTransform() const;
			Math::Transform GetWorldTransform();
			const Math::Transform GetWorldTransform() const;

		private:
			// Implementation data.
			Math::Transform mTransform;
			TransformComponent* mpParent;
			Vector<TransformComponent*> mChildren;
		};
	}
}
