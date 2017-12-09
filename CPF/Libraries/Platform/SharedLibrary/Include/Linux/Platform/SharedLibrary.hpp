
#include <dlfcn.h>

namespace Cpf
{
	namespace Platform
	{
		using LibraryPtr = void*;
		inline LibraryPtr Load(const char* const name)
		{
			return ::dlopen(name, RTLD_NOW);
		}
		inline void Unload(LibraryPtr ptr)
		{
			::dlclose(ptr);
		}
		inline void* FindSymbol(LibraryPtr ptr, const char* const name)
		{
			return ::dlsym(ptr, name);
		}
	}
}
