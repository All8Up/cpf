//////////////////////////////////////////////////////////////////////////
#include "AST/Const.hpp"

using namespace AST;

std::shared_ptr<Const> Const::Create(const std::string& name, uint64_t value)
{
	return std::shared_ptr<Const>(new Const(name, value));
}

std::shared_ptr<Const> Const::Create(const std::string& name, double value)
{
	return std::shared_ptr<Const>(new Const(name, value));
}

std::shared_ptr<Const> Const::Create(const std::string& name, Type type, const std::string& value)
{
	return std::shared_ptr<Const>(new Const(name, type, value));
}

Const::Const(const std::string& name, uint64_t value)
	: mType(Type::eIntegral)
	, mName(name)
{
	mUInt64 = value;
}

Const::Const(const std::string& name, double value)
	: mType(Type::eFloat)
	, mName(name)
{
	mDouble = value;
}

Const::Const(const std::string& name, Type type, const std::string& value)
	: mType(type)
	, mName(name)
{
	mpString = new char[value.length() + 1];
	::strcpy(mpString, value.c_str());
}

Const::~Const()
{
	if (mType == Type::eString || mType == Type::eClassID)
		delete[] mpString;
}
