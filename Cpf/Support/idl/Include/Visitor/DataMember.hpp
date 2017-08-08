//////////////////////////////////////////////////////////////////////////
#pragma once
#include "AST/Struct.hpp"
#include "IDLParser.h"
#include "AST/SymbolTable.hpp"


namespace IDL
{
	AST::DataMemberVector GetDataMembers(IDLParser::Struct_declContext *context);
}
