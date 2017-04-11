//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/iComponent.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "EntityService/Helpers/ComponentBase.hpp"
#include "MultiCore/iSystem.hpp"

namespace Cpf
{
	namespace EntityService
	{
		class TransformComponent : public ComponentBase<iTransformComponent>
		{
		public:
			static constexpr auto kID = ComponentID("iTransformComponent"_crc64);

			static COM::Result Install(Plugin::iRegistry*);
			static COM::Result Remove(Plugin::iRegistry*);

			TransformComponent();
			~TransformComponent() override;

			//
			COM::Result QueryInterface(COM::InterfaceID id, void**) override;

			// Component overrides.
			ComponentID GetID() const override;

			void Shutdown() override;

			void SetOwner(MultiCore::iSystem*) override {}
			MultiCore::iSystem* GetOwner() override { return nullptr; }

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
