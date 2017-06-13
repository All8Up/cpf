//////////////////////////////////////////////////////////////////////////
#include "PlanBuilder.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Logging/Logging.hpp"
#include "Concurrency/iWorkBuffer.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
bool PlanBuilder::DependencyEntry::operator < (const DependencyEntry& rhs) const
{
	return mID < rhs.mID;
}


//////////////////////////////////////////////////////////////////////////

PlanBuilder::PlanBuilder(Plugin::iRegistry* regy, iExecutionPlan* pipeline)
	: mpPipeline(pipeline)
{
	regy->Create(nullptr, Concurrency::kWorkBufferCID.GetID(), Concurrency::iWorkBuffer::kIID.GetID(), mpQueue.AsVoidPP());
}

PlanBuilder::~PlanBuilder()
{}

void PlanBuilder::Add(const Instruction& instruction)
{
	mInstructions.push_back(instruction);
}

void PlanBuilder::Add(const BlockDependencies& dependencies)
{
	CPF_LOG(MultiCore, Info) << "--- Dependencies ---";
	for (const auto& dep : dependencies)
	{
		if (mDependencies.find(dep.mDependent) == mDependencies.end())
			mDependencies[dep.mDependent] = DependencySet();
		DependencyEntry entry{dep.mTarget, dep.mPolicy};
		mDependencies[dep.mDependent].insert(entry);

		CPF_LOG(MultiCore, Info) <<
			" " << dep.mDependent.mSystem.GetString() <<
			" : " << dep.mDependent.mStage.GetString() <<
			" = " << dep.mTarget.mSystem.GetString() <<
			" : " << dep.mTarget.mStage.GetString();
	}
	CPF_LOG(MultiCore, Info) << "--- Dependencies ---";
}

void PlanBuilder::_GatherStageDependencies()
{
	int32_t systemCount = 0;
	mpPipeline->GetSystems(&systemCount, nullptr);
	Vector<iSystem*> systems(systemCount);
	mpPipeline->GetSystems(&systemCount, systems.data());

	for (auto system : systems)
	{
		int32_t stageCount = 0;
		system->GetStages(&stageCount, nullptr);
		Vector<iStage*> stages(stageCount);
		system->GetStages(&stageCount, stages.data());

		for (auto stage : stages)
		{
			int32_t depCount = 0;
			stage->GetDependencies(&depCount, nullptr);
			Vector<MultiCore::BlockDependency> dependencies(depCount);
			stage->GetDependencies(&depCount, dependencies.data());

			if (!dependencies.empty())
				Add(dependencies);
		}
	}
}

bool PlanBuilder::Solve()
{
	_GatherStageDependencies();

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

void PlanBuilder::_BuildQueue()
{
	mpQueue->Reset();
	for (const auto& bucket : mBuckets)
	{
		for (const auto& instruction : bucket)
		{
			switch (instruction.mOpcode)
			{
			case BlockOpcode::eFirst:
				mpQueue->FirstOne(instruction.mpFunction, instruction.mpContext);
				break;

			case BlockOpcode::eAll:
				mpQueue->All(instruction.mpFunction, instruction.mpContext);
				break;

			case BlockOpcode::eLast:
				mpQueue->LastOne(instruction.mpFunction, instruction.mpContext);
				break;

			default:
				CPF_ASSERT_ALWAYS;
				break;
			}
		}
		mpQueue->Barrier();
	}

	_MakeQueueInfo();

	CPF_LOG(MultiCore, Info) << "--------------------- Queue disassembly ---------------------";
	for (const auto& string : mQueueInfo)
	{
		CPF_LOG(MultiCore, Info) << string;
	}
	CPF_LOG(MultiCore, Info) << "--------------------- Queue disassembly ---------------------";
}

Vector<String> PlanBuilder::GetQueueInfo() const
{
	return mQueueInfo;
}

void PlanBuilder::_MakeQueueInfo()
{
	for (const auto& bucket : mBuckets)
	{
		for (const auto& instruction : bucket)
		{
			switch (instruction.mOpcode)
			{
			case BlockOpcode::eFirst:
				mQueueInfo.push_back( String("First: ")
					+ String(instruction.mID.mSystem.GetString()) + String(" : ")
					+ String(instruction.mID.mStage.GetString()) + String("=")
					+ String(instruction.mID.mBlock.GetString()) );
				break;

			case BlockOpcode::eAll:
				mQueueInfo.push_back(String("All: ")
					+ String(instruction.mID.mSystem.GetString()) + String(" : ")
					+ String(instruction.mID.mStage.GetString()) + String("=")
					+ String(instruction.mID.mBlock.GetString()));
				break;

			case BlockOpcode::eLast:
				mQueueInfo.push_back(String("Last: ")
					+ String(instruction.mID.mSystem.GetString()) + String(" : ")
					+ String(instruction.mID.mStage.GetString()) + String("=")
					+ String(instruction.mID.mBlock.GetString()));
				break;

			default:
				CPF_ASSERT_ALWAYS;
				break;
			}
		}
		mQueueInfo.push_back("<<< Barrier >>>");
	}
}

bool PlanBuilder::_Solve(const DependencySet& dependencies, BucketVector::iterator& outLocation)
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
				DependencyPolicy::eAfter
			};
			auto it = remaining.find(comparator);
			if (it == remaining.end())
				continue;

			// If any dependency is solved in the current bucket which
			// specifies a barrier is needed, it is sticky until we
			// move to the next bucket.
			if (it->mPolicy == DependencyPolicy::eBarrier)
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

void PlanBuilder::_AddToBucket(BucketVector::iterator it, const Instruction& data)
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
