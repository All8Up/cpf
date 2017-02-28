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
		using OpcodeID = Hash::HashID<uint64_t, 12332>;
		struct StageOpcodeID
		{
			StageID mStage;
			OpcodeID mOpcode;

			bool operator <(const StageOpcodeID& rhs) const
			{
				if (mStage < rhs.mStage)
					return true;
				if (mOpcode < rhs.mOpcode)
					return true;
				return false;
			}
			bool operator == (const StageOpcodeID& rhs) const
			{
				return mStage == rhs.mStage && mOpcode == rhs.mOpcode;
			}
		};

		enum class OpcodeType
		{
			eFirst,
			eAll,
			eLast
		};

		enum class DependencyPolicy
		{
			eBarrier,		// Must be separated by a barrier.
			eAfter			// Does not require a barrier, just needs to be scheduled afterwards.  (Usually used with eLast types.)
		};

		struct DependencyDesc
		{
			StageOpcodeID mID;
			OpcodeType mType;
			DependencyPolicy mPolicy;

			bool operator < (const DependencyDesc& rhs) const
			{
				return mID < rhs.mID;
			}
		};

		struct OpcodeDependency
		{
			StageOpcodeID mDependent;
			Vector<DependencyDesc> mDependencies;
		};

		class QueueBuilder
		{
		public:
			QueueBuilder();
			~QueueBuilder();

			void Add(StageID stageId, OpcodeID opcodeID, const OpcodeType opcode);
			void Add(const OpcodeDependency& dependency);

			bool Solve();

		private:
			struct OpcodeData
			{
				bool operator < (const OpcodeData& rhs) const
				{
					return mStageOpcodeID < rhs.mStageOpcodeID;
				}

				StageOpcodeID mStageOpcodeID;
				OpcodeType mOpcodeType;
			};
			using OpcodeDataVector = Vector<OpcodeData>;
			using DependencySet = Set<DependencyDesc>;
			using OpcodeMap = Map<OpcodeData, DependencySet>;
			using Buckets = Vector<OpcodeDataVector>;

			bool _Solve(const DependencySet& dependencies, Buckets::iterator& outLocation);
			const DependencySet* _GetDependencies(const StageOpcodeID& rhs) const;
			void _AddToBucket(Buckets::iterator it, OpcodeData data);

			OpcodeMap mOpcodes;

			using DependencyMap = Map<StageOpcodeID, DependencySet>;

			DependencyMap mDependencies;

			Buckets mBuckets;

			Concurrency::Scheduler::Queue mResultQueue;
		};
	}
}
