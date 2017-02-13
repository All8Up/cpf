//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "EASTL/string.h"
#include <ostream>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename CHAR_TYPE>
	using BasicString = eastl::basic_string<CHAR_TYPE>;
	using String = eastl::string8;
	using WString = eastl::wstring;
}


namespace eastl {
	inline
	std::ostream &operator<<(std::ostream &os, const Cpf::String &val) {
		os << val.c_str();
		return os;
	}


	inline
	std::ostream &operator<<(std::ostream &os, const Cpf::WString &val) {
		os << val.c_str();
		return os;
	}
}
