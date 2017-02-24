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
		// These are simply hints to the system, when concurrent is used it is just
		// a user hint that they want to group stages together.
		enum class ConcurrencyStyle
		{
			eSequencial = 0,
			eConcurrent = 1
		};
		using SystemStagePair = Pair<SystemID, StageID>;
		struct Dependency
		{
			ConcurrencyStyle mStyle;
			SystemStagePair mDependent;
			SystemStagePair mTarget;
		};
		using DependencyVector = Vector<Dependency>;
	}
}
