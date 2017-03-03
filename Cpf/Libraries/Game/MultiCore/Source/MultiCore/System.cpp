//////////////////////////////////////////////////////////////////////////
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/Pipeline.hpp"
#include "UnorderedMap.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace MultiCore;

System::System(Pipeline* owner, const char* name)
	: mpOwner(owner)
	, mID(name, strlen(name))
{
}

System::~System()
{}

Pipeline* System::GetOwner() const
{
	return mpOwner;
}

Stage* System::GetStage(StageID id) const
{
	for (const auto& stage : mStages)
	{
		if (stage->GetID() == id)
		{
			stage->AddRef();
			return stage;
		}
	}
	return nullptr;
}

bool System::AddStage(Stage* stage)
{
	if (stage && stage->IsEnabled())
	{
		stage->AddRef();
		mStages.emplace_back(stage);
		return true;
	}
	return false;
}

bool System::RemoveStage(StageID id)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i]->GetID() == id)
		{
			mStages.erase(mStages.begin() + i);
			return true;
		}
	}
	return false;
}

SystemID System::GetID() const
{
	return mID;
}

const StageVector& System::GetStages() const
{
	return mStages;
}

Instructions System::GetInstructions() const
{
	Instructions result;
	for (const auto& stage : mStages)
	{
		if (stage->IsEnabled())
		{
			const auto& instructions = stage->GetInstructions(GetID());
			result.insert(result.end(), instructions.begin(), instructions.end());
		}
	}
	return result;
}

/**
 @brief Adds a fully described dependency.
 @param dependency The dependency between fully identified blocks.
 */
void System::AddDependency(const BlockDependency& dependency)
{
	mDependencies.emplace_back(dependency);
}

/**
 @brief Gets the dependencies.
 @return The dependency vector.
 */
BlockDependencies System::GetDependencies() const
{
	BlockDependencies result;
	for (const auto& dep : mDependencies)
	{
		Stage* depStage = GetOwner()->GetStage(dep.mDependent.mSystem, dep.mDependent.mStage);
		Stage* targetStage = GetOwner()->GetStage(dep.mTarget.mSystem, dep.mTarget.mStage);
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
	return result;
}

//////////////////////////////////////////////////////////////////////////
namespace
{
	using SystemMap = UnorderedMap<SystemID, System::Creator>;
	SystemMap s_SystemMap;
}

System* System::_Create(Pipeline* owner, SystemID id, const char* name, const Desc* desc)
{
	auto it = s_SystemMap.find(id);
	if (it != s_SystemMap.end())
		return (*it->second)(owner, name, desc);
	return nullptr;
}

bool System::Install(SystemID id, Creator creator)
{
	if (s_SystemMap.find(id) != s_SystemMap.end())
		return false;
	s_SystemMap[id] = creator;
	return true;
}

bool System::Remove(SystemID id)
{
	if (s_SystemMap.find(id) == s_SystemMap.end())
		return false;
	s_SystemMap.erase(id);
	return true;
}
