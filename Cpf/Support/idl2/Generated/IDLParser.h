
// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLParser : public antlr4::Parser {
public:
  enum {
    IMPORT = 1, STRING_LIT = 2, SEMICOLON = 3, NAMESPACE = 4, IDENT = 5, 
    LBRACE = 6, RBRACE = 7, STRUCT = 8, INTERFACE = 9, COLON = 10, LPAREN = 11, 
    RPAREN = 12, COMMA = 13, LBRACKET = 14, IN = 15, RBRACKET = 16, OUT = 17, 
    CONST = 18, STAR = 19, VOID = 20, RESULT = 21, U8 = 22, S8 = 23, CHAR = 24, 
    BYTE = 25, U16 = 26, S16 = 27, SHORT = 28, U32 = 29, S32 = 30, INT = 31, 
    U64 = 32, S64 = 33, F32 = 34, FLOAT = 35, F64 = 36, DOUBLE = 37
  };

  enum {
    RuleMain = 0, RuleGlobal_statements = 1, RuleGlobal_statement = 2, RuleImport_stmt = 3, 
    RuleNamespace_stmt = 4, RuleNamespace_block = 5, RuleNamespace_item = 6, 
    RuleStruct_stmt = 7, RuleStruct_decl = 8, RuleStruct_fwd = 9, RuleStruct_block = 10, 
    RuleStruct_item = 11, RuleInterface_stmt = 12, RuleInterface_fwd = 13, 
    RuleInterface_decl = 14, RuleInterface_super = 15, RuleInterface_block = 16, 
    RuleInterface_item = 17, RuleFunction_decl = 18, RuleFunction_param_list = 19, 
    RuleFunction_param = 20, RuleParam_dir_qualifier = 21, RuleQualified_ident = 22, 
    RuleQualified_part_opt = 23, RuleQualified_part = 24, RuleQualified_separator = 25, 
    RuleMember_decl = 26, RuleType_decl = 27, RuleType_modifier = 28, RulePointer_opt_type = 29, 
    RuleAny_type = 30, RuleUtility_type = 31, RuleIntegral_type = 32, RuleFloat_type = 33
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
  class Import_stmtContext;
  class Namespace_stmtContext;
  class Namespace_blockContext;
  class Namespace_itemContext;
  class Struct_stmtContext;
  class Struct_declContext;
  class Struct_fwdContext;
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
  class Qualified_identContext;
  class Qualified_part_optContext;
  class Qualified_partContext;
  class Qualified_separatorContext;
  class Member_declContext;
  class Type_declContext;
  class Type_modifierContext;
  class Pointer_opt_typeContext;
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MainContext* main();

  class  Global_statementsContext : public antlr4::ParserRuleContext {
  public:
    Global_statementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Global_statementContext *> global_statement();
    Global_statementContext* global_statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_statementsContext* global_statements();

  class  Global_statementContext : public antlr4::ParserRuleContext {
  public:
    Global_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Import_stmtContext *import_stmt();
    Namespace_stmtContext *namespace_stmt();
    Struct_stmtContext *struct_stmt();
    Interface_stmtContext *interface_stmt();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_statementContext* global_statement();

  class  Import_stmtContext : public antlr4::ParserRuleContext {
  public:
    Import_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *STRING_LIT();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Import_stmtContext* import_stmt();

  class  Namespace_stmtContext : public antlr4::ParserRuleContext {
  public:
    Namespace_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMESPACE();
    antlr4::tree::TerminalNode *IDENT();
    Namespace_blockContext *namespace_block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_stmtContext* namespace_stmt();

  class  Namespace_blockContext : public antlr4::ParserRuleContext {
  public:
    Namespace_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<Namespace_itemContext *> namespace_item();
    Namespace_itemContext* namespace_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_blockContext* namespace_block();

  class  Namespace_itemContext : public antlr4::ParserRuleContext {
  public:
    Namespace_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Struct_stmtContext *struct_stmt();
    Namespace_stmtContext *namespace_stmt();
    Interface_stmtContext *interface_stmt();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_itemContext* namespace_item();

  class  Struct_stmtContext : public antlr4::ParserRuleContext {
  public:
    Struct_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Struct_declContext *struct_decl();
    Struct_fwdContext *struct_fwd();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Struct_stmtContext* struct_stmt();

  class  Struct_declContext : public antlr4::ParserRuleContext {
  public:
    Struct_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *IDENT();
    Struct_blockContext *struct_block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Struct_declContext* struct_decl();

  class  Struct_fwdContext : public antlr4::ParserRuleContext {
  public:
    Struct_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Struct_fwdContext* struct_fwd();

  class  Struct_blockContext : public antlr4::ParserRuleContext {
  public:
    Struct_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<Struct_itemContext *> struct_item();
    Struct_itemContext* struct_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Struct_blockContext* struct_block();

  class  Struct_itemContext : public antlr4::ParserRuleContext {
  public:
    Struct_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_declContext *member_decl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Struct_itemContext* struct_item();

  class  Interface_stmtContext : public antlr4::ParserRuleContext {
  public:
    Interface_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interface_declContext *interface_decl();
    Interface_fwdContext *interface_fwd();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Interface_stmtContext* interface_stmt();

  class  Interface_fwdContext : public antlr4::ParserRuleContext {
  public:
    Interface_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Interface_declContext* interface_decl();

  class  Interface_superContext : public antlr4::ParserRuleContext {
  public:
    Interface_superContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    Qualified_identContext *qualified_ident();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Interface_blockContext* interface_block();

  class  Interface_itemContext : public antlr4::ParserRuleContext {
  public:
    Interface_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_declContext *function_decl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_param_listContext* function_param_list();

  class  Function_paramContext : public antlr4::ParserRuleContext {
  public:
    Function_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Pointer_opt_typeContext *pointer_opt_type();
    antlr4::tree::TerminalNode *IDENT();
    Param_dir_qualifierContext *param_dir_qualifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Param_dir_qualifierContext* param_dir_qualifier();

  class  Qualified_identContext : public antlr4::ParserRuleContext {
  public:
    Qualified_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    Qualified_part_optContext *qualified_part_opt();
    Qualified_separatorContext *qualified_separator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Qualified_identContext* qualified_ident();

  class  Qualified_part_optContext : public antlr4::ParserRuleContext {
  public:
    Qualified_part_optContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_partContext *qualified_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Qualified_part_optContext* qualified_part_opt();

  class  Qualified_partContext : public antlr4::ParserRuleContext {
  public:
    Qualified_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_separatorContext *qualified_separator();
    antlr4::tree::TerminalNode *IDENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Qualified_partContext* qualified_part();

  class  Qualified_separatorContext : public antlr4::ParserRuleContext {
  public:
    Qualified_separatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Qualified_separatorContext* qualified_separator();

  class  Member_declContext : public antlr4::ParserRuleContext {
  public:
    Member_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Member_declContext* member_decl();

  class  Type_declContext : public antlr4::ParserRuleContext {
  public:
    Type_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Pointer_opt_typeContext *pointer_opt_type();
    Type_modifierContext *type_modifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_declContext* type_decl();

  class  Type_modifierContext : public antlr4::ParserRuleContext {
  public:
    Type_modifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONST();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_modifierContext* type_modifier();

  class  Pointer_opt_typeContext : public antlr4::ParserRuleContext {
  public:
    Pointer_opt_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Any_typeContext *any_type();
    std::vector<antlr4::tree::TerminalNode *> STAR();
    antlr4::tree::TerminalNode* STAR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Pointer_opt_typeContext* pointer_opt_type();

  class  Any_typeContext : public antlr4::ParserRuleContext {
  public:
    Any_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Integral_typeContext *integral_type();
    Float_typeContext *float_type();
    Utility_typeContext *utility_type();
    antlr4::tree::TerminalNode *IDENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Any_typeContext* any_type();

  class  Utility_typeContext : public antlr4::ParserRuleContext {
  public:
    Utility_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *RESULT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Utility_typeContext* utility_type();

  class  Integral_typeContext : public antlr4::ParserRuleContext {
  public:
    Integral_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *U8();
    antlr4::tree::TerminalNode *S8();
    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *BYTE();
    antlr4::tree::TerminalNode *U16();
    antlr4::tree::TerminalNode *S16();
    antlr4::tree::TerminalNode *SHORT();
    antlr4::tree::TerminalNode *U32();
    antlr4::tree::TerminalNode *S32();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *U64();
    antlr4::tree::TerminalNode *S64();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Integral_typeContext* integral_type();

  class  Float_typeContext : public antlr4::ParserRuleContext {
  public:
    Float_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *F32();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *F64();
    antlr4::tree::TerminalNode *DOUBLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Float_typeContext* float_type();


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

