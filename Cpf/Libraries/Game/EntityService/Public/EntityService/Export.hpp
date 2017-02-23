//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ENTITYSERVICE
#		define CPF_EXPORT_ENTITYSERVICE
#	else // CPF_STATIC_ENTITYSERVICE
#		if CPF_BUILD_ENTITYSERVICE
#			define CPF_EXPORT_ENTITYSERVICE CPF_EXPORT
#		else
#			define CPF_EXPORT_ENTITYSERVICE CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_ENTITYSERVICE CPF_EXPORT
#	else
#		define CPF_EXPORT_ENTITYSERVICE
#	endif
#endif // CPF_TARGET_WINDOWS
