//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Pipeline.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"
#include "Logging/Logging.hpp"
#include "Hash/Crc.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
Pipeline::Pipeline()
#ifdef CPF_DEBUG
	: mChanged(false)
#endif
{
}

Pipeline::~Pipeline()
{}

bool Pipeline::Create(Pipeline** pipeline)
{
	if (pipeline)
	{
		*pipeline = new Pipeline();
		if (*pipeline)
			return true;
	}
	return false;
}

System* Pipeline::Install(System* system)
{
	SystemID id = system->GetID();
	if (mSystemMap.find(id) == mSystemMap.end())
	{
#ifdef CPF_DEBUG
		mChanged = true;
#endif
		system->AddRef();
		mSystemMap.emplace(id, system);
		system->SetOwner(this);
		return system;
	}
	return nullptr;
}

bool Pipeline::Remove(System* system)
{
	SystemID id = system->GetID();
	if (mSystemMap.find(id) == mSystemMap.end())
		return false;
#ifdef CPF_DEBUG
	mChanged = true;
#endif
	mSystemMap.erase(id);
	system->SetOwner(nullptr);
	return true;
}

Stage::Dependencies::const_iterator FindDependency(const Stage& stage, const Stage::Dependencies& deps)
{
	for (int i = 0; i < deps.size(); ++i)
	{
		if (stage.GetSystem()->GetID() != deps[i].first)
			continue;
		if (stage.GetID() == deps[i].second)
			return deps.begin() + i;
	}
	return deps.end();
}

bool Pipeline::Configure()
{
	mStages.clear();
	StageVector stages;

	// First get a flat list of the stages,
	// stages without dependencies go to the final list.
	for (const auto& system : mSystemMap)
	{
		for (auto stage : system.second->GetStages())
		{
			if (stage->GetDependencies().empty())
				mStages.emplace_back(stage);
			else
				stages.emplace_back(stage);
		}
	}

	// Now insert sort the dependency based stages.
	IntrusivePtr<Stage> barrier;
	while (!stages.empty())
	{
		bool resolved = false;
		StageVector remaining = stages;

		for (int i = 0; i < remaining.size(); ++i)
		{
			Stage::Dependencies deps = remaining[i]->GetDependencies();

			for (int j = 0; j < mStages.size(); ++j)
			{
				if (mStages[j])
				{
					const Stage& comp = *mStages[j];
					auto it = FindDependency(comp, deps);
					if (it != deps.end())
					{
						deps.erase(it);
						if (deps.empty())
						{
							// Check for an existing barrier.
							auto target = mStages.begin() + j + 1;
							if (target == mStages.end())
							{
								// At the end, just insert both.
								mStages.emplace_back(barrier);
								mStages.emplace_back(remaining[i]);
							}
							else
							{
								if (*target)
								{
									// Have a live stage, need to insert a barrier.
									mStages.emplace(mStages.begin() + j + 1, barrier);
									mStages.emplace(mStages.begin() + j + 2, remaining[i]);
								}
								else
								{
									// Have a barrier, insert after it.
									mStages.emplace(mStages.begin() + j + 2, remaining[i]);
								}
							}

							remaining.erase(remaining.begin() + i);
							resolved = true;
							goto goagain;
						}
					}
#ifdef CPF_DEBUG
					if (deps.size()>0)
					{
						CPF_LOG(Experimental, Info) << "---- Dependencies failed:";
						for (auto& dep : deps)
						{
							System* system = GetSystem(dep.first);
							Stage* stage = GetStage(dep.first, dep.second);
							CPF_LOG(Experimental, Info) << (system ? system->GetName() : "<missing>") << " - "
								<< (stage ? stage->GetName() : "<missing>");
						}
					}
#endif
				}
			}
		}

	goagain:
		if (!resolved)
		{
			CPF_LOG(Experimental, Info) << "!!!!! Dependencies failed !!!!!";
			break;	// Failed to resolve all dependencies.
		}
		stages = remaining;
	}

	// Let the systems configure to the new pipeline.
	_ConfigureSystems();

#ifdef CPF_DEBUG
	CPF_LOG(Experimental, Info) << "---------------- Stage Order ---------------------------";
	for (const auto& stage : mStages)
	{
		if (stage)
			CPF_LOG(Experimental, Info) << " " << stage->GetName();
		else
			CPF_LOG(Experimental, Info) << " <barrier>";
	}
	CPF_LOG(Experimental, Info) << "---------------- Stage Order ---------------------------";
#endif

#ifdef CPF_DEBUG
	mChanged = false;
#endif

	return false;
}

bool Pipeline::_ConfigureSystems() const
{
	bool result = true;

	// Let the systems configure to the new pipeline.
	for (const auto& system : mSystemMap)
	{
		if (!system.second->Configure())
			result = false;
	}

	return result;
}


System* Pipeline::GetSystem(SystemID id) const
{
	auto result = mSystemMap.find(id);
	if (result != mSystemMap.end())
	{
		result->second->AddRef();
		return result->second;
	}
	return nullptr;
}

System* Pipeline::GetSystem(const String& name) const
{
	return GetSystem(SystemID(Hash::Crc64(name.c_str(), name.size())));
}

Stage* Pipeline::GetStage(SystemID systemID, StageID stageID)
{
	System* system = GetSystem(systemID);
	if (system)
		return system->GetStage(stageID);
	return nullptr;
}

const StageVector& Pipeline::GetStages() const
{
	return mStages;
}

void Pipeline::operator ()(Concurrency::Scheduler::Queue& q)
{
#ifdef CPF_DEBUG
	// Asserts can be enabled in release mode.
	CPF_ASSERT(mChanged == false);
#endif

	for (auto stage : mStages)
	{
		if (stage)
		{
			if (stage->IsEnabled())
				stage->Emit(&q);
		}
		else
			q.Barrier();
	}
}
