//////////////////////////////////////////////////////////////////////////
#include "AST/Struct.hpp"

using namespace AST;

std::shared_ptr<Struct> Struct::Create(const std::string& name)
{
	return std::shared_ptr<Struct>(new Struct(name));
}

Struct::Struct(const std::string& name)
	: mName(name)
{}
