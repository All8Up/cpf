//////////////////////////////////////////////////////////////////////////
#include "Std/CwCType.hpp"
#include <cwctype>

using namespace Cpf;

CPF_EXPORT_STD int Std::IsWAlNum(wint_t c)
{
	return iswalnum(c);
}

CPF_EXPORT_STD int Std::IsWAlpha(wint_t c)
{
	return iswalpha(c);
}

CPF_EXPORT_STD int Std::IsWBlank(wint_t c)
{
	return iswblank(c);
}

CPF_EXPORT_STD int Std::IsWCntrl(wint_t c)
{
	return iswcntrl(c);
}

CPF_EXPORT_STD int Std::IsWDigit(wint_t c)
{
	return iswdigit(c);
}

CPF_EXPORT_STD int Std::IsWGraph(wint_t c)
{
	return iswgraph(c);
}

CPF_EXPORT_STD int Std::IsWLower(wint_t c)
{
	return iswlower(c);
}

CPF_EXPORT_STD int Std::IsWPrint(wint_t c)
{
	return iswprint(c);
}

CPF_EXPORT_STD int Std::IsWPunct(wint_t c)
{
	return iswpunct(c);
}

CPF_EXPORT_STD int Std::IsWSpace(wint_t c)
{
	return iswspace(c);
}

CPF_EXPORT_STD int Std::IsWUpper(wint_t c)
{
	return iswupper(c);
}

CPF_EXPORT_STD int Std::IsWXDigit(wint_t c)
{
	return iswxdigit(c);
}

CPF_EXPORT_STD int Std::ToWLower(wint_t c)
{
	return towlower(c);
}

CPF_EXPORT_STD int Std::ToWUpper(wint_t c)
{
	return towupper(c);
}
