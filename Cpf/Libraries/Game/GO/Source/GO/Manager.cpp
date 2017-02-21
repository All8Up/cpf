//////////////////////////////////////////////////////////////////////////
#include "GO/Manager.hpp"
#include "GO/Object.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
int64_t Manager::mNextID = 0;

//////////////////////////////////////////////////////////////////////////
Manager::Manager()
{}

Manager::~Manager()
{}

Object* Manager::CreateObject(ObjectID id)
{
	ObjectID realID = id;
	if (id == kInvalidObjectID)
		realID = mNextID;

	Object* result;
	if (Object::Create(realID, &result))
	{
		++mNextID;
		result->Initialize(this);
		result->AddRef();
		mObjectIDMap.emplace(realID, IntrusivePtr<Object>(result));
		result->Activate();
		return result;
	}
	return nullptr;
}

void Manager::Remove(Object* object)
{
	auto it = mObjectIDMap.find(object->GetID());
	CPF_ASSERT(it != mObjectIDMap.end());
	object->Deactivate();
	mObjectIDMap.erase(it);
}

void Manager::IterateObjects(Function<void(Object*)> cb)
{
	for (auto& it : mObjectIDMap)
	{
		cb(it.second);
	}
}
