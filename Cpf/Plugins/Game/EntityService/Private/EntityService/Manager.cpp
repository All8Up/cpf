//////////////////////////////////////////////////////////////////////////
#include "Manager.hpp"
#include "Entity.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
uint64_t Manager::mNextID = uint64_t(0);

//////////////////////////////////////////////////////////////////////////
Manager::Manager(iBase*)
	: mpPipeline(nullptr)
{}

Manager::~Manager()
{}

GOM::Result Manager::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
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

iEntity* Manager::CreateEntity(uint64_t id)
{
	uint64_t realID = id;
	if (id == uint64_t(-1))
		realID = mNextID;

	iEntity* result;
	if (Entity::Create(realID, &result))
	{
		mNextID = mNextID+1;
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
