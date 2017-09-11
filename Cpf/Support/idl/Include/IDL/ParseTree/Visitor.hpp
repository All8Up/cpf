//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"
#include "IDL/SyntaxTree.hpp"
#include "IDL/CodeGen/Context.hpp"
#include "Events/Emitter.hpp"

namespace IDL
{
	class Visitor
		: public IDLParserBaseVisitor
		, public Cpf::Events::Emitter
	{
	public:
		using String = Cpf::String;
		typedef Cpf::Events::Event<0, Cpf::Function<void(void)>> Start;
		typedef Cpf::Events::Event<1, Cpf::Function<void (const SymbolPath&)>> ModuleStmt;
		typedef Cpf::Events::Event<2, Cpf::Function<void(const String&, const String&, const String&)>> SuccessType;
		typedef Cpf::Events::Event<3, Cpf::Function<void(const String&, const String&, const String&)>> FailureType;
		typedef Cpf::Events::Event<4, Cpf::Function<void(const String&)>> ImportAllStmt;

		Visitor();

	protected:
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
	};
}
