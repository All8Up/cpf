//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Time
	{
		class Ratio;
		bool InitializeCounter();
		const Ratio& GetCounterFrequency();
		int64_t GetCounter();

		namespace
		{
			inline Time::Ratio Initialize()
			{
				Time::Ratio result;
				LARGE_INTEGER freq;
				if (::QueryPerformanceFrequency(&freq))
				{
					result.SetNumerator(1);
					result.SetDenominator(freq.QuadPart);
				}
				return result;
			}

			/** @brief The os time ratio, retrieved at library startup. */
			template <typename TYPE>
			struct TimeRatio
			{
				static Time::Ratio Ratio;
			};
			Time::Ratio TimeRatio<int>::Ratio = Initialize();
		}

		/**
		@brief Initialize the counter system.
		@returns True if the OS time systems initialized correctly.
		*/
		inline bool Time::InitializeCounter()
		{
			LARGE_INTEGER freq;
			if (::QueryPerformanceFrequency(&freq))
			{
				TimeRatio<int>::Ratio.SetNumerator(1);
				TimeRatio<int>::Ratio.SetDenominator(freq.QuadPart);
				return true;
			}
			return false;
		}


		/**
		@brief Get the frequency of the system counter.
		@returns The ratio which represents the conversion of the OS specific time value to seconds.
		*/
		inline const Time::Ratio &Time::GetCounterFrequency()
		{
			CPF_ASSERT(TimeRatio<int>::Ratio.GetNumerator() != 0 && TimeRatio<int>::Ratio.GetDenominator() != 0);
			return TimeRatio<int>::Ratio;
		}


		/**
		@brief Get the current system counter.
		@returns The current OS specific time value.
		*/
		inline int64_t Time::GetCounter()
		{
			LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			return counter.QuadPart;
		}
	}
}
