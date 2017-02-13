//////////////////////////////////////////////////////////////////////////
#pragma once


//////////////////////////////////////////////////////////////////////////
#include <Configuration/Configuration.hpp>


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_SIMD
#		define CPF_EXPORT_SIMD
#	else // CPF_STATIC_SIMD
#		if CPF_BUILD_SIMD
#			define CPF_EXPORT_SIMD CPF_EXPORT
#		else
#			define CPF_EXPORT_SIMD CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_SIMD CPF_EXPORT
#	else
#		define CPF_EXPORT_SIMD
#	endif
#endif // CPF_TARGET_WINDOWS


//////////////////////////////////////////////////////////////////////////
#include <Simd/Types.hpp>
