//////////////////////////////////////////////////////////////////////////
#include "Threading/CPU.hpp"

using namespace Cpf;
using namespace Threading;

CPUUsage::CPUUsage()
{
	PdhOpenQuery(nullptr, NULL, &mQuery);
	PdhAddCounter(mQuery, "\\Processor(_Total)\\% Processor Time", NULL, &mTotal);
	PdhCollectQueryData(mQuery);
}

CPUUsage::~CPUUsage()
{
	PdhRemoveCounter(mTotal);
	PdhCloseQuery(mQuery);
}

float CPUUsage::GetValue() const
{
	PDH_FMT_COUNTERVALUE counterVal;
	PdhCollectQueryData(mQuery);
	PdhGetFormattedCounterValue(mTotal, PDH_FMT_DOUBLE, nullptr, &counterVal);
	return float(counterVal.doubleValue);
}
