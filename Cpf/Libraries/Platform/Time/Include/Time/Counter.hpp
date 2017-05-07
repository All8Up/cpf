//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Time
	{
		class Ratio;
		bool InitializeCounter();
		const Ratio& GetCounterFrequency();
		int64_t GetCounter();
	}
}
#include "Platform/Time/Counter.hpp"
