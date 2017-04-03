//////////////////////////////////////////////////////////////////////////
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/iPipeline.hpp"
#include "System.hpp"
#include "UnorderedMap.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
COM::Result CPF_STDCALL StageList::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;

		case iStageList::kIID.GetID():
			*outIface = static_cast<iStageList*>(this);
			break;

		default:
			*outIface = nullptr;
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kUnknownInterface;
}

COM::Result CPF_STDCALL StageList::FindStage(StageID id, iStage** outStage) const
{
	for (const auto& stage : mStages)
	{
		if (stage->GetID() == id)
		{
			stage->AddRef();
			*outStage = stage;
			return COM::kOK;
		}
	}
	return COM::kInvalid;
}

COM::Result CPF_STDCALL StageList::GetStages(int32_t* count, iStage** outStages) const
{
	if (count)
	{
		if (outStages)
		{
			if (int32_t(mStages.size()) > *count)
				return COM::kNotEnoughSpace;
			int32_t index = 0;
			for (auto stage : mStages)
				outStages[index++] = stage;
			return COM::kOK;
		}
		else
		{
			*count = int32_t(mStages.size());
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL StageList::AddStage(iStage* stage)
{
	if (stage)
	{
		stage->AddRef();
		mStages.emplace_back(stage);
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL StageList::RemoveStage(StageID id)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i]->GetID() == id)
		{
			mStages.erase(mStages.begin() + i);
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL StageList::GetInstructions(int32_t* count, Instruction* instructions)
{
	if (count)
	{
		Instructions result;
		for (const auto& stage : mStages)
		{
			if (stage->IsEnabled())
			{
				int32_t instructionCount = 0;
				stage->GetInstructions(&instructionCount, nullptr);
				Vector<Instruction> instrs(instructionCount);
				stage->GetInstructions(&instructionCount, instrs.data());
				result.insert(result.end(), instrs.begin(), instrs.end());
			}
		}
		if (instructions)
		{
			if (*count >= result.size())
			{
				int32_t index = 0;
				for (auto& inst : result)
					instructions[index++] = inst;
				return COM::kOK;
			}
			return COM::kNotEnoughSpace;
		}
		*count = int32_t(result.size());
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void CPF_STDCALL StageList::AddDependency(BlockDependency dep)
{
	mDependencies.push_back(dep);
}

COM::Result CPF_STDCALL StageList::GetDependencies(iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	if (count)
	{
		BlockDependencies result;
		for (const auto& dep : mDependencies)
		{
			iStage* depStage = nullptr;
			owner->GetStage(dep.mDependent.mSystem, dep.mDependent.mStage, &depStage);
			iStage* targetStage = nullptr;
			owner->GetStage(dep.mTarget.mSystem, dep.mTarget.mStage, &targetStage);
			if (depStage && depStage->IsEnabled() &&
				targetStage && targetStage->IsEnabled())
			{
				result.push_back(dep);
			}
			else
			{
				CPF_LOG(MultiCore, Info) << "Dropped disabled dependency.";
			}
		}

		if (deps)
		{
			int32_t index = 0;
			for (const auto& dep : result)
				deps[index++] = dep;
			return COM::kOK;
		}
		else
		{
			*count = int32_t(result.size());
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

//////////////////////////////////////////////////////////////////////////
System::System()
{
}

System::~System()
{}

COM::Result CPF_STDCALL System::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		default:
			return COM::kNotImplemented;
		}

		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL System::Initialize(Plugin::iRegistry* rgy, const char* name)
{
	(void)rgy;
	if (name)
	{
		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(nullptr, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (COM::Succeeded(result))
			return COM::kOK;
		return result;
	}
	return COM::kInvalidParameter;
}

SystemID CPF_STDCALL System::GetID() const
{
	return mID;
}

COM::Result CPF_STDCALL System::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

COM::Result CPF_STDCALL System::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

COM::Result CPF_STDCALL System::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

COM::Result CPF_STDCALL System::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

COM::Result CPF_STDCALL System::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL System::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

COM::Result CPF_STDCALL System::GetDependencies(iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}


//////////////////////////////////////////////////////////////////////////
namespace
{
	using SystemMap = UnorderedMap<SystemID, System::Creator>;
	SystemMap s_SystemMap;
}

iSystem* iSystem::_Create(Plugin::iRegistry* rgy, SystemID id, const char* name, const Desc* desc)
{
	auto it = s_SystemMap.find(id);
	if (it != s_SystemMap.end())
		return (*it->second)(rgy, name, desc);
	return nullptr;
}

bool iSystem::Install(SystemID id, Creator creator)
{
	if (s_SystemMap.find(id) != s_SystemMap.end())
		return false;
	s_SystemMap[id] = creator;
	return true;
}

bool iSystem::Remove(SystemID id)
{
	if (s_SystemMap.find(id) == s_SystemMap.end())
		return false;
	s_SystemMap.erase(id);
	return true;
}
