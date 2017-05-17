//////////////////////////////////////////////////////////////////////////
#include "Application/iWindowedApplication.hpp"
#include "Application/iApplicationMain.hpp"
#include "String.hpp"
#include "StringUtils.hpp"
#include <vector>
#include "PluginHost/Registry.hpp"


extern Cpf::iApplicationMain::AppMainCreate gs_AppMainCreate;

namespace
{
	Cpf::GOM::Result RunApplication(Cpf::iApplicationMain* appMain)
	{
		if (appMain)
		{
			Cpf::Plugin::iRegistry* registry = nullptr;
			Cpf::GOM::Result result;
			if (Cpf::GOM::Succeeded(result = Cpf::PluginHost::CreateRegistry(&registry)))
			{
				Cpf::GOM::ClassID appId;
				if (Cpf::GOM::Succeeded(appMain->Initialize(registry, &appId)))
				{
					Cpf::IntrusivePtr<Cpf::iApplication> app;
					if (Cpf::GOM::Succeeded(result = registry->Create(nullptr, appId, Cpf::iApplication::kIID, app.AsVoidPP())))
					{
						if (Cpf::GOM::Succeeded(app->Initialize(registry, appMain)))
							result = app->Run();
					}
				}
				appMain->Shutdown();
			}
			appMain->Release();
			return result;
		}
		return Cpf::GOM::kOutOfMemory;
	}
}


int main(int argc, char** argv)
{
	(void)argc; (void)argv;
	auto app = gs_AppMainCreate();
	if (app)
	{
		auto result = RunApplication(app);
		return Cpf::GOM::Succeeded(result) ? 0 : -int(result.Value);
	}
	return -int(Cpf::GOM::kOutOfMemory.Value);
}


#if CPF_TARGET_WINDOWS
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int)
{
	(void)hInstance; (void)hPrevInstance;
	auto app = gs_AppMainCreate();
	if (app)
	{
		auto result = RunApplication(app);
		return Cpf::GOM::Succeeded(result) ? 0 : -int(result.Value);
	}
	return -int(Cpf::GOM::kOutOfMemory.Value);
}
#endif
