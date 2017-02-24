//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Vector.hpp"
#include "IntrusivePtr.hpp"
#include "Hash/HashID.hpp"
#include "Pair.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Pipeline;

		using SystemID = Hash::HashID<uint64_t, 1>;
		class System;

		using StageID = Hash::HashID<uint64_t, 2>;
		class Stage;
		using StageVector = Vector<IntrusivePtr<Stage>>;

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
		using SystemStageIDVector = Vector<SystemStageID>;

		struct Dependency
		{
			SystemStageID mDependent;
			SystemStageID mTarget;
		};
		using DependencyVector = Vector<Dependency>;

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
