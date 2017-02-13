//////////////////////////////////////////////////////////////////////////
#include "Std/Time.hpp"

using namespace Cpf;
using namespace Std;

CPF_EXPORT_STD Clock_t Std::Clock()
{
	return clock();
}

CPF_EXPORT_STD double Std::DiffTime(Time_t end, Time_t begin)
{
	return difftime(end, begin);
}

CPF_EXPORT_STD Time_t Std::MkTime(Tm* timePtr)
{
	return mktime(timePtr);
}

CPF_EXPORT_STD Time_t Std::Time(Time_t* timer)
{
	return time(timer);
}

CPF_EXPORT_STD char* Std::AscTime(const Tm* timePtr)
{
	return asctime(timePtr);
}

CPF_EXPORT_STD char* Std::CTime(const Time_t* timePtr)
{
	return ctime(timePtr);
}

CPF_EXPORT_STD Tm* Std::GmTime(const Time_t* timePtr)
{
	return gmtime(timePtr);
}

CPF_EXPORT_STD Tm* Std::LocalTime(const Time_t* timePtr)
{
	return localtime(timePtr);
}

CPF_EXPORT_STD size_t Std::StrFTime(char* ptr, size_t maxSize, const char* format, const Tm* timePtr)
{
	return strftime(ptr, maxSize, format, timePtr);
}
