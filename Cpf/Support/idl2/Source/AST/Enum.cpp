//////////////////////////////////////////////////////////////////////////
#include "AST/Enum.hpp"

using namespace AST;

//////////////////////////////////////////////////////////////////////////
EnumItem::EnumItem(const std::string& name, uint64_t value)
	: mName(name)
	, mValue(value)
{}


//////////////////////////////////////////////////////////////////////////
std::shared_ptr<Enum> Enum::Create(const std::string& name)
{
	return std::shared_ptr<Enum>(new Enum(name));
}

std::shared_ptr<Enum> Enum::Create(const std::string& name, IntegralType type)
{
	return std::shared_ptr<Enum>(new Enum(name, type));
}

Enum::Enum(const std::string& name)
	: mName(name)
	, mType(IntegralType::Unknown)
{}

Enum::Enum(const std::string& name, IntegralType type)
	: mName(name)
	, mType(type)
{}
