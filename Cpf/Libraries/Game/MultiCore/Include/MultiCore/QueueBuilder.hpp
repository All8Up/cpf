//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"
#include "Hash/HashID.hpp"
#include "Stage.hpp"
#include "Set.hpp"
#include "Map.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class QueueBuilder
		{
		public:
			QueueBuilder(Pipeline* pipeline);
			~QueueBuilder();

			void Add(const Instruction& instructions);
			void Add(const BlockDependencies& dependencies);

			bool Solve();

			Concurrency::Scheduler::Queue& GetQueue() { return mResultQueue; }

		private:
			Instructions mInstructions;

			struct DependencyEntry
			{
				SSBID mID;
				BlockPolicy mPolicy;

				bool operator < (const DependencyEntry& rhs) const;
			};

			using DependencySet = Set<DependencyEntry>;
			using DependencyMap = Map<SSBID, DependencySet>;
			DependencyMap mDependencies;

			using BucketVector = Vector<Instructions>;
			BucketVector mBuckets;

			void _BuildQueue();
			bool _Solve(const DependencySet& dependencies, BucketVector::iterator& outLocation);
			void _AddToBucket(BucketVector::iterator it, const Instruction& data);

			//
			Concurrency::Scheduler::Queue mResultQueue;

			Pipeline* mpPipeline;
		};
	}
}
