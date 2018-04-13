//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <wchar.h>

namespace CPF
{
	namespace CSTD
	{
		inline int IsWAlNum(wint_t c) { return iswalnum(c); }
		inline int IsWAlpha(wint_t c) { return iswalpha(c); }
		inline int IsWBlank(wint_t c) { return iswblank(c); }
		inline int IsWCntrl(wint_t c) { return iswcntrl(c); }
		inline int IsWDigit(wint_t c) { return iswdigit(c); }
		inline int IsWGraph(wint_t c) { return iswgraph(c); }
		inline int IsWLower(wint_t c) { return iswlower(c); }
		inline int IsWPrint(wint_t c) { return iswprint(c); }
		inline int IsWPunct(wint_t c) { return iswpunct(c); }
		inline int IsWSpace(wint_t c) { return iswspace(c); }
		inline int IsWUpper(wint_t c) { return iswupper(c); }
		inline int IsWXDigit(wint_t c) { return iswxdigit(c); }

		inline int ToWLower(wint_t c) { return towlower(c); }
		inline int ToWUpper(wint_t c) { return towupper(c); }
	}
}
