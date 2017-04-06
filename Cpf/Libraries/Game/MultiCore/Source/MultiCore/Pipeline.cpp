//////////////////////////////////////////////////////////////////////////
#include "Pipeline.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Logging/Logging.hpp"
#include "Hash/Crc.hpp"
#include "QueueBuilder.hpp"

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
		case iPipeline::kIID.GetID():
			*iface = static_cast<iPipeline*>(this);
			AddRef();
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

iSystem* CPF_STDCALL Pipeline::Install(iSystem* system)
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

COM::Result CPF_STDCALL Pipeline::Remove(iSystem* system)
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
		iSystem* systemPtr = nullptr;
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
		system.second->GetDependencies(this, &depCount, nullptr);
		BlockDependencies dependencies(depCount);
		system.second->GetDependencies(this, &depCount, dependencies.data());
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

bool Pipeline::_ConfigureSystems()
{
	bool result = true;

	// Let the systems configure to the new pipeline.
	for (const auto& system : mSystemMap)
	{
		if (COM::Failed(system.second->Configure(this)))
			result = false;
	}

	return result;
}

COM::Result CPF_STDCALL Pipeline::GetSystem(SystemID id, iSystem** system) const
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

COM::Result CPF_STDCALL Pipeline::GetSystem(const char* const name, iSystem** outSystem) const
{
	if (outSystem)
	{
		return GetSystem(SystemID(name, strlen(name)), outSystem);
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Pipeline::GetStage(SystemID systemID, StageID stageID, iStage** outStage)
{
	if (outStage)
	{
		iSystem* system = nullptr;
		if (COM::Succeeded(GetSystem(systemID, &system)))
		{
			if (system)
			{
				iStage* result = nullptr;
				if (COM::Succeeded(system->FindStage(stageID, &result)))
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

COM::Result CPF_STDCALL Pipeline::GetSystems(int32_t* count, iSystem** systems)
{
	if (count)
	{
		if (systems)
		{
			if (*count >= mSystemMap.size())
			{
				int32_t index = 0;
				for (const auto& pair : mSystemMap)
				{
					systems[index++] = pair.second;
				}
			}
			return COM::kNotEnoughSpace;
		}
		*count = int32_t(mSystemMap.size());
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
