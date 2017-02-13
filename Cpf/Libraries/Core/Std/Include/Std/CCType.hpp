//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"

namespace Cpf
{
	namespace Std
	{
		CPF_EXPORT_STD int IsAlNum(int c);
		CPF_EXPORT_STD int IsAlpha(int c);
		CPF_EXPORT_STD int IsBlank(int c);
		CPF_EXPORT_STD int IsCntrl(int c);
		CPF_EXPORT_STD int IsDigit(int c);
		CPF_EXPORT_STD int IsGraph(int c);
		CPF_EXPORT_STD int IsLower(int c);
		CPF_EXPORT_STD int IsPrint(int c);
		CPF_EXPORT_STD int IsPunct(int c);
		CPF_EXPORT_STD int IsSpace(int c);
		CPF_EXPORT_STD int IsUpper(int c);
		CPF_EXPORT_STD int IsXDigit(int c);

		CPF_EXPORT_STD int ToLower(int c);
		CPF_EXPORT_STD int ToUpper(int c);
	}
}
