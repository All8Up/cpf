//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"

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
	};
}
