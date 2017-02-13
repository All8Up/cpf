//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"
#include <wchar.h>

namespace Cpf
{
	namespace Std
	{
		CPF_EXPORT_STD int IsWAlNum(wint_t c);
		CPF_EXPORT_STD int IsWAlpha(wint_t c);
		CPF_EXPORT_STD int IsWBlank(wint_t c);
		CPF_EXPORT_STD int IsWCntrl(wint_t c);
		CPF_EXPORT_STD int IsWDigit(wint_t c);
		CPF_EXPORT_STD int IsWGraph(wint_t c);
		CPF_EXPORT_STD int IsWLower(wint_t c);
		CPF_EXPORT_STD int IsWPrint(wint_t c);
		CPF_EXPORT_STD int IsWPunct(wint_t c);
		CPF_EXPORT_STD int IsWSpace(wint_t c);
		CPF_EXPORT_STD int IsWUpper(wint_t c);
		CPF_EXPORT_STD int IsWXDigit(wint_t c);

		CPF_EXPORT_STD int ToWLower(wint_t c);
		CPF_EXPORT_STD int ToWUpper(wint_t c);
	}
}
