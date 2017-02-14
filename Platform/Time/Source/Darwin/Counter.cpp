//////////////////////////////////////////////////////////////////////////
#include "Time/Time.hpp"
#include "Time/Ratio.hpp"
#include "Time/Counter.hpp"
#include <mach/mach_time.h>

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
	mach_timebase_info_data_t timebase;
	mach_timebase_info(&timebase);

	TimeRatio.SetNumerator(timebase.numer);
	// NOTE: Rescale the denominator so the pair ends up converting to seconds.
	TimeRatio.SetDenominator(timebase.denom * 1e+9);
	return true;
}


/**
 @brief Get the frequency of the system counter.
 @returns The ratio which represents the conversion of the OS specific time value to seconds.
 */
CPF_EXPORT_TIME const Time::Ratio& Time::GetCounterFrequency()
{
	return TimeRatio;
}


/**
 @brief Get the current system counter.
 @returns The current OS specific time value.
 */
CPF_EXPORT_TIME int64_t Time::GetCounter()
{
	return mach_absolute_time();
}
