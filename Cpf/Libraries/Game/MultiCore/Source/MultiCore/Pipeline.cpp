//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Pipeline.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"
#include "Logging/Logging.hpp"
#include "Hash/Crc.hpp"
#include "MultiCore/DependencySolver.hpp"
#include "MultiCore/QueueBuilder.hpp"

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

bool Pipeline::Configure()
{
	// Iterate the systems and fill in the dependency solver.
	DependencySolver solver;
	for (auto& system : mSystemMap)
	{
		for (auto& stage : system.second->GetStages())
		{
			solver.AddStage(system.first, stage->GetID());
		}
		// Resolve system dependencies into full descriptions.
		DependencyVector dependencies;
		for (auto& dep : system.second->GetSystemDependencies())
			dependencies.push_back({ { system.first, dep.mDependent }, dep.mTarget });
		solver.AddDependencies(dependencies);
	}
	if (!solver.Solve())
	{
		// Do something about the error here.
		CPF_LOG(Experimental, Info) << "Error solving stage dependencies.";
	}

	// Convert the solved stage order into the stage vector.
	mStages.clear();
	for (size_t i=0; i<solver.GetBucketCount(); ++i)
	{
		const auto& bucket = solver.GetBucket(i);
		for (const auto& systemStage : bucket)
		{
			Stage* stage = GetStage(systemStage.mSystem, systemStage.mStage);
			mStages.emplace_back(stage);
		}
		mStages.emplace_back(nullptr);
	}

	// Let the systems configure to the new pipeline.
	_ConfigureSystems();

#ifdef CPF_DEBUG
	CPF_LOG(Experimental, Info) << "---------------- Stage Order ---------------------------";
	for (const auto& stage : mStages)
	{
		if (stage)
			CPF_LOG(Experimental, Info) << "  " << stage->GetSystem()->GetName() << " : " << stage->GetName();
		else
			CPF_LOG(Experimental, Info) << "  <---- barrier ---->";
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

	QueueBuilder builder;
	for (auto stage : mStages)
	{
		if (stage)
		{
			if (stage->IsEnabled())
				stage->Emit(builder, &q);
		}
		else
			q.Barrier();
	}
}
