//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"
#include "IDL/SyntaxTree.hpp"
#include "IDL/CodeGen/Context.hpp"

namespace IDL
{
	class Visitor : public IDLParserBaseVisitor
	{
	public:
		Visitor(CodeGen::Context& context, SyntaxTree& tree);

		antlrcpp::Any visitMain(IDLParser::MainContext *ctx) override;
		antlrcpp::Any visitGlobal_statements(IDLParser::Global_statementsContext *ctx) override;
		antlrcpp::Any visitGlobal_statement(IDLParser::Global_statementContext *ctx) override;
		antlrcpp::Any visitModule_stmt(IDLParser::Module_stmtContext *context) override;
		antlrcpp::Any visitError_code_stmt(IDLParser::Error_code_stmtContext *ctx) override;
		antlrcpp::Any visitSuccess_stmt(IDLParser::Success_stmtContext *ctx) override;
		antlrcpp::Any visitFailure_stmt(IDLParser::Failure_stmtContext *ctx) override;
		antlrcpp::Any visitImport_all_from_stmt(IDLParser::Import_all_from_stmtContext *ctx) override;
		antlrcpp::Any visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx) override;
		antlrcpp::Any visitImport_stmt(IDLParser::Import_stmtContext *ctx) override;
		antlrcpp::Any visitNamespace_stmt(IDLParser::Namespace_stmtContext *ctx) override;
		antlrcpp::Any visitInterface_stmt(IDLParser::Interface_stmtContext *ctx) override;

	private:
		CodeGen::Context& mContext;
		SyntaxTree& mSyntaxTree;
	};
}
