//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include "IDLParser.h"
#include "AST/Types.hpp"

namespace IDL
{
	std::string Handle(IDLParser::Qualified_identContext* ctx);
	uint64_t Handle(IDLParser::Integer_litContext* context);
	double Handle(IDLParser::Float_litContext* context);
	AST::IntegralType Handle(IDLParser::Integral_typeContext* ctx);
}
