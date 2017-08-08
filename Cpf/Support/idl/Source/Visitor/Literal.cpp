//////////////////////////////////////////////////////////////////////////
#include "Visitor/Literal.hpp"

using namespace IDL;

uint64_t IDL::GetIntegerLiteral(IDLParser::Integer_litContext* context)
{
	bool negate = false;
	uint64_t result = 0;
	if (context->BIN_LIT())
	{
		auto binary = context->BIN_LIT();
		auto strValue = binary->toString();
		if (strValue[0] == '-')
		{
			negate = true;
			strValue.erase(strValue.begin());
		}
		if (strValue[0] == '+')
			strValue.erase(strValue.begin());
		// Remove the '0b', it must be there or the parser would not have accepted this rule.
		strValue.erase(strValue.begin(), strValue.begin() + 2);
		for (auto c : strValue)
		{
			result <<= 1;
			if (c == '1')
				result |= 1;
		}
	}
	else if (context->OCT_LIT())
	{
		auto oct = context->OCT_LIT();
		auto strValue = oct->toString();
		if (strValue[0] == '-')
		{
			negate = true;
			strValue.erase(strValue.begin());
		}
		if (strValue[0] == '+')
			strValue.erase(strValue.begin());
		for (auto c : strValue)
		{
			result *= 8;
			result += c - '0';
		}
	}
	else if (context->DECIMAL_LIT())
	{
		auto dec = context->DECIMAL_LIT();
		auto strValue = dec->toString();
		if (strValue[0] == '-')
		{
			negate = true;
			strValue.erase(strValue.begin());
		}
		if (strValue[0] == '+')
			strValue.erase(strValue.begin());
		for (auto c : strValue)
		{
			result *= 10;
			result += c - '0';
		}
	}
	else if (context->HEX_LIT())
	{
		auto hex = context->HEX_LIT();
		auto strValue = hex->toString();
		if (strValue[0] == '-')
		{
			negate = true;
			strValue.erase(strValue.begin());
		}
		if (strValue[0] == '+')
			strValue.erase(strValue.begin());
		// Remove the '0x', it must be there or the parser would not have accepted this rule.
		strValue.erase(strValue.begin(), strValue.begin() + 2);
		for (auto c : strValue)
		{
			result *= 16;
			if (c >= '0' && c <= '9')
				result += c - '0';
			if (c >= 'A' && c <= 'F')
				result += c - 'A' + 10;
			if (c >= 'a' && c <= 'f')
				result += c - 'a' + 10;
		}
	}
	return negate ? uint64_t(-int64_t(result)) : result;
}

double IDL::GetFloatLiteral(IDLParser::Float_litContext* context)
{
	auto f = context->FLOAT_LIT();
	auto strValue = f->toString();
	return ::atof(strValue.c_str());
}

AST::AllTypes IDL::GetType(IDLParser::Integral_typeContext* ctx)
{
	AST::AllTypes result = AST::AllTypes::Unknown;
	if (ctx->U8()) result = AST::AllTypes::U8;
	if (ctx->S8()) result = AST::AllTypes::S8;
	if (ctx->U16()) result = AST::AllTypes::U16;
	if (ctx->S16()) result = AST::AllTypes::S16;
	if (ctx->U32()) result = AST::AllTypes::U32;
	if (ctx->S32()) result = AST::AllTypes::S32;
	if (ctx->U64()) result = AST::AllTypes::U64;
	if (ctx->S64()) result = AST::AllTypes::S64;
	return result;
}
