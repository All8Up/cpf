//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO.hpp"

namespace CPF
{
	namespace STD
	{
		class Utf8String;
	}
	namespace IO
	{
		CPF_EXPORT bool Glob(const STD::Utf8String& pattern, const STD::Utf8String& value);
	}
}
