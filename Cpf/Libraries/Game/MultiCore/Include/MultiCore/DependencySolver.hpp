//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "UnorderedMap.hpp"
#include "UnorderedSet.hpp"
#include "Set.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class DependencySolver
		{
		public:
			DependencySolver();
			~DependencySolver();

			bool AddStage(const SystemStagePair systemStage);
			void AddDependencies(const DependencyVector& deps);

			bool Solve();

		private:
			using StageVector = Vector<SystemStagePair>;
			using StagesVector = Vector<StageVector>;
			using SystemStageMap = UnorderedMap<SystemID, UnorderedSet<StageID>>;

			using TargetStageMap = UnorderedMap<StageID, ConcurrencyStyle>;
			using TargetSystemMap = UnorderedMap<SystemID, TargetStageMap>;
			using DependentStageMap = UnorderedMap<StageID, TargetSystemMap>;
			using DependentSystemMap = UnorderedMap<SystemID, DependentStageMap>;

			const TargetSystemMap* _FindDependencies(SystemID, StageID) const;
			bool _Solve(SystemID system, TargetSystemMap deps, StagesVector::iterator& bucket);
			void _AddToBucket(StagesVector::iterator, SystemID, StageID);

			SystemStageMap mSystemStages;
			DependentSystemMap mDependencies;

			StagesVector mStages;
		};
	}
}
