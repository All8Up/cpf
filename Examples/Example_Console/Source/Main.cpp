//////////////////////////////////////////////////////////////////////////
#include "CPF/Plugin.hpp"
#include "CPF/Application.hpp"
#include "CPF/GOM/tUnknown.hpp"

using namespace CPF;

/** @brief A basic console application.
	Applications are plugins like most things meaning
	that eventually all the examples could be compiled
	into a single executable if desired and selected
	on the fly.
 */
class ExampleCoreConsole : public GOM::tUnknown<iApplication>
{
public:
	int32_t Run() override
	{
		printf("Hello World!");
		return 0;
	}
};

/* Utility macro registers the application as a plugin.
   This only supplies the descriptor and the install/remove
   functions, if it were desired to make these available
   from dll's, the plugin api call will have to be added.
 */
CPF_APPLICATION(ExampleCoreConsole);
