//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Vector.hpp"
#include "IntrusivePtr.hpp"
#include "Hash/HashID.hpp"
#include "Hash/HashString.hpp"
#include "Concurrency/Scheduler.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Pipeline;

		using SystemID = Hash::HashString;
		class System;

		using StageID = Hash::HashString;
		class Stage;
		using StageVector = Vector<IntrusivePtr<Stage>>;

		using BlockID = Hash::HashString;

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

			bool operator <(const SSBID& rhs) const;
			bool operator ==(const SSBID& rhs) const;
		};

		struct Instruction
		{
			SSBID mID;
			BlockOpcode mOpcode;
			Concurrency::Scheduler::PayloadFunc_t mpFunction;
			void* mpContext;
		};
		using Instructions = Vector<Instruction>;

		struct StageBlockID
		{
			StageBlockID(StageID stageID, BlockID blockID);
			explicit StageBlockID(const SSBID& ssbid);

			StageID mStage;
			BlockID mBlock;
		};

		enum class BlockPolicy
		{
			eBarrier,		// Must be separated by a barrier.
			eAfter			// Does not require a barrier, just needs to be scheduled afterwards.  (Usually used with eLast types.)
		};

		struct BlockDependency
		{
			BlockDependency(SSBID dependent, SSBID target, BlockPolicy policy = BlockPolicy::eBarrier);

			SSBID mDependent;
			SSBID mTarget;
			BlockPolicy mPolicy;
		};
		using BlockDependencies = Vector<BlockDependency>;

		//////////////////////////////////////////////////////////////////////////
		struct SystemStageID
		{
			constexpr SystemStageID(SystemID system, StageID stage)
				: mSystem(system)
				, mStage(stage)
			{}

			SystemID mSystem;
			StageID mStage;

			bool operator == (const SystemStageID& rhs) const
			{
				return mSystem == rhs.mSystem && mStage == rhs.mStage;
			}

			bool operator < (const SystemStageID& rhs) const
			{
				if (mSystem < rhs.mSystem)
					return true;
				if (mStage < rhs.mStage)
					return true;
				return false;
			}
		};

		struct SystemDependency
		{
			StageID mDependent;
			SystemStageID mTarget;
		};
		using SystemDependencies = Vector<SystemDependency>;
	}
}

namespace CPF_STL_NAMESPACE
{
	template<>
	struct hash<Cpf::MultiCore::SystemStageID>
	{
		size_t operator ()(const Cpf::MultiCore::SystemStageID& id) const
		{
			size_t first = id.mSystem.GetID();
			size_t second = id.mStage.GetID();
			first <<= 11;
			first ^= second;
			return size_t(first);
		}
	};
}
