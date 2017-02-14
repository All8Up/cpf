//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_JSON
#		define CPF_EXPORT_JSON
#	else // CPF_STATIC_JSON
#		if CPF_BUILD_JSON
#			define CPF_EXPORT_JSON CPF_EXPORT
#		else
#			define CPF_EXPORT_JSON CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_JSON CPF_EXPORT
#	else
#		define CPF_EXPORT_JSON
#	endif
#endif // CPF_TARGET_WINDOWS


namespace Cpf
{
	namespace Platform
	{
		class CPF_EXPORT_JSON Json
		{
		public:
			Json();
			~Json();

			bool Parse(const char* json);

		private:
			using Doc = void*;
			Doc mpDocument;
		};
	}
}
