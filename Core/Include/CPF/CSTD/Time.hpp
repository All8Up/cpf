//////////////////////////////////////////////////////////////////////////
#pragma once
#include <ctime>

namespace CPF
{
	namespace CSTD
	{
		using Clock_t = clock_t;
		using Time_t = time_t;
		using Tm = tm;

		inline Clock_t Clock()
		{
			return clock();
		}

		inline double DiffTime(Time_t end, Time_t begin)
		{
			return difftime(end, begin);
		}

		inline Time_t MkTime(Tm* timePtr)
		{
			return mktime(timePtr);
		}

		inline Time_t Time(Time_t* timer)
		{
			return time(timer);
		}

		inline char* AscTime(const Tm* timePtr)
		{
			return asctime(timePtr);
		}

		inline char* CTime(const Time_t* timePtr)
		{
			return ctime(timePtr);
		}

		inline Tm* GmTime(const Time_t* timePtr)
		{
			return gmtime(timePtr);
		}

		inline Tm* LocalTime(const Time_t* timePtr)
		{
			return localtime(timePtr);
		}

		inline size_t StrFTime(char* ptr, size_t maxSize, const char* format, const Tm* timePtr)
		{
			return strftime(ptr, maxSize, format, timePtr);
		}
	}
}
