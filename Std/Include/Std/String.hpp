//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"

namespace Cpf
{
	namespace Std
	{
		CPF_EXPORT_STD char* StrCat(char* dst, const char* src);
		CPF_EXPORT_STD const char* StrChr(const char* str, int ch);
		CPF_EXPORT_STD char* StrChr(char* str, int ch);
		CPF_EXPORT_STD int StrCmp(const char* lhs, const char* rhs);
		CPF_EXPORT_STD int StrColl(const char* lhs, const char* rhs);
		CPF_EXPORT_STD char* StrCpy(char* dst, const char* src);
		CPF_EXPORT_STD size_t StrCspn(const char* lhs, const char* rhs);
		CPF_EXPORT_STD char* StrError(int errnum);
		CPF_EXPORT_STD size_t StrLen(const char* str);

		CPF_EXPORT_STD char* StrNCat(char* dst, const char* src, size_t num);
		CPF_EXPORT_STD int StrNCmp(const char* lhs, const char* rhs, size_t num);
		CPF_EXPORT_STD char* StrNCpy(char* dst, const char* src, size_t num);

		CPF_EXPORT_STD const char* StrPBrk(const char* lhs, const char* rhs);
		CPF_EXPORT_STD char* StrPBrk(char* lhs, const char* rhs);
		CPF_EXPORT_STD const char* StrRChr(const char* str, int ch);
		CPF_EXPORT_STD char* StrRChr(char* str, int ch);
		CPF_EXPORT_STD size_t StrSpn(const char* lhs, const char* rhs);
		CPF_EXPORT_STD const char* StrStr(const char* lhs, const char* rhs);
		CPF_EXPORT_STD char* StrStr(char* lhs, const char* rhs);
		CPF_EXPORT_STD char* StrTok(char* lhs, const char* dels);
		CPF_EXPORT_STD size_t StrXfrm(char* dst, const char* src, size_t num);
	}
}
