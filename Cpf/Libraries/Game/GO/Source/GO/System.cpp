//////////////////////////////////////////////////////////////////////////
#include "GO/System.hpp"
#include "GO/Stage.hpp"

using namespace Cpf;
using namespace GO;

System::System(Service* service)
	: mpService(service)
{
}

Service* System::GetService() const
{
	return mpService;
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
