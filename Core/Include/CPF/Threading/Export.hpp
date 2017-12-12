//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_THREADING
#		define CPF_EXPORT_THREADING
#	else // CPF_STATIC_THREADING
#		if CPF_BUILD_THREADING
#			define CPF_EXPORT_THREADING CPF_EXPORT
#		else
#			define CPF_EXPORT_THREADING CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_THREADING CPF_EXPORT
#	else
#		define CPF_EXPORT_THREADING
#	endif
#endif // CPF_TARGET_WINDOWS
