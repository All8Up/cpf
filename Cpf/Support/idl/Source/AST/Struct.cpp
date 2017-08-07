//////////////////////////////////////////////////////////////////////////
#include "AST/Struct.hpp"

using namespace AST;

//////////////////////////////////////////////////////////////////////////
DataMember::DataMember(const std::string& name)
	: mName(name)
{}


//////////////////////////////////////////////////////////////////////////
Struct::Struct(const ScopeVector& scope, const std::string& name)
	: Symbol(scope, name)
{}

Struct::~Struct()
{}

std::string Struct::ToString() const
{
	std::string result = "Struct: " + GetName() + "\n";
	return result;
}
