//////////////////////////////////////////////////////////////////////////
#include "Manager.hpp"
#include "Entity.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
EntityID Manager::mNextID = EntityID(0);

//////////////////////////////////////////////////////////////////////////
Manager::Manager(iUnknown*)
	: mpPipeline(nullptr)
{}

Manager::~Manager()
{}

GOM::Result Manager::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;

		case iManager::kIID.GetID():
			*outIface = static_cast<iManager*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
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
