
// Generated from C:/Projects/Cpf/Cpf/Support/idl\IDLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLParser : public antlr4::Parser {
public:
  enum {
    IMPORT = 1, STRUCT = 2, UNION = 3, INTERFACE = 4, ENUM = 5, MODULE = 6, 
    FROM = 7, IN = 8, OUT = 9, COLON = 10, SEMICOLON = 11, STAR = 12, SLASH = 13, 
    DOT = 14, COMMA = 15, EQUALS = 16, QUOTE = 17, LBRACE = 18, RBRACE = 19, 
    LPAREN = 20, RPAREN = 21, LBRACKET = 22, RBRACKET = 23, LT = 24, GT = 25, 
    PLUS = 26, MINUS = 27, LSHIFT = 28, RSHIFT = 29, Const = 30, Void = 31, 
    RESULT = 32, SUCCESS = 33, FAILURE = 34, CLASS_ID = 35, STRING = 36, 
    U8 = 37, S8 = 38, U16 = 39, S16 = 40, U32 = 41, S32 = 42, U64 = 43, 
    S64 = 44, F32 = 45, F64 = 46, IDENT = 47, DECIMAL_LIT = 48, HEX_LIT = 49, 
    BIN_LIT = 50, OCT_LIT = 51, STRING_LIT = 52, FLOAT_LIT = 53, WHITE_SPACE = 54, 
    BLOCK_COMMENT = 55, LINE_COMMENT = 56
  };

  enum {
    RuleMain = 0, RuleGlobal_statements = 1, RuleGlobal_statement = 2, RuleEmpty_stmt = 3, 
    RuleModule_stmt = 4, RuleError_code_stmt = 5, RuleSuccess_stmt = 6, 
    RuleFailure_stmt = 7, RuleImport_from_stmt = 8, RuleImport_stmt = 9, 
    RuleStruct_stmt = 10, RuleStruct_decl = 11, RuleStruct_fwd = 12, RuleUnion_stmt = 13, 
    RuleUnion_decl = 14, RuleUnion_fwd = 15, RuleStruct_block = 16, RuleStruct_item = 17, 
    RuleInterface_stmt = 18, RuleInterface_fwd = 19, RuleInterface_decl = 20, 
    RuleInterface_super = 21, RuleInterface_block = 22, RuleInterface_item = 23, 
    RuleFunction_decl = 24, RuleFunction_param_list = 25, RuleFunction_param = 26, 
    RuleParam_dir_qualifier = 27, RuleConst_def = 28, RuleConst_integral_def = 29, 
    RuleConst_float_def = 30, RuleConst_string_def = 31, RuleConst_class_id_def = 32, 
    RuleEnum_fwd = 33, RuleEnum_def = 34, RuleEnum_type = 35, RuleEnum_elements = 36, 
    RuleEnum_item = 37, RuleEnum_expr = 38, RuleExpr_add_sub = 39, RuleExpr_mul_div = 40, 
    RuleExpr_shift = 41, RuleExpr_value = 42, RuleAny_literal = 43, RuleNumeric_lit = 44, 
    RuleInteger_lit = 45, RuleFloat_lit = 46, RuleString_lit = 47, RuleQualified_ident = 48, 
    RuleQualified_part = 49, RuleQualified_separator = 50, RuleAll_or_ident = 51, 
    RuleMember_decl = 52, RuleType_decl = 53, RuleType_modifier = 54, RulePointer_type = 55, 
    RulePointer_decl = 56, RuleAny_type = 57, RuleUtility_type = 58, RuleIntegral_type = 59, 
    RuleFloat_type = 60
  };

  IDLParser(antlr4::TokenStream *input);
  ~IDLParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class MainContext;
  class Global_statementsContext;
  class Global_statementContext;
  class Empty_stmtContext;
  class Module_stmtContext;
  class Error_code_stmtContext;
  class Success_stmtContext;
  class Failure_stmtContext;
  class Import_from_stmtContext;
  class Import_stmtContext;
  class Struct_stmtContext;
  class Struct_declContext;
  class Struct_fwdContext;
  class Union_stmtContext;
  class Union_declContext;
  class Union_fwdContext;
  class Struct_blockContext;
  class Struct_itemContext;
  class Interface_stmtContext;
  class Interface_fwdContext;
  class Interface_declContext;
  class Interface_superContext;
  class Interface_blockContext;
  class Interface_itemContext;
  class Function_declContext;
  class Function_param_listContext;
  class Function_paramContext;
  class Param_dir_qualifierContext;
  class Const_defContext;
  class Const_integral_defContext;
  class Const_float_defContext;
  class Const_string_defContext;
  class Const_class_id_defContext;
  class Enum_fwdContext;
  class Enum_defContext;
  class Enum_typeContext;
  class Enum_elementsContext;
  class Enum_itemContext;
  class Enum_exprContext;
  class Expr_add_subContext;
  class Expr_mul_divContext;
  class Expr_shiftContext;
  class Expr_valueContext;
  class Any_literalContext;
  class Numeric_litContext;
  class Integer_litContext;
  class Float_litContext;
  class String_litContext;
  class Qualified_identContext;
  class Qualified_partContext;
  class Qualified_separatorContext;
  class All_or_identContext;
  class Member_declContext;
  class Type_declContext;
  class Type_modifierContext;
  class Pointer_typeContext;
  class Pointer_declContext;
  class Any_typeContext;
  class Utility_typeContext;
  class Integral_typeContext;
  class Float_typeContext; 

  class  MainContext : public antlr4::ParserRuleContext {
  public:
    MainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    Global_statementsContext *global_statements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MainContext* main();

  class  Global_statementsContext : public antlr4::ParserRuleContext {
  public:
    Global_statementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Global_statementContext *> global_statement();
    Global_statementContext* global_statement(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_statementsContext* global_statements();

  class  Global_statementContext : public antlr4::ParserRuleContext {
  public:
    Global_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Import_stmtContext *import_stmt();
    Struct_stmtContext *struct_stmt();
    Union_stmtContext *union_stmt();
    Interface_stmtContext *interface_stmt();
    Const_defContext *const_def();
    Enum_defContext *enum_def();
    Enum_fwdContext *enum_fwd();
    Module_stmtContext *module_stmt();
    Error_code_stmtContext *error_code_stmt();
    Empty_stmtContext *empty_stmt();
    Import_from_stmtContext *import_from_stmt();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_statementContext* global_statement();

  class  Empty_stmtContext : public antlr4::ParserRuleContext {
  public:
    Empty_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Empty_stmtContext* empty_stmt();

  class  Module_stmtContext : public antlr4::ParserRuleContext {
  public:
    Module_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MODULE();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Module_stmtContext* module_stmt();

  class  Error_code_stmtContext : public antlr4::ParserRuleContext {
  public:
    Error_code_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Success_stmtContext *success_stmt();
    Failure_stmtContext *failure_stmt();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Error_code_stmtContext* error_code_stmt();

  class  Success_stmtContext : public antlr4::ParserRuleContext {
  public:
    Success_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUCCESS();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> STRING_LIT();
    antlr4::tree::TerminalNode* STRING_LIT(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Success_stmtContext* success_stmt();

  class  Failure_stmtContext : public antlr4::ParserRuleContext {
  public:
    Failure_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FAILURE();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> STRING_LIT();
    antlr4::tree::TerminalNode* STRING_LIT(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Failure_stmtContext* failure_stmt();

  class  Import_from_stmtContext : public antlr4::ParserRuleContext {
  public:
    Import_from_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    All_or_identContext *all_or_ident();
    antlr4::tree::TerminalNode *FROM();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Import_from_stmtContext* import_from_stmt();

  class  Import_stmtContext : public antlr4::ParserRuleContext {
  public:
    Import_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    String_litContext *string_lit();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Import_stmtContext* import_stmt();

  class  Struct_stmtContext : public antlr4::ParserRuleContext {
  public:
    Struct_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Struct_declContext *struct_decl();
    Struct_fwdContext *struct_fwd();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_stmtContext* struct_stmt();

  class  Struct_declContext : public antlr4::ParserRuleContext {
  public:
    Struct_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *IDENT();
    Struct_blockContext *struct_block();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_declContext* struct_decl();

  class  Struct_fwdContext : public antlr4::ParserRuleContext {
  public:
    Struct_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_fwdContext* struct_fwd();

  class  Union_stmtContext : public antlr4::ParserRuleContext {
  public:
    Union_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Union_declContext *union_decl();
    Union_fwdContext *union_fwd();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Union_stmtContext* union_stmt();

  class  Union_declContext : public antlr4::ParserRuleContext {
  public:
    Union_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNION();
    antlr4::tree::TerminalNode *IDENT();
    Struct_blockContext *struct_block();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Union_declContext* union_decl();

  class  Union_fwdContext : public antlr4::ParserRuleContext {
  public:
    Union_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNION();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Union_fwdContext* union_fwd();

  class  Struct_blockContext : public antlr4::ParserRuleContext {
  public:
    Struct_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<Struct_itemContext *> struct_item();
    Struct_itemContext* struct_item(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_blockContext* struct_block();

  class  Struct_itemContext : public antlr4::ParserRuleContext {
  public:
    Struct_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_declContext *member_decl();
    Const_defContext *const_def();
    Enum_defContext *enum_def();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_itemContext* struct_item();

  class  Interface_stmtContext : public antlr4::ParserRuleContext {
  public:
    Interface_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interface_declContext *interface_decl();
    Interface_fwdContext *interface_fwd();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_stmtContext* interface_stmt();

  class  Interface_fwdContext : public antlr4::ParserRuleContext {
  public:
    Interface_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_fwdContext* interface_fwd();

  class  Interface_declContext : public antlr4::ParserRuleContext {
  public:
    Interface_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    antlr4::tree::TerminalNode *IDENT();
    Interface_blockContext *interface_block();
    Interface_superContext *interface_super();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_declContext* interface_decl();

  class  Interface_superContext : public antlr4::ParserRuleContext {
  public:
    Interface_superContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    Qualified_identContext *qualified_ident();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_superContext* interface_super();

  class  Interface_blockContext : public antlr4::ParserRuleContext {
  public:
    Interface_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<Interface_itemContext *> interface_item();
    Interface_itemContext* interface_item(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_blockContext* interface_block();

  class  Interface_itemContext : public antlr4::ParserRuleContext {
  public:
    Interface_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_declContext *function_decl();
    Const_defContext *const_def();
    Enum_defContext *enum_def();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_itemContext* interface_item();

  class  Function_declContext : public antlr4::ParserRuleContext {
  public:
    Function_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Function_param_listContext *function_param_list();
    antlr4::tree::TerminalNode *Const();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_declContext* function_decl();

  class  Function_param_listContext : public antlr4::ParserRuleContext {
  public:
    Function_param_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Function_paramContext *> function_param();
    Function_paramContext* function_param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_param_listContext* function_param_list();

  class  Function_paramContext : public antlr4::ParserRuleContext {
  public:
    Function_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *IDENT();
    Param_dir_qualifierContext *param_dir_qualifier();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_paramContext* function_param();

  class  Param_dir_qualifierContext : public antlr4::ParserRuleContext {
  public:
    Param_dir_qualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *OUT();
    antlr4::tree::TerminalNode *COMMA();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Param_dir_qualifierContext* param_dir_qualifier();

  class  Const_defContext : public antlr4::ParserRuleContext {
  public:
    Const_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Const_integral_defContext *const_integral_def();
    Const_float_defContext *const_float_def();
    Const_string_defContext *const_string_def();
    Const_class_id_defContext *const_class_id_def();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_defContext* const_def();

  class  Const_integral_defContext : public antlr4::ParserRuleContext {
  public:
    Const_integral_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    Integral_typeContext *integral_type();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    Integer_litContext *integer_lit();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_integral_defContext* const_integral_def();

  class  Const_float_defContext : public antlr4::ParserRuleContext {
  public:
    Const_float_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    Float_typeContext *float_type();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    Float_litContext *float_lit();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_float_defContext* const_float_def();

  class  Const_string_defContext : public antlr4::ParserRuleContext {
  public:
    Const_string_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    String_litContext *string_lit();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_string_defContext* const_string_def();

  class  Const_class_id_defContext : public antlr4::ParserRuleContext {
  public:
    Const_class_id_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    antlr4::tree::TerminalNode *CLASS_ID();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    String_litContext *string_lit();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_class_id_defContext* const_class_id_def();

  class  Enum_fwdContext : public antlr4::ParserRuleContext {
  public:
    Enum_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();
    Enum_typeContext *enum_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_fwdContext* enum_fwd();

  class  Enum_defContext : public antlr4::ParserRuleContext {
  public:
    Enum_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LBRACE();
    Enum_elementsContext *enum_elements();
    antlr4::tree::TerminalNode *RBRACE();
    Enum_typeContext *enum_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_defContext* enum_def();

  class  Enum_typeContext : public antlr4::ParserRuleContext {
  public:
    Enum_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    Integral_typeContext *integral_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_typeContext* enum_type();

  class  Enum_elementsContext : public antlr4::ParserRuleContext {
  public:
    Enum_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Enum_itemContext *> enum_item();
    Enum_itemContext* enum_item(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_elementsContext* enum_elements();

  class  Enum_itemContext : public antlr4::ParserRuleContext {
  public:
    Enum_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    Enum_exprContext *enum_expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_itemContext* enum_item();

  class  Enum_exprContext : public antlr4::ParserRuleContext {
  public:
    Enum_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_add_subContext *expr_add_sub();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_exprContext* enum_expr();

  class  Expr_add_subContext : public antlr4::ParserRuleContext {
  public:
    Expr_add_subContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_mul_divContext *expr_mul_div();
    Expr_add_subContext *expr_add_sub();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_add_subContext* expr_add_sub();
  Expr_add_subContext* expr_add_sub(int precedence);
  class  Expr_mul_divContext : public antlr4::ParserRuleContext {
  public:
    Expr_mul_divContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_shiftContext *expr_shift();
    Expr_mul_divContext *expr_mul_div();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_mul_divContext* expr_mul_div();
  Expr_mul_divContext* expr_mul_div(int precedence);
  class  Expr_shiftContext : public antlr4::ParserRuleContext {
  public:
    Expr_shiftContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_valueContext *expr_value();
    Expr_shiftContext *expr_shift();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_shiftContext* expr_shift();
  Expr_shiftContext* expr_shift(int precedence);
  class  Expr_valueContext : public antlr4::ParserRuleContext {
  public:
    Expr_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Integer_litContext *integer_lit();
    antlr4::tree::TerminalNode *LPAREN();
    Enum_exprContext *enum_expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_valueContext* expr_value();

  class  Any_literalContext : public antlr4::ParserRuleContext {
  public:
    Any_literalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Numeric_litContext *numeric_lit();
    String_litContext *string_lit();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Any_literalContext* any_literal();

  class  Numeric_litContext : public antlr4::ParserRuleContext {
  public:
    Numeric_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Integer_litContext *integer_lit();
    Float_litContext *float_lit();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Numeric_litContext* numeric_lit();

  class  Integer_litContext : public antlr4::ParserRuleContext {
  public:
    Integer_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_LIT();
    antlr4::tree::TerminalNode *HEX_LIT();
    antlr4::tree::TerminalNode *OCT_LIT();
    antlr4::tree::TerminalNode *BIN_LIT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Integer_litContext* integer_lit();

  class  Float_litContext : public antlr4::ParserRuleContext {
  public:
    Float_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT_LIT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Float_litContext* float_lit();

  class  String_litContext : public antlr4::ParserRuleContext {
  public:
    String_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LIT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  String_litContext* string_lit();

  class  Qualified_identContext : public antlr4::ParserRuleContext {
  public:
    Qualified_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    Qualified_separatorContext *qualified_separator();
    std::vector<Qualified_partContext *> qualified_part();
    Qualified_partContext* qualified_part(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qualified_identContext* qualified_ident();

  class  Qualified_partContext : public antlr4::ParserRuleContext {
  public:
    Qualified_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_separatorContext *qualified_separator();
    antlr4::tree::TerminalNode *IDENT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qualified_partContext* qualified_part();

  class  Qualified_separatorContext : public antlr4::ParserRuleContext {
  public:
    Qualified_separatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qualified_separatorContext* qualified_separator();

  class  All_or_identContext : public antlr4::ParserRuleContext {
  public:
    All_or_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *STAR();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  All_or_identContext* all_or_ident();

  class  Member_declContext : public antlr4::ParserRuleContext {
  public:
    Member_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *LBRACKET();
    Integer_litContext *integer_lit();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_declContext* member_decl();

  class  Type_declContext : public antlr4::ParserRuleContext {
  public:
    Type_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Any_typeContext *any_type();
    Type_modifierContext *type_modifier();
    Pointer_typeContext *pointer_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_declContext* type_decl();

  class  Type_modifierContext : public antlr4::ParserRuleContext {
  public:
    Type_modifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_modifierContext* type_modifier();

  class  Pointer_typeContext : public antlr4::ParserRuleContext {
  public:
    Pointer_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Pointer_declContext *> pointer_decl();
    Pointer_declContext* pointer_decl(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pointer_typeContext* pointer_type();

  class  Pointer_declContext : public antlr4::ParserRuleContext {
  public:
    Pointer_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *Const();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pointer_declContext* pointer_decl();

  class  Any_typeContext : public antlr4::ParserRuleContext {
  public:
    Any_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Integral_typeContext *integral_type();
    Float_typeContext *float_type();
    Utility_typeContext *utility_type();
    Qualified_identContext *qualified_ident();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Any_typeContext* any_type();

  class  Utility_typeContext : public antlr4::ParserRuleContext {
  public:
    Utility_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *RESULT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Utility_typeContext* utility_type();

  class  Integral_typeContext : public antlr4::ParserRuleContext {
  public:
    Integral_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *U8();
    antlr4::tree::TerminalNode *S8();
    antlr4::tree::TerminalNode *U16();
    antlr4::tree::TerminalNode *S16();
    antlr4::tree::TerminalNode *U32();
    antlr4::tree::TerminalNode *S32();
    antlr4::tree::TerminalNode *U64();
    antlr4::tree::TerminalNode *S64();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Integral_typeContext* integral_type();

  class  Float_typeContext : public antlr4::ParserRuleContext {
  public:
    Float_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *F32();
    antlr4::tree::TerminalNode *F64();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Float_typeContext* float_type();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool expr_add_subSempred(Expr_add_subContext *_localctx, size_t predicateIndex);
  bool expr_mul_divSempred(Expr_mul_divContext *_localctx, size_t predicateIndex);
  bool expr_shiftSempred(Expr_shiftContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

