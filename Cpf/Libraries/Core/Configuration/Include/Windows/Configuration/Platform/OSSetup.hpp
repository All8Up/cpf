//////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef NOCOMM
#	define NOCOMM
#endif
#ifndef STRICT
#	define STRICT
#endif
#ifndef NOMINMAX
#	define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include <Windows.h>

#define CPF_DLL_SAFE_BEGIN __pragma(warning(push))	\
	__pragma(warning(disable:4251))
#define CPF_DLL_SAFE_END __pragma(warning(pop))

#define CPF_CDECL __cdecl
#define CPF_STDCALL __stdcall
#define CPF_VECTORCALL __vectorcall

#define CPF_NOVTABLE __declspec(novtable)

#define CPF_FORCE_INLINE __forceinline
