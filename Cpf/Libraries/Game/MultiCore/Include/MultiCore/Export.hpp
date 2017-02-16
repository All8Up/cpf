//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_MULTICORE
#		define CPF_EXPORT_MULTICORE
#	else // CPF_STATIC_MULTICORE
#		if CPF_BUILD_MULTICORE
#			define CPF_EXPORT_MULTICORE CPF_EXPORT
#		else
#			define CPF_EXPORT_MULTICORE CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_MULTICORE CPF_EXPORT
#	else
#		define CPF_EXPORT_MULTICORE
#	endif
#endif // CPF_TARGET_WINDOWS
