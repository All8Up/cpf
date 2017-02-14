//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_HASH
#		define CPF_EXPORT_HASH
#	else // CPF_STATIC_HASH
#		if CPF_BUILD_HASH
#			define CPF_EXPORT_HASH CPF_EXPORT
#		else
#			define CPF_EXPORT_HASH CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_HASH CPF_EXPORT
#	else
#		define CPF_EXPORT_HASH
#	endif
#endif // CPF_TARGET_WINDOWS


namespace Cpf
{
	namespace Platform
	{
		//////////////////////////////////////////////////////////////////////////
		struct HashInitializer
		{
			CPF_EXPORT_HASH static int Install();
			CPF_EXPORT_HASH static int Remove();

		private:
			HashInitializer() = delete;
			~HashInitializer() = delete;
		};
	}
}
