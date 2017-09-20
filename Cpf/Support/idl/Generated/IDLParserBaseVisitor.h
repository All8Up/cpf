
// Generated from C:/Projects/Cpf/Cpf/Support/idl\IDLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "IDLParserVisitor.h"


/**
 * This class provides an empty implementation of IDLParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  IDLParserBaseVisitor : public IDLParserVisitor {
public:

  virtual antlrcpp::Any visitMain(IDLParser::MainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_statements(IDLParser::Global_statementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_statement(IDLParser::Global_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEmpty_stmt(IDLParser::Empty_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitModule_stmt(IDLParser::Module_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitError_code_stmt(IDLParser::Error_code_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSuccess_stmt(IDLParser::Success_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFailure_stmt(IDLParser::Failure_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImport_stmt(IDLParser::Import_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_stmt(IDLParser::Struct_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_decl(IDLParser::Struct_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_fwd(IDLParser::Struct_fwdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefaults_stmt(IDLParser::Defaults_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefaults_item(IDLParser::Defaults_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefaults_array(IDLParser::Defaults_arrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefaults_value(IDLParser::Defaults_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnion_stmt(IDLParser::Union_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnion_decl(IDLParser::Union_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnion_fwd(IDLParser::Union_fwdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_block(IDLParser::Struct_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_item(IDLParser::Struct_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOs_specific(IDLParser::Os_specificContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOs_tag(IDLParser::Os_tagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterface_stmt(IDLParser::Interface_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterface_fwd(IDLParser::Interface_fwdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterface_decl(IDLParser::Interface_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterface_super(IDLParser::Interface_superContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterface_block(IDLParser::Interface_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterface_item(IDLParser::Interface_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunction_decl(IDLParser::Function_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunction_param_list(IDLParser::Function_param_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunction_param(IDLParser::Function_paramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParam_dir_qualifier(IDLParser::Param_dir_qualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConst_def(IDLParser::Const_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConst_integral_def(IDLParser::Const_integral_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConst_float_def(IDLParser::Const_float_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConst_string_def(IDLParser::Const_string_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConst_class_id_def(IDLParser::Const_class_id_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnum_fwd(IDLParser::Enum_fwdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnum_def(IDLParser::Enum_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFlags_fwd(IDLParser::Flags_fwdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFlags_def(IDLParser::Flags_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnum_type(IDLParser::Enum_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnum_elements(IDLParser::Enum_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnum_item(IDLParser::Enum_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnum_expr(IDLParser::Enum_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr_add_sub(IDLParser::Expr_add_subContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr_mul_div(IDLParser::Expr_mul_divContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr_shift(IDLParser::Expr_shiftContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr_logical(IDLParser::Expr_logicalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr_value(IDLParser::Expr_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAny_literal(IDLParser::Any_literalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumeric_lit(IDLParser::Numeric_litContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInteger_lit(IDLParser::Integer_litContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloat_lit(IDLParser::Float_litContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitString_lit(IDLParser::String_litContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQualified_ident(IDLParser::Qualified_identContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQualified_part(IDLParser::Qualified_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQualified_separator(IDLParser::Qualified_separatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAll_or_ident(IDLParser::All_or_identContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMember_decl(IDLParser::Member_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMember_init(IDLParser::Member_initContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMember_init_value(IDLParser::Member_init_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType_decl(IDLParser::Type_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType_modifier(IDLParser::Type_modifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPointer_type(IDLParser::Pointer_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPointer_decl(IDLParser::Pointer_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAny_type(IDLParser::Any_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUtility_type(IDLParser::Utility_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntegral_type(IDLParser::Integral_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloat_type(IDLParser::Float_typeContext *ctx) override {
    return visitChildren(ctx);
  }


};

