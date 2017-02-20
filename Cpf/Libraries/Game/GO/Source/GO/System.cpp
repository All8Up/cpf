//////////////////////////////////////////////////////////////////////////
#include "GO/System.hpp"
#include "GO/Stage.hpp"
#include "Hash/Crc.hpp"

using namespace Cpf;
using namespace GO;

System::System(Service* service, const String& name)
	: mpService(service)
	, mName(name)
	, mID(Platform::Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1)))
{
}

Service* System::GetService() const
{
	return mpService;
}

SystemID System::GetID() const
{
	return mID;
}

const String& System::GetName() const
{
	return mName;
}

const StageVector& System::GetStages() const
{
	return mStages;
}

void System::Activate()
{}

void System::Deactivate()
{}

void System::Add(Stage* stage)
{
	mStages.emplace_back(IntrusivePtr<Stage>(stage));
}

void System::Remove(Stage* stage)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i] == stage)
		{
			mStages.erase(mStages.begin() + i);
			return;
		}
	}
}
