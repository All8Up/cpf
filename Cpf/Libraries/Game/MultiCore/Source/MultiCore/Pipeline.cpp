//////////////////////////////////////////////////////////////////////////
#include "Pipeline.hpp"
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

COM::Result CPF_STDCALL Pipeline::QueryInterface(COM::InterfaceID id, void** iface)
{
	if (iface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*iface = static_cast<COM::iUnknown*>(this);
			AddRef();
			return COM::kOK;
		case iPipeline::kID.GetID():
			*iface = static_cast<iPipeline*>(this);
			AddRef();
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

System* CPF_STDCALL Pipeline::Install(System* system)
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

COM::Result CPF_STDCALL Pipeline::Remove(System* system)
{
	SystemID id = system->GetID();
	if (mSystemMap.find(id) == mSystemMap.end())
		return COM::kInvalidParameter;
#ifdef CPF_DEBUG
	mChanged = true;
#endif
	mSystemMap.erase(id);
	return COM::kOK;
}

COM::Result CPF_STDCALL Pipeline::Configure()
{
	// Iterate the systems and setup the queue builder.
	QueueBuilder builder(this);
	for (auto& system : mSystemMap)
	{
		// Iterate and add all blocks.
		System* systemPtr = nullptr;
		if (COM::Succeeded(GetSystem(system.first, &systemPtr)))
		{
			int32_t instructionCount = 0;
			systemPtr->GetInstructions(&instructionCount, nullptr);
			Vector<Instruction> instructions(instructionCount);
			systemPtr->GetInstructions(&instructionCount, instructions.data());
			for (auto& instruction : instructions)
			{
				builder.Add(instruction);
			}
		}

		// Add dependencies between blocks.
		int32_t depCount = 0;
		system.second->GetDependencies(&depCount, nullptr);
		BlockDependencies dependencies(depCount);
		system.second->GetDependencies(&depCount, dependencies.data());
		if (!dependencies.empty())
			builder.Add(dependencies);
	}
	if (!builder.Solve())
	{
		CPF_LOG(MultiCore, Error) << "Error resolving block dependencies.";
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
	return result ? COM::kOK : kConfigurationError;
}

bool Pipeline::_ConfigureSystems() const
{
	bool result = true;

	// Let the systems configure to the new pipeline.
	for (const auto& system : mSystemMap)
	{
		if (COM::Succeeded(system.second->Configure()))
			result = false;
	}

	return result;
}

COM::Result CPF_STDCALL Pipeline::GetSystem(SystemID id, System** system) const
{
	if (system)
	{
		auto result = mSystemMap.find(id);
		if (result != mSystemMap.end())
		{
			result->second->AddRef();
			*system = result->second;
			return COM::kOK;
		}
		return COM::kInvalid;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Pipeline::GetSystem(const char* const name, System** outSystem) const
{
	if (outSystem)
	{
		return GetSystem(SystemID(name, strlen(name)), outSystem);
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Pipeline::GetStage(SystemID systemID, StageID stageID, Stage** outStage)
{
	if (outStage)
	{
		System* system = nullptr;
		if (COM::Succeeded(GetSystem(systemID, &system)))
		{
			if (system)
			{
				Stage* result = nullptr;
				if (COM::Succeeded(system->GetStage(stageID, &result)))
					return COM::kOK;
			}
		}
		return COM::kInvalid;
	}
	return COM::kInvalidParameter;
}

void CPF_STDCALL Pipeline::Submit(Concurrency::Scheduler* scheduler)
{
#ifdef CPF_DEBUG
	// Asserts can be enabled in release mode.
	CPF_ASSERT(mChanged == false);
#endif
	scheduler->Execute(mQueue, false);
}

COM::Result CPF_STDCALL Pipeline::GetQueueInfo(int32_t idx, const char** outString)
{
	if (outString)
	{
		if (idx < mQueueInfo.size())
		{
			*outString = mQueueInfo[idx].c_str();
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Pipeline::EnumerateSystems(void* context, bool(CPF_STDCALL *callback)(void*, SystemID, IntrusivePtr<System>))
{
	if (callback)
	{
		for (auto pair : mSystemMap)
		{
			if (!callback(context, pair.first, pair.second))
				break;
		}
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
