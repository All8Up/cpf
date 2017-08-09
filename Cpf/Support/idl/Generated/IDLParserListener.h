
// Generated from C:/Projects/cpf/Cpf/Support/idl\IDLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "IDLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by IDLParser.
 */
class  IDLParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterMain(IDLParser::MainContext *ctx) = 0;
  virtual void exitMain(IDLParser::MainContext *ctx) = 0;

  virtual void enterGlobal_statements(IDLParser::Global_statementsContext *ctx) = 0;
  virtual void exitGlobal_statements(IDLParser::Global_statementsContext *ctx) = 0;

  virtual void enterGlobal_statement(IDLParser::Global_statementContext *ctx) = 0;
  virtual void exitGlobal_statement(IDLParser::Global_statementContext *ctx) = 0;

  virtual void enterEmpty_stmt(IDLParser::Empty_stmtContext *ctx) = 0;
  virtual void exitEmpty_stmt(IDLParser::Empty_stmtContext *ctx) = 0;

  virtual void enterModule_stmt(IDLParser::Module_stmtContext *ctx) = 0;
  virtual void exitModule_stmt(IDLParser::Module_stmtContext *ctx) = 0;

  virtual void enterError_code_stmt(IDLParser::Error_code_stmtContext *ctx) = 0;
  virtual void exitError_code_stmt(IDLParser::Error_code_stmtContext *ctx) = 0;

  virtual void enterSuccess_stmt(IDLParser::Success_stmtContext *ctx) = 0;
  virtual void exitSuccess_stmt(IDLParser::Success_stmtContext *ctx) = 0;

  virtual void enterFailure_stmt(IDLParser::Failure_stmtContext *ctx) = 0;
  virtual void exitFailure_stmt(IDLParser::Failure_stmtContext *ctx) = 0;

  virtual void enterImport_from_stmt(IDLParser::Import_from_stmtContext *ctx) = 0;
  virtual void exitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx) = 0;

  virtual void enterImport_stmt(IDLParser::Import_stmtContext *ctx) = 0;
  virtual void exitImport_stmt(IDLParser::Import_stmtContext *ctx) = 0;

  virtual void enterNamespace_stmt(IDLParser::Namespace_stmtContext *ctx) = 0;
  virtual void exitNamespace_stmt(IDLParser::Namespace_stmtContext *ctx) = 0;

  virtual void enterNamespace_name(IDLParser::Namespace_nameContext *ctx) = 0;
  virtual void exitNamespace_name(IDLParser::Namespace_nameContext *ctx) = 0;

  virtual void enterNamespace_block(IDLParser::Namespace_blockContext *ctx) = 0;
  virtual void exitNamespace_block(IDLParser::Namespace_blockContext *ctx) = 0;

  virtual void enterNamespace_item(IDLParser::Namespace_itemContext *ctx) = 0;
  virtual void exitNamespace_item(IDLParser::Namespace_itemContext *ctx) = 0;

  virtual void enterStruct_stmt(IDLParser::Struct_stmtContext *ctx) = 0;
  virtual void exitStruct_stmt(IDLParser::Struct_stmtContext *ctx) = 0;

  virtual void enterStruct_decl(IDLParser::Struct_declContext *ctx) = 0;
  virtual void exitStruct_decl(IDLParser::Struct_declContext *ctx) = 0;

  virtual void enterStruct_name(IDLParser::Struct_nameContext *ctx) = 0;
  virtual void exitStruct_name(IDLParser::Struct_nameContext *ctx) = 0;

  virtual void enterStruct_fwd(IDLParser::Struct_fwdContext *ctx) = 0;
  virtual void exitStruct_fwd(IDLParser::Struct_fwdContext *ctx) = 0;

  virtual void enterStruct_block(IDLParser::Struct_blockContext *ctx) = 0;
  virtual void exitStruct_block(IDLParser::Struct_blockContext *ctx) = 0;

  virtual void enterStruct_item(IDLParser::Struct_itemContext *ctx) = 0;
  virtual void exitStruct_item(IDLParser::Struct_itemContext *ctx) = 0;

  virtual void enterInterface_stmt(IDLParser::Interface_stmtContext *ctx) = 0;
  virtual void exitInterface_stmt(IDLParser::Interface_stmtContext *ctx) = 0;

  virtual void enterInterface_fwd(IDLParser::Interface_fwdContext *ctx) = 0;
  virtual void exitInterface_fwd(IDLParser::Interface_fwdContext *ctx) = 0;

  virtual void enterInterface_decl(IDLParser::Interface_declContext *ctx) = 0;
  virtual void exitInterface_decl(IDLParser::Interface_declContext *ctx) = 0;

  virtual void enterInterface_super(IDLParser::Interface_superContext *ctx) = 0;
  virtual void exitInterface_super(IDLParser::Interface_superContext *ctx) = 0;

  virtual void enterInterface_block(IDLParser::Interface_blockContext *ctx) = 0;
  virtual void exitInterface_block(IDLParser::Interface_blockContext *ctx) = 0;

  virtual void enterInterface_item(IDLParser::Interface_itemContext *ctx) = 0;
  virtual void exitInterface_item(IDLParser::Interface_itemContext *ctx) = 0;

  virtual void enterFunction_decl(IDLParser::Function_declContext *ctx) = 0;
  virtual void exitFunction_decl(IDLParser::Function_declContext *ctx) = 0;

  virtual void enterFunction_param_list(IDLParser::Function_param_listContext *ctx) = 0;
  virtual void exitFunction_param_list(IDLParser::Function_param_listContext *ctx) = 0;

  virtual void enterFunction_param(IDLParser::Function_paramContext *ctx) = 0;
  virtual void exitFunction_param(IDLParser::Function_paramContext *ctx) = 0;

  virtual void enterParam_dir_qualifier(IDLParser::Param_dir_qualifierContext *ctx) = 0;
  virtual void exitParam_dir_qualifier(IDLParser::Param_dir_qualifierContext *ctx) = 0;

  virtual void enterConst_def(IDLParser::Const_defContext *ctx) = 0;
  virtual void exitConst_def(IDLParser::Const_defContext *ctx) = 0;

  virtual void enterConst_integral_def(IDLParser::Const_integral_defContext *ctx) = 0;
  virtual void exitConst_integral_def(IDLParser::Const_integral_defContext *ctx) = 0;

  virtual void enterConst_float_def(IDLParser::Const_float_defContext *ctx) = 0;
  virtual void exitConst_float_def(IDLParser::Const_float_defContext *ctx) = 0;

  virtual void enterConst_string_def(IDLParser::Const_string_defContext *ctx) = 0;
  virtual void exitConst_string_def(IDLParser::Const_string_defContext *ctx) = 0;

  virtual void enterConst_class_id_def(IDLParser::Const_class_id_defContext *ctx) = 0;
  virtual void exitConst_class_id_def(IDLParser::Const_class_id_defContext *ctx) = 0;

  virtual void enterEnum_fwd(IDLParser::Enum_fwdContext *ctx) = 0;
  virtual void exitEnum_fwd(IDLParser::Enum_fwdContext *ctx) = 0;

  virtual void enterEnum_def(IDLParser::Enum_defContext *ctx) = 0;
  virtual void exitEnum_def(IDLParser::Enum_defContext *ctx) = 0;

  virtual void enterEnum_type(IDLParser::Enum_typeContext *ctx) = 0;
  virtual void exitEnum_type(IDLParser::Enum_typeContext *ctx) = 0;

  virtual void enterEnum_elements(IDLParser::Enum_elementsContext *ctx) = 0;
  virtual void exitEnum_elements(IDLParser::Enum_elementsContext *ctx) = 0;

  virtual void enterEnum_item(IDLParser::Enum_itemContext *ctx) = 0;
  virtual void exitEnum_item(IDLParser::Enum_itemContext *ctx) = 0;

  virtual void enterEnum_expr(IDLParser::Enum_exprContext *ctx) = 0;
  virtual void exitEnum_expr(IDLParser::Enum_exprContext *ctx) = 0;

  virtual void enterExpr_add_sub(IDLParser::Expr_add_subContext *ctx) = 0;
  virtual void exitExpr_add_sub(IDLParser::Expr_add_subContext *ctx) = 0;

  virtual void enterExpr_mul_div(IDLParser::Expr_mul_divContext *ctx) = 0;
  virtual void exitExpr_mul_div(IDLParser::Expr_mul_divContext *ctx) = 0;

  virtual void enterExpr_shift(IDLParser::Expr_shiftContext *ctx) = 0;
  virtual void exitExpr_shift(IDLParser::Expr_shiftContext *ctx) = 0;

  virtual void enterExpr_value(IDLParser::Expr_valueContext *ctx) = 0;
  virtual void exitExpr_value(IDLParser::Expr_valueContext *ctx) = 0;

  virtual void enterAny_literal(IDLParser::Any_literalContext *ctx) = 0;
  virtual void exitAny_literal(IDLParser::Any_literalContext *ctx) = 0;

  virtual void enterNumeric_lit(IDLParser::Numeric_litContext *ctx) = 0;
  virtual void exitNumeric_lit(IDLParser::Numeric_litContext *ctx) = 0;

  virtual void enterInteger_lit(IDLParser::Integer_litContext *ctx) = 0;
  virtual void exitInteger_lit(IDLParser::Integer_litContext *ctx) = 0;

  virtual void enterFloat_lit(IDLParser::Float_litContext *ctx) = 0;
  virtual void exitFloat_lit(IDLParser::Float_litContext *ctx) = 0;

  virtual void enterString_lit(IDLParser::String_litContext *ctx) = 0;
  virtual void exitString_lit(IDLParser::String_litContext *ctx) = 0;

  virtual void enterQualified_ident(IDLParser::Qualified_identContext *ctx) = 0;
  virtual void exitQualified_ident(IDLParser::Qualified_identContext *ctx) = 0;

  virtual void enterQualified_part(IDLParser::Qualified_partContext *ctx) = 0;
  virtual void exitQualified_part(IDLParser::Qualified_partContext *ctx) = 0;

  virtual void enterQualified_separator(IDLParser::Qualified_separatorContext *ctx) = 0;
  virtual void exitQualified_separator(IDLParser::Qualified_separatorContext *ctx) = 0;

  virtual void enterMember_decl(IDLParser::Member_declContext *ctx) = 0;
  virtual void exitMember_decl(IDLParser::Member_declContext *ctx) = 0;

  virtual void enterType_decl(IDLParser::Type_declContext *ctx) = 0;
  virtual void exitType_decl(IDLParser::Type_declContext *ctx) = 0;

  virtual void enterType_modifier(IDLParser::Type_modifierContext *ctx) = 0;
  virtual void exitType_modifier(IDLParser::Type_modifierContext *ctx) = 0;

  virtual void enterPointer_type(IDLParser::Pointer_typeContext *ctx) = 0;
  virtual void exitPointer_type(IDLParser::Pointer_typeContext *ctx) = 0;

  virtual void enterAny_type(IDLParser::Any_typeContext *ctx) = 0;
  virtual void exitAny_type(IDLParser::Any_typeContext *ctx) = 0;

  virtual void enterUtility_type(IDLParser::Utility_typeContext *ctx) = 0;
  virtual void exitUtility_type(IDLParser::Utility_typeContext *ctx) = 0;

  virtual void enterIntegral_type(IDLParser::Integral_typeContext *ctx) = 0;
  virtual void exitIntegral_type(IDLParser::Integral_typeContext *ctx) = 0;

  virtual void enterFloat_type(IDLParser::Float_typeContext *ctx) = 0;
  virtual void exitFloat_type(IDLParser::Float_typeContext *ctx) = 0;


};

