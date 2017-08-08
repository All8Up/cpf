//////////////////////////////////////////////////////////////////////////
#include "Visitor/Visitor.hpp"
#include "AST/Import.hpp"
#include "AST/Const.hpp"
#include "AST/Enum.hpp"
#include "AST/Struct.hpp"
#include "AST/Interface.hpp"
#include "Visitor/Literal.hpp"
#include "Visitor/Enum.hpp"
#include "Visitor/DataMember.hpp"

using namespace IDL;

antlrcpp::Any Visitor::visitMain(IDLParser::MainContext *context)
{
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitImport_stmt(IDLParser::Import_stmtContext *context)
{
	auto* module = context->string_lit();
	auto value = module->STRING_LIT()->toString();
	mSymbolTable.AddImport(std::make_shared<AST::Import>(value));
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_integral_def(IDLParser::Const_integral_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = GetIntegerLiteral(context->integer_lit());

	mSymbolTable.AddSymbol(std::make_shared<AST::Const>(mSymbolTable.GetCurrentScope(), name, value));
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_float_def(IDLParser::Const_float_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = GetFloatLiteral(context->float_lit());
	mSymbolTable.AddSymbol(std::make_shared<AST::Const>(mSymbolTable.GetCurrentScope(), name, value));
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_string_def(IDLParser::Const_string_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = context->string_lit()->STRING_LIT()->toString();
	mSymbolTable.AddSymbol(std::make_shared<AST::Const>(mSymbolTable.GetCurrentScope(), name, AST::Const::Type::eString, value));
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitConst_class_id_def(IDLParser::Const_class_id_defContext *context)
{
	auto name = context->IDENT()->toString();
	auto value = context->string_lit()->STRING_LIT()->toString();
	mSymbolTable.AddSymbol(std::make_shared<AST::Const>(mSymbolTable.GetCurrentScope(), name, AST::Const::Type::eClassID, value));
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitEnum_fwd(IDLParser::Enum_fwdContext *context)
{
	auto name = context->IDENT()->toString();
	if (context->enum_type() && context->enum_type()->integral_type())
	{
		auto type = GetType(context->enum_type()->integral_type());
		mSymbolTable.AddSymbol(std::make_shared<AST::Enum>(mSymbolTable.GetCurrentScope(), name, type));
	}
	else
	{
		mSymbolTable.AddSymbol(std::make_shared<AST::Enum>(mSymbolTable.GetCurrentScope(), name));
	}

	return visitChildren(context);
}

antlrcpp::Any Visitor::visitEnum_def(IDLParser::Enum_defContext *context)
{
	std::shared_ptr<AST::Enum> result;
	auto name = context->IDENT()->toString();
	if (context->enum_type() && context->enum_type()->integral_type())
	{
		auto type = GetType(context->enum_type()->integral_type());
		result = std::make_shared<AST::Enum>(mSymbolTable.GetCurrentScope(), name, type);
	}
	else
	{
		result = std::make_shared<AST::Enum>(mSymbolTable.GetCurrentScope(), name);
	}

	// Enumerate the contents.
	AST::EnumItemArray entryArray = GetEnumValues(context->enum_elements());
	result->SetItems(entryArray);

	mSymbolTable.AddSymbol(result);
	return visitChildren(context);
}

antlrcpp::Any Visitor::visitStruct_fwd(IDLParser::Struct_fwdContext *context)
{
	auto name = context->IDENT()->toString();
	auto result = std::make_shared<AST::Struct>(mSymbolTable.GetCurrentScope(), name);
	mSymbolTable.AddSymbol(result);

	return visitChildren(context);
}

antlrcpp::Any Visitor::visitStruct_decl(IDLParser::Struct_declContext *context)
{
	auto name = context->struct_name()->IDENT()->toString();
	auto result = std::make_shared<AST::Struct>(mSymbolTable.GetCurrentScope(), name);
	result->SetDataMembers(GetDataMembers(context));
	mSymbolTable.AddSymbol(result);

	return visitChildren(context);
}

antlrcpp::Any Visitor::visitInterface_fwd(IDLParser::Interface_fwdContext *context)
{
	auto name = context->IDENT()->toString();
	auto result = std::make_shared<AST::Interface>(mSymbolTable.GetCurrentScope(), name);
	mSymbolTable.AddSymbol(result);

	// When visiting the children, push this struct as a scope.
	mSymbolTable.PushScope(name, false);
	auto visitResult = visitChildren(context);
	mSymbolTable.PopScope(false);
	return visitResult;
}

antlrcpp::Any Visitor::visitInterface_decl(IDLParser::Interface_declContext *context)
{
	auto name = context->IDENT()->toString();
	auto result = std::make_shared<AST::Interface>(mSymbolTable.GetCurrentScope(), name);
	mSymbolTable.AddSymbol(result);

	// When visiting the children, push this struct as a scope.
	mSymbolTable.PushScope(name, false);
	auto visitResult = visitChildren(context);
	mSymbolTable.PopScope(false);
	return visitResult;
}

antlrcpp::Any Visitor::visitNamespace_stmt(IDLParser::Namespace_stmtContext *context)
{
	// Get the name.
	auto name = context->namespace_name()->IDENT()->toString();

	// Push the new namespace onto the scope stack.
	mSymbolTable.PushScope(name, true);

	// Process children of the new namespace.
	auto any = visitChildren(context);

	// Pop the namespace off the scope stack.
	mSymbolTable.PopScope(true);

	return any;
}
