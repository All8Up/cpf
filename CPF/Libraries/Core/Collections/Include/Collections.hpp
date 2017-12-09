//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_COLLECTIONS
#		define CPF_EXPORT_COLLECTIONS
#	else // CPF_STATIC_COLLECTIONS
#		if CPF_BUILD_COLLECTIONS
#			define CPF_EXPORT_COLLECTIONS CPF_EXPORT
#		else
#			define CPF_EXPORT_COLLECTIONS CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_COLLECTIONS CPF_EXPORT
#	else
#		define CPF_EXPORT_COLLECTIONS
#	endif
#endif // CPF_TARGET_WINDOWS
