//////////////////////////////////////////////////////////////////////////
#include "GO/Service.hpp"
#include "GO/Object.hpp"
#include "GO/System.hpp"

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
bool Service::Install(const String& name, System* system)
{
	if (mSystemMap.find(name)==mSystemMap.end())
	{
		mSystemMap[name].Adopt(system);
		system->AddRef();
		_InstallStages(system);
		return true;
	}
	return false;
}

bool Service::Remove(const String& name)
{
	auto it = mSystemMap.find(name);
	if (it != mSystemMap.end())
	{
		mSystemMap.erase(it);
		return true;
	}
	return false;
}

System* Service::GetSystem(const String& name) const
{
	auto it = mSystemMap.find(name);
	if (it == mSystemMap.end())
		return nullptr;
	return it->second;
}

//////////////////////////////////////////////////////////////////////////
bool Service::_InstallStages(System* system)
{
	// TODO: This will need to perform the insertion sort eventually based on system dependencies.
	for (auto it : system->GetStages())
		mStageArray.emplace_back(it.second);
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
	// TODO: This is wrong but functional for the moment.
	for (auto& it : mStageArray)
	{
		q.AllBarrier(&Stage::Update, (Stage*)it);
	}
}
