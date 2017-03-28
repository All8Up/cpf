//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_CONCURRENCY
#		define CPF_EXPORT_CONCURRENCY
#	else // CPF_STATIC_CONCURRENCY
#		if CPF_BUILD_CONCURRENCY
#			define CPF_EXPORT_CONCURRENCY CPF_EXPORT
#		else
#			define CPF_EXPORT_CONCURRENCY CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_CONCURRENCY CPF_EXPORT
#	else
#		define CPF_EXPORT_CONCURRENCY
#	endif
#endif // CPF_TARGET_WINDOWS


namespace Cpf
{
	namespace Concurrency
	{
		class Scheduler;
	}

	struct ConcurrencyInitializer
	{
		CPF_EXPORT_CONCURRENCY static int Install();
		CPF_EXPORT_CONCURRENCY static int Remove();

	private:
		ConcurrencyInitializer() = delete;
		~ConcurrencyInitializer() = delete;
	};
}
