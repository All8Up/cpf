//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time/Export.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
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
