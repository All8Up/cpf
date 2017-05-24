//////////////////////////////////////////////////////////////////////////
#include "Pipeline.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Logging/Logging.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "PipelineBuilder.hpp"

using namespace Cpf;
using namespace MultiCore;


//////////////////////////////////////////////////////////////////////////
Pipeline::Pipeline(iBase*)
#ifdef CPF_DEBUG
	: mChanged(false)
#endif
{
}

Pipeline::~Pipeline()
{}

GOM::Result CPF_STDCALL Pipeline::Cast(GOM::InterfaceID id, void** iface)
{
	if (iface)
	{
		switch (id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*iface = static_cast<GOM::iBase*>(this);
			AddRef();
			return GOM::kOK;
		case iPipeline::kIID.GetID():
			*iface = static_cast<iPipeline*>(this);
			AddRef();
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
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

GOM::Result CPF_STDCALL Pipeline::Remove(iSystem* system)
{
	SystemID id = system->GetID();
	if (mSystemMap.find(id) == mSystemMap.end())
		return GOM::kInvalidParameter;
#ifdef CPF_DEBUG
	mChanged = true;
#endif
	mSystemMap.erase(id);
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Pipeline::Configure(Plugin::iRegistry* regy)
{
	// Iterate the systems and setup the queue builder.
	PipelineBuilder builder(regy, this);
	mpQueue.Adopt(nullptr);
	regy->Create(nullptr, Concurrency::kWorkBufferCID, Concurrency::iWorkBuffer::kIID, mpQueue.AsVoidPP());
	for (auto& system : mSystemMap)
	{
		// Iterate and add all blocks.
		iSystem* systemPtr = nullptr;
		if (GOM::Succeeded(GetSystem(system.first, &systemPtr)))
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
		mpQueue->Copy(builder.GetQueue());

	// Let the systems configure to the new pipeline.
	// This allows systems to get pointers to other configured systems.
	bool result = _ConfigureSystems();

#ifdef CPF_DEBUG
	mChanged = false;
#endif

	mQueueInfo = builder.GetQueueInfo();
	return result ? GOM::kOK : kConfigurationError;
}

bool Pipeline::_ConfigureSystems()
{
	bool result = true;

	// Let the systems configure to the new pipeline.
	for (const auto& system : mSystemMap)
	{
		if (GOM::Failed(system.second->Configure(this)))
			result = false;
	}

	return result;
}

GOM::Result CPF_STDCALL Pipeline::GetSystem(SystemID id, iSystem** system) const
{
	if (system)
	{
		auto result = mSystemMap.find(id);
		if (result != mSystemMap.end())
		{
			result->second->AddRef();
			*system = result->second;
			return GOM::kOK;
		}
		return GOM::kInvalid;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Pipeline::GetSystem(const char* const name, iSystem** outSystem) const
{
	if (outSystem)
	{
		return GetSystem(SystemID(name, strlen(name)), outSystem);
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Pipeline::GetStage(SystemID systemID, StageID stageID, iStage** outStage)
{
	if (outStage)
	{
		iSystem* system = nullptr;
		if (GOM::Succeeded(GetSystem(systemID, &system)))
		{
			if (system)
			{
				iStage* result = nullptr;
				if (GOM::Succeeded(system->FindStage(stageID, &result)))
					return GOM::kOK;
			}
		}
		return GOM::kInvalid;
	}
	return GOM::kInvalidParameter;
}

void CPF_STDCALL Pipeline::Submit(Concurrency::iScheduler* scheduler)
{
#ifdef CPF_DEBUG
	// Asserts can be enabled in release mode.
	CPF_ASSERT(mChanged == false);
#endif
	scheduler->Execute(mpQueue, false);
}

GOM::Result CPF_STDCALL Pipeline::GetQueueInfo(int32_t idx, const char** outString)
{
	if (outString)
	{
		if (idx < mQueueInfo.size())
		{
			*outString = mQueueInfo[idx].c_str();
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Pipeline::GetSystems(int32_t* count, iSystem** systems)
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
			return GOM::kNotEnoughSpace;
		}
		*count = int32_t(mSystemMap.size());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
