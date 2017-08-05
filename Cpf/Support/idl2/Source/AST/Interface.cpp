//////////////////////////////////////////////////////////////////////////
#include "AST/Interface.hpp"

using namespace AST;

std::shared_ptr<Interface> Interface::Create(const std::string& name)
{
	return std::shared_ptr<Interface>(new Interface(name));
}

Interface::Interface(const std::string& name)
	: mName(name)
{}
