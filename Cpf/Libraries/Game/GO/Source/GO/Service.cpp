//////////////////////////////////////////////////////////////////////////
#include "GO/Service.hpp"
#include "GO/Object.hpp"
#include "GO/System.hpp"
#include "GO/Stage.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
int64_t Service::mNextID = 0;

//////////////////////////////////////////////////////////////////////////
Service::Service()
	: MultiCore::Service(0)
{}

Service::~Service()
{}

void Service::Activate()
{
	for (auto it : mSystemMap)
	{
		it.second->Activate();
		_InstallStages(it.second);
	}
}

void Service::Deactivate()
{
	for (auto it : mSystemMap)
		it.second->Deactivate();
}

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
		result->Activate();
		return result;
	}
	return nullptr;
}

void Service::Remove(Object* object)
{
	auto it = mObjectIDMap.find(object->GetID());
	CPF_ASSERT(it != mObjectIDMap.end());
	object->Deactivate();
	mObjectIDMap.erase(it);
}

void Service::IterateObjects(Function<void(Object*)> cb)
{
	for (auto& it : mObjectIDMap)
	{
		cb(it.second);
	}
}

//////////////////////////////////////////////////////////////////////////
bool Service::Install(SystemID id, System* system)
{
	if (mSystemMap.find(id)==mSystemMap.end())
	{
		mSystemMap[id].Adopt(system);
		system->AddRef();
		return true;
	}
	return false;
}

bool Service::Remove(SystemID id)
{
	auto it = mSystemMap.find(id);
	if (it != mSystemMap.end())
	{
		mSystemMap.erase(it);
		return true;
	}
	return false;
}

System* Service::GetSystem(SystemID id) const
{
	auto it = mSystemMap.find(id);
	if (it == mSystemMap.end())
		return nullptr;
	return it->second;
}

//////////////////////////////////////////////////////////////////////////
bool Service::_InstallStages(System* system)
{
	// TODO: This will need to perform the insertion sort eventually based on system dependencies.
	for (auto it : system->GetStages())
		mStageArray.emplace_back(it);
	// Resolve inter system dependencies.
	for (auto it : mStageArray)
	{
		if (!it->ResolveDependencies(this, it->GetSystem()))
			return false;
	}
	return true;
}

void Service::Submit(Concurrency::Scheduler::Queue& q)
{
	// TODO: This is currently inserting a barrier which should not be done here.
	for (auto& it : mStageArray)
	{
		it->Submit(q);
		q.Barrier();
	}
}
