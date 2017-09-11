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

antlrcpp::Any Visitor::visitImport_all_from_stmt(IDLParser::Import_all_from_stmtContext *ctx)
{
	// TODO: Remove this special case and add a path type to the grammar
	// which includes * as a valid terminal symbol.
	Emit<ImportAllStmt>(ctx->FROM()->toString());
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_stmt(IDLParser::Import_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitNamespace_stmt(IDLParser::Namespace_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitInterface_stmt(IDLParser::Interface_stmtContext *ctx)
{
	return visitChildren(ctx);
}
