//////////////////////////////////////////////////////////////////////////
#include "GO/Service.hpp"
#include "GO/Object.hpp"
#include "GO/System.hpp"
#include "GO/Stage.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
int64_t Service::mNextID = 0;

//////////////////////////////////////////////////////////////////////////
Service::Service()
	: MultiCore::Service(0)
	, mStagesChanged(false)
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
	_ResolveOutstanding();
}

void Service::Deactivate()
{
	for (auto it : mSystemMap)
		it.second->Deactivate();
}

bool Service::GetStagesChanged() const
{
	return mStagesChanged;
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
	{
		mOutstanding.emplace_back(it);
	}

	mStagesChanged = true;
	return true;
}

Stage::Dependencies::const_iterator FindDependency(const Stage& stage, const Stage::Dependencies& deps)
{
	for (int i=0; i<deps.size(); ++i)
	{
		if (stage.GetID() == deps[i].second)
			return deps.begin() + i;
	}
	return deps.end();
}

bool Service::_ResolveOutstanding()
{
	// Run through and insert all non-dependency stages.
	for (int i=0; i<mOutstanding.size();)
	{
		if (mOutstanding[i]->GetDependencies().empty())
		{
			mStageArray.emplace_back(mOutstanding[i]);
			mOutstanding.erase(mOutstanding.begin() + i);
			continue;
		}
		++i;
	}

	// Now insert sort the dependency based stages.
	while (!mOutstanding.empty())
	{
		bool resolved = false;
		StageVector remaining = mOutstanding;

		for (int i=0; i<remaining.size(); ++i)
		{
			Stage::Dependencies deps = remaining[i]->GetDependencies();

			for (int j=0; j<mStageArray.size(); ++j)
			{
				const Stage& comp = *mStageArray[j];
				auto it = FindDependency(comp, deps);
				if (it != deps.end())
				{
					deps.erase(it);
					if (deps.empty())
					{
						mStageArray.emplace(mStageArray.begin() + j + 1, remaining[i]);
						remaining.erase(remaining.begin() + i);
						resolved = true;
						goto goagain;
					}
				}
			}
		}

	goagain:
		if (!resolved)
			break;	// Failed to resolve all dependencies.
		mOutstanding = remaining;
	}

	CPF_LOG(Experimental, Info) << "---------------";
	for (auto& i : mStageArray)
	{
		CPF_LOG(Experimental, Info) << "Stage: " << i->GetName();
	}

	// Resolve inter system dependencies.
	for (auto it : mStageArray)
	{
		if (!it->ResolveDependencies(this, it->GetSystem()))
			return false;
	}

	return mOutstanding.empty();
}

void Service::Submit(Concurrency::Scheduler::Queue& q)
{
	// TODO: This is currently inserting a barrier which should not be done here.
	for (auto& it : mStageArray)
	{
		it->Submit(q);
		q.Barrier();
	}
	mStagesChanged = false;
}
