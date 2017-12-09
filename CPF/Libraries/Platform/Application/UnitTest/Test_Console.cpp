//////////////////////////////////////////////////////////////////////////
#include "Application/Application.hpp"
#include "Application/Arguments.hpp"


int Cpf::Core::Application::Main(const Arguments& args)
{
	for (size_t i = 0; i < args.Size(); ++i)
	{
		printf("%s\n", args[i].c_str());
	}

	return 0;
}
