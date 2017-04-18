//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"
#include "Hash/HashID.hpp"
#include "MultiCore/iStage.hpp"
#include "Set.hpp"
#include "Map.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class QueueBuilder
		{
		public:
			QueueBuilder(iPipeline* pipeline);
			~QueueBuilder();

			void Add(const Instruction& instructions);
			void Add(const BlockDependencies& dependencies);

			bool Solve();

			Concurrency::Scheduler::Queue& GetQueue() { return mResultQueue; }

			Vector<String> GetQueueInfo() const;

		private:
			Instructions mInstructions;

			struct DependencyEntry
			{
				SSBID mID;
				DependencyPolicy mPolicy;

				bool operator < (const DependencyEntry& rhs) const;
			};

			using DependencySet = Set<DependencyEntry>;
			using DependencyMap = Map<SSBID, DependencySet>;
			DependencyMap mDependencies;

			using BucketVector = Vector<Instructions>;
			BucketVector mBuckets;

			void _MakeQueueInfo();
			void _BuildQueue();
			bool _Solve(const DependencySet& dependencies, BucketVector::iterator& outLocation);
			void _AddToBucket(BucketVector::iterator it, const Instruction& data);
			void _GatherStageDependencies();

			//
			Concurrency::Scheduler::Queue mResultQueue;

			iPipeline* mpPipeline;

			Vector<String> mQueueInfo;
		};
	}
}
