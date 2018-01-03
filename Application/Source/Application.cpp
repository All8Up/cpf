//////////////////////////////////////////////////////////////////////////
#include "CPF/Application.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Plugin/Registry.hpp"
#include "CPF/Logging.hpp"
#include "CPF/IntrusivePtr.hpp"
#include <gflags/gflags.h>

using namespace CPF;

int main(int argc, char** argv)
{
	IntrusivePtr<Plugin::iRegistry> registry;
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	CPF_INIT_LOGGING(argc, argv[0]);
	if (GOM::Succeeded(PluginHost::CreateRegistry(registry.AsTypePP())))
	{
		CPF_INSTALL_STATIC_PLUGIN(registry, Application);
		CPF::IntrusivePtr<iApplication> application;
		if (GOM::Succeeded(registry->Create(nullptr, iApplication::kCID.GetID(), iApplication::kIID.GetID(), application.AsVoidPP())))
		{
			registry->InstanceInstall(iApplication::kIID.GetID(), application);
			int32_t result = application->Run();
			registry->InstanceRemove(iApplication::kIID.GetID());
			return result;
		}
	}
	return -1;
}

#if CPF_TARGET_WINDOWS
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int)
{
	(void)hInstance; (void)hPrevInstance;
	CPF_INIT_LOGGING(0, "");

	IntrusivePtr<Plugin::iRegistry> registry;
	if (GOM::Succeeded(PluginHost::CreateRegistry(registry.AsTypePP())))
	{
		CPF_INSTALL_STATIC_PLUGIN(registry, Application);
		IntrusivePtr<iApplication> application;
		if (GOM::Succeeded(registry->Create(nullptr, iApplication::kCID.GetID(), iApplication::kIID.GetID(), application.AsVoidPP())))
		{
			registry->InstanceInstall(iApplication::kIID.GetID(), application);
			int32_t result = application->Run();
			registry->InstanceRemove(iApplication::kIID.GetID());
			return result;
		}
	}
	return -1;
}
#endif
