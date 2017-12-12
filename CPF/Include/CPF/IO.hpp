//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	struct IOInitializer
	{
		CPF_EXPORT static int Install();
		CPF_EXPORT static int Remove();

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
