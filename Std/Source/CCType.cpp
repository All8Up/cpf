//////////////////////////////////////////////////////////////////////////
#include "Std/CCType.hpp"
#include <cctype>

using namespace Cpf;


CPF_EXPORT_STD int Std::IsAlNum(int c)
{
	return isalnum(c);
}

CPF_EXPORT_STD int Std::IsAlpha(int c)
{
	return isalpha(c);
}

CPF_EXPORT_STD int Std::IsBlank(int c)
{
	return isblank(c);
}

CPF_EXPORT_STD int Std::IsCntrl(int c)
{
	return iscntrl(c);
}

CPF_EXPORT_STD int Std::IsDigit(int c)
{
	return isdigit(c);
}

CPF_EXPORT_STD int Std::IsGraph(int c)
{
	return isgraph(c);
}

CPF_EXPORT_STD int Std::IsLower(int c)
{
	return islower(c);
}

CPF_EXPORT_STD int Std::IsPrint(int c)
{
	return isprint(c);
}

CPF_EXPORT_STD int Std::IsPunct(int c)
{
	return ispunct(c);
}

CPF_EXPORT_STD int Std::IsSpace(int c)
{
	return isspace(c);
}

CPF_EXPORT_STD int Std::IsUpper(int c)
{
	return isupper(c);
}

CPF_EXPORT_STD int Std::IsXDigit(int c)
{
	return isxdigit(c);
}

CPF_EXPORT_STD int Std::ToLower(int c)
{
	return tolower(c);
}

CPF_EXPORT_STD int Std::ToUpper(int c)
{
	return toupper(c);
}
