//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Configuration/Configuration.hpp>


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_REFCOUNT
#		define CPF_EXPORT_REFCOUNT
#	else // CPF_STATIC_REFCOUNT
#		if CPF_BUILD_REFCOUNT
#			define CPF_EXPORT_REFCOUNT CPF_EXPORT
#		else
#			define CPF_EXPORT_REFCOUNT CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_REFCOUNT CPF_EXPORT
#	else
#		define CPF_EXPORT_REFCOUNT
#	endif
#endif // CPF_TARGET_WINDOWS


namespace Cpf
{
	struct RefCountInitializer
	{
		CPF_EXPORT_REFCOUNT static int Install();
		CPF_EXPORT_REFCOUNT static int Remove();

	private:
		RefCountInitializer() = delete;
		~RefCountInitializer() = delete;
	};
}
