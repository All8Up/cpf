//////////////////////////////////////////////////////////////////////////
#include "Application/iWindowedApplication.hpp"
#include "Application/iApplicationMain.hpp"
#include "Application/Arguments.hpp"
#include "String.hpp"
#include "StringUtils.hpp"
#include <vector>
#include "PluginHost/Registry.hpp"


extern Cpf::iApplicationMain::AppMainCreate gs_AppMainCreate;

namespace
{
	Cpf::COM::Result RunApplication(Cpf::iApplicationMain* appMain)
	{
		if (appMain)
		{
			Cpf::Plugin::iRegistry* registry = nullptr;
			Cpf::COM::Result result;
			if (Cpf::COM::Succeeded(result = Cpf::PluginHost::CreateRegistry(&registry)))
			{
				Cpf::COM::ClassID appId;
				if (Cpf::COM::Succeeded(appMain->Initialize(registry, &appId)))
				{
					Cpf::IntrusivePtr<Cpf::iApplication> app;
					if (Cpf::COM::Succeeded(result = registry->Create(nullptr, appId, Cpf::iApplication::kIID, app.AsVoidPP())))
					{
						if (Cpf::COM::Succeeded(app->Initialize(registry, appMain)))
							result = app->Run();
					}
				}
				appMain->Shutdown();
			}
			appMain->Release();
			return result;
		}
		return Cpf::COM::kOutOfMemory;
	}
}


int main(int argc, char** argv)
{
	(void)argc; (void)argv;
	auto app = gs_AppMainCreate();
	if (app)
	{
		auto result = RunApplication(app);
		return Cpf::COM::Succeeded(result) ? 0 : -int(result.Value);
	}
	return -int(Cpf::COM::kOutOfMemory.Value);
}


#if CPF_TARGET_WINDOWS
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int)
{
	(void)hInstance; (void)hPrevInstance;
	auto app = gs_AppMainCreate();
	if (app)
	{
		auto result = RunApplication(app);
		return Cpf::COM::Succeeded(result) ? 0 : -int(result.Value);
	}
	return -int(Cpf::COM::kOutOfMemory.Value);
}
#endif
