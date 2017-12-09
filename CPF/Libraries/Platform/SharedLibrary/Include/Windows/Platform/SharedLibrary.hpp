namespace Cpf
{
	namespace Platform
	{
		using LibraryPtr = HMODULE;
		inline LibraryPtr Load(const char* const name)
		{
			return ::LoadLibrary(name);
		}
		inline void Unload(LibraryPtr ptr)
		{
			::FreeLibrary(ptr);
		}
		inline void* FindSymbol(LibraryPtr ptr, const char* const name)
		{
			return ::GetProcAddress(ptr, name);
		}
	}
}
