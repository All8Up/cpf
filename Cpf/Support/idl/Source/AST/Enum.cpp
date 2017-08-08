//////////////////////////////////////////////////////////////////////////
#include "AST/Enum.hpp"

using namespace AST;

//////////////////////////////////////////////////////////////////////////
EnumItem::EnumItem(const std::string& name)
	: mName(name)
	, mValue(0)
{
}

EnumItem::EnumItem(const std::string& name, uint64_t value)
	: mName(name)
	, mValue(value)
{}


//////////////////////////////////////////////////////////////////////////
Enum::Enum(const ScopeVector& scope, const std::string& name)
	: Symbol(scope, name)
	, mType(AllTypes::Unknown)
{}

Enum::Enum(const ScopeVector& scope, const std::string& name, AllTypes type)
	: Symbol(scope, name)
	, mType(type)
{}

std::string Enum::ToString() const
{
	std::string result = "Enum: " + GetName() + "\n";
	for (const auto& item : mItems)
	{
		result += "  " + item.GetName() + " - ";
		result += std::to_string(item.GetValue()) + "\n";
	}
	return result;
}
