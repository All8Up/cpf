//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/iComponent.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "EntityService/Helpers/ComponentBase.hpp"
#include "MultiCore/System.hpp"

namespace Cpf
{
	namespace EntityService
	{
		class TransformComponent
			: private ComponentBase<iTransformComponent>
		{
		public:
			static constexpr auto kID = ComponentID("Component Implementation"_crc64);

			static bool Install();
			static bool Remove();

			static iComponent* Creator(MultiCore::System*);

			TransformComponent(MultiCore::System*);
			~TransformComponent() override;

			//
			COM::Result QueryInterface(COM::InterfaceID id, void**) override;

			// Component overrides.
			ComponentID GetID() const override;

			void Shutdown() override;

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
