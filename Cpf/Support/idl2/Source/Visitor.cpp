//////////////////////////////////////////////////////////////////////////
#include "Visitor.hpp"
#include "Handlers.hpp"
#include "AST/Import.hpp"
#include "AST/Const.hpp"
#include "AST/Enum.hpp"

using namespace IDL;

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
	printf("Const int: %s = %llu\n", name.c_str(), value);
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_float_def(IDLParser::Const_float_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = Handle(context->float_lit());
	auto result = AST::Const::Create(name, value);
	printf("Const float: %s = %f\n", name.c_str(), value);
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_string_def(IDLParser::Const_string_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = context->string_lit()->STRING_LIT()->toString();
	auto result = AST::Const::Create(name, AST::Const::Type::eString, value);
	printf("Const string: %s = %s\n", name.c_str(), value.c_str());
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_class_id_def(IDLParser::Const_class_id_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = context->string_lit()->STRING_LIT()->toString();
	auto result = AST::Const::Create(name, AST::Const::Type::eClassID, value);
	printf("Const class id: %s = %s\n", name.c_str(), value.c_str());
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitEnum_fwd(IDLParser::Enum_fwdContext *context)
{
	auto name = context->IDENT()->toString();
	if (context->enum_type() && context->enum_type()->integral_type())
	{
		auto type = Handle(context->enum_type()->integral_type());
		auto result = AST::Enum::Create(name, type);
		printf("Enum forward: %s - %s\n", name.c_str(), TypeString(type).c_str());
	}
	else
	{
		printf("Enum forward: %s - Unknown\n", name.c_str());
		auto result = AST::Enum::Create(name);
	}

	return visitChildren(context);
}

antlrcpp::Any Visitor::visitEnum_def(IDLParser::Enum_defContext *context)
{
	std::shared_ptr<AST::Enum> result;
	auto name = context->IDENT()->toString();
	if (context->enum_type() && context->enum_type()->integral_type())
	{
		auto type = Handle(context->enum_type()->integral_type());
		result = std::shared_ptr<AST::Enum>(AST::Enum::Create(name, type));
	}
	else
	{
		result = std::shared_ptr<AST::Enum>(AST::Enum::Create(name));
	}
	printf("Enum: %s - %s\n", result->GetName().c_str(), TypeString(result->GetType()).c_str());

	// Enumerate the contents.
	const auto entries = context->enum_elements()->enum_item();
	AST::EnumItemArray entryArray;
	for (const auto entry : entries)
	{
		auto entryName = entry->IDENT()->toString();
		printf(" - %s\n", entryName.c_str());
		entryArray.emplace_back(AST::EnumItem(entryName, 0));
	}

	return visitChildren(context);
}
