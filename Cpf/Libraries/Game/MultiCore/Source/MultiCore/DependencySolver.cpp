//////////////////////////////////////////////////////////////////////////
#include "MultiCore/DependencySolver.hpp"

#if CPF_TARGET_WINDOWS
#pragma warning(disable : 4503)
#endif

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
DependencySolver::DependencySolver()
{}

DependencySolver::~DependencySolver()
{}

bool DependencySolver::AddStage(const SystemStagePair systemStage)
{
	auto it = mSystemStages.find(systemStage.first);
	if (it != mSystemStages.end())
		if (it->second.find(systemStage.second)!=it->second.end())
			return false;

	mSystemStages[systemStage.first].insert(systemStage.second);
	return true;
}

void DependencySolver::AddDependencies(const DependencyVector& deps)
{
	for (auto& it : deps)
	{
		mDependencies[it.mDependent.first][it.mDependent.second][it.mTarget.first][it.mTarget.second] = it.mStyle;
	}
}

bool DependencySolver::Solve()
{
	bool madeProgress;
	do
	{
		madeProgress = false;
		SystemStageMap remaining = mSystemStages;
		mSystemStages.clear();

		for (auto& system : remaining)
		{
			for (auto& stage : system.second)
			{
				auto dependencies = _FindDependencies(system.first, stage);
				if (dependencies == nullptr)
				{
					// Put this in the first bucket, it has no dependencies.
					_AddToBucket(mStages.begin(), system.first, stage);
					madeProgress = true;
				}
				else
				{
					StagesVector::iterator targetBucket = mStages.end();
					auto solved = _Solve(system.first, *dependencies, targetBucket);
					if (solved)
					{
						_AddToBucket(targetBucket, system.first, stage);
						madeProgress = true;
					}
					else
					{
						// Push this back into the dependency vector and try again later.
						AddStage({system.first, stage});
					}
				}
			}
		}
	} while (mSystemStages.size() > 0 && madeProgress);

	return true;
}

bool DependencySolver::_Solve(SystemID system, TargetSystemMap deps, StagesVector::iterator& outBucket)
{
	// Iterate the buckets.
	for (auto& bucket : mStages)
	{
		// Iterate the system stage pairs in each bucket.
		for (auto& systemStage : bucket)
		{
			if (systemStage.first == system)
			{
				for (auto& it : deps)
				{
				}
			}
		}
	}
	return false;
}

const DependencySolver::TargetSystemMap* DependencySolver::_FindDependencies(SystemID system, StageID stage) const
{
	auto systemIt = mDependencies.find(system);
	if (systemIt != mDependencies.end())
	{
		auto stageIt = systemIt->second.find(stage);
		if (stageIt != systemIt->second.end())
		{
			auto& deps = stageIt->second;
			if (!deps.empty())
				return &deps;
		}
	}
	return nullptr;
}

void DependencySolver::_AddToBucket(StagesVector::iterator it, SystemID system, StageID stage)
{
	if (it == mStages.end())
	{
		mStages.push_back(StageVector());
		mStages.back().push_back({system, stage});
	}
	else
	{
		(*it).push_back({ system, stage });
	}
}
