//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "MultiCore/Export.hpp"
#include "Vector.hpp"
#include "IntrusivePtr.hpp"
#include "Hash/HashID.hpp"
#include "Hash/HashString.hpp"
#include "Concurrency/Scheduler.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		struct iPipeline;

		struct CPF_EXPORT_MULTICORE SystemID_tag {};
		using SystemID = CPF_EXPORT_MULTICORE Hash::HashString<SystemID_tag>;
		class CPF_EXPORT_MULTICORE System;

		struct CPF_EXPORT_MULTICORE StageID_tag {};
		using StageID = Hash::HashString<StageID_tag>;
		class CPF_EXPORT_MULTICORE Stage;
		using StageVector = Vector<IntrusivePtr<Stage>>;

		struct CPF_EXPORT_MULTICORE BlockID_tag {};
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

		enum class DependencyPolicy
		{
			eBarrier,		// Must be separated by a barrier.
			eAfter			// Does not require a barrier, just needs to be scheduled afterwards.  (Usually used with eLast types.)
		};

		struct BlockDependency
		{
			BlockDependency(SSBID dependent, SSBID target, DependencyPolicy policy = DependencyPolicy::eBarrier);

			SSBID mDependent;
			SSBID mTarget;
			DependencyPolicy mPolicy;
		};
		using BlockDependencies = Vector<BlockDependency>;
	}
}
