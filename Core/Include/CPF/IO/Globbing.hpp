//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO.hpp"

namespace CPF
{
	namespace Std
	{
		class Utf8String;
	}
	namespace IO
	{
		CPF_EXPORT bool Glob(const Std::Utf8String& pattern, const Std::Utf8String& value);
	}
}
