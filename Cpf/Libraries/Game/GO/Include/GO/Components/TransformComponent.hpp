//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GO/Component.hpp"
#include "Math/Transform.hpp"
#include "Vector.hpp"
#include "Math/Matrix44v.hpp"

namespace Cpf
{
	namespace GO
	{
		class TransformComponent : public Component
		{
		public:
			static constexpr ComponentID kID = "Transform Component"_crc64;

			TransformComponent();
			~TransformComponent() override;

			// Component overrides.
			ComponentID GetID() const override;

			void Shutdown() override;

			// Local transform interface.
			TransformComponent* GetParent() const;
			void SetParent(TransformComponent* transform, bool maintainRelative = false);

			void AddChild(TransformComponent*);
			void RemoveChild(TransformComponent*);

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
