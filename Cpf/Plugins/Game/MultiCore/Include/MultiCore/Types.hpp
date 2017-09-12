//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Vector.hpp"
#include "IntrusivePtr.hpp"
#include "Hash/HashID.hpp"
#include "Hash/HashString.hpp"
#include "Concurrency/iScheduler.hpp"

namespace CPF
{
	namespace MultiCore
	{
		struct iExecutionPlan;

		struct SystemID_tag {};
		using SystemID = Hash::HashString<SystemID_tag>;
		struct iSystem;

		struct StageID_tag {};
		using StageID = Hash::HashString<StageID_tag>;
		struct iStage;
		using StageVector = Vector<IntrusivePtr<iStage>>;

		struct BlockID_tag {};
		using BlockID = Hash::HashString<BlockID_tag>;

		enum class BlockOpcode
		{
			eFirst,
			eAll,
			eLast
		};

		struct Block
		{
			BlockID mID;
			BlockOpcode mType;
		};
		using Blocks = Vector<Block>;

		// System, stage, block id.
		struct SSBID
		{
			SystemID mSystem;
			StageID mStage;
			BlockID mBlock;
		};

		inline bool operator <(const SSBID& lhs, const SSBID& rhs)
		{
			if (lhs.mSystem < rhs.mSystem)
				return true;
			if (lhs.mSystem == rhs.mSystem)
			{
				if (lhs.mStage < rhs.mStage)
					return true;
				if (lhs.mStage == rhs.mStage)
				{
					if (lhs.mBlock < rhs.mBlock)
						return true;
				}
			}
			return false;
		}

		inline bool operator ==(const SSBID& lhs, const SSBID& rhs)
		{
			return lhs.mSystem == rhs.mSystem && lhs.mStage == rhs.mStage && lhs.mBlock == rhs.mBlock;
		}

		struct Instruction
		{
			SSBID mID;
			BlockOpcode mOpcode;
			Concurrency::WorkFunction mpFunction;
			void* mpContext;
		};
		using Instructions = Vector<Instruction>;

		enum class DependencyPolicy
		{
			eBarrier,	// Must be separated by a barrier.
			eAfter		// Does not require a barrier, just needs to be scheduled afterwards.  (Usually used with eLast types.)
		};

		struct BlockDependency
		{
			BlockDependency() {};
			BlockDependency(SSBID dependent, SSBID target, DependencyPolicy policy = DependencyPolicy::eBarrier)
				: mDependent(dependent)
				, mTarget(target)
				, mPolicy(policy)
			{}

			SSBID mDependent;
			SSBID mTarget;
			DependencyPolicy mPolicy;
		};
		using BlockDependencies = Vector<BlockDependency>;
	}
}
