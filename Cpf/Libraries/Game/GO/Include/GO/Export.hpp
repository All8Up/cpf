//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_GO
#		define CPF_EXPORT_GO
#	else // CPF_STATIC_GO
#		if CPF_BUILD_GO
#			define CPF_EXPORT_GO CPF_EXPORT
#		else
#			define CPF_EXPORT_GO CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_GO CPF_EXPORT
#	else
#		define CPF_EXPORT_GO
#	endif
#endif // CPF_TARGET_WINDOWS
