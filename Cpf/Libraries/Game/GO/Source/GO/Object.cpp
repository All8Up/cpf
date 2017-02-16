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
	, mComponentCount(0)
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
	for (int i = 0; i < mComponentCount; ++i)
		mComponents[i].second->Activate();
}

void Object::Deactivate()
{
	for (int i = 0; i < mComponentCount; ++i)
		mComponents[i].second->Deactivate();
	mActive = false;
}

ObjectID Object::GetID() const
{
	return mID;
}

void Object::AddComponent(ComponentID id, Component* component)
{
	component->SetObject(this);
	CPF_ASSERT(mComponentCount < kMaxComponents);
	int i = 0;
	while (i < mComponentCount)
	{
		if (id < mComponents[i].first)
		{
			// First move everything up by one slot.
			for (int j = mComponentCount; j > i; --j)
				mComponents[j] = Move(mComponents[j - 1]);
			break;
		}
	}
	// Insert.
	mComponents[i] = Move(ComponentPair(id, component));
	++mComponentCount;
	if (mActive)
		component->Activate();
}

int Object::_GetComponentIndex(ComponentID id) const
{
	int low = 0;
	int high = mComponentCount;

	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (mComponents[mid].first < id)
		{
			low = mid + 1;
			continue;
		}
		if (id < mComponents[mid].first)
		{
			high = mid;
			continue;
		}
		if (id == mComponents[mid].first)
			return mid;
		return -1;
	}
	return -1;
}

Component* Object::GetComponent(ComponentID id)
{
	int index = _GetComponentIndex(id);
	return index==-1 ? nullptr : static_cast<Component*>(mComponents[index].second);
}

const Component* Object::GetComponent(ComponentID id) const
{
	int index = _GetComponentIndex(id);
	return index == -1 ? nullptr : static_cast<const Component*>(mComponents[index].second);
}

System* Object::GetSystem(const String& name) const
{
	return mpOwner->GetSystem(name);
}
