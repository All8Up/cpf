//////////////////////////////////////////////////////////////////////////
#include "AST/Const.hpp"

using namespace AST;

Const::Const(const ScopeVector& scope, const std::string& name, uint64_t value)
	: Symbol(scope, name)
	, mType(Type::eIntegral)
{
	mUInt64 = value;
}

Const::Const(const ScopeVector& scope, const std::string& name, double value)
	: Symbol(scope, name)
	, mType(Type::eFloat)
{
	mDouble = value;
}

Const::Const(const ScopeVector& scope, const std::string& name, Type type, const std::string& value)
	: Symbol(scope, name)
	, mType(type)
{
	mpString = new char[value.length() + 1];
	::strcpy(mpString, value.c_str());
}

Const::~Const()
{
	if (mType == Type::eString || mType == Type::eClassID)
		delete[] mpString;
}
