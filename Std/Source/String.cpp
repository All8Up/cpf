//////////////////////////////////////////////////////////////////////////
#include "Std/String.hpp"
#include <cstring>

using namespace Cpf;

CPF_EXPORT_STD char* Std::StrCat(char* dst, const char* src)
{
	return strcat(dst, src);
}

CPF_EXPORT_STD const char* Std::StrChr(const char* str, int ch)
{
	return strchr(str, ch);
}

CPF_EXPORT_STD char* Std::StrChr(char* str, int ch)
{
	return strchr(str, ch);
}

CPF_EXPORT_STD int Std::StrCmp(const char* lhs, const char* rhs)
{
	return strcmp(lhs, rhs);
}

CPF_EXPORT_STD int Std::StrColl(const char* lhs, const char* rhs)
{
	return strcoll(lhs, rhs);
}

CPF_EXPORT_STD char* Std::StrCpy(char* dst, const char* src)
{
	return strcpy(dst, src);
}

CPF_EXPORT_STD size_t Std::StrCspn(const char* lhs, const char* rhs)
{
	return strcspn(lhs, rhs);
}

CPF_EXPORT_STD char* Std::StrError(int errnum)
{
	return strerror(errnum);
}

CPF_EXPORT_STD size_t Std::StrLen(const char* str)
{
	return strlen(str);
}

CPF_EXPORT_STD char* Std::StrNCat(char* dst, const char* src, size_t num)
{
	return strncat(dst, src, num);
}

CPF_EXPORT_STD int Std::StrNCmp(const char* lhs, const char* rhs, size_t num)
{
	return strncmp(lhs, rhs, num);
}

CPF_EXPORT_STD char* Std::StrNCpy(char* dst, const char* src, size_t num)
{
	return strncpy(dst, src, num);
}

CPF_EXPORT_STD const char* Std::StrPBrk(const char* lhs, const char* rhs)
{
	return strpbrk(lhs, rhs);
}

CPF_EXPORT_STD char* Std::StrPBrk(char* lhs, const char* rhs)
{
	return strpbrk(lhs, rhs);
}

CPF_EXPORT_STD const char* Std::StrRChr(const char* str, int ch)
{
	return strrchr(str, ch);
}

CPF_EXPORT_STD char* Std::StrRChr(char* str, int ch)
{
	return strrchr(str, ch);
}

CPF_EXPORT_STD size_t Std::StrSpn(const char* lhs, const char* rhs)
{
	return strspn(lhs, rhs);
}

CPF_EXPORT_STD const char* Std::StrStr(const char* lhs, const char* rhs)
{
	return strstr(lhs, rhs);
}

CPF_EXPORT_STD char* Std::StrStr(char* lhs, const char* rhs)
{
	return strstr(lhs, rhs);
}

CPF_EXPORT_STD char* Std::StrTok(char* lhs, const char* dels)
{
	return strtok(lhs, dels);
}

CPF_EXPORT_STD size_t Std::StrXfrm(char* dst, const char* src, size_t num)
{
	return strxfrm(dst, src, num);
}
