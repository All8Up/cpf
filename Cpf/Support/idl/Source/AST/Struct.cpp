//////////////////////////////////////////////////////////////////////////
#include "AST/Struct.hpp"

using namespace AST;

Struct::Struct(const ScopeVector& scope, const std::string& name)
	: Symbol(scope, name)
{}

Struct::~Struct()
{}
