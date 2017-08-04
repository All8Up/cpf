//////////////////////////////////////////////////////////////////////////
#include "AST/Import.hpp"

using namespace AST;

std::shared_ptr<Import> Import::Create(const std::string& module)
{
	std::shared_ptr<Import> result(new Import(module));
	return result;
}

Import::Import(const std::string& module)
	: mModule(module)
{
}
