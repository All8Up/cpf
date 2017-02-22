//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Vector.hpp"
#include "IntrusivePtr.hpp"
#include "Hash/HashID.hpp"

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

		enum class ExecutionMode
		{
			eSequencial = 0,
			eConcurrent = 1
		};
	}
}
