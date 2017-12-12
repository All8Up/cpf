//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO.hpp"


namespace CPF
{
	namespace IO
	{
		CPF_EXPORT bool Glob(const char *pattern, const char *inString);
		CPF_EXPORT bool Glob(const wchar_t *pattern, const wchar_t *inString);
	}
}
