//////////////////////////////////////////////////////////////////////////
#pragma once
#define NOCOMM
#ifndef STRICT
#	define STRICT
#endif
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>

#define CPF_DLL_SAFE_BEGIN __pragma(warning(push))	\
	__pragma(warning(disable:4251))
#define CPF_DLL_SAFE_END __pragma(warning(pop))

#define CPF_CDECL __cdecl
