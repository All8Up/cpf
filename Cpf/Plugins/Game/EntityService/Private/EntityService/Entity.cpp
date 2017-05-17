//////////////////////////////////////////////////////////////////////////
#include "Entity.hpp"
#include "EntityService/Interfaces/iComponent.hpp"
#include "EntityService/Interfaces/iManager.hpp"
#include "Move.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
bool Entity::Create(EntityID id, iEntity** outEntity)
{
	CPF_ASSERT(outEntity != nullptr);
	Entity* result = new Entity();
	if (result)
	{
		result->mID = id;
		*outEntity = result;
		return true;
	}
	*outEntity = nullptr;
	return false;
}


//////////////////////////////////////////////////////////////////////////
GOM::Result Entity::QueryInterface(GOM::InterfaceID id, void** outPtr)
{
	switch (id.GetID())
	{
	case iUnknown::kIID.GetID():
		{
			iUnknown* result = static_cast<iUnknown*>(this);
			result->AddRef();
			*outPtr = result;
			return GOM::kOK;
		}

	default:
		{
			iComponent* component = static_cast<iComponent*>(GetComponent(id));
			if (component)
			{
				*outPtr = component;
				component->AddRef();
				return GOM::kOK;
			}
		}
	}

	*outPtr = nullptr;
	return GOM::kUnknownInterface;
}

Entity::Entity()
	: mpManager(nullptr)
	, mID(kInvalidEntityID)
	, mActive(false)
	, mComponentCount(0)
{}

Entity::~Entity()
{}

void Entity::Initialize(iManager* owner)
{
	CPF_ASSERT(mpManager == nullptr);
	mpManager = owner;
}

void Entity::Shutdown()
{
	CPF_ASSERT(mpManager != nullptr);
#ifdef CPF_DEBUG

#endif
	mpManager = nullptr;
}

void Entity::Activate()
{
	mActive = true;
	for (int i = 0; i < mComponentCount; ++i)
		mComponents[i].second->Activate();
}

void Entity::Deactivate()
{
	for (int i = 0; i < mComponentCount; ++i)
		mComponents[i].second->Deactivate();
	mActive = false;
}

const EntityID& Entity::GetID() const
{
	return mID;
}

void Entity::AddComponent(GOM::InterfaceID id, iComponent* component)
{
	component->SetEntity(this);
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
		++i;
	}
	// Insert.
	component->AddRef();
	mComponents[i] = Move(ComponentPair(id, component));
	++mComponentCount;
	if (mActive)
		component->Activate();
}

int Entity::_GetComponentIndex(GOM::InterfaceID id) const
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

iComponent* Entity::GetComponent(GOM::InterfaceID id)
{
	int index = _GetComponentIndex(id);
	return index==-1 ? nullptr : static_cast<iComponent*>(mComponents[index].second);
}

const iComponent* Entity::GetComponent(GOM::InterfaceID id) const
{
	int index = _GetComponentIndex(id);
	return index == -1 ? nullptr : static_cast<const iComponent*>(mComponents[index].second);
}
