//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


//////////////////////////////////////////////////////////////////////////
// Setup the shared library export mechanism.
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_TIME
#		define CPF_EXPORT_TIME
#	else // CPF_STATIC_TIME
#		if CPF_BUILD_TIME
#			define CPF_EXPORT_TIME CPF_EXPORT
#		else
#			define CPF_EXPORT_TIME CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_TIME CPF_EXPORT
#	else
#		define CPF_EXPORT_TIME
#	endif
#endif // CPF_TARGET_WINDOWS



//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Platform
	{
		//////////////////////////////////////////////////////////////////////////
		/// Initialize the time library.
		//////////////////////////////////////////////////////////////////////////
		struct TimeInitializer
		{
			CPF_EXPORT_TIME static int Install();
			CPF_EXPORT_TIME static int Remove();

		private:
			TimeInitializer() = delete;
			~TimeInitializer() = delete;
		};
	}
}
