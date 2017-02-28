//////////////////////////////////////////////////////////////////////////
#include "MultiCore/QueueBuilder.hpp"

using namespace Cpf;
using namespace MultiCore;


QueueBuilder::QueueBuilder()
{}

QueueBuilder::~QueueBuilder()
{}

void QueueBuilder::Add(StageID stageID, OpcodeID opcodeID, const OpcodeType opcode)
{
	mOpcodes[{{stageID, opcodeID}, opcode}] = DependencySet();
}

void QueueBuilder::Add(const OpcodeDependency& dependency)
{
	mDependencies[dependency.mDependent] = DependencySet(dependency.mDependencies.begin(), dependency.mDependencies.end());
}

bool QueueBuilder::Solve()
{
#if 0
	bool madeProgress;
	do
	{
		madeProgress = false;
		OpcodeMap remaining = mOpcodes;
		mOpcodes.clear();

		for (auto& opcode : remaining)
		{
			auto stageOpcodeID = opcode.first;
			const auto& dependencies = opcode.second;

			for (auto& depStageOpcodeID : dependencies)
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
#endif
	return true;
}

bool QueueBuilder::_Solve(const DependencySet& dependencies, Buckets::iterator& outLocation)
{
	// Copy the dependencies.  As dependencies are identified, they are removed from this.
	// If this still has items in it after iterating through the stage buckets, we have failed
	// the constraints.  If it runs out of items, then the location to insert will be after
	// the current bucket.
	DependencySet remaining = dependencies;

	outLocation = mBuckets.begin();
	for (auto ibucket = mBuckets.begin(), iend = mBuckets.end(); ibucket != iend; ++ibucket)
	{
		for (auto& opcodeData : *ibucket)
		{
			DependencyDesc temp;
			temp.mID = opcodeData.mStageOpcodeID;

			auto it = remaining.find(temp);
			if (it == remaining.end())
				continue;

			remaining.erase(temp);
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

const QueueBuilder::DependencySet* QueueBuilder::_GetDependencies(const StageOpcodeID& rhs) const
{
	const auto& systemStageSet = mDependencies.find(rhs);

	if (systemStageSet != mDependencies.end())
	{
		return &systemStageSet->second;
	}
	return nullptr;
}

void QueueBuilder::_AddToBucket(Buckets::iterator it, OpcodeData data)
{
	if (it == mBuckets.end())
	{
		mBuckets.push_back(OpcodeDataVector());
		mBuckets.back().push_back(data);
	}
	else
	{
		(*it).push_back(data);
	}
}
