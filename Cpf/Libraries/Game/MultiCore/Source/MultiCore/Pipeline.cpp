//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Pipeline.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"
#include "Logging/Logging.hpp"
#include "Hash/Crc.hpp"
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
	return true;
}

bool Pipeline::Configure()
{
	// Iterate the systems and setup the queue builder.
	QueueBuilder builder(this);
	for (auto& system : mSystemMap)
	{
		// Iterate and add all blocks.
		for (auto& instruction : GetSystem(system.first)->GetInstructions())
		{
			builder.Add(instruction);
		}

		// Add dependencies between blocks.
		BlockDependencies dependencies = system.second->GetDependencies();
		if (!dependencies.empty())
			builder.Add(dependencies);
	}
	if (!builder.Solve())
	{
		CPF_LOG(Experimental, Error) << "Error resolving block dependencies.";
	}
	else
		mQueue = Move(builder.GetQueue());

	// Let the systems configure to the new pipeline.
	// This allows systems to get pointers to other configured systems.
	bool result = _ConfigureSystems();

#ifdef CPF_DEBUG
	mChanged = false;
#endif

	mQueueInfo = builder.GetQueueInfo();
	return result;
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
	return GetSystem(SystemID(name.c_str(), name.size()));
}

Stage* Pipeline::GetStage(SystemID systemID, StageID stageID)
{
	System* system = GetSystem(systemID);
	if (system)
		return system->GetStage(stageID);
	return nullptr;
}

void Pipeline::operator ()(Concurrency::Scheduler& scheduler)
{
#ifdef CPF_DEBUG
	// Asserts can be enabled in release mode.
	CPF_ASSERT(mChanged == false);
#endif
	scheduler.Execute(mQueue, false);
}
