//////////////////////////////////////////////////////////////////////////
#pragma once
#include "../../Generated/IDLParser.h"
#include "IDLTree/Enum.hpp"


namespace IDL
{
	IDLTree::EnumItemArray GetEnumValues(IDLParser::Enum_elementsContext* context);
}
