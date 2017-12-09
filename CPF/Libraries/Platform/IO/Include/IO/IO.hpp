//
#pragma once
#include "CPF/Configuration.hpp"


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
namespace CPF
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


		//////////////////////////////////////////////////////////////////////////
		enum class Access : int32_t;
		enum class Origin : int32_t;
	}
}

#include "CPF/IO/Attributes.hpp"
#include "CPF/IO/Access.hpp"
#include "CPF/IO/Origin.hpp"
