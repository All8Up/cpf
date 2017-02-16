//////////////////////////////////////////////////////////////////////////
#include "GO/Object.hpp"
#include "GO/Component.hpp"
#include "GO/Service.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
int32_t Object::AddRef()
{
	return ++mRefCount;
}

int32_t Object::Release()
{
	CPF_ASSERT(mRefCount > -1);
	if (--mRefCount == 1)
	{
		mpOwner->Remove(this);
		CPF_ASSERT(mRefCount == 0);
		delete this;
		return 0;
	}
	return mRefCount;
}

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
	: mRefCount(1)
	, mpOwner(nullptr)
	, mID(kInvalidObjectID)
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
}

void Object::Deactivate()
{
}

ObjectID Object::GetID() const
{
	return mID;
}

void Object::AddComponent(ComponentID id, Component* component)
{
	mComponents.insert(ComponentEntry(id, component));
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
