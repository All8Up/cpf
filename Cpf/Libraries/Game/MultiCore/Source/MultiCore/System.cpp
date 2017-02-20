//////////////////////////////////////////////////////////////////////////
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"
#include "Hash/Crc.hpp"
#include "UnorderedMap.hpp"

using namespace Cpf;
using namespace MultiCore;

System::System(Pipeline* owner, const String& name)
	: mpOwner(owner)
	, mName(name)
	, mID(Platform::Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1)))
{}

System::~System()
{}

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

Stage* System::GetStage(const String& name) const
{
	StageID id = Platform::Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1));
	return GetStage(id);
}

bool System::AddStage(Stage* stage)
{
	if (stage)
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

const String& System::GetName() const
{
	return mName;
}

SystemID System::GetID() const
{
	return mID;
}

const StageVector& System::GetStages() const
{
	return mStages;
}

//////////////////////////////////////////////////////////////////////////
namespace
{
	using SystemMap = UnorderedMap<SystemID, System::Creator>;
	SystemMap s_SystemMap;
}

System* System::_Create(SystemID id, Pipeline* pipeline, const String& name)
{
	auto it = s_SystemMap.find(id);
	if (it != s_SystemMap.end())
		return (*it->second)(pipeline, name);
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
