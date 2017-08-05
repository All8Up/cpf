//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"
#include "AST/SymbolTable.hpp"

namespace IDL
{
	class Visitor : public IDLParserBaseVisitor
	{
	public:
		antlrcpp::Any visitMain(IDLParser::MainContext *context) override;

		antlrcpp::Any visitImport_stmt(IDLParser::Import_stmtContext *ctx) override;
		antlrcpp::Any visitConst_integral_def(IDLParser::Const_integral_defContext *context) override;
		antlrcpp::Any visitConst_float_def(IDLParser::Const_float_defContext *context) override;
		antlrcpp::Any visitConst_string_def(IDLParser::Const_string_defContext *context) override;
		antlrcpp::Any visitConst_class_id_def(IDLParser::Const_class_id_defContext *context) override;
		antlrcpp::Any visitEnum_fwd(IDLParser::Enum_fwdContext *context) override;
		antlrcpp::Any visitEnum_def(IDLParser::Enum_defContext *context) override;
		antlrcpp::Any visitStruct_fwd(IDLParser::Struct_fwdContext *context) override;
		antlrcpp::Any visitStruct_decl(IDLParser::Struct_declContext *context) override;
		antlrcpp::Any visitInterface_fwd(IDLParser::Interface_fwdContext *context) override;
		antlrcpp::Any visitInterface_decl(IDLParser::Interface_declContext *context) override;
		antlrcpp::Any visitNamespace_stmt(IDLParser::Namespace_stmtContext *context) override;

		const AST::SymbolTable& GetSymbolTable() const { return mSymbolTable; }

	private:
		AST::SymbolTable mSymbolTable;
	};
}
