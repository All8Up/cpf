//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "rapidjson/document.h"

#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_RESOURCES
#		define CPF_EXPORT_RESOURCES
#	else // CPF_STATIC_RESOURCES
#		if CPF_BUILD_RESOURCES
#			define CPF_EXPORT_RESOURCES CPF_EXPORT
#		else
#			define CPF_EXPORT_RESOURCES CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_RESOURCES CPF_EXPORT
#	else
#		define CPF_EXPORT_RESOURCES
#	endif
#endif // CPF_TARGET_WINDOWS

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Resources
	{
		struct ResourcesInitializer
		{
			CPF_EXPORT_RESOURCES static int Install();
			CPF_EXPORT_RESOURCES static int Remove();

		private:
			ResourcesInitializer() = delete;
			~ResourcesInitializer() = delete;
		};
	}
}
