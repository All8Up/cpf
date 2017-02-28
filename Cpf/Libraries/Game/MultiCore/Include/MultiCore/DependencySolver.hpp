//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "MultiCore/QueueBuilder.hpp"
#include "UnorderedMap.hpp"
#include "UnorderedSet.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class DependencySolver
		{
		public:
			DependencySolver();
			~DependencySolver();

			bool AddStage(const SystemID& system, const StageID& stage);
			void AddDependencies(const DependencyVector& deps);

			bool Solve();

			size_t GetBucketCount() const;
			const SystemStageIDVector& GetBucket(size_t index) const;

		private:
			using SystemStageMap = UnorderedMap<SystemID, UnorderedSet<StageID>>;

			using SystemStageSet = UnorderedSet<SystemStageID>;
			using DependencyMap = UnorderedMap<SystemStageID, SystemStageSet>;

			using Buckets = Vector<SystemStageIDVector>;

			const SystemStageSet* _GetDependencies(const SystemID& system, const StageID& stage) const;
			void _AddToBucket(Buckets::iterator it, SystemID system, StageID stage);
			bool _Solve(const SystemStageSet& dependencies, Buckets::iterator& outLocation);

			SystemStageMap mSystemStages;
			DependencyMap mDependencies;

			Buckets mStages;

			QueueBuilder mQueueBuilder;
		};
	}
}
