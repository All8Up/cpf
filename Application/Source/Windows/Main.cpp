//////////////////////////////////////////////////////////////////////////
#include "Application/Application.hpp"
#include "Application/Arguments.hpp"
#include "String.hpp"
#include "StringUtils.hpp"
#include <vector>


extern Cpf::Application::ApplicationCreate gs_ApplicationCreate;

int main(int argc, char** argv)
{
	auto app = gs_ApplicationCreate();
//	app->GetCommandLine().parse(argc, argv);
	auto result = app->Start(app->GetCommandLine());
	delete app;

	return result;
}


#if CPF_TARGET_WINDOWS
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int)
{
	(void)hInstance; (void)hPrevInstance;
	auto app = gs_ApplicationCreate();

	std::string argString(::GetCommandLineA());
	std::vector<std::string> args;

	for (auto it=argString.cbegin(); it!=argString.cend();)
	{
		auto next = Cpf::FindAnyOf(it, argString.end(), std::string(" "));
		if (it == next)
			++it;
		else
			it = next;
	}
//	app->CommandLine().parse(Cpf::String(::GetCommandLineA()));
	auto result = app->Start(app->GetCommandLine());
	delete app;

	return result;
}


bool Cpf::WindowedApplication::Poll()
{
	if (IsRunning())
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				Quit();
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		return true;
	}
	return false;
}


bool Cpf::WindowedApplication::Wait()
{
	if (IsRunning())
	{
		MSG msg;
		if (GetMessage(&msg, nullptr, NULL, NULL))
		{
			if (msg.message == WM_QUIT)
			{
				Quit();
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		return true;
	}
	return false;
}

#endif
