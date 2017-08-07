//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParser.h"
#include "AST/Types.hpp"

namespace IDL
{
	uint64_t GetIntegerLiteral(IDLParser::Integer_litContext* context);
	double GetFloatLiteral(IDLParser::Float_litContext* context);
	AST::IntegralType GetType(IDLParser::Integral_typeContext* ctx);
}
