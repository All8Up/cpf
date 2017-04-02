//////////////////////////////////////////////////////////////////////////
#include "Entity.hpp"
#include "EntityService/Interfaces/iComponent.hpp"
#include "EntityService/Interfaces/iManager.hpp"
#include "Move.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
bool EntityService::ComponentFactoryInstall(COM::InterfaceID iid, ComponentCreator creator)
{
	return Entity::Install(iid, creator);
}

bool EntityService::ComponentFactoryRemove(COM::InterfaceID iid)
{
	return Entity::Remove(iid);
}

iComponent* EntityService::ComponentFactoryCreate(COM::InterfaceID iid, MultiCore::iSystem* system)
{
	return Entity::CreateComponent(iid, system);
}

//////////////////////////////////////////////////////////////////////////
Entity::ComponentMap Entity::mComponentCreators;

//////////////////////////////////////////////////////////////////////////
bool Entity::Install(COM::InterfaceID iid, ComponentCreator creator)
{
	if (mComponentCreators.find(iid)==mComponentCreators.end())
	{
		mComponentCreators[iid] = creator;
		return true;
	}
	return false;
}

bool Entity::Remove(COM::InterfaceID iid)
{
	if (mComponentCreators.find(iid) == mComponentCreators.end())
	{
		mComponentCreators.erase(iid);
		return true;
	}
	return false;
}

iComponent* Entity::CreateComponent(COM::InterfaceID iid, MultiCore::iSystem* system)
{
	iComponent* result = nullptr;
	const auto& creator = mComponentCreators.find(iid);
	if (creator != mComponentCreators.end())
	{
		result = (*creator->second)(system);
	}
	return result;
}

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
COM::Result Entity::QueryInterface(COM::InterfaceID id, void** outPtr)
{
	switch (id.GetID())
	{
	case iUnknown::kIID.GetID():
		{
			iUnknown* result = static_cast<iUnknown*>(this);
			result->AddRef();
			*outPtr = result;
			return COM::kOK;
		}

	default:
		{
			iComponent* component = static_cast<iComponent*>(GetComponent(id));
			if (component)
			{
				*outPtr = component;
				component->AddRef();
				return COM::kOK;
			}
		}
	}

	*outPtr = nullptr;
	return COM::kUnknownInterface;
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

void Entity::AddComponent(COM::InterfaceID id, iComponent* component)
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
	mComponents[i] = Move(ComponentPair(id, component));
	++mComponentCount;
	if (mActive)
		component->Activate();
}

int Entity::_GetComponentIndex(COM::InterfaceID id) const
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

iComponent* Entity::GetComponent(COM::InterfaceID id)
{
	int index = _GetComponentIndex(id);
	return index==-1 ? nullptr : static_cast<iComponent*>(mComponents[index].second);
}

const iComponent* Entity::GetComponent(COM::InterfaceID id) const
{
	int index = _GetComponentIndex(id);
	return index == -1 ? nullptr : static_cast<const iComponent*>(mComponents[index].second);
}
