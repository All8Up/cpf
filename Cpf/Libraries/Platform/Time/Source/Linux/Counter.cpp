//////////////////////////////////////////////////////////////////////////
#include "Time/Time.hpp"
#include "Time/Ratio.hpp"
#include <time.h>

using namespace Cpf;
using namespace Platform;

namespace
{
	Time::Ratio TimeRatio;
}


/**
 @brief Initialize the counter system.
 @returns True if the OS time systems initialized correctly.
 */
CPF_EXPORT_TIME bool Time::InitializeCounter()
{
	TimeRatio.SetNumerator(1);
	// NOTE: Rescale the denominator so the pair ends up converting to seconds.
	TimeRatio.SetDenominator(100000);
	return true;
}


/**
 @brief Get the frequency of the system counter.
 @returns The ratio which represents the conversion of the OS specific time value to seconds.
 */
CPF_EXPORT_TIME const Ratio& Time::GetCounterFrequency()
{
	return TimeRatio;
}


/**
 @brief Get the current system counter.
 @returns The current OS specific time value.
 */
CPF_EXPORT_TIME int64_t Time::GetCounter()
{
	timespec temp;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &temp);
	return (temp.tv_sec*100000) + (temp.tv_nsec/1000);
}
