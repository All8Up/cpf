//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_PLATFORM
#		define CPF_EXPORT_PLATFORM
#	else
#		if CPF_BUILD_PLATFORM
#			define CPF_EXPORT_PLATFORM CPF_EXPORT
#		else
#			define CPF_EXPORT_PLATFORM CPF_IMPORT
#		endif
#	endif
#else
#		define CPF_EXPORT_PLATFORM CPF_EXPORT
#endif


namespace Cpf
{
	struct PlatformInitializer
	{
	public:
		CPF_EXPORT_PLATFORM static bool Install();
		CPF_EXPORT_PLATFORM static bool Remove();

	private:
		PlatformInitializer() = delete;
		~PlatformInitializer() = delete;
	};
}
