//////////////////////////////////////////////////////////////////////////
#include "GO/Manager.hpp"
#include "GO/Object.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
ObjectID Manager::mNextID = ObjectID(0);

//////////////////////////////////////////////////////////////////////////
Manager::Manager()
{}

Manager::~Manager()
{}

iEntity* Manager::CreateObject(ObjectID id)
{
	ObjectID realID = id;
	if (id == kInvalidObjectID)
		realID = mNextID;

	iEntity* result;
	if (Object::Create(realID, &result))
	{
		mNextID = ObjectID(mNextID.GetID()+1);
		result->Initialize(this);
		result->AddRef();
		mObjectIDMap.emplace(realID, IntrusivePtr<iEntity>(result));
		result->Activate();
		return result;
	}
	return nullptr;
}

void Manager::Remove(iEntity* object)
{
	auto it = mObjectIDMap.find(object->GetID());
	CPF_ASSERT(it != mObjectIDMap.end());
	object->Deactivate();
	mObjectIDMap.erase(it);
}

void Manager::IterateObjects(Function<void(iEntity*)> cb)
{
	for (auto& it : mObjectIDMap)
	{
		cb(it.second);
	}
}
