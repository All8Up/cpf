//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "String.hpp"
#include "RefCount.hpp"
#include "Platform/SharedLibrary.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_SHAREDLIBRARY
#		define CPF_EXPORT_SHAREDLIBRARY
#	else // CPF_STATIC_SHAREDLIBRARY
#		if CPF_BUILD_SHAREDLIBRARY
#			define CPF_EXPORT_SHAREDLIBRARY CPF_EXPORT
#		else
#			define CPF_EXPORT_SHAREDLIBRARY CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_SHAREDLIBRARY CPF_EXPORT
#	else
#		define CPF_EXPORT_SHAREDLIBRARY
#	endif
#endif // CPF_TARGET_WINDOWS


namespace Cpf
{
	namespace Platform
	{
		class CPF_EXPORT_SHAREDLIBRARY SharedLibrary : public tRefCounted<>
		{
		public:
			using Ptr_t = IntrusivePtr<SharedLibrary>;

			SharedLibrary(const String& name);
			SharedLibrary(SharedLibrary&& rhs);
			virtual ~SharedLibrary();

			operator bool() const;

			void* Find(const String& name);

			template<typename FUNC>
			FUNC Get(const String& name)
			{
				return reinterpret_cast<FUNC>(Find(name));
			}

		private:
			CPF_DLL_SAFE_BEGIN;
			String mLibraryName;
			CPF_DLL_SAFE_END;
			LibraryPtr mpLibrary;
		};
	}
}
