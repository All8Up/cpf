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
	bool madeProgress;
	do
	{
		madeProgress = false;
		OpcodeMap remaining = mOpcodes;
		mOpcodes.clear();

		for (auto& opcode : remaining)
		{
			auto opcodeData = opcode.first;
			const auto& dependencySet = opcode.second;

			for (auto& depStageOpcodeID : dependencySet)
			{
				auto dependencies = _GetDependencies(depStageOpcodeID.mID);
				if (dependencies == nullptr)
				{
					// Put this in the first bucket, it has no dependencies.
					_AddToBucket(mBuckets.begin(), opcodeData);
					madeProgress = true;
				}
				else
				{
					// If it has dependencies, sort the system/stage into the appropriate location.
					Buckets::iterator targetBucket = mBuckets.end();
					if (_Solve(*dependencies, targetBucket))
					{
						_AddToBucket(targetBucket, opcodeData);
						madeProgress = true;
					}
					else
					{
						// Push this back into the dependency vector and try again later.
						Add(opcodeData.mStageOpcodeID.mStage, opcodeData.mStageOpcodeID.mOpcode, opcodeData.mOpcodeType);
					}
				}
			}
		}
	} while (mOpcodes.size() > 0 && madeProgress);
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
		bool needsNewBucket = false;
		for (auto& opcodeData : *ibucket)
		{
			DependencyDesc temp;
			temp.mID = opcodeData.mStageOpcodeID;

			auto it = remaining.find(temp);
			if (it == remaining.end())
				continue;

			// If any dependency is solved in the current bucket which
			// specifies a barrier is needed, it is sticky until we
			// move to the next bucket.
			if (it->mPolicy == DependencyPolicy::eBarrier)
				needsNewBucket = true;

			remaining.erase(temp);
			if (remaining.empty())
			{
				// Constraints are resolved.
				if (needsNewBucket)
					// Goes in the next bucket.
					outLocation = ibucket + 1;
				else
					// Goes in the same bucket.
					outLocation = ibucket;
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
