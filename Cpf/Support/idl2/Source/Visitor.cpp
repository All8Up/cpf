//////////////////////////////////////////////////////////////////////////
#include "Visitor.hpp"
#include "AST/Import.hpp"
#include "AST/Const.hpp"

using namespace IDL;

namespace
{
	uint64_t Handle(IDLParser::Integer_litContext* context)
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

	double Handle(IDLParser::Float_litContext* context)
	{
		auto f = context->FLOAT_LIT();
		auto strValue = f->toString();
		return ::atof(strValue.c_str());
	}
}

antlrcpp::Any Visitor::visitMain(IDLParser::MainContext *context)
{
	printf("********************\n");
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitImport_stmt(IDLParser::Import_stmtContext *context)
{
	auto* module = context->string_lit();
	auto value = module->STRING_LIT()->toString();
	auto result = AST::Import::Create(value);

	printf("Import: %s\n", value.c_str());
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_integral_def(IDLParser::Const_integral_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = Handle(context->integer_lit());

	auto result = AST::Const::Create(name, value);
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_float_def(IDLParser::Const_float_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = Handle(context->float_lit());
	auto result = AST::Const::Create(name, value);
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_string_def(IDLParser::Const_string_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto result = AST::Const::Create(name, AST::Const::Type::eString, context->string_lit()->STRING_LIT()->toString());
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_class_id_def(IDLParser::Const_class_id_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto result = AST::Const::Create(name, AST::Const::Type::eClassID, context->string_lit()->STRING_LIT()->toString());
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitEnum_fwd(IDLParser::Enum_fwdContext *context)
{
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitEnum_def(IDLParser::Enum_defContext *context)
{
	return visitChildren(context);
}
