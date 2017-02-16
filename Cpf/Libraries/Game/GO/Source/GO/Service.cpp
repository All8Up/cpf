//////////////////////////////////////////////////////////////////////////
#include "GO/Service.hpp"
#include "GO/Object.hpp"

using namespace Cpf;
using namespace GO;

int64_t Service::mNextID = 0;

Service::Service()
{}

Service::~Service()
{}

Object* Service::CreateObject(ObjectID id)
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
		return result;
	}
	return nullptr;
}

void Service::Remove(Object* object)
{
	auto it = mObjectIDMap.find(object->GetID());
	CPF_ASSERT(it != mObjectIDMap.end());
	mObjectIDMap.erase(it);
}
