//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLTree/Struct.hpp"
#include "IDLTree/SymbolTable.hpp"
#include "../../Generated/IDLParser.h"


namespace IDL
{
	IDLTree::DataMemberVector GetDataMembers(IDLParser::Struct_declContext *context);
}
