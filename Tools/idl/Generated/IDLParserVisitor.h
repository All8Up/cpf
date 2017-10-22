
// Generated from C:/Projects/MotD/CPF/Tools/idl\IDLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "IDLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by IDLParser.
 */
class  IDLParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by IDLParser.
   */
    virtual antlrcpp::Any visitMain(IDLParser::MainContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_statements(IDLParser::Global_statementsContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_statement(IDLParser::Global_statementContext *context) = 0;

    virtual antlrcpp::Any visitEmpty_stmt(IDLParser::Empty_stmtContext *context) = 0;

    virtual antlrcpp::Any visitModule_stmt(IDLParser::Module_stmtContext *context) = 0;

    virtual antlrcpp::Any visitError_code_stmt(IDLParser::Error_code_stmtContext *context) = 0;

    virtual antlrcpp::Any visitSuccess_stmt(IDLParser::Success_stmtContext *context) = 0;

    virtual antlrcpp::Any visitFailure_stmt(IDLParser::Failure_stmtContext *context) = 0;

    virtual antlrcpp::Any visitImport_from_stmt(IDLParser::Import_from_stmtContext *context) = 0;

    virtual antlrcpp::Any visitImport_stmt(IDLParser::Import_stmtContext *context) = 0;

    virtual antlrcpp::Any visitStruct_stmt(IDLParser::Struct_stmtContext *context) = 0;

    virtual antlrcpp::Any visitStruct_decl(IDLParser::Struct_declContext *context) = 0;

    virtual antlrcpp::Any visitStruct_fwd(IDLParser::Struct_fwdContext *context) = 0;

    virtual antlrcpp::Any visitUnion_stmt(IDLParser::Union_stmtContext *context) = 0;

    virtual antlrcpp::Any visitUnion_decl(IDLParser::Union_declContext *context) = 0;

    virtual antlrcpp::Any visitUnion_fwd(IDLParser::Union_fwdContext *context) = 0;

    virtual antlrcpp::Any visitStruct_block(IDLParser::Struct_blockContext *context) = 0;

    virtual antlrcpp::Any visitStruct_item(IDLParser::Struct_itemContext *context) = 0;

    virtual antlrcpp::Any visitOs_specific(IDLParser::Os_specificContext *context) = 0;

    virtual antlrcpp::Any visitOs_tag(IDLParser::Os_tagContext *context) = 0;

    virtual antlrcpp::Any visitInterface_stmt(IDLParser::Interface_stmtContext *context) = 0;

    virtual antlrcpp::Any visitInterface_fwd(IDLParser::Interface_fwdContext *context) = 0;

    virtual antlrcpp::Any visitInterface_decl(IDLParser::Interface_declContext *context) = 0;

    virtual antlrcpp::Any visitInterface_super(IDLParser::Interface_superContext *context) = 0;

    virtual antlrcpp::Any visitInterface_block(IDLParser::Interface_blockContext *context) = 0;

    virtual antlrcpp::Any visitInterface_item(IDLParser::Interface_itemContext *context) = 0;

    virtual antlrcpp::Any visitFunction_decl(IDLParser::Function_declContext *context) = 0;

    virtual antlrcpp::Any visitFunction_param_list(IDLParser::Function_param_listContext *context) = 0;

    virtual antlrcpp::Any visitFunction_param(IDLParser::Function_paramContext *context) = 0;

    virtual antlrcpp::Any visitParam_dir_qualifier(IDLParser::Param_dir_qualifierContext *context) = 0;

    virtual antlrcpp::Any visitEvent_decl(IDLParser::Event_declContext *context) = 0;

    virtual antlrcpp::Any visitConst_def(IDLParser::Const_defContext *context) = 0;

    virtual antlrcpp::Any visitConst_integral_def(IDLParser::Const_integral_defContext *context) = 0;

    virtual antlrcpp::Any visitConst_float_def(IDLParser::Const_float_defContext *context) = 0;

    virtual antlrcpp::Any visitConst_string_def(IDLParser::Const_string_defContext *context) = 0;

    virtual antlrcpp::Any visitConst_class_id_def(IDLParser::Const_class_id_defContext *context) = 0;

    virtual antlrcpp::Any visitEnum_fwd(IDLParser::Enum_fwdContext *context) = 0;

    virtual antlrcpp::Any visitEnum_def(IDLParser::Enum_defContext *context) = 0;

    virtual antlrcpp::Any visitFlags_fwd(IDLParser::Flags_fwdContext *context) = 0;

    virtual antlrcpp::Any visitFlags_def(IDLParser::Flags_defContext *context) = 0;

    virtual antlrcpp::Any visitEnum_type(IDLParser::Enum_typeContext *context) = 0;

    virtual antlrcpp::Any visitEnum_elements(IDLParser::Enum_elementsContext *context) = 0;

    virtual antlrcpp::Any visitEnum_item(IDLParser::Enum_itemContext *context) = 0;

    virtual antlrcpp::Any visitEnum_expr(IDLParser::Enum_exprContext *context) = 0;

    virtual antlrcpp::Any visitExpr_add_sub(IDLParser::Expr_add_subContext *context) = 0;

    virtual antlrcpp::Any visitExpr_mul_div(IDLParser::Expr_mul_divContext *context) = 0;

    virtual antlrcpp::Any visitExpr_shift(IDLParser::Expr_shiftContext *context) = 0;

    virtual antlrcpp::Any visitExpr_logical(IDLParser::Expr_logicalContext *context) = 0;

    virtual antlrcpp::Any visitExpr_value(IDLParser::Expr_valueContext *context) = 0;

    virtual antlrcpp::Any visitAny_literal(IDLParser::Any_literalContext *context) = 0;

    virtual antlrcpp::Any visitNumeric_lit(IDLParser::Numeric_litContext *context) = 0;

    virtual antlrcpp::Any visitInteger_lit(IDLParser::Integer_litContext *context) = 0;

    virtual antlrcpp::Any visitFloat_lit(IDLParser::Float_litContext *context) = 0;

    virtual antlrcpp::Any visitString_lit(IDLParser::String_litContext *context) = 0;

    virtual antlrcpp::Any visitChar_lit(IDLParser::Char_litContext *context) = 0;

    virtual antlrcpp::Any visitQualified_ident(IDLParser::Qualified_identContext *context) = 0;

    virtual antlrcpp::Any visitQualified_part(IDLParser::Qualified_partContext *context) = 0;

    virtual antlrcpp::Any visitQualified_separator(IDLParser::Qualified_separatorContext *context) = 0;

    virtual antlrcpp::Any visitAll_or_ident(IDLParser::All_or_identContext *context) = 0;

    virtual antlrcpp::Any visitMember_decl(IDLParser::Member_declContext *context) = 0;

    virtual antlrcpp::Any visitMember_init(IDLParser::Member_initContext *context) = 0;

    virtual antlrcpp::Any visitMember_init_value(IDLParser::Member_init_valueContext *context) = 0;

    virtual antlrcpp::Any visitInit_as_type(IDLParser::Init_as_typeContext *context) = 0;

    virtual antlrcpp::Any visitType_decl(IDLParser::Type_declContext *context) = 0;

    virtual antlrcpp::Any visitType_modifier(IDLParser::Type_modifierContext *context) = 0;

    virtual antlrcpp::Any visitPointer_type(IDLParser::Pointer_typeContext *context) = 0;

    virtual antlrcpp::Any visitPointer_decl(IDLParser::Pointer_declContext *context) = 0;

    virtual antlrcpp::Any visitAny_type(IDLParser::Any_typeContext *context) = 0;

    virtual antlrcpp::Any visitUtility_type(IDLParser::Utility_typeContext *context) = 0;

    virtual antlrcpp::Any visitIntegral_type(IDLParser::Integral_typeContext *context) = 0;

    virtual antlrcpp::Any visitFloat_type(IDLParser::Float_typeContext *context) = 0;

    virtual antlrcpp::Any visitTemplate_type(IDLParser::Template_typeContext *context) = 0;

    virtual antlrcpp::Any visitTemplate_params(IDLParser::Template_paramsContext *context) = 0;

    virtual antlrcpp::Any visitTemplate_param(IDLParser::Template_paramContext *context) = 0;


};

