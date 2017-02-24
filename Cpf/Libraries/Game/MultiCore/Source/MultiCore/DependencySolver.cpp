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

bool DependencySolver::AddStage(const SystemID& system, const StageID& stage)
{
	auto it = mSystemStages.find(system);
	if (it != mSystemStages.end())
		if (it->second.find(stage)!=it->second.end())
			return false;

	mSystemStages[system].insert(stage);
	return true;
}

void DependencySolver::AddDependencies(const DependencyVector& deps)
{
	for (auto& it : deps)
	{
		auto system = mDependencies.find(it.mDependent);
		if (system!=mDependencies.end())
		{
			mDependencies[it.mDependent].insert(it.mTarget);
		}
		else
		{
			mDependencies[it.mDependent] = SystemStageSet();
			mDependencies[it.mDependent].insert(it.mTarget);
		}
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

		for (auto& systemStage : remaining)
		{
			auto system = systemStage.first;
			const auto& stages = systemStage.second;

			for (auto& stage : stages)
			{
				auto dependencies = _GetDependencies(system, stage);

				if (dependencies == nullptr)
				{
					// Put this in the first bucket, it has no dependencies.
					_AddToBucket(mStages.begin(), system, stage);
					madeProgress = true;
				}
				else
				{
					// If it has dependencies, sort the system/stage into the appropriate location.
					Buckets::iterator targetBucket = mStages.end();
					if (_Solve(*dependencies, targetBucket))
					{
						_AddToBucket(targetBucket, system, stage);
						madeProgress = true;
					}
					else
					{
						// Push this back into the dependency vector and try again later.
						AddStage(system, stage);
					}
				}
			}
		}
	} while (mSystemStages.size() > 0 && madeProgress);
	return true;
}

size_t DependencySolver::GetBucketCount() const
{
	return mStages.size();
}

const SystemStageIDVector& DependencySolver::GetBucket(size_t index) const
{
	return mStages[index];
}

bool DependencySolver::_Solve(const SystemStageSet& dependencies, Buckets::iterator& outLocation)
{
	// Copy the dependencies.  As dependencies are identified, they are removed from this.
	// If this still has items in it after iterating through the stage buckets, we have failed
	// the constraints.  If it runs out of items, then the location to insert will be after
	// the current bucket.
	SystemStageSet remaining = dependencies;

	outLocation = mStages.begin();
	for (auto ibucket = mStages.begin(), iend = mStages.end(); ibucket != iend; ++ibucket)
	{
		for (auto& systemStage : *ibucket)
		{
			auto it = remaining.find(systemStage);
			if (it == remaining.end())
				continue;

			remaining.erase(systemStage);
			if (remaining.empty())
			{
				// Constraints are resolved, we go in the next bucket.
				outLocation = ibucket + 1;
				return true;
			}
		}
	}

	return false;
}

const DependencySolver::SystemStageSet* DependencySolver::_GetDependencies(const SystemID& system, const StageID& stage) const
{
	const SystemStageID systemStageID {system, stage};
	const auto& systemStageSet = mDependencies.find(systemStageID);

	if (systemStageSet != mDependencies.end())
	{
		return &systemStageSet->second;
	}
	return nullptr;
}

void DependencySolver::_AddToBucket(Buckets::iterator it, SystemID system, StageID stage)
{
	if (it == mStages.end())
	{
		mStages.push_back(SystemStageIDVector());
		mStages.back().push_back({system, stage});
	}
	else
	{
		(*it).push_back({ system, stage });
	}
}
