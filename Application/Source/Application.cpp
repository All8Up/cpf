//////////////////////////////////////////////////////////////////////////
#include "CPF/Application.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Plugin/Registry.hpp"

using namespace CPF;

int main(int argc, char** argv)
{
	IntrusivePtr<Plugin::iRegistry> registry;
	if (GOM::Succeeded(PluginHost::CreateRegistry(registry.AsTypePP())))
	{
		CPF_INSTALL_STATIC_PLUGIN(registry, Application);
		CPF::IntrusivePtr<iApplication> application;
		if (GOM::Succeeded(registry->Create(nullptr, iApplication::kCID.GetID(), iApplication::kIID.GetID(), application.AsVoidPP())))
		{
			return application->Run();
		}
	}
	return -1;
}

#if 0
#include "CPF/Application/iWindowedApplication.hpp"
#include "Application/iApplicationMain.hpp"
#include "String.hpp"
#include "StringUtils.hpp"
#include <vector>
#include "PluginHost/Registry.hpp"
#include "CPF/Logging.hpp"

#if CPF_TARGET_WINDOWS
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int)
{
	(void)hInstance; (void)hPrevInstance;
	CPF_INIT_LOGGING(0, "");
	auto app = gs_AppMainCreate();
	if (app)
	{
		auto result = RunApplication(app);
		return CPF::GOM::Succeeded(result) ? 0 : -int(result & 0x7FFF);
	}
	return -int(CPF::GOM::kOutOfMemory & 0x7FFF);
}
#endif
#endif
