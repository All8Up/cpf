//////////////////////////////////////////////////////////////////////////
#include "IDL/ParseTree/Visitor.hpp"

using namespace IDL;

//////////////////////////////////////////////////////////////////////////
Cpf::String TrimStringLit(const Cpf::String& lit)
{
	if (lit.empty())
		return Cpf::String();
	return Cpf::String(lit.begin() + 1, lit.end() - 1);
}

SymbolPath GetPath(IDLParser::Qualified_identContext* ctx)
{
	const auto ident = ctx->IDENT()->toString();
	SymbolPath path(ident);

	for (const auto& p : ctx->qualified_part())
	{
		path.Push(Cpf::String(p->IDENT()->toString().c_str()));
	}
	return path;
}

//////////////////////////////////////////////////////////////////////////
Visitor::Visitor()
{}

antlrcpp::Any Visitor::visitMain(IDLParser::MainContext *ctx)
{
	Emit<Start>();
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitGlobal_statements(IDLParser::Global_statementsContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitGlobal_statement(IDLParser::Global_statementContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitModule_stmt(IDLParser::Module_stmtContext *ctx)
{
	const auto ident = ctx->qualified_ident()->IDENT()->toString();
	SymbolPath path(ident);

	for (const auto& p : ctx->qualified_ident()->qualified_part())
	{
		path.Push(Cpf::String(p->IDENT()->toString().c_str()));
	}
	Emit<ModuleStmt>(path);

	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitError_code_stmt(IDLParser::Error_code_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitSuccess_stmt(IDLParser::Success_stmtContext *ctx)
{
	auto name = ctx->IDENT()->toString();
	auto subSystem = TrimStringLit(ctx->STRING_LIT()[0]->toString());
	auto desc = TrimStringLit(ctx->STRING_LIT()[1]->toString());
	Emit<SuccessType>(name, subSystem, desc);

	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitFailure_stmt(IDLParser::Failure_stmtContext *ctx)
{
	auto name = ctx->IDENT()->toString();
	auto subSystem = TrimStringLit(ctx->STRING_LIT()[0]->toString());
	auto desc = TrimStringLit(ctx->STRING_LIT()[1]->toString());
	Emit<FailureType>(name, subSystem, desc);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx)
{
	String source;
	if (ctx->all_or_ident()->IDENT())
		source = ctx->all_or_ident()->IDENT()->toString();
	else
		source = "*";
	Emit<ImportStmt>(source, GetPath(ctx->qualified_ident()));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_stmt(IDLParser::Import_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitInterface_stmt(IDLParser::Interface_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitInterface_decl(IDLParser::Interface_declContext *ctx)
{
	InterfaceDecl decl;
	decl.mName = ctx->IDENT()->toString();
	if (ctx->interface_super())
	{
		// Have a parent.
		decl.mSuper = GetPath(ctx->interface_super()->qualified_ident());
	}

	for (const auto& item : ctx->interface_block()->interface_item())
	{
		if (item->const_def())
		{

		}
		else if (item->enum_def())
		{

		}
		else if (item->function_decl())
		{
			auto func = item->function_decl();
			FunctionDecl funcDecl;
			funcDecl.mName = func->IDENT()->toString();
			funcDecl.mReturnType = ParseTypeDecl(func->type_decl());
			if (func->function_param_list())
			{
				for (auto param : func->function_param_list()->function_param())
				{
					ParamDecl paramDecl;
					paramDecl.mName = param->IDENT() ? param->IDENT()->toString() : String();
					paramDecl.mType = ParseTypeDecl(param->type_decl());
					funcDecl.mParams.push_back(paramDecl);
				}
			}

			decl.mFunctions.push_back(funcDecl);
		}
	}

	Emit<InterfaceDeclStmt>(decl);
	return visitChildren(ctx);
}

Visitor::TypeDecl Visitor::ParseTypeDecl(IDLParser::Type_declContext* typeDecl)
{
	TypeDecl result;
	result.mConst = typeDecl->type_modifier() == nullptr ? false : true;

	auto anyType = typeDecl->any_type();
	if (anyType->integral_type())
	{
		auto intType = anyType->integral_type();
		if (intType->U8()) result.mType = Type::U8;
		else if (intType->S8()) result.mType = Type::S8;
		else if (intType->U16()) result.mType = Type::U16;
		else if (intType->S16()) result.mType = Type::S16;
		else if (intType->U32()) result.mType = Type::U32;
		else if (intType->S32()) result.mType = Type::S32;
		else if (intType->U64()) result.mType = Type::U64;
		else if (intType->S64()) result.mType = Type::S64;
	}
	else if (anyType->float_type())
	{
		auto floatType = anyType->float_type();
		if (floatType->F32()) result.mType = Type::F32;
		else if (floatType->F64()) result.mType = Type::F64;
	}
	else if (anyType->utility_type())
	{
		auto utilType = anyType->utility_type();
		if (utilType->Void()) result.mType = Type::Void;
		else if (utilType->RESULT()) result.mType = Type::Result;
	}
	else if (anyType->IDENT())
	{
		result.mType = Type::Ident;
		result.mIdent = anyType->IDENT()->toString();
	}
	else
	{
		// Error.
	}

	if (typeDecl->pointer_type())
	{
		for (const auto& ptr : typeDecl->pointer_type()->STAR())
		{
			(void)ptr;
			result.mPointer.push_back(Pointer());
		}
	}

	return result;
}
