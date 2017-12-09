//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "IO/FileSystem.hpp"
#include "Move.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ANSI_C_FILESYSTEM
#		define CPF_EXPORT_ANSI_C_FILESYSTEM
#	else
#		if CPF_BUILD_ANSI_C_FILESYSTEM
#			define CPF_EXPORT_ANSI_C_FILESYSTEM CPF_EXPORT
#		else
#			define CPF_EXPORT_ANSI_C_FILESYSTEM CPF_IMPORT
#		endif
#	endif
#else
#		define CPF_EXPORT_ANSI_C_FILESYSTEM CPF_EXPORT
#endif
