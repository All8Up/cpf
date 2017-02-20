//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Vector.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Pipeline;

		using SystemID = int64_t;
		class System;

		using StageID = int64_t;
		class Stage;
		using StageVector = Vector<IntrusivePtr<Stage>>;
	}
}
