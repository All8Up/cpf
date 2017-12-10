//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading.hpp"
#include "Platform/Threading/CPU.hpp"
#include <Pdh.h>

namespace CPF
{
	namespace Threading
	{
		class CPUUsage
		{
		public:
			CPUUsage()
			{
				PdhOpenQuery(nullptr, NULL, &mQuery);
				PdhAddCounter(mQuery, "\\Processor(_Total)\\% Processor Time", NULL, &mTotal);
				PdhCollectQueryData(mQuery);
			}
			~CPUUsage()
			{
				PdhRemoveCounter(mTotal);
				PdhCloseQuery(mQuery);
			}

			float GetValue() const
			{
				PDH_FMT_COUNTERVALUE counterVal;
				PdhCollectQueryData(mQuery);
				PdhGetFormattedCounterValue(mTotal, PDH_FMT_DOUBLE, nullptr, &counterVal);
				return float(counterVal.doubleValue);
			}

		private:
			PDH_HQUERY mQuery;
			PDH_HCOUNTER mTotal;
		};
	}
}
