//////////////////////////////////////////////////////////////////////////
#include "Manager.hpp"
#include "Entity.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
iManager* EntityService::CreateManager()
{
	return new Manager();
}


//////////////////////////////////////////////////////////////////////////
EntityID Manager::mNextID = EntityID(0);

//////////////////////////////////////////////////////////////////////////
Manager::Manager()
{}

Manager::~Manager()
{}

COM::Result Manager::QueryInterface(COM::InterfaceID id, void**)
{
	return COM::kNotImplemented;
}

iEntity* Manager::CreateEntity(EntityID id)
{
	EntityID realID = id;
	if (id == kInvalidEntityID)
		realID = mNextID;

	iEntity* result;
	if (Entity::Create(realID, &result))
	{
		mNextID = EntityID(mNextID.GetID()+1);
		result->Initialize(this);
		result->AddRef();
		mEntityIDMap.emplace(realID, IntrusivePtr<iEntity>(result));
		result->Activate();
		return result;
	}
	return nullptr;
}

void Manager::Remove(iEntity* object)
{
	auto it = mEntityIDMap.find(object->GetID());
	CPF_ASSERT(it != mEntityIDMap.end());
	object->Deactivate();
	mEntityIDMap.erase(it);
}

void Manager::IterateEntities(Function<void(iEntity*)> cb)
{
	for (auto& it : mEntityIDMap)
	{
		cb(it.second);
	}
}
