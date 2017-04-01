//////////////////////////////////////////////////////////////////////////
#include "TransformComponent.hpp"
#include "../Entity.hpp"

using namespace Cpf;
using namespace EntityService;

bool TransformComponent::Install()
{
	return Entity::Install(iTransformComponent::kIID, &TransformComponent::Creator);
}

bool TransformComponent::Remove()
{
	return Entity::Remove(iTransformComponent::kIID);
}

iComponent* TransformComponent::Creator(MultiCore::System* system)
{
	return static_cast<iComponent*>(new TransformComponent(system));
}

COM::Result TransformComponent::QueryInterface(COM::InterfaceID id, void** outPtr)
{
	switch(id.GetID())
	{
	case iUnknown::kIID.GetID():
		{
			iUnknown* result = static_cast<iUnknown*>(this);
			result->AddRef();
			*outPtr = result;
			return COM::kOK;
		}

	case iTransformComponent::kIID.GetID():
		{
			iTransformComponent* result = static_cast<iTransformComponent*>(this);
			result->AddRef();
			*outPtr = result;
			return COM::kOK;
		}
	}
	*outPtr = nullptr;
	return COM::kUnknownInterface;
}

/** @brief Default constructor. */
TransformComponent::TransformComponent(MultiCore::System*)
	: mpParent(nullptr)
{}

/** @brief Destructor. */
TransformComponent::~TransformComponent()
{}

/**
 @brief Gets the ID of the component type.
 @return The ComponentID.
 */
ComponentID TransformComponent::GetID() const
{
	return kID;
}

/** @brief Call shutdown on children.  TODO: May do something real in the future. */
void TransformComponent::Shutdown()
{
	for (auto child : mChildren)
		child->Shutdown();
}

/**
 @brief Gets the parent of transform.
 @return null if this is in world space, else the parent.
 */
iTransformComponent* TransformComponent::GetParent() const
{
	return mpParent;
}

/**
 @brief Sets the parent.
 @param [in,out] transform The parent to set.
 @param maintainRelative true to maintain relative transform information.
 */
void TransformComponent::SetParent(iTransformComponent* transform, bool maintainRelative)
{
	CPF_ASSERT(mpParent != transform);
	if (mpParent)
		mpParent->RemoveChild(this);

	if (maintainRelative)
	{
		CPF_ASSERT_ALWAYS; // TODO
		// 1. Get a transform from our current parent into the new parent.
		// 2. Modify this transform by the mapping.
	}
	mpParent = static_cast<TransformComponent*>(transform);
	if (transform)
		transform->AddChild(this);
}

/**
 @brief Adds a child.
 @param [in,out] transform If non-null, the transform.
 */
void TransformComponent::AddChild(iTransformComponent* transform)
{
#ifdef CPF_DEBUG
	// Can't be owned already.
	for (auto& it : mChildren)
		CPF_ASSERT(it != transform);
#endif
	mChildren.emplace_back(static_cast<TransformComponent*>(transform));
}

/**
 @brief Removes the child described by transform.
 @param [in,out] transform If non-null, the transform.
 */
void TransformComponent::RemoveChild(iTransformComponent* transform)
{
	for (auto ibegin = mChildren.begin(), iend=mChildren.end(); ibegin!=iend; ++ibegin)
	{
		if (*ibegin == transform)
		{
			mChildren.erase(ibegin);
			return;
		}
	}
	// Should have been in the list.
	CPF_ASSERT_ALWAYS;
}

/**
 @brief Gets the transform in local space.
 @return The local matrix.
 */
Math::Matrix44fv TransformComponent::GetMatrix() const
{
	return mTransform.GetMatrix();
}

/**
 @brief Gets the transform to world space.
 @return The world matrix.
 */
Math::Matrix44fv TransformComponent::GetWorldMatrix() const
{
	return GetWorldTransform().GetMatrix();
}

/**
 @brief Gets local transform.
 @return The local transform.
 */
Math::Transform& TransformComponent::GetTransform()
{
	return mTransform;
}

/**
 @brief Gets local transform.
 @return The local transform.
 */
const Math::Transform& TransformComponent::GetTransform() const
{
	return mTransform;
}

/**
 @brief Gets world transform.
 @return The world transform.
 */
Math::Transform TransformComponent::GetWorldTransform()
{
	Math::Transform result = mTransform;
	TransformComponent* parent = mpParent;
	while (parent)
		result = result * mpParent->mTransform;
	return result;
}

/**
 @brief Gets world transform.
 @return The world transform.
 */
const Math::Transform TransformComponent::GetWorldTransform() const
{
	Math::Transform result = mTransform;
	TransformComponent* parent = mpParent;
	while (parent)
		result = result * mpParent->mTransform;
	return result;
}
