//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"
#include <cctype>

namespace Cpf
{
	namespace Std
	{
		inline int IsAlNum(int c) { return isalnum(c); }
		inline int IsAlpha(int c) { return isalpha(c); }
		inline int IsBlank(int c) { return isblank(c); }
		inline int IsCntrl(int c) { return iscntrl(c); }
		inline int IsDigit(int c) { return isdigit(c); }
		inline int IsGraph(int c) { return isgraph(c); }
		inline int IsLower(int c) { return islower(c); }
		inline int IsPrint(int c) { return isprint(c); }
		inline int IsPunct(int c) { return ispunct(c); }
		inline int IsSpace(int c) { return isspace(c); }
		inline int IsUpper(int c) { return isupper(c); }
		inline int IsXDigit(int c) { return isxdigit(c); }

		inline int ToLower(int c) { return tolower(c); }
		inline int ToUpper(int c) { return toupper(c); }
	}
}
