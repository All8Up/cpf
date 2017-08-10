//////////////////////////////////////////////////////////////////////////
#pragma once
#include "../../Generated/IDLParser.h"
#include "IDLTree/Types.hpp"


namespace IDL
{
	uint64_t GetIntegerLiteral(IDLParser::Integer_litContext* context);
	double GetFloatLiteral(IDLParser::Float_litContext* context);
	IDLTree::AllTypes GetType(IDLParser::Integral_typeContext* ctx);
}
