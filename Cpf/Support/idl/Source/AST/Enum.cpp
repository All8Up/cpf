//////////////////////////////////////////////////////////////////////////
#include "AST/Enum.hpp"

using namespace AST;

//////////////////////////////////////////////////////////////////////////
EnumItem::EnumItem(const std::string& name, uint64_t value)
	: mName(name)
	, mValue(value)
{}


//////////////////////////////////////////////////////////////////////////
Enum::Enum(const ScopeVector& scope, const std::string& name)
	: Symbol(scope, name)
	, mType(IntegralType::Unknown)
{}

Enum::Enum(const ScopeVector& scope, const std::string& name, IntegralType type)
	: Symbol(scope, name)
	, mType(type)
{}
