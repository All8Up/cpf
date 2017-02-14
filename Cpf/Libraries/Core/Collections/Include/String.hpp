//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/string.h"
#	include <ostream>
#else
#	include <string>
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename CHAR_TYPE>
	using BasicString = CPF_STL_NAMESPACE::basic_string<CHAR_TYPE>;
	using String = CPF_STL_NAMESPACE::string;
	using WString = CPF_STL_NAMESPACE::wstring;
}


#ifdef CPF_USE_EASTL
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
#endif
