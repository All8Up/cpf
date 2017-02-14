//
#pragma once
#include "Configuration.hpp"


#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_IO
#		define CPF_EXPORT_IO
#	else // CPF_STATIC_IO
#		if CPF_BUILD_IO
#			define CPF_EXPORT_IO CPF_EXPORT
#		else
#			define CPF_EXPORT_IO CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_IO CPF_EXPORT
#	else
#		define CPF_EXPORT_IO
#	endif
#endif // CPF_TARGET_WINDOWS



//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Platform
	{
		struct IOInitializer
		{
			CPF_EXPORT_IO static int Install();
			CPF_EXPORT_IO static int Remove();

		private:
			IOInitializer() = delete;
			~IOInitializer() = delete;
		};


		namespace IO
		{
			//////////////////////////////////////////////////////////////////////////
			class Stream;


			/** @brief Error type enumeration. */
			enum class Error : int64_t
			{
				eNone = 0,
				eUnknownError = -1,
				eOutOfMemory = 1,
				eInvalidFile
			};


			/** @brief File attributes. */
			namespace Attributes
			{
				enum
				{
					eFile = 1 << 0,
					eDirectory = 1 << 1,
					eHidden = 1 << 2,
					eReadOnly = 1 << 3
				};
			}


			//////////////////////////////////////////////////////////////////////////
			enum class StreamAccess : int64_t;
			enum class StreamOrigin : int64_t;
		}
	}
}
