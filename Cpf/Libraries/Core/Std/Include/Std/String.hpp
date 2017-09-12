//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"

namespace CPF
{
	namespace Std
	{

		inline char* StrCat(char* dst, const char* src)
		{
			return strcat(dst, src);
		}

		inline const char* StrChr(const char* str, int ch)
		{
			return strchr(str, ch);
		}

		inline char* StrChr(char* str, int ch)
		{
			return strchr(str, ch);
		}

		inline int StrCmp(const char* lhs, const char* rhs)
		{
			return strcmp(lhs, rhs);
		}

		inline int StrColl(const char* lhs, const char* rhs)
		{
			return strcoll(lhs, rhs);
		}

		inline char* StrCpy(char* dst, const char* src)
		{
			return strcpy(dst, src);
		}

		inline size_t StrCspn(const char* lhs, const char* rhs)
		{
			return strcspn(lhs, rhs);
		}

		inline char* StrError(int errnum)
		{
			return strerror(errnum);
		}

		inline size_t StrLen(const char* str)
		{
			return strlen(str);
		}

		inline char* StrNCat(char* dst, const char* src, size_t num)
		{
			return strncat(dst, src, num);
		}

		inline int StrNCmp(const char* lhs, const char* rhs, size_t num)
		{
			return strncmp(lhs, rhs, num);
		}

		inline char* StrNCpy(char* dst, const char* src, size_t num)
		{
			return strncpy(dst, src, num);
		}

		inline const char* StrPBrk(const char* lhs, const char* rhs)
		{
			return strpbrk(lhs, rhs);
		}

		inline char* StrPBrk(char* lhs, const char* rhs)
		{
			return strpbrk(lhs, rhs);
		}

		inline const char* StrRChr(const char* str, int ch)
		{
			return strrchr(str, ch);
		}

		inline char* StrRChr(char* str, int ch)
		{
			return strrchr(str, ch);
		}

		inline size_t StrSpn(const char* lhs, const char* rhs)
		{
			return strspn(lhs, rhs);
		}

		inline const char* StrStr(const char* lhs, const char* rhs)
		{
			return strstr(lhs, rhs);
		}

		inline char* StrStr(char* lhs, const char* rhs)
		{
			return strstr(lhs, rhs);
		}

		inline char* StrTok(char* lhs, const char* dels)
		{
			return strtok(lhs, dels);
		}

		inline size_t StrXfrm(char* dst, const char* src, size_t num)
		{
			return strxfrm(dst, src, num);
		}
	}
}
