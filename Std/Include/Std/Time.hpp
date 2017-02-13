//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"
#include <ctime>

namespace Cpf
{
	namespace Std
	{
		using Clock_t = clock_t;
		using Time_t = time_t;
		using Tm = tm;

		CPF_EXPORT_STD Clock_t Clock();
		CPF_EXPORT_STD double DiffTime(Time_t end, Time_t begin);
		CPF_EXPORT_STD Time_t MkTime(Tm* timePtr);
		CPF_EXPORT_STD Time_t Time(Time_t* timer);

		CPF_EXPORT_STD char* AscTime(const Tm* timePtr);
		CPF_EXPORT_STD char* CTime(const Time_t* timePtr);
		CPF_EXPORT_STD Tm* GmTime(const Time_t* timePtr);
		CPF_EXPORT_STD Tm* LocalTime(const Time_t* timePtr);
		CPF_EXPORT_STD size_t StrFTime(char* ptr, size_t maxSize, const char* format, const Tm* timePtr);
	}
}
