//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/iComponent.hpp"
#include "Math/Transform.hpp"
#include "Math/Matrix44v.hpp"

namespace CPF
{
	namespace EntityService
	{
		static constexpr GOM::ClassID kTransformComponentCID = GOM::ClassID("EntityService::iTransformComponentCID"_crc64);
		struct iTransformComponent : iComponent
		{
			static constexpr auto kIID = GOM::InterfaceID("EntityService::iTransformComponent"_crc64);

			// Local transform interface.
			virtual iTransformComponent* GetParent() const = 0;
			virtual void SetParent(iTransformComponent* transform, bool maintainRelative = false) = 0;

			virtual void AddChild(iTransformComponent*) = 0;
			virtual void RemoveChild(iTransformComponent*) = 0;

			virtual Math::Matrix44fv GetMatrix() const = 0;
			virtual Math::Matrix44fv GetWorldMatrix() const = 0;

			virtual Math::Transform& GetTransform() = 0;
			virtual const Math::Transform& GetTransform() const = 0;
			virtual Math::Transform GetWorldTransform() = 0;
			virtual const Math::Transform GetWorldTransform() const = 0;
		};
	}
}
