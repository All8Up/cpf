
// Generated from C:/Projects/cpf/Cpf/Support/idl\IDLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "IDLParserListener.h"


/**
 * This class provides an empty implementation of IDLParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  IDLParserBaseListener : public IDLParserListener {
public:

  virtual void enterMain(IDLParser::MainContext * /*ctx*/) override { }
  virtual void exitMain(IDLParser::MainContext * /*ctx*/) override { }

  virtual void enterGlobal_statements(IDLParser::Global_statementsContext * /*ctx*/) override { }
  virtual void exitGlobal_statements(IDLParser::Global_statementsContext * /*ctx*/) override { }

  virtual void enterGlobal_statement(IDLParser::Global_statementContext * /*ctx*/) override { }
  virtual void exitGlobal_statement(IDLParser::Global_statementContext * /*ctx*/) override { }

  virtual void enterEmpty_stmt(IDLParser::Empty_stmtContext * /*ctx*/) override { }
  virtual void exitEmpty_stmt(IDLParser::Empty_stmtContext * /*ctx*/) override { }

  virtual void enterModule_stmt(IDLParser::Module_stmtContext * /*ctx*/) override { }
  virtual void exitModule_stmt(IDLParser::Module_stmtContext * /*ctx*/) override { }

  virtual void enterError_code_stmt(IDLParser::Error_code_stmtContext * /*ctx*/) override { }
  virtual void exitError_code_stmt(IDLParser::Error_code_stmtContext * /*ctx*/) override { }

  virtual void enterSuccess_stmt(IDLParser::Success_stmtContext * /*ctx*/) override { }
  virtual void exitSuccess_stmt(IDLParser::Success_stmtContext * /*ctx*/) override { }

  virtual void enterFailure_stmt(IDLParser::Failure_stmtContext * /*ctx*/) override { }
  virtual void exitFailure_stmt(IDLParser::Failure_stmtContext * /*ctx*/) override { }

  virtual void enterImport_from_stmt(IDLParser::Import_from_stmtContext * /*ctx*/) override { }
  virtual void exitImport_from_stmt(IDLParser::Import_from_stmtContext * /*ctx*/) override { }

  virtual void enterImport_stmt(IDLParser::Import_stmtContext * /*ctx*/) override { }
  virtual void exitImport_stmt(IDLParser::Import_stmtContext * /*ctx*/) override { }

  virtual void enterStruct_stmt(IDLParser::Struct_stmtContext * /*ctx*/) override { }
  virtual void exitStruct_stmt(IDLParser::Struct_stmtContext * /*ctx*/) override { }

  virtual void enterStruct_decl(IDLParser::Struct_declContext * /*ctx*/) override { }
  virtual void exitStruct_decl(IDLParser::Struct_declContext * /*ctx*/) override { }

  virtual void enterStruct_fwd(IDLParser::Struct_fwdContext * /*ctx*/) override { }
  virtual void exitStruct_fwd(IDLParser::Struct_fwdContext * /*ctx*/) override { }

  virtual void enterStruct_block(IDLParser::Struct_blockContext * /*ctx*/) override { }
  virtual void exitStruct_block(IDLParser::Struct_blockContext * /*ctx*/) override { }

  virtual void enterStruct_item(IDLParser::Struct_itemContext * /*ctx*/) override { }
  virtual void exitStruct_item(IDLParser::Struct_itemContext * /*ctx*/) override { }

  virtual void enterInterface_stmt(IDLParser::Interface_stmtContext * /*ctx*/) override { }
  virtual void exitInterface_stmt(IDLParser::Interface_stmtContext * /*ctx*/) override { }

  virtual void enterInterface_fwd(IDLParser::Interface_fwdContext * /*ctx*/) override { }
  virtual void exitInterface_fwd(IDLParser::Interface_fwdContext * /*ctx*/) override { }

  virtual void enterInterface_decl(IDLParser::Interface_declContext * /*ctx*/) override { }
  virtual void exitInterface_decl(IDLParser::Interface_declContext * /*ctx*/) override { }

  virtual void enterInterface_super(IDLParser::Interface_superContext * /*ctx*/) override { }
  virtual void exitInterface_super(IDLParser::Interface_superContext * /*ctx*/) override { }

  virtual void enterInterface_block(IDLParser::Interface_blockContext * /*ctx*/) override { }
  virtual void exitInterface_block(IDLParser::Interface_blockContext * /*ctx*/) override { }

  virtual void enterInterface_item(IDLParser::Interface_itemContext * /*ctx*/) override { }
  virtual void exitInterface_item(IDLParser::Interface_itemContext * /*ctx*/) override { }

  virtual void enterFunction_decl(IDLParser::Function_declContext * /*ctx*/) override { }
  virtual void exitFunction_decl(IDLParser::Function_declContext * /*ctx*/) override { }

  virtual void enterFunction_param_list(IDLParser::Function_param_listContext * /*ctx*/) override { }
  virtual void exitFunction_param_list(IDLParser::Function_param_listContext * /*ctx*/) override { }

  virtual void enterFunction_param(IDLParser::Function_paramContext * /*ctx*/) override { }
  virtual void exitFunction_param(IDLParser::Function_paramContext * /*ctx*/) override { }

  virtual void enterParam_dir_qualifier(IDLParser::Param_dir_qualifierContext * /*ctx*/) override { }
  virtual void exitParam_dir_qualifier(IDLParser::Param_dir_qualifierContext * /*ctx*/) override { }

  virtual void enterConst_def(IDLParser::Const_defContext * /*ctx*/) override { }
  virtual void exitConst_def(IDLParser::Const_defContext * /*ctx*/) override { }

  virtual void enterConst_integral_def(IDLParser::Const_integral_defContext * /*ctx*/) override { }
  virtual void exitConst_integral_def(IDLParser::Const_integral_defContext * /*ctx*/) override { }

  virtual void enterConst_float_def(IDLParser::Const_float_defContext * /*ctx*/) override { }
  virtual void exitConst_float_def(IDLParser::Const_float_defContext * /*ctx*/) override { }

  virtual void enterConst_string_def(IDLParser::Const_string_defContext * /*ctx*/) override { }
  virtual void exitConst_string_def(IDLParser::Const_string_defContext * /*ctx*/) override { }

  virtual void enterConst_class_id_def(IDLParser::Const_class_id_defContext * /*ctx*/) override { }
  virtual void exitConst_class_id_def(IDLParser::Const_class_id_defContext * /*ctx*/) override { }

  virtual void enterEnum_fwd(IDLParser::Enum_fwdContext * /*ctx*/) override { }
  virtual void exitEnum_fwd(IDLParser::Enum_fwdContext * /*ctx*/) override { }

  virtual void enterEnum_def(IDLParser::Enum_defContext * /*ctx*/) override { }
  virtual void exitEnum_def(IDLParser::Enum_defContext * /*ctx*/) override { }

  virtual void enterEnum_type(IDLParser::Enum_typeContext * /*ctx*/) override { }
  virtual void exitEnum_type(IDLParser::Enum_typeContext * /*ctx*/) override { }

  virtual void enterEnum_elements(IDLParser::Enum_elementsContext * /*ctx*/) override { }
  virtual void exitEnum_elements(IDLParser::Enum_elementsContext * /*ctx*/) override { }

  virtual void enterEnum_item(IDLParser::Enum_itemContext * /*ctx*/) override { }
  virtual void exitEnum_item(IDLParser::Enum_itemContext * /*ctx*/) override { }

  virtual void enterEnum_expr(IDLParser::Enum_exprContext * /*ctx*/) override { }
  virtual void exitEnum_expr(IDLParser::Enum_exprContext * /*ctx*/) override { }

  virtual void enterExpr_add_sub(IDLParser::Expr_add_subContext * /*ctx*/) override { }
  virtual void exitExpr_add_sub(IDLParser::Expr_add_subContext * /*ctx*/) override { }

  virtual void enterExpr_mul_div(IDLParser::Expr_mul_divContext * /*ctx*/) override { }
  virtual void exitExpr_mul_div(IDLParser::Expr_mul_divContext * /*ctx*/) override { }

  virtual void enterExpr_shift(IDLParser::Expr_shiftContext * /*ctx*/) override { }
  virtual void exitExpr_shift(IDLParser::Expr_shiftContext * /*ctx*/) override { }

  virtual void enterExpr_value(IDLParser::Expr_valueContext * /*ctx*/) override { }
  virtual void exitExpr_value(IDLParser::Expr_valueContext * /*ctx*/) override { }

  virtual void enterAny_literal(IDLParser::Any_literalContext * /*ctx*/) override { }
  virtual void exitAny_literal(IDLParser::Any_literalContext * /*ctx*/) override { }

  virtual void enterNumeric_lit(IDLParser::Numeric_litContext * /*ctx*/) override { }
  virtual void exitNumeric_lit(IDLParser::Numeric_litContext * /*ctx*/) override { }

  virtual void enterInteger_lit(IDLParser::Integer_litContext * /*ctx*/) override { }
  virtual void exitInteger_lit(IDLParser::Integer_litContext * /*ctx*/) override { }

  virtual void enterFloat_lit(IDLParser::Float_litContext * /*ctx*/) override { }
  virtual void exitFloat_lit(IDLParser::Float_litContext * /*ctx*/) override { }

  virtual void enterString_lit(IDLParser::String_litContext * /*ctx*/) override { }
  virtual void exitString_lit(IDLParser::String_litContext * /*ctx*/) override { }

  virtual void enterQualified_ident(IDLParser::Qualified_identContext * /*ctx*/) override { }
  virtual void exitQualified_ident(IDLParser::Qualified_identContext * /*ctx*/) override { }

  virtual void enterQualified_part(IDLParser::Qualified_partContext * /*ctx*/) override { }
  virtual void exitQualified_part(IDLParser::Qualified_partContext * /*ctx*/) override { }

  virtual void enterQualified_separator(IDLParser::Qualified_separatorContext * /*ctx*/) override { }
  virtual void exitQualified_separator(IDLParser::Qualified_separatorContext * /*ctx*/) override { }

  virtual void enterAll_or_ident(IDLParser::All_or_identContext * /*ctx*/) override { }
  virtual void exitAll_or_ident(IDLParser::All_or_identContext * /*ctx*/) override { }

  virtual void enterMember_decl(IDLParser::Member_declContext * /*ctx*/) override { }
  virtual void exitMember_decl(IDLParser::Member_declContext * /*ctx*/) override { }

  virtual void enterType_decl(IDLParser::Type_declContext * /*ctx*/) override { }
  virtual void exitType_decl(IDLParser::Type_declContext * /*ctx*/) override { }

  virtual void enterType_modifier(IDLParser::Type_modifierContext * /*ctx*/) override { }
  virtual void exitType_modifier(IDLParser::Type_modifierContext * /*ctx*/) override { }

  virtual void enterPointer_type(IDLParser::Pointer_typeContext * /*ctx*/) override { }
  virtual void exitPointer_type(IDLParser::Pointer_typeContext * /*ctx*/) override { }

  virtual void enterPointer_decl(IDLParser::Pointer_declContext * /*ctx*/) override { }
  virtual void exitPointer_decl(IDLParser::Pointer_declContext * /*ctx*/) override { }

  virtual void enterAny_type(IDLParser::Any_typeContext * /*ctx*/) override { }
  virtual void exitAny_type(IDLParser::Any_typeContext * /*ctx*/) override { }

  virtual void enterUtility_type(IDLParser::Utility_typeContext * /*ctx*/) override { }
  virtual void exitUtility_type(IDLParser::Utility_typeContext * /*ctx*/) override { }

  virtual void enterIntegral_type(IDLParser::Integral_typeContext * /*ctx*/) override { }
  virtual void exitIntegral_type(IDLParser::Integral_typeContext * /*ctx*/) override { }

  virtual void enterFloat_type(IDLParser::Float_typeContext * /*ctx*/) override { }
  virtual void exitFloat_type(IDLParser::Float_typeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

