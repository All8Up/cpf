//////////////////////////////////////////////////////////////////////////
#pragma once
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
				return ::LoadLibraryA(name);
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
