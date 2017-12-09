//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_PLATFORM
#		define CPF_EXPORT_PLATFORM
#	else
#		if CPF_BUILD_PLATFORM
#			define CPF_EXPORT_PLATFORM CPF_EXPORT
#		else
#			define CPF_EXPORT_PLATFORM CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_PLATFORM CPF_EXPORT
#	else
#		define CPF_EXPORT_PLATFORM
#	endif
#endif // CPF_TARGET_WINDOWS
