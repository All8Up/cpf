//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time.hpp"


namespace Cpf
{
	namespace Time
	{
		class Ratio;
		CPF_EXPORT_TIME bool InitializeCounter();
		CPF_EXPORT_TIME const Ratio& GetCounterFrequency();
		CPF_EXPORT_TIME int64_t GetCounter();
	}
}
