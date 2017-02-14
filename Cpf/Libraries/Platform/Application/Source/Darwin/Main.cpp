//////////////////////////////////////////////////////////////////////////
#include "Application/Application.hpp"
#include "Application/Arguments.hpp"


extern Cpf::Application::ApplicationCreate gs_ApplicationCreate;

int main(int argc, char** argv)
{
	auto app = gs_ApplicationCreate();
//	app->GetCommandLine().parse(argc, argv);
	auto result = app->Start(app->GetCommandLine());
	delete app;

	return result;
}
