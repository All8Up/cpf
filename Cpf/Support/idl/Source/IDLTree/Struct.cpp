//////////////////////////////////////////////////////////////////////////
#include "IDLTree/Struct.hpp"

using namespace IDLTree;

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
	for (const auto& item : mDataMembers)
	{
		result += "  " + item.GetName() + " - " + TypeString(item.GetType().mType) + "\n";
	}
	return result;
}
