//////////////////////////////////////////////////////////////////////////
#pragma once
#include <dlfcn.h>

namespace Cpf
{
	namespace Platform
	{
		namespace Library
		{
			using Handle = void*;
			static constexpr Handle kInvalid = nullptr;

			Handle Load(const char* const name);

			void Free(Handle);

			void* GetAddress(Handle, const char* const);

			inline
			Handle Load(const char* const name)
			{
				return ::dlopen(name, RTLD_NOW);
			}

			inline
			void Free(Handle lib)
			{
				::dlclose(lib);
			}

			inline
			void* GetAddress(Handle lib, const char* const symbol)
			{
				return ::dlsym(lib, symbol);
			}
		}
	}
}
