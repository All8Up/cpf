//////////////////////////////////////////////////////////////////////////
#include "MultiCore/QueueBuilder.hpp"
#include "MultiCore/Pipeline.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
bool QueueBuilder::DependencyEntry::operator < (const DependencyEntry& rhs) const
{
	return mID < rhs.mID;
}


//////////////////////////////////////////////////////////////////////////

QueueBuilder::QueueBuilder(Pipeline* pipeline)
	: mpPipeline(pipeline)
{}

QueueBuilder::~QueueBuilder()
{}

void QueueBuilder::Add(const Instruction& instruction)
{
	mInstructions.push_back(instruction);
}

void QueueBuilder::Add(const BlockDependencies& dependencies)
{
	CPF_LOG(Experimental, Info) << "--- Dependencies ---";
	for (const auto& dep : dependencies)
	{
		if (mDependencies.find(dep.mDependent) == mDependencies.end())
			mDependencies[dep.mDependent] = DependencySet();
		DependencyEntry entry{dep.mTarget, dep.mPolicy};
		mDependencies[dep.mDependent].insert(entry);

		CPF_LOG(Experimental, Info) <<
			" " << dep.mDependent.mSystem.GetString() <<
			" : " << dep.mDependent.mStage.GetString() <<
			" = " << dep.mTarget.mSystem.GetString() <<
			" : " << dep.mTarget.mStage.GetString();
	}
	CPF_LOG(Experimental, Info) << "--- Dependencies ---";
}

bool QueueBuilder::Solve()
{
	bool madeProgress;
	do
	{
		madeProgress = false;
		Instructions remaining = mInstructions;
		mInstructions.clear();

		for (auto& instruction : remaining)
		{
			const auto dependencySet = mDependencies.find(instruction.mID);

			if (dependencySet == mDependencies.end())
			{
				// No dependencies for this block, push into the first bucket.
				_AddToBucket(mBuckets.begin(), instruction);
			}
			else
			{
				// Solve the dependencies if possible.
				BucketVector::iterator it;
				if (_Solve(dependencySet->second, it))
				{
					// Add this to the buckets.
					_AddToBucket(it, instruction);
					madeProgress = true;
				}
				else
				{
					// Try again later.
					Add(instruction);
				}
			}
		}
	} while (mInstructions.size() > 0 && madeProgress);

	_BuildQueue();
	return mInstructions.empty();
}

void QueueBuilder::_BuildQueue()
{
	mResultQueue.Discard();
	for (const auto& bucket : mBuckets)
	{
		for (const auto& instruction : bucket)
		{
			switch (instruction.mOpcode)
			{
			case BlockOpcode::eFirst:
				mResultQueue.FirstOne(instruction.mpFunction, instruction.mpContext);
				break;

			case BlockOpcode::eAll:
				mResultQueue.All(instruction.mpFunction, instruction.mpContext);
				break;

			case BlockOpcode::eLast:
				mResultQueue.LastOne(instruction.mpFunction, instruction.mpContext);
				break;

			default:
				CPF_ASSERT_ALWAYS;
				break;
			}
		}
		mResultQueue.Barrier();
	}

#ifdef CPF_DEBUG
	CPF_LOG(Experimental, Info) << "--------------------- Queue disassembly ---------------------";
	for (const auto& bucket : mBuckets)
	{
		for (const auto& instruction : bucket)
		{
			switch (instruction.mOpcode)
			{
			case BlockOpcode::eFirst:
				CPF_LOG(Experimental, Info) << "  -- First: "
					<< instruction.mID.mSystem.GetString() << " : "
					<< instruction.mID.mStage.GetString() << "="
					<< instruction.mID.mBlock.GetString();
				break;

			case BlockOpcode::eAll:
				CPF_LOG(Experimental, Info) << "  -- All: "
					<< instruction.mID.mSystem.GetString() << " : "
					<< instruction.mID.mStage.GetString() << "="
					<< instruction.mID.mBlock.GetString();
				break;

			case BlockOpcode::eLast:
				CPF_LOG(Experimental, Info) << "  -- Last: "
					<< instruction.mID.mSystem.GetString() << " : "
					<< instruction.mID.mStage.GetString() << "="
					<< instruction.mID.mBlock.GetString();
				break;

			default:
				CPF_ASSERT_ALWAYS;
				break;
			}
		}
		CPF_LOG(Experimental, Info) << "  <<< Barrier >>>";
	}
	CPF_LOG(Experimental, Info) << "--------------------- Queue disassembly ---------------------";
#endif
}

bool QueueBuilder::_Solve(const DependencySet& dependencies, BucketVector::iterator& outLocation)
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
		for (auto& instruction : *ibucket)
		{
			DependencyEntry comparator{
				instruction.mID,
				BlockPolicy::eAfter
			};
			auto it = remaining.find(comparator);
			if (it == remaining.end())
				continue;

			// If any dependency is solved in the current bucket which
			// specifies a barrier is needed, it is sticky until we
			// move to the next bucket.
			if (it->mPolicy == BlockPolicy::eBarrier)
				needsNewBucket = true;

			remaining.erase(comparator);
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

void QueueBuilder::_AddToBucket(BucketVector::iterator it, const Instruction& data)
{
	if (it == mBuckets.end())
	{
		mBuckets.push_back(Instructions());
		mBuckets.back().push_back(data);
	}
	else
	{
		(*it).push_back(data);
	}
}
