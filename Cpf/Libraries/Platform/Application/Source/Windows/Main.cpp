//////////////////////////////////////////////////////////////////////////
#include "Application/iWindowedApplication.hpp"
#include "Application/iApplicationMain.hpp"
#include "String.hpp"
#include "StringUtils.hpp"
#include <vector>
#include "PluginHost/Registry.hpp"


extern CPF::iApplicationMain::AppMainCreate gs_AppMainCreate;

namespace
{
	CPF::GOM::Result RunApplication(CPF::iApplicationMain* appMain)
	{
		if (appMain)
		{
			CPF::Plugin::iRegistry* registry = nullptr;
			CPF::GOM::Result result;
			if (CPF::GOM::Succeeded(result = CPF::PluginHost::CreateRegistry(&registry)))
			{
				CPF::GOM::ClassID appId;
				if (CPF::GOM::Succeeded(appMain->Initialize(registry, &appId)))
				{
					CPF::IntrusivePtr<CPF::iApplication> app;
					if (CPF::GOM::Succeeded(result = registry->Create(nullptr, appId.GetID(), CPF::iApplication::kIID.GetID(), app.AsVoidPP())))
					{
						if (CPF::GOM::Succeeded(app->Initialize(registry, appMain)))
							result = app->Run();
					}
				}
				appMain->Shutdown();
			}
			appMain->Release();
			return result;
		}
		return CPF::GOM::kOutOfMemory;
	}
}


int main(int argc, char** argv)
{
	(void)argc; (void)argv;
	auto app = gs_AppMainCreate();
	if (app)
	{
		auto result = RunApplication(app);
		return CPF::GOM::Succeeded(result) ? 0 : -int(result&0x7FFF);
	}
	return -int(CPF::GOM::kOutOfMemory & 0x7FFF);
}


#if CPF_TARGET_WINDOWS
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int)
{
	(void)hInstance; (void)hPrevInstance;
	auto app = gs_AppMainCreate();
	if (app)
	{
		auto result = RunApplication(app);
		return CPF::GOM::Succeeded(result) ? 0 : -int(result & 0x7FFF);
	}
	return -int(CPF::GOM::kOutOfMemory & 0x7FFF);
}
#endif
