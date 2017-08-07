//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParser.h"
#include "AST/Enum.hpp"

namespace IDL
{
	AST::EnumItemArray GetEnumValues(IDLParser::Enum_elementsContext* context);
}
