//////////////////////////////////////////////////////////////////////////
#include "GO/Object.hpp"
#include "GO/Component.hpp"
#include "GO/Service.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
bool Object::Create(int64_t id, Object** outObject)
{
	CPF_ASSERT(outObject != nullptr);
	Object* result = new Object();
	if (result)
	{
		result->mID = id;
		*outObject = result;
		return true;
	}
	*outObject = nullptr;
	return false;
}


//////////////////////////////////////////////////////////////////////////
Object::Object()
	: mpOwner(nullptr)
	, mID(kInvalidObjectID)
	, mActive(false)
{}

Object::~Object()
{}

void Object::Initialize(Service* owner)
{
	CPF_ASSERT(mpOwner == nullptr);
	mpOwner = owner;
}

void Object::Shutdown()
{
	CPF_ASSERT(mpOwner != nullptr);
#ifdef CPF_DEBUG

#endif
	mpOwner = nullptr;
}

void Object::Activate()
{
	mActive = true;
	for (auto it : mComponents)
		it.second->Activate();
}

void Object::Deactivate()
{
	for (auto it : mComponents)
		it.second->Deactivate();
	mActive = false;
}

ObjectID Object::GetID() const
{
	return mID;
}

void Object::AddComponent(ComponentID id, Component* component)
{
	component->SetObject(this);
	mComponents.insert(ComponentEntry(id, component));
	if (mActive)
		component->Activate();
}

Component* Object::GetComponent(ComponentID id)
{
	ComponentMap::const_iterator it = mComponents.find(id);
	if (it != mComponents.end())
		return it->second;
	return nullptr;
}

const Component* Object::GetComponent(ComponentID id) const
{
	ComponentMap::const_iterator it = mComponents.find(id);
	if (it != mComponents.end())
		return it->second;
	return nullptr;
}

Object::ComponentRange Object::GetComponents(ComponentID id)
{
	return mComponents.equal_range(id);
}

System* Object::GetSystem(const String& name) const
{
	return mpOwner->GetSystem(name);
}
