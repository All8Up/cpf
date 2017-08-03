//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IO/IO.hpp"


namespace Cpf
{
	namespace IO
	{
		CPF_EXPORT_IO bool Glob(const char *pattern, const char *inString);
		CPF_EXPORT_IO bool Glob(const wchar_t *pattern, const wchar_t *inString);
	}
}
