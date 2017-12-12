//////////////////////////////////////////////////////////////////////////
#define CPF_PLUGIN_STATIC
#include "CPF/Plugin.hpp"
#include "CPF/Application.hpp"
#include "CPF/Plugin/tClassFactory.hpp"

// NOTE: This app type is only really different on Win32 due to the different main.
using namespace CPF;

class BasicConsoleApp : public GOM::tUnknown<iApplication>
{
public:
	BasicConsoleApp(Plugin::iRegistry* registry, iUnknown*)
		: mpRegistry(registry)
	{}

	int32_t Run() override
	{
		return 0;
	}

private:
	IntrusivePtr<Plugin::iRegistry> mpRegistry;
};

CPF_APPLICATION(BasicConsoleApp);
