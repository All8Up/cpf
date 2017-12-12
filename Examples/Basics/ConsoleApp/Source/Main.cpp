//////////////////////////////////////////////////////////////////////////
#define CPF_PLUGIN_STATIC
#include "CPF/Plugin.hpp"
#include "CPF/Application.hpp"
#include "CPF/Plugin/tClassFactory.hpp"

using namespace CPF;

class BasicConsoleApp : public tRefCounted<iApplication>
{
public:
	BasicConsoleApp(Plugin::iRegistry* registry, iUnknown*)
		: mpRegistry(registry)
	{}

	GOM::Result CPF_STDCALL QueryInterface(uint64_t iid, void** outIface)
	{
		if (outIface)
		{
			switch (iid)
			{
			case iUnknown::kIID.GetID():
				*outIface = static_cast<iUnknown*>(this);
				break;

			case iApplication::kIID.GetID():
				*outIface = static_cast<iApplication*>(this);
				break;
			default:
				*outIface = nullptr;
				return GOM::kUnknownInterface;
			}
			AddRef();
			return GOM::kOK;
		}
		return GOM::kInvalidParameter;
	}

	int32_t Run() override
	{
		return 0;
	}

	Plugin::iRegistry* GetRegistry() { return mpRegistry; }

private:
	IntrusivePtr<Plugin::iRegistry> mpRegistry;
};


static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Install(iApplication::kCID.GetID(), new Plugin::tClassFactory<BasicConsoleApp>());
	}
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Remove(iApplication::kCID.GetID());
	}
	return GOM::kInvalidParameter;
}

PluginDesc PluginRegistration_Application = { "Application",
	&Install,
	&Remove
};
