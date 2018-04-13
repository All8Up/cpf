//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <string>

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace STD
	{
		template<typename CHAR_TYPE>
		using BasicString = std::basic_string<CHAR_TYPE>;
		using String = std::string;
		using WString = std::wstring;
	}
}
