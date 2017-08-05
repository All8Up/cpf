//////////////////////////////////////////////////////////////////////////
#include "AST/Interface.hpp"

using namespace AST;

Interface::Interface(const ScopeVector& scope, const std::string& name)
	: Symbol(scope, name)
{}
