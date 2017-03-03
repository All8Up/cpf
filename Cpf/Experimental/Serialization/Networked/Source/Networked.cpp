#include "Networked.hpp"
#include "Logging/Logging.hpp"
#include "asio.hpp"

using namespace Cpf;

//////////////////////////////////////////////////////////////////////////
Networked::Networked()
{}

Networked::~Networked()
{}

int Networked::Start(const CommandLine&)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
CPF_CREATE_APPLICATION(Cpf::Networked);
