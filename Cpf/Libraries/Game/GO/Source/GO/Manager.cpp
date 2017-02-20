//////////////////////////////////////////////////////////////////////////
#include "GO/Manager.hpp"
#include "GO/Object.hpp"
#include "GO/System.hpp"
#include "GO/Stage.hpp"
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

#if 0
void Manager::Activate()
{
	for (auto it : mSystemMap)
	{
		it.second->Activate();
		_InstallStages(it.second);
	}
	_ResolveOutstanding();
}

void Manager::Deactivate()
{
	for (auto it : mSystemMap)
		it.second->Deactivate();
	mStageArray.clear();
}

bool Manager::GetStagesChanged() const
{
	return mStagesChanged;
}
#endif

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

//////////////////////////////////////////////////////////////////////////
#if 0
bool Manager::Install(System* system)
{
	if (mSystemMap.find(system->GetID())==mSystemMap.end())
	{
		mSystemMap[system->GetID()].Adopt(system);
		system->AddRef();
		return true;
	}
	return false;
}

bool Manager::Remove(SystemID id)
{
	auto it = mSystemMap.find(id);
	if (it != mSystemMap.end())
	{
		mSystemMap.erase(it);
		return true;
	}
	return false;
}

System* Manager::GetSystem(SystemID id) const
{
	auto it = mSystemMap.find(id);
	if (it == mSystemMap.end())
		return nullptr;
	return it->second;
}

//////////////////////////////////////////////////////////////////////////
bool Manager::_InstallStages(System* system)
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
		if (stage.GetSystem()->GetID() != CPF_STL_NAMESPACE::get<1>(deps[i]))
			continue;
		if (stage.GetID() == CPF_STL_NAMESPACE::get<2>(deps[i]))
			return deps.begin() + i;
	}
	return deps.end();
}

bool Manager::_ResolveOutstanding()
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
	IntrusivePtr<Stage> barrier;
	while (!mOutstanding.empty())
	{
		bool resolved = false;
		StageVector remaining = mOutstanding;

		for (int i=0; i<remaining.size(); ++i)
		{
			Stage::Dependencies deps = remaining[i]->GetDependencies();

			for (int j=0; j<mStageArray.size(); ++j)
			{
				if (mStageArray[j])
				{
					const Stage& comp = *mStageArray[j];
					auto it = FindDependency(comp, deps);
					if (it != deps.end())
					{
						deps.erase(it);
						if (deps.empty())
						{
							// Check for an existing barrier.
							auto target = mStageArray.begin() + j + 1;
							if (target == mStageArray.end())
							{
								// At the end, just insert both.
								mStageArray.emplace_back(barrier);
								mStageArray.emplace_back(remaining[i]);
							}
							else
							{
								if (*target)
								{
									// Have a live stage, need to insert a barrier.
									mStageArray.emplace(mStageArray.begin() + j + 1, barrier);
									mStageArray.emplace(mStageArray.begin() + j + 2, remaining[i]);
								}
								else
								{
									// Have a barrier, insert after it.
									mStageArray.emplace(mStageArray.begin() + j + 2, remaining[i]);
								}
							}

							remaining.erase(remaining.begin() + i);
							resolved = true;
							goto goagain;
						}
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
		if (i)
		{
			CPF_LOG(Experimental, Info) << "Stage: " << i->GetName();
		}
		else
		{
			CPF_LOG(Experimental, Info) << "-- Barrier --";
		}
	}

	// Resolve inter system dependencies.
	for (auto it : mStageArray)
	{
		if (it)
			if (!it->ResolveDependencies(this, it->GetSystem()))
				return false;
	}

	return mOutstanding.empty();
}

void Manager::Submit(Concurrency::Scheduler::Queue& q)
{
	// TODO: This is currently inserting a barrier which should not be done here.
	for (auto& it : mStageArray)
	{
		if (it)
			it->Submit(q);
		else
			q.Barrier();
	}
	mStagesChanged = false;
}
#endif
