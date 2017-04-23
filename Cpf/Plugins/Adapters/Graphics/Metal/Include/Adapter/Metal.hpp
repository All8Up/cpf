//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ADAPTERS_METAL
#		define CPF_EXPORT_ADAPTERS_METAL
#	else
#		if CPF_STATIC_ADAPTERS_METAL
#			define CPF_EXPORT_ADAPTERS_METAL CPF_EXPORT
#		else
#			define CPF_EXPORT_ADAPTERS_METAL CPF_IMPORT
#		endif
#	endif
#else
#	if __GNUC__ >= 4
#		define CPF_EXPORT_ADAPTERS_METAL CPF_EXPORT
#	else
#		define CPF_EXPORT_ADAPTERS_METAL
#	endif
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Adapters
	{
		struct MetalInitializer
		{
			CPF_EXPORT_ADAPTERS_METAL static int Install();
			CPF_EXPORT_ADAPTERS_METAL static int Remove();

		private:
			MetalInitializer() = delete;
			~MetalInitializer() = delete;
		};
	}
}
