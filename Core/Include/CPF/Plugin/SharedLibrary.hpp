//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Logging.hpp"
#include <Windows.h>

namespace CPF
{
	namespace Platform
	{
		namespace Library
		{
			using Handle = HMODULE;
			static constexpr Handle kInvalid = nullptr;

			Handle Load(const char* const name);
			void Free(Handle);
			void* GetAddress(Handle, const char* const);


			inline
			Handle Load(const char* const name)
			{
				Handle handle = ::LoadLibraryA(name);
				/*
				if (handle == Platform::Library::kInvalid)
				{
					DWORD result = ::GetLastError();
					CPF_LOG(Core, Info) << "Windows error code: " << result;
				}
				*/
				return handle;
			}

			inline
			void Free(Handle lib)
			{
				::FreeLibrary(lib);
			}

			inline
			void* GetAddress(Handle lib, const char* const symbol)
			{
				return ::GetProcAddress(lib, symbol);
			}
		}
	}
}
