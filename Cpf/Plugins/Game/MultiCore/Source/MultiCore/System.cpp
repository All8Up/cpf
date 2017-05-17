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
GOM::Result CPF_STDCALL StageList::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iStageList::kIID.GetID():
			*outIface = static_cast<iStageList*>(this);
			break;

		default:
			CPF_ASSERT(mpOuter != nullptr);
			return mpOuter->QueryInterface(id, outIface);
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kUnknownInterface;
}

int32_t CPF_STDCALL StageList::AddRef()
{
	if (mpOuter)
		return mpOuter->AddRef();
	return ++mRefCount;
}

int32_t CPF_STDCALL StageList::Release()
{
	if (mpOuter)
	{
		int32_t outer = mpOuter->Release();
		if (outer > 0)
			return outer;
		mpOuter = nullptr;
	}
	if (--mRefCount == 0)
	{
		delete this;
		return 0;
	}
	return mRefCount;
}

GOM::Result CPF_STDCALL StageList::FindStage(StageID id, iStage** outStage) const
{
	for (const auto& stage : mStages)
	{
		if (stage->GetID() == id)
		{
			stage->AddRef();
			*outStage = stage;
			return GOM::kOK;
		}
	}
	return GOM::kInvalid;
}

GOM::Result CPF_STDCALL StageList::GetStages(int32_t* count, iStage** outStages) const
{
	if (count)
	{
		if (outStages)
		{
			if (int32_t(mStages.size()) > *count)
				return GOM::kNotEnoughSpace;
			int32_t index = 0;
			for (auto stage : mStages)
				outStages[index++] = stage;
			return GOM::kOK;
		}
		else
		{
			*count = int32_t(mStages.size());
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL StageList::AddStage(iStage* stage)
{
	if (stage)
	{
		stage->AddRef();
		mStages.emplace_back(stage);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL StageList::RemoveStage(StageID id)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i]->GetID() == id)
		{
			mStages.erase(mStages.begin() + i);
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL StageList::GetInstructions(int32_t* count, Instruction* instructions)
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
				return GOM::kOK;
			}
			return GOM::kNotEnoughSpace;
		}
		*count = int32_t(result.size());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

void CPF_STDCALL StageList::AddDependency(BlockDependency dep)
{
	mDependencies.push_back(dep);
}

GOM::Result CPF_STDCALL StageList::GetDependencies(iPipeline* owner, int32_t* count, BlockDependency* deps)
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
			return GOM::kOK;
		}
		else
		{
			*count = int32_t(result.size());
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}
