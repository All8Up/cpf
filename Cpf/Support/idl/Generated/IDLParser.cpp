
// Generated from C:/Projects/Cpf/Cpf/Support/idl\IDLParser.g4 by ANTLR 4.7


#include "IDLParserVisitor.h"

#include "IDLParser.h"


using namespace antlrcpp;
using namespace antlr4;

IDLParser::IDLParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

IDLParser::~IDLParser() {
  delete _interpreter;
}

std::string IDLParser::getGrammarFileName() const {
  return "IDLParser.g4";
}

const std::vector<std::string>& IDLParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& IDLParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- MainContext ------------------------------------------------------------------

IDLParser::MainContext::MainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::MainContext::EOF() {
  return getToken(IDLParser::EOF, 0);
}

IDLParser::Global_statementsContext* IDLParser::MainContext::global_statements() {
  return getRuleContext<IDLParser::Global_statementsContext>(0);
}


size_t IDLParser::MainContext::getRuleIndex() const {
  return IDLParser::RuleMain;
}

antlrcpp::Any IDLParser::MainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitMain(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::MainContext* IDLParser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 0, IDLParser::RuleMain);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::DEFAULTS)
      | (1ULL << IDLParser::UNION)
      | (1ULL << IDLParser::INTERFACE)
      | (1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::FLAGS)
      | (1ULL << IDLParser::MODULE)
      | (1ULL << IDLParser::SEMICOLON)
      | (1ULL << IDLParser::Const)
      | (1ULL << IDLParser::SUCCESS)
      | (1ULL << IDLParser::FAILURE))) != 0)) {
      setState(144);
      global_statements();
    }
    setState(147);
    match(IDLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_statementsContext ------------------------------------------------------------------

IDLParser::Global_statementsContext::Global_statementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IDLParser::Global_statementContext *> IDLParser::Global_statementsContext::global_statement() {
  return getRuleContexts<IDLParser::Global_statementContext>();
}

IDLParser::Global_statementContext* IDLParser::Global_statementsContext::global_statement(size_t i) {
  return getRuleContext<IDLParser::Global_statementContext>(i);
}


size_t IDLParser::Global_statementsContext::getRuleIndex() const {
  return IDLParser::RuleGlobal_statements;
}

antlrcpp::Any IDLParser::Global_statementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitGlobal_statements(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Global_statementsContext* IDLParser::global_statements() {
  Global_statementsContext *_localctx = _tracker.createInstance<Global_statementsContext>(_ctx, getState());
  enterRule(_localctx, 2, IDLParser::RuleGlobal_statements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(149);
      global_statement();
      setState(152); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::DEFAULTS)
      | (1ULL << IDLParser::UNION)
      | (1ULL << IDLParser::INTERFACE)
      | (1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::FLAGS)
      | (1ULL << IDLParser::MODULE)
      | (1ULL << IDLParser::SEMICOLON)
      | (1ULL << IDLParser::Const)
      | (1ULL << IDLParser::SUCCESS)
      | (1ULL << IDLParser::FAILURE))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_statementContext ------------------------------------------------------------------

IDLParser::Global_statementContext::Global_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Import_stmtContext* IDLParser::Global_statementContext::import_stmt() {
  return getRuleContext<IDLParser::Import_stmtContext>(0);
}

IDLParser::Struct_stmtContext* IDLParser::Global_statementContext::struct_stmt() {
  return getRuleContext<IDLParser::Struct_stmtContext>(0);
}

IDLParser::Defaults_stmtContext* IDLParser::Global_statementContext::defaults_stmt() {
  return getRuleContext<IDLParser::Defaults_stmtContext>(0);
}

IDLParser::Union_stmtContext* IDLParser::Global_statementContext::union_stmt() {
  return getRuleContext<IDLParser::Union_stmtContext>(0);
}

IDLParser::Interface_stmtContext* IDLParser::Global_statementContext::interface_stmt() {
  return getRuleContext<IDLParser::Interface_stmtContext>(0);
}

IDLParser::Const_defContext* IDLParser::Global_statementContext::const_def() {
  return getRuleContext<IDLParser::Const_defContext>(0);
}

IDLParser::Enum_defContext* IDLParser::Global_statementContext::enum_def() {
  return getRuleContext<IDLParser::Enum_defContext>(0);
}

IDLParser::Flags_fwdContext* IDLParser::Global_statementContext::flags_fwd() {
  return getRuleContext<IDLParser::Flags_fwdContext>(0);
}

IDLParser::Flags_defContext* IDLParser::Global_statementContext::flags_def() {
  return getRuleContext<IDLParser::Flags_defContext>(0);
}

IDLParser::Enum_fwdContext* IDLParser::Global_statementContext::enum_fwd() {
  return getRuleContext<IDLParser::Enum_fwdContext>(0);
}

IDLParser::Module_stmtContext* IDLParser::Global_statementContext::module_stmt() {
  return getRuleContext<IDLParser::Module_stmtContext>(0);
}

IDLParser::Error_code_stmtContext* IDLParser::Global_statementContext::error_code_stmt() {
  return getRuleContext<IDLParser::Error_code_stmtContext>(0);
}

IDLParser::Empty_stmtContext* IDLParser::Global_statementContext::empty_stmt() {
  return getRuleContext<IDLParser::Empty_stmtContext>(0);
}

IDLParser::Import_from_stmtContext* IDLParser::Global_statementContext::import_from_stmt() {
  return getRuleContext<IDLParser::Import_from_stmtContext>(0);
}


size_t IDLParser::Global_statementContext::getRuleIndex() const {
  return IDLParser::RuleGlobal_statement;
}

antlrcpp::Any IDLParser::Global_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitGlobal_statement(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Global_statementContext* IDLParser::global_statement() {
  Global_statementContext *_localctx = _tracker.createInstance<Global_statementContext>(_ctx, getState());
  enterRule(_localctx, 4, IDLParser::RuleGlobal_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(169);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(154);
      import_stmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(155);
      struct_stmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(156);
      defaults_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(157);
      union_stmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(158);
      interface_stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(159);
      const_def();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(160);
      enum_def();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(161);
      flags_fwd();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(162);
      flags_def();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(163);
      enum_fwd();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(164);
      module_stmt();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(165);
      error_code_stmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(166);
      empty_stmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(167);
      import_stmt();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(168);
      import_from_stmt();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Empty_stmtContext ------------------------------------------------------------------

IDLParser::Empty_stmtContext::Empty_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Empty_stmtContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Empty_stmtContext::getRuleIndex() const {
  return IDLParser::RuleEmpty_stmt;
}

antlrcpp::Any IDLParser::Empty_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEmpty_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Empty_stmtContext* IDLParser::empty_stmt() {
  Empty_stmtContext *_localctx = _tracker.createInstance<Empty_stmtContext>(_ctx, getState());
  enterRule(_localctx, 6, IDLParser::RuleEmpty_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(171);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Module_stmtContext ------------------------------------------------------------------

IDLParser::Module_stmtContext::Module_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Module_stmtContext::MODULE() {
  return getToken(IDLParser::MODULE, 0);
}

IDLParser::Qualified_identContext* IDLParser::Module_stmtContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

tree::TerminalNode* IDLParser::Module_stmtContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Module_stmtContext::getRuleIndex() const {
  return IDLParser::RuleModule_stmt;
}

antlrcpp::Any IDLParser::Module_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitModule_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Module_stmtContext* IDLParser::module_stmt() {
  Module_stmtContext *_localctx = _tracker.createInstance<Module_stmtContext>(_ctx, getState());
  enterRule(_localctx, 8, IDLParser::RuleModule_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    match(IDLParser::MODULE);
    setState(174);
    qualified_ident();
    setState(175);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Error_code_stmtContext ------------------------------------------------------------------

IDLParser::Error_code_stmtContext::Error_code_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Success_stmtContext* IDLParser::Error_code_stmtContext::success_stmt() {
  return getRuleContext<IDLParser::Success_stmtContext>(0);
}

IDLParser::Failure_stmtContext* IDLParser::Error_code_stmtContext::failure_stmt() {
  return getRuleContext<IDLParser::Failure_stmtContext>(0);
}


size_t IDLParser::Error_code_stmtContext::getRuleIndex() const {
  return IDLParser::RuleError_code_stmt;
}

antlrcpp::Any IDLParser::Error_code_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitError_code_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Error_code_stmtContext* IDLParser::error_code_stmt() {
  Error_code_stmtContext *_localctx = _tracker.createInstance<Error_code_stmtContext>(_ctx, getState());
  enterRule(_localctx, 10, IDLParser::RuleError_code_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(179);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::SUCCESS: {
        enterOuterAlt(_localctx, 1);
        setState(177);
        success_stmt();
        break;
      }

      case IDLParser::FAILURE: {
        enterOuterAlt(_localctx, 2);
        setState(178);
        failure_stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Success_stmtContext ------------------------------------------------------------------

IDLParser::Success_stmtContext::Success_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Success_stmtContext::SUCCESS() {
  return getToken(IDLParser::SUCCESS, 0);
}

tree::TerminalNode* IDLParser::Success_stmtContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Success_stmtContext::LPAREN() {
  return getToken(IDLParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> IDLParser::Success_stmtContext::STRING_LIT() {
  return getTokens(IDLParser::STRING_LIT);
}

tree::TerminalNode* IDLParser::Success_stmtContext::STRING_LIT(size_t i) {
  return getToken(IDLParser::STRING_LIT, i);
}

tree::TerminalNode* IDLParser::Success_stmtContext::COMMA() {
  return getToken(IDLParser::COMMA, 0);
}

tree::TerminalNode* IDLParser::Success_stmtContext::RPAREN() {
  return getToken(IDLParser::RPAREN, 0);
}


size_t IDLParser::Success_stmtContext::getRuleIndex() const {
  return IDLParser::RuleSuccess_stmt;
}

antlrcpp::Any IDLParser::Success_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitSuccess_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Success_stmtContext* IDLParser::success_stmt() {
  Success_stmtContext *_localctx = _tracker.createInstance<Success_stmtContext>(_ctx, getState());
  enterRule(_localctx, 12, IDLParser::RuleSuccess_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    match(IDLParser::SUCCESS);
    setState(182);
    match(IDLParser::IDENT);
    setState(183);
    match(IDLParser::LPAREN);
    setState(184);
    match(IDLParser::STRING_LIT);
    setState(185);
    match(IDLParser::COMMA);
    setState(186);
    match(IDLParser::STRING_LIT);
    setState(187);
    match(IDLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Failure_stmtContext ------------------------------------------------------------------

IDLParser::Failure_stmtContext::Failure_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Failure_stmtContext::FAILURE() {
  return getToken(IDLParser::FAILURE, 0);
}

tree::TerminalNode* IDLParser::Failure_stmtContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Failure_stmtContext::LPAREN() {
  return getToken(IDLParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> IDLParser::Failure_stmtContext::STRING_LIT() {
  return getTokens(IDLParser::STRING_LIT);
}

tree::TerminalNode* IDLParser::Failure_stmtContext::STRING_LIT(size_t i) {
  return getToken(IDLParser::STRING_LIT, i);
}

tree::TerminalNode* IDLParser::Failure_stmtContext::COMMA() {
  return getToken(IDLParser::COMMA, 0);
}

tree::TerminalNode* IDLParser::Failure_stmtContext::RPAREN() {
  return getToken(IDLParser::RPAREN, 0);
}


size_t IDLParser::Failure_stmtContext::getRuleIndex() const {
  return IDLParser::RuleFailure_stmt;
}

antlrcpp::Any IDLParser::Failure_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFailure_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Failure_stmtContext* IDLParser::failure_stmt() {
  Failure_stmtContext *_localctx = _tracker.createInstance<Failure_stmtContext>(_ctx, getState());
  enterRule(_localctx, 14, IDLParser::RuleFailure_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(IDLParser::FAILURE);
    setState(190);
    match(IDLParser::IDENT);
    setState(191);
    match(IDLParser::LPAREN);
    setState(192);
    match(IDLParser::STRING_LIT);
    setState(193);
    match(IDLParser::COMMA);
    setState(194);
    match(IDLParser::STRING_LIT);
    setState(195);
    match(IDLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_from_stmtContext ------------------------------------------------------------------

IDLParser::Import_from_stmtContext::Import_from_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Import_from_stmtContext::IMPORT() {
  return getToken(IDLParser::IMPORT, 0);
}

IDLParser::All_or_identContext* IDLParser::Import_from_stmtContext::all_or_ident() {
  return getRuleContext<IDLParser::All_or_identContext>(0);
}

tree::TerminalNode* IDLParser::Import_from_stmtContext::FROM() {
  return getToken(IDLParser::FROM, 0);
}

IDLParser::Qualified_identContext* IDLParser::Import_from_stmtContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

tree::TerminalNode* IDLParser::Import_from_stmtContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Import_from_stmtContext::getRuleIndex() const {
  return IDLParser::RuleImport_from_stmt;
}

antlrcpp::Any IDLParser::Import_from_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitImport_from_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Import_from_stmtContext* IDLParser::import_from_stmt() {
  Import_from_stmtContext *_localctx = _tracker.createInstance<Import_from_stmtContext>(_ctx, getState());
  enterRule(_localctx, 16, IDLParser::RuleImport_from_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    match(IDLParser::IMPORT);
    setState(198);
    all_or_ident();
    setState(199);
    match(IDLParser::FROM);
    setState(200);
    qualified_ident();
    setState(201);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_stmtContext ------------------------------------------------------------------

IDLParser::Import_stmtContext::Import_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Import_stmtContext::IMPORT() {
  return getToken(IDLParser::IMPORT, 0);
}

tree::TerminalNode* IDLParser::Import_stmtContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Import_stmtContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Import_stmtContext::getRuleIndex() const {
  return IDLParser::RuleImport_stmt;
}

antlrcpp::Any IDLParser::Import_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitImport_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Import_stmtContext* IDLParser::import_stmt() {
  Import_stmtContext *_localctx = _tracker.createInstance<Import_stmtContext>(_ctx, getState());
  enterRule(_localctx, 18, IDLParser::RuleImport_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    match(IDLParser::IMPORT);
    setState(204);
    match(IDLParser::IDENT);
    setState(205);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_stmtContext ------------------------------------------------------------------

IDLParser::Struct_stmtContext::Struct_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Struct_declContext* IDLParser::Struct_stmtContext::struct_decl() {
  return getRuleContext<IDLParser::Struct_declContext>(0);
}

IDLParser::Struct_fwdContext* IDLParser::Struct_stmtContext::struct_fwd() {
  return getRuleContext<IDLParser::Struct_fwdContext>(0);
}


size_t IDLParser::Struct_stmtContext::getRuleIndex() const {
  return IDLParser::RuleStruct_stmt;
}

antlrcpp::Any IDLParser::Struct_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_stmtContext* IDLParser::struct_stmt() {
  Struct_stmtContext *_localctx = _tracker.createInstance<Struct_stmtContext>(_ctx, getState());
  enterRule(_localctx, 20, IDLParser::RuleStruct_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(209);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(207);
      struct_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(208);
      struct_fwd();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_declContext ------------------------------------------------------------------

IDLParser::Struct_declContext::Struct_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Struct_declContext::STRUCT() {
  return getToken(IDLParser::STRUCT, 0);
}

tree::TerminalNode* IDLParser::Struct_declContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

IDLParser::Struct_blockContext* IDLParser::Struct_declContext::struct_block() {
  return getRuleContext<IDLParser::Struct_blockContext>(0);
}


size_t IDLParser::Struct_declContext::getRuleIndex() const {
  return IDLParser::RuleStruct_decl;
}

antlrcpp::Any IDLParser::Struct_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_declContext* IDLParser::struct_decl() {
  Struct_declContext *_localctx = _tracker.createInstance<Struct_declContext>(_ctx, getState());
  enterRule(_localctx, 22, IDLParser::RuleStruct_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(IDLParser::STRUCT);
    setState(212);
    match(IDLParser::IDENT);
    setState(213);
    struct_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_fwdContext ------------------------------------------------------------------

IDLParser::Struct_fwdContext::Struct_fwdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Struct_fwdContext::STRUCT() {
  return getToken(IDLParser::STRUCT, 0);
}

IDLParser::Qualified_identContext* IDLParser::Struct_fwdContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

tree::TerminalNode* IDLParser::Struct_fwdContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Struct_fwdContext::getRuleIndex() const {
  return IDLParser::RuleStruct_fwd;
}

antlrcpp::Any IDLParser::Struct_fwdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_fwd(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_fwdContext* IDLParser::struct_fwd() {
  Struct_fwdContext *_localctx = _tracker.createInstance<Struct_fwdContext>(_ctx, getState());
  enterRule(_localctx, 24, IDLParser::RuleStruct_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    match(IDLParser::STRUCT);
    setState(216);
    qualified_ident();
    setState(217);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Defaults_stmtContext ------------------------------------------------------------------

IDLParser::Defaults_stmtContext::Defaults_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Defaults_stmtContext::DEFAULTS() {
  return getToken(IDLParser::DEFAULTS, 0);
}

tree::TerminalNode* IDLParser::Defaults_stmtContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Defaults_stmtContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

tree::TerminalNode* IDLParser::Defaults_stmtContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

std::vector<IDLParser::Defaults_itemContext *> IDLParser::Defaults_stmtContext::defaults_item() {
  return getRuleContexts<IDLParser::Defaults_itemContext>();
}

IDLParser::Defaults_itemContext* IDLParser::Defaults_stmtContext::defaults_item(size_t i) {
  return getRuleContext<IDLParser::Defaults_itemContext>(i);
}


size_t IDLParser::Defaults_stmtContext::getRuleIndex() const {
  return IDLParser::RuleDefaults_stmt;
}

antlrcpp::Any IDLParser::Defaults_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitDefaults_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Defaults_stmtContext* IDLParser::defaults_stmt() {
  Defaults_stmtContext *_localctx = _tracker.createInstance<Defaults_stmtContext>(_ctx, getState());
  enterRule(_localctx, 26, IDLParser::RuleDefaults_stmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    match(IDLParser::DEFAULTS);
    setState(220);
    match(IDLParser::IDENT);
    setState(221);
    match(IDLParser::LBRACE);
    setState(225);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::IDENT) {
      setState(222);
      defaults_item();
      setState(227);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(228);
    match(IDLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Defaults_itemContext ------------------------------------------------------------------

IDLParser::Defaults_itemContext::Defaults_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Defaults_itemContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Defaults_itemContext::COLON() {
  return getToken(IDLParser::COLON, 0);
}

IDLParser::Defaults_valueContext* IDLParser::Defaults_itemContext::defaults_value() {
  return getRuleContext<IDLParser::Defaults_valueContext>(0);
}

tree::TerminalNode* IDLParser::Defaults_itemContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}

tree::TerminalNode* IDLParser::Defaults_itemContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

IDLParser::Defaults_arrayContext* IDLParser::Defaults_itemContext::defaults_array() {
  return getRuleContext<IDLParser::Defaults_arrayContext>(0);
}

tree::TerminalNode* IDLParser::Defaults_itemContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}


size_t IDLParser::Defaults_itemContext::getRuleIndex() const {
  return IDLParser::RuleDefaults_item;
}

antlrcpp::Any IDLParser::Defaults_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitDefaults_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Defaults_itemContext* IDLParser::defaults_item() {
  Defaults_itemContext *_localctx = _tracker.createInstance<Defaults_itemContext>(_ctx, getState());
  enterRule(_localctx, 28, IDLParser::RuleDefaults_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(230);
      match(IDLParser::IDENT);
      setState(231);
      match(IDLParser::COLON);
      setState(232);
      defaults_value();
      setState(233);
      match(IDLParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(235);
      match(IDLParser::IDENT);
      setState(236);
      match(IDLParser::COLON);
      setState(237);
      match(IDLParser::LBRACE);
      setState(238);
      defaults_array();
      setState(239);
      match(IDLParser::RBRACE);
      setState(240);
      match(IDLParser::SEMICOLON);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Defaults_arrayContext ------------------------------------------------------------------

IDLParser::Defaults_arrayContext::Defaults_arrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IDLParser::Defaults_valueContext *> IDLParser::Defaults_arrayContext::defaults_value() {
  return getRuleContexts<IDLParser::Defaults_valueContext>();
}

IDLParser::Defaults_valueContext* IDLParser::Defaults_arrayContext::defaults_value(size_t i) {
  return getRuleContext<IDLParser::Defaults_valueContext>(i);
}

std::vector<tree::TerminalNode *> IDLParser::Defaults_arrayContext::COMMA() {
  return getTokens(IDLParser::COMMA);
}

tree::TerminalNode* IDLParser::Defaults_arrayContext::COMMA(size_t i) {
  return getToken(IDLParser::COMMA, i);
}


size_t IDLParser::Defaults_arrayContext::getRuleIndex() const {
  return IDLParser::RuleDefaults_array;
}

antlrcpp::Any IDLParser::Defaults_arrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitDefaults_array(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Defaults_arrayContext* IDLParser::defaults_array() {
  Defaults_arrayContext *_localctx = _tracker.createInstance<Defaults_arrayContext>(_ctx, getState());
  enterRule(_localctx, 30, IDLParser::RuleDefaults_array);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::DEFAULTS)
      | (1ULL << IDLParser::COLON)
      | (1ULL << IDLParser::IDENT))) != 0)) {
      setState(244);
      defaults_value();
      setState(246);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == IDLParser::COMMA) {
        setState(245);
        match(IDLParser::COMMA);
      }
      setState(252);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Defaults_valueContext ------------------------------------------------------------------

IDLParser::Defaults_valueContext::Defaults_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Qualified_identContext* IDLParser::Defaults_valueContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

tree::TerminalNode* IDLParser::Defaults_valueContext::DEFAULTS() {
  return getToken(IDLParser::DEFAULTS, 0);
}


size_t IDLParser::Defaults_valueContext::getRuleIndex() const {
  return IDLParser::RuleDefaults_value;
}

antlrcpp::Any IDLParser::Defaults_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitDefaults_value(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Defaults_valueContext* IDLParser::defaults_value() {
  Defaults_valueContext *_localctx = _tracker.createInstance<Defaults_valueContext>(_ctx, getState());
  enterRule(_localctx, 32, IDLParser::RuleDefaults_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(256);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::COLON:
      case IDLParser::IDENT: {
        enterOuterAlt(_localctx, 1);
        setState(253);
        qualified_ident();
        break;
      }

      case IDLParser::DEFAULTS: {
        enterOuterAlt(_localctx, 2);
        setState(254);
        match(IDLParser::DEFAULTS);
        setState(255);
        qualified_ident();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Union_stmtContext ------------------------------------------------------------------

IDLParser::Union_stmtContext::Union_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Union_declContext* IDLParser::Union_stmtContext::union_decl() {
  return getRuleContext<IDLParser::Union_declContext>(0);
}

IDLParser::Union_fwdContext* IDLParser::Union_stmtContext::union_fwd() {
  return getRuleContext<IDLParser::Union_fwdContext>(0);
}


size_t IDLParser::Union_stmtContext::getRuleIndex() const {
  return IDLParser::RuleUnion_stmt;
}

antlrcpp::Any IDLParser::Union_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitUnion_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Union_stmtContext* IDLParser::union_stmt() {
  Union_stmtContext *_localctx = _tracker.createInstance<Union_stmtContext>(_ctx, getState());
  enterRule(_localctx, 34, IDLParser::RuleUnion_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(260);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(258);
      union_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(259);
      union_fwd();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Union_declContext ------------------------------------------------------------------

IDLParser::Union_declContext::Union_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Union_declContext::UNION() {
  return getToken(IDLParser::UNION, 0);
}

tree::TerminalNode* IDLParser::Union_declContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

IDLParser::Struct_blockContext* IDLParser::Union_declContext::struct_block() {
  return getRuleContext<IDLParser::Struct_blockContext>(0);
}


size_t IDLParser::Union_declContext::getRuleIndex() const {
  return IDLParser::RuleUnion_decl;
}

antlrcpp::Any IDLParser::Union_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitUnion_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Union_declContext* IDLParser::union_decl() {
  Union_declContext *_localctx = _tracker.createInstance<Union_declContext>(_ctx, getState());
  enterRule(_localctx, 36, IDLParser::RuleUnion_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    match(IDLParser::UNION);
    setState(263);
    match(IDLParser::IDENT);
    setState(264);
    struct_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Union_fwdContext ------------------------------------------------------------------

IDLParser::Union_fwdContext::Union_fwdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Union_fwdContext::UNION() {
  return getToken(IDLParser::UNION, 0);
}

IDLParser::Qualified_identContext* IDLParser::Union_fwdContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

tree::TerminalNode* IDLParser::Union_fwdContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Union_fwdContext::getRuleIndex() const {
  return IDLParser::RuleUnion_fwd;
}

antlrcpp::Any IDLParser::Union_fwdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitUnion_fwd(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Union_fwdContext* IDLParser::union_fwd() {
  Union_fwdContext *_localctx = _tracker.createInstance<Union_fwdContext>(_ctx, getState());
  enterRule(_localctx, 38, IDLParser::RuleUnion_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    match(IDLParser::UNION);
    setState(267);
    qualified_ident();
    setState(268);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_blockContext ------------------------------------------------------------------

IDLParser::Struct_blockContext::Struct_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Struct_blockContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

tree::TerminalNode* IDLParser::Struct_blockContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

std::vector<IDLParser::Struct_itemContext *> IDLParser::Struct_blockContext::struct_item() {
  return getRuleContexts<IDLParser::Struct_itemContext>();
}

IDLParser::Struct_itemContext* IDLParser::Struct_blockContext::struct_item(size_t i) {
  return getRuleContext<IDLParser::Struct_itemContext>(i);
}

std::vector<IDLParser::Os_specificContext *> IDLParser::Struct_blockContext::os_specific() {
  return getRuleContexts<IDLParser::Os_specificContext>();
}

IDLParser::Os_specificContext* IDLParser::Struct_blockContext::os_specific(size_t i) {
  return getRuleContext<IDLParser::Os_specificContext>(i);
}


size_t IDLParser::Struct_blockContext::getRuleIndex() const {
  return IDLParser::RuleStruct_block;
}

antlrcpp::Any IDLParser::Struct_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_block(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_blockContext* IDLParser::struct_block() {
  Struct_blockContext *_localctx = _tracker.createInstance<Struct_blockContext>(_ctx, getState());
  enterRule(_localctx, 40, IDLParser::RuleStruct_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    match(IDLParser::LBRACE);
    setState(283);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(274);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << IDLParser::ENUM)
        | (1ULL << IDLParser::COLON)
        | (1ULL << IDLParser::Const)
        | (1ULL << IDLParser::Void)
        | (1ULL << IDLParser::RESULT)
        | (1ULL << IDLParser::U8)
        | (1ULL << IDLParser::S8)
        | (1ULL << IDLParser::U16)
        | (1ULL << IDLParser::S16)
        | (1ULL << IDLParser::U32)
        | (1ULL << IDLParser::S32)
        | (1ULL << IDLParser::U64)
        | (1ULL << IDLParser::S64)
        | (1ULL << IDLParser::F32)
        | (1ULL << IDLParser::F64)
        | (1ULL << IDLParser::IDENT))) != 0)) {
        setState(271);
        struct_item();
        setState(276);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      setState(280);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == IDLParser::Windows

      || _la == IDLParser::Darwin) {
        setState(277);
        os_specific();
        setState(282);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    }
    setState(285);
    match(IDLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_itemContext ------------------------------------------------------------------

IDLParser::Struct_itemContext::Struct_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Member_declContext* IDLParser::Struct_itemContext::member_decl() {
  return getRuleContext<IDLParser::Member_declContext>(0);
}

IDLParser::Const_defContext* IDLParser::Struct_itemContext::const_def() {
  return getRuleContext<IDLParser::Const_defContext>(0);
}

IDLParser::Enum_defContext* IDLParser::Struct_itemContext::enum_def() {
  return getRuleContext<IDLParser::Enum_defContext>(0);
}


size_t IDLParser::Struct_itemContext::getRuleIndex() const {
  return IDLParser::RuleStruct_item;
}

antlrcpp::Any IDLParser::Struct_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_itemContext* IDLParser::struct_item() {
  Struct_itemContext *_localctx = _tracker.createInstance<Struct_itemContext>(_ctx, getState());
  enterRule(_localctx, 42, IDLParser::RuleStruct_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(290);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(287);
      member_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(288);
      const_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(289);
      enum_def();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Os_specificContext ------------------------------------------------------------------

IDLParser::Os_specificContext::Os_specificContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Os_tagContext* IDLParser::Os_specificContext::os_tag() {
  return getRuleContext<IDLParser::Os_tagContext>(0);
}

tree::TerminalNode* IDLParser::Os_specificContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

tree::TerminalNode* IDLParser::Os_specificContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

std::vector<IDLParser::Struct_itemContext *> IDLParser::Os_specificContext::struct_item() {
  return getRuleContexts<IDLParser::Struct_itemContext>();
}

IDLParser::Struct_itemContext* IDLParser::Os_specificContext::struct_item(size_t i) {
  return getRuleContext<IDLParser::Struct_itemContext>(i);
}


size_t IDLParser::Os_specificContext::getRuleIndex() const {
  return IDLParser::RuleOs_specific;
}

antlrcpp::Any IDLParser::Os_specificContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitOs_specific(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Os_specificContext* IDLParser::os_specific() {
  Os_specificContext *_localctx = _tracker.createInstance<Os_specificContext>(_ctx, getState());
  enterRule(_localctx, 44, IDLParser::RuleOs_specific);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    os_tag();
    setState(293);
    match(IDLParser::LBRACE);
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::COLON)
      | (1ULL << IDLParser::Const)
      | (1ULL << IDLParser::Void)
      | (1ULL << IDLParser::RESULT)
      | (1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64)
      | (1ULL << IDLParser::F32)
      | (1ULL << IDLParser::F64)
      | (1ULL << IDLParser::IDENT))) != 0)) {
      setState(294);
      struct_item();
      setState(299);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(300);
    match(IDLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Os_tagContext ------------------------------------------------------------------

IDLParser::Os_tagContext::Os_tagContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Os_tagContext::Windows() {
  return getToken(IDLParser::Windows, 0);
}

tree::TerminalNode* IDLParser::Os_tagContext::Darwin() {
  return getToken(IDLParser::Darwin, 0);
}


size_t IDLParser::Os_tagContext::getRuleIndex() const {
  return IDLParser::RuleOs_tag;
}

antlrcpp::Any IDLParser::Os_tagContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitOs_tag(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Os_tagContext* IDLParser::os_tag() {
  Os_tagContext *_localctx = _tracker.createInstance<Os_tagContext>(_ctx, getState());
  enterRule(_localctx, 46, IDLParser::RuleOs_tag);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(302);
    _la = _input->LA(1);
    if (!(_la == IDLParser::Windows

    || _la == IDLParser::Darwin)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interface_stmtContext ------------------------------------------------------------------

IDLParser::Interface_stmtContext::Interface_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Interface_declContext* IDLParser::Interface_stmtContext::interface_decl() {
  return getRuleContext<IDLParser::Interface_declContext>(0);
}

IDLParser::Interface_fwdContext* IDLParser::Interface_stmtContext::interface_fwd() {
  return getRuleContext<IDLParser::Interface_fwdContext>(0);
}


size_t IDLParser::Interface_stmtContext::getRuleIndex() const {
  return IDLParser::RuleInterface_stmt;
}

antlrcpp::Any IDLParser::Interface_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_stmtContext* IDLParser::interface_stmt() {
  Interface_stmtContext *_localctx = _tracker.createInstance<Interface_stmtContext>(_ctx, getState());
  enterRule(_localctx, 48, IDLParser::RuleInterface_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(306);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(304);
      interface_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(305);
      interface_fwd();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interface_fwdContext ------------------------------------------------------------------

IDLParser::Interface_fwdContext::Interface_fwdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Interface_fwdContext::INTERFACE() {
  return getToken(IDLParser::INTERFACE, 0);
}

IDLParser::Qualified_identContext* IDLParser::Interface_fwdContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

tree::TerminalNode* IDLParser::Interface_fwdContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Interface_fwdContext::getRuleIndex() const {
  return IDLParser::RuleInterface_fwd;
}

antlrcpp::Any IDLParser::Interface_fwdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_fwd(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_fwdContext* IDLParser::interface_fwd() {
  Interface_fwdContext *_localctx = _tracker.createInstance<Interface_fwdContext>(_ctx, getState());
  enterRule(_localctx, 50, IDLParser::RuleInterface_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(IDLParser::INTERFACE);
    setState(309);
    qualified_ident();
    setState(310);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interface_declContext ------------------------------------------------------------------

IDLParser::Interface_declContext::Interface_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Interface_declContext::INTERFACE() {
  return getToken(IDLParser::INTERFACE, 0);
}

tree::TerminalNode* IDLParser::Interface_declContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

IDLParser::Interface_blockContext* IDLParser::Interface_declContext::interface_block() {
  return getRuleContext<IDLParser::Interface_blockContext>(0);
}

IDLParser::Interface_superContext* IDLParser::Interface_declContext::interface_super() {
  return getRuleContext<IDLParser::Interface_superContext>(0);
}


size_t IDLParser::Interface_declContext::getRuleIndex() const {
  return IDLParser::RuleInterface_decl;
}

antlrcpp::Any IDLParser::Interface_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_declContext* IDLParser::interface_decl() {
  Interface_declContext *_localctx = _tracker.createInstance<Interface_declContext>(_ctx, getState());
  enterRule(_localctx, 52, IDLParser::RuleInterface_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    match(IDLParser::INTERFACE);
    setState(313);
    match(IDLParser::IDENT);
    setState(315);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(314);
      interface_super();
    }
    setState(317);
    interface_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interface_superContext ------------------------------------------------------------------

IDLParser::Interface_superContext::Interface_superContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Interface_superContext::COLON() {
  return getToken(IDLParser::COLON, 0);
}

IDLParser::Qualified_identContext* IDLParser::Interface_superContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}


size_t IDLParser::Interface_superContext::getRuleIndex() const {
  return IDLParser::RuleInterface_super;
}

antlrcpp::Any IDLParser::Interface_superContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_super(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_superContext* IDLParser::interface_super() {
  Interface_superContext *_localctx = _tracker.createInstance<Interface_superContext>(_ctx, getState());
  enterRule(_localctx, 54, IDLParser::RuleInterface_super);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    match(IDLParser::COLON);
    setState(320);
    qualified_ident();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interface_blockContext ------------------------------------------------------------------

IDLParser::Interface_blockContext::Interface_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Interface_blockContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

tree::TerminalNode* IDLParser::Interface_blockContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

std::vector<IDLParser::Interface_itemContext *> IDLParser::Interface_blockContext::interface_item() {
  return getRuleContexts<IDLParser::Interface_itemContext>();
}

IDLParser::Interface_itemContext* IDLParser::Interface_blockContext::interface_item(size_t i) {
  return getRuleContext<IDLParser::Interface_itemContext>(i);
}


size_t IDLParser::Interface_blockContext::getRuleIndex() const {
  return IDLParser::RuleInterface_block;
}

antlrcpp::Any IDLParser::Interface_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_block(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_blockContext* IDLParser::interface_block() {
  Interface_blockContext *_localctx = _tracker.createInstance<Interface_blockContext>(_ctx, getState());
  enterRule(_localctx, 56, IDLParser::RuleInterface_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(322);
    match(IDLParser::LBRACE);
    setState(326);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::COLON)
      | (1ULL << IDLParser::Const)
      | (1ULL << IDLParser::Void)
      | (1ULL << IDLParser::RESULT)
      | (1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64)
      | (1ULL << IDLParser::F32)
      | (1ULL << IDLParser::F64)
      | (1ULL << IDLParser::IDENT))) != 0)) {
      setState(323);
      interface_item();
      setState(328);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(329);
    match(IDLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interface_itemContext ------------------------------------------------------------------

IDLParser::Interface_itemContext::Interface_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Function_declContext* IDLParser::Interface_itemContext::function_decl() {
  return getRuleContext<IDLParser::Function_declContext>(0);
}

IDLParser::Const_defContext* IDLParser::Interface_itemContext::const_def() {
  return getRuleContext<IDLParser::Const_defContext>(0);
}

IDLParser::Enum_defContext* IDLParser::Interface_itemContext::enum_def() {
  return getRuleContext<IDLParser::Enum_defContext>(0);
}


size_t IDLParser::Interface_itemContext::getRuleIndex() const {
  return IDLParser::RuleInterface_item;
}

antlrcpp::Any IDLParser::Interface_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_itemContext* IDLParser::interface_item() {
  Interface_itemContext *_localctx = _tracker.createInstance<Interface_itemContext>(_ctx, getState());
  enterRule(_localctx, 58, IDLParser::RuleInterface_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(334);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(331);
      function_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(332);
      const_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(333);
      enum_def();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_declContext ------------------------------------------------------------------

IDLParser::Function_declContext::Function_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Type_declContext* IDLParser::Function_declContext::type_decl() {
  return getRuleContext<IDLParser::Type_declContext>(0);
}

tree::TerminalNode* IDLParser::Function_declContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Function_declContext::LPAREN() {
  return getToken(IDLParser::LPAREN, 0);
}

tree::TerminalNode* IDLParser::Function_declContext::RPAREN() {
  return getToken(IDLParser::RPAREN, 0);
}

tree::TerminalNode* IDLParser::Function_declContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}

IDLParser::Function_param_listContext* IDLParser::Function_declContext::function_param_list() {
  return getRuleContext<IDLParser::Function_param_listContext>(0);
}

tree::TerminalNode* IDLParser::Function_declContext::Const() {
  return getToken(IDLParser::Const, 0);
}


size_t IDLParser::Function_declContext::getRuleIndex() const {
  return IDLParser::RuleFunction_decl;
}

antlrcpp::Any IDLParser::Function_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFunction_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Function_declContext* IDLParser::function_decl() {
  Function_declContext *_localctx = _tracker.createInstance<Function_declContext>(_ctx, getState());
  enterRule(_localctx, 60, IDLParser::RuleFunction_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    type_decl();
    setState(337);
    match(IDLParser::IDENT);
    setState(338);
    match(IDLParser::LPAREN);
    setState(340);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::COLON)
      | (1ULL << IDLParser::LBRACKET)
      | (1ULL << IDLParser::Const)
      | (1ULL << IDLParser::Void)
      | (1ULL << IDLParser::RESULT)
      | (1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64)
      | (1ULL << IDLParser::F32)
      | (1ULL << IDLParser::F64)
      | (1ULL << IDLParser::IDENT))) != 0)) {
      setState(339);
      function_param_list();
    }
    setState(342);
    match(IDLParser::RPAREN);
    setState(344);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::Const) {
      setState(343);
      match(IDLParser::Const);
    }
    setState(346);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_param_listContext ------------------------------------------------------------------

IDLParser::Function_param_listContext::Function_param_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IDLParser::Function_paramContext *> IDLParser::Function_param_listContext::function_param() {
  return getRuleContexts<IDLParser::Function_paramContext>();
}

IDLParser::Function_paramContext* IDLParser::Function_param_listContext::function_param(size_t i) {
  return getRuleContext<IDLParser::Function_paramContext>(i);
}

std::vector<tree::TerminalNode *> IDLParser::Function_param_listContext::COMMA() {
  return getTokens(IDLParser::COMMA);
}

tree::TerminalNode* IDLParser::Function_param_listContext::COMMA(size_t i) {
  return getToken(IDLParser::COMMA, i);
}


size_t IDLParser::Function_param_listContext::getRuleIndex() const {
  return IDLParser::RuleFunction_param_list;
}

antlrcpp::Any IDLParser::Function_param_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFunction_param_list(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Function_param_listContext* IDLParser::function_param_list() {
  Function_param_listContext *_localctx = _tracker.createInstance<Function_param_listContext>(_ctx, getState());
  enterRule(_localctx, 62, IDLParser::RuleFunction_param_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(348);
    function_param();
    setState(353);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COMMA) {
      setState(349);
      match(IDLParser::COMMA);
      setState(350);
      function_param();
      setState(355);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_paramContext ------------------------------------------------------------------

IDLParser::Function_paramContext::Function_paramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Type_declContext* IDLParser::Function_paramContext::type_decl() {
  return getRuleContext<IDLParser::Type_declContext>(0);
}

tree::TerminalNode* IDLParser::Function_paramContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

IDLParser::Param_dir_qualifierContext* IDLParser::Function_paramContext::param_dir_qualifier() {
  return getRuleContext<IDLParser::Param_dir_qualifierContext>(0);
}


size_t IDLParser::Function_paramContext::getRuleIndex() const {
  return IDLParser::RuleFunction_param;
}

antlrcpp::Any IDLParser::Function_paramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFunction_param(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Function_paramContext* IDLParser::function_param() {
  Function_paramContext *_localctx = _tracker.createInstance<Function_paramContext>(_ctx, getState());
  enterRule(_localctx, 64, IDLParser::RuleFunction_param);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(357);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::LBRACKET) {
      setState(356);
      param_dir_qualifier();
    }
    setState(359);
    type_decl();
    setState(360);
    match(IDLParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Param_dir_qualifierContext ------------------------------------------------------------------

IDLParser::Param_dir_qualifierContext::Param_dir_qualifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Param_dir_qualifierContext::LBRACKET() {
  return getToken(IDLParser::LBRACKET, 0);
}

tree::TerminalNode* IDLParser::Param_dir_qualifierContext::IN() {
  return getToken(IDLParser::IN, 0);
}

tree::TerminalNode* IDLParser::Param_dir_qualifierContext::RBRACKET() {
  return getToken(IDLParser::RBRACKET, 0);
}

tree::TerminalNode* IDLParser::Param_dir_qualifierContext::OUT() {
  return getToken(IDLParser::OUT, 0);
}

tree::TerminalNode* IDLParser::Param_dir_qualifierContext::COMMA() {
  return getToken(IDLParser::COMMA, 0);
}


size_t IDLParser::Param_dir_qualifierContext::getRuleIndex() const {
  return IDLParser::RuleParam_dir_qualifier;
}

antlrcpp::Any IDLParser::Param_dir_qualifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitParam_dir_qualifier(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Param_dir_qualifierContext* IDLParser::param_dir_qualifier() {
  Param_dir_qualifierContext *_localctx = _tracker.createInstance<Param_dir_qualifierContext>(_ctx, getState());
  enterRule(_localctx, 66, IDLParser::RuleParam_dir_qualifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(373);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(362);
      match(IDLParser::LBRACKET);
      setState(363);
      match(IDLParser::IN);
      setState(364);
      match(IDLParser::RBRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(365);
      match(IDLParser::LBRACKET);
      setState(366);
      match(IDLParser::OUT);
      setState(367);
      match(IDLParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(368);
      match(IDLParser::LBRACKET);
      setState(369);
      match(IDLParser::IN);
      setState(370);
      match(IDLParser::COMMA);
      setState(371);
      match(IDLParser::OUT);
      setState(372);
      match(IDLParser::RBRACKET);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_defContext ------------------------------------------------------------------

IDLParser::Const_defContext::Const_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Const_integral_defContext* IDLParser::Const_defContext::const_integral_def() {
  return getRuleContext<IDLParser::Const_integral_defContext>(0);
}

IDLParser::Const_float_defContext* IDLParser::Const_defContext::const_float_def() {
  return getRuleContext<IDLParser::Const_float_defContext>(0);
}

IDLParser::Const_string_defContext* IDLParser::Const_defContext::const_string_def() {
  return getRuleContext<IDLParser::Const_string_defContext>(0);
}

IDLParser::Const_class_id_defContext* IDLParser::Const_defContext::const_class_id_def() {
  return getRuleContext<IDLParser::Const_class_id_defContext>(0);
}


size_t IDLParser::Const_defContext::getRuleIndex() const {
  return IDLParser::RuleConst_def;
}

antlrcpp::Any IDLParser::Const_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_defContext* IDLParser::const_def() {
  Const_defContext *_localctx = _tracker.createInstance<Const_defContext>(_ctx, getState());
  enterRule(_localctx, 68, IDLParser::RuleConst_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(379);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(375);
      const_integral_def();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(376);
      const_float_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(377);
      const_string_def();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(378);
      const_class_id_def();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_integral_defContext ------------------------------------------------------------------

IDLParser::Const_integral_defContext::Const_integral_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Const_integral_defContext::Const() {
  return getToken(IDLParser::Const, 0);
}

IDLParser::Integral_typeContext* IDLParser::Const_integral_defContext::integral_type() {
  return getRuleContext<IDLParser::Integral_typeContext>(0);
}

tree::TerminalNode* IDLParser::Const_integral_defContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Const_integral_defContext::EQUALS() {
  return getToken(IDLParser::EQUALS, 0);
}

IDLParser::Integer_litContext* IDLParser::Const_integral_defContext::integer_lit() {
  return getRuleContext<IDLParser::Integer_litContext>(0);
}

tree::TerminalNode* IDLParser::Const_integral_defContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Const_integral_defContext::getRuleIndex() const {
  return IDLParser::RuleConst_integral_def;
}

antlrcpp::Any IDLParser::Const_integral_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_integral_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_integral_defContext* IDLParser::const_integral_def() {
  Const_integral_defContext *_localctx = _tracker.createInstance<Const_integral_defContext>(_ctx, getState());
  enterRule(_localctx, 70, IDLParser::RuleConst_integral_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(381);
    match(IDLParser::Const);
    setState(382);
    integral_type();
    setState(383);
    match(IDLParser::IDENT);
    setState(384);
    match(IDLParser::EQUALS);
    setState(385);
    integer_lit();
    setState(386);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_float_defContext ------------------------------------------------------------------

IDLParser::Const_float_defContext::Const_float_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Const_float_defContext::Const() {
  return getToken(IDLParser::Const, 0);
}

IDLParser::Float_typeContext* IDLParser::Const_float_defContext::float_type() {
  return getRuleContext<IDLParser::Float_typeContext>(0);
}

tree::TerminalNode* IDLParser::Const_float_defContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Const_float_defContext::EQUALS() {
  return getToken(IDLParser::EQUALS, 0);
}

IDLParser::Float_litContext* IDLParser::Const_float_defContext::float_lit() {
  return getRuleContext<IDLParser::Float_litContext>(0);
}

tree::TerminalNode* IDLParser::Const_float_defContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Const_float_defContext::getRuleIndex() const {
  return IDLParser::RuleConst_float_def;
}

antlrcpp::Any IDLParser::Const_float_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_float_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_float_defContext* IDLParser::const_float_def() {
  Const_float_defContext *_localctx = _tracker.createInstance<Const_float_defContext>(_ctx, getState());
  enterRule(_localctx, 72, IDLParser::RuleConst_float_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(388);
    match(IDLParser::Const);
    setState(389);
    float_type();
    setState(390);
    match(IDLParser::IDENT);
    setState(391);
    match(IDLParser::EQUALS);
    setState(392);
    float_lit();
    setState(393);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_string_defContext ------------------------------------------------------------------

IDLParser::Const_string_defContext::Const_string_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Const_string_defContext::Const() {
  return getToken(IDLParser::Const, 0);
}

tree::TerminalNode* IDLParser::Const_string_defContext::STRING() {
  return getToken(IDLParser::STRING, 0);
}

tree::TerminalNode* IDLParser::Const_string_defContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Const_string_defContext::EQUALS() {
  return getToken(IDLParser::EQUALS, 0);
}

IDLParser::String_litContext* IDLParser::Const_string_defContext::string_lit() {
  return getRuleContext<IDLParser::String_litContext>(0);
}

tree::TerminalNode* IDLParser::Const_string_defContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Const_string_defContext::getRuleIndex() const {
  return IDLParser::RuleConst_string_def;
}

antlrcpp::Any IDLParser::Const_string_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_string_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_string_defContext* IDLParser::const_string_def() {
  Const_string_defContext *_localctx = _tracker.createInstance<Const_string_defContext>(_ctx, getState());
  enterRule(_localctx, 74, IDLParser::RuleConst_string_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(395);
    match(IDLParser::Const);
    setState(396);
    match(IDLParser::STRING);
    setState(397);
    match(IDLParser::IDENT);
    setState(398);
    match(IDLParser::EQUALS);
    setState(399);
    string_lit();
    setState(400);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_class_id_defContext ------------------------------------------------------------------

IDLParser::Const_class_id_defContext::Const_class_id_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::Const() {
  return getToken(IDLParser::Const, 0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::CLASS_ID() {
  return getToken(IDLParser::CLASS_ID, 0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::LPAREN() {
  return getToken(IDLParser::LPAREN, 0);
}

IDLParser::String_litContext* IDLParser::Const_class_id_defContext::string_lit() {
  return getRuleContext<IDLParser::String_litContext>(0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::RPAREN() {
  return getToken(IDLParser::RPAREN, 0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Const_class_id_defContext::getRuleIndex() const {
  return IDLParser::RuleConst_class_id_def;
}

antlrcpp::Any IDLParser::Const_class_id_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_class_id_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_class_id_defContext* IDLParser::const_class_id_def() {
  Const_class_id_defContext *_localctx = _tracker.createInstance<Const_class_id_defContext>(_ctx, getState());
  enterRule(_localctx, 76, IDLParser::RuleConst_class_id_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(402);
    match(IDLParser::Const);
    setState(403);
    match(IDLParser::CLASS_ID);
    setState(404);
    match(IDLParser::IDENT);
    setState(405);
    match(IDLParser::LPAREN);
    setState(406);
    string_lit();
    setState(407);
    match(IDLParser::RPAREN);
    setState(408);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_fwdContext ------------------------------------------------------------------

IDLParser::Enum_fwdContext::Enum_fwdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Enum_fwdContext::ENUM() {
  return getToken(IDLParser::ENUM, 0);
}

tree::TerminalNode* IDLParser::Enum_fwdContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Enum_fwdContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}

IDLParser::Enum_typeContext* IDLParser::Enum_fwdContext::enum_type() {
  return getRuleContext<IDLParser::Enum_typeContext>(0);
}


size_t IDLParser::Enum_fwdContext::getRuleIndex() const {
  return IDLParser::RuleEnum_fwd;
}

antlrcpp::Any IDLParser::Enum_fwdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_fwd(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_fwdContext* IDLParser::enum_fwd() {
  Enum_fwdContext *_localctx = _tracker.createInstance<Enum_fwdContext>(_ctx, getState());
  enterRule(_localctx, 78, IDLParser::RuleEnum_fwd);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(410);
    match(IDLParser::ENUM);
    setState(411);
    match(IDLParser::IDENT);
    setState(413);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(412);
      enum_type();
    }
    setState(415);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_defContext ------------------------------------------------------------------

IDLParser::Enum_defContext::Enum_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Enum_defContext::ENUM() {
  return getToken(IDLParser::ENUM, 0);
}

tree::TerminalNode* IDLParser::Enum_defContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Enum_defContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

IDLParser::Enum_elementsContext* IDLParser::Enum_defContext::enum_elements() {
  return getRuleContext<IDLParser::Enum_elementsContext>(0);
}

tree::TerminalNode* IDLParser::Enum_defContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

IDLParser::Enum_typeContext* IDLParser::Enum_defContext::enum_type() {
  return getRuleContext<IDLParser::Enum_typeContext>(0);
}


size_t IDLParser::Enum_defContext::getRuleIndex() const {
  return IDLParser::RuleEnum_def;
}

antlrcpp::Any IDLParser::Enum_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_defContext* IDLParser::enum_def() {
  Enum_defContext *_localctx = _tracker.createInstance<Enum_defContext>(_ctx, getState());
  enterRule(_localctx, 80, IDLParser::RuleEnum_def);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(417);
    match(IDLParser::ENUM);
    setState(418);
    match(IDLParser::IDENT);
    setState(420);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(419);
      enum_type();
    }
    setState(422);
    match(IDLParser::LBRACE);
    setState(423);
    enum_elements();
    setState(424);
    match(IDLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Flags_fwdContext ------------------------------------------------------------------

IDLParser::Flags_fwdContext::Flags_fwdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Flags_fwdContext::FLAGS() {
  return getToken(IDLParser::FLAGS, 0);
}

tree::TerminalNode* IDLParser::Flags_fwdContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Flags_fwdContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}

IDLParser::Enum_typeContext* IDLParser::Flags_fwdContext::enum_type() {
  return getRuleContext<IDLParser::Enum_typeContext>(0);
}


size_t IDLParser::Flags_fwdContext::getRuleIndex() const {
  return IDLParser::RuleFlags_fwd;
}

antlrcpp::Any IDLParser::Flags_fwdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFlags_fwd(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Flags_fwdContext* IDLParser::flags_fwd() {
  Flags_fwdContext *_localctx = _tracker.createInstance<Flags_fwdContext>(_ctx, getState());
  enterRule(_localctx, 82, IDLParser::RuleFlags_fwd);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(426);
    match(IDLParser::FLAGS);
    setState(427);
    match(IDLParser::IDENT);
    setState(429);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(428);
      enum_type();
    }
    setState(431);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Flags_defContext ------------------------------------------------------------------

IDLParser::Flags_defContext::Flags_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Flags_defContext::FLAGS() {
  return getToken(IDLParser::FLAGS, 0);
}

tree::TerminalNode* IDLParser::Flags_defContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Flags_defContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

IDLParser::Enum_elementsContext* IDLParser::Flags_defContext::enum_elements() {
  return getRuleContext<IDLParser::Enum_elementsContext>(0);
}

tree::TerminalNode* IDLParser::Flags_defContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

IDLParser::Enum_typeContext* IDLParser::Flags_defContext::enum_type() {
  return getRuleContext<IDLParser::Enum_typeContext>(0);
}


size_t IDLParser::Flags_defContext::getRuleIndex() const {
  return IDLParser::RuleFlags_def;
}

antlrcpp::Any IDLParser::Flags_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFlags_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Flags_defContext* IDLParser::flags_def() {
  Flags_defContext *_localctx = _tracker.createInstance<Flags_defContext>(_ctx, getState());
  enterRule(_localctx, 84, IDLParser::RuleFlags_def);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(433);
    match(IDLParser::FLAGS);
    setState(434);
    match(IDLParser::IDENT);
    setState(436);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(435);
      enum_type();
    }
    setState(438);
    match(IDLParser::LBRACE);
    setState(439);
    enum_elements();
    setState(440);
    match(IDLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_typeContext ------------------------------------------------------------------

IDLParser::Enum_typeContext::Enum_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Enum_typeContext::COLON() {
  return getToken(IDLParser::COLON, 0);
}

IDLParser::Integral_typeContext* IDLParser::Enum_typeContext::integral_type() {
  return getRuleContext<IDLParser::Integral_typeContext>(0);
}


size_t IDLParser::Enum_typeContext::getRuleIndex() const {
  return IDLParser::RuleEnum_type;
}

antlrcpp::Any IDLParser::Enum_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_typeContext* IDLParser::enum_type() {
  Enum_typeContext *_localctx = _tracker.createInstance<Enum_typeContext>(_ctx, getState());
  enterRule(_localctx, 86, IDLParser::RuleEnum_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(442);
    match(IDLParser::COLON);
    setState(443);
    integral_type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_elementsContext ------------------------------------------------------------------

IDLParser::Enum_elementsContext::Enum_elementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IDLParser::Enum_itemContext *> IDLParser::Enum_elementsContext::enum_item() {
  return getRuleContexts<IDLParser::Enum_itemContext>();
}

IDLParser::Enum_itemContext* IDLParser::Enum_elementsContext::enum_item(size_t i) {
  return getRuleContext<IDLParser::Enum_itemContext>(i);
}

std::vector<tree::TerminalNode *> IDLParser::Enum_elementsContext::COMMA() {
  return getTokens(IDLParser::COMMA);
}

tree::TerminalNode* IDLParser::Enum_elementsContext::COMMA(size_t i) {
  return getToken(IDLParser::COMMA, i);
}


size_t IDLParser::Enum_elementsContext::getRuleIndex() const {
  return IDLParser::RuleEnum_elements;
}

antlrcpp::Any IDLParser::Enum_elementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_elements(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_elementsContext* IDLParser::enum_elements() {
  Enum_elementsContext *_localctx = _tracker.createInstance<Enum_elementsContext>(_ctx, getState());
  enterRule(_localctx, 88, IDLParser::RuleEnum_elements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(445);
    enum_item();
    setState(450);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COMMA) {
      setState(446);
      match(IDLParser::COMMA);
      setState(447);
      enum_item();
      setState(452);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_itemContext ------------------------------------------------------------------

IDLParser::Enum_itemContext::Enum_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Enum_itemContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Enum_itemContext::EQUALS() {
  return getToken(IDLParser::EQUALS, 0);
}

IDLParser::Enum_exprContext* IDLParser::Enum_itemContext::enum_expr() {
  return getRuleContext<IDLParser::Enum_exprContext>(0);
}


size_t IDLParser::Enum_itemContext::getRuleIndex() const {
  return IDLParser::RuleEnum_item;
}

antlrcpp::Any IDLParser::Enum_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_itemContext* IDLParser::enum_item() {
  Enum_itemContext *_localctx = _tracker.createInstance<Enum_itemContext>(_ctx, getState());
  enterRule(_localctx, 90, IDLParser::RuleEnum_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(457);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(453);
      match(IDLParser::IDENT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(454);
      match(IDLParser::IDENT);
      setState(455);
      match(IDLParser::EQUALS);
      setState(456);
      enum_expr();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_exprContext ------------------------------------------------------------------

IDLParser::Enum_exprContext::Enum_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Expr_add_subContext* IDLParser::Enum_exprContext::expr_add_sub() {
  return getRuleContext<IDLParser::Expr_add_subContext>(0);
}


size_t IDLParser::Enum_exprContext::getRuleIndex() const {
  return IDLParser::RuleEnum_expr;
}

antlrcpp::Any IDLParser::Enum_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_expr(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_exprContext* IDLParser::enum_expr() {
  Enum_exprContext *_localctx = _tracker.createInstance<Enum_exprContext>(_ctx, getState());
  enterRule(_localctx, 92, IDLParser::RuleEnum_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(459);
    expr_add_sub(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr_add_subContext ------------------------------------------------------------------

IDLParser::Expr_add_subContext::Expr_add_subContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Expr_mul_divContext* IDLParser::Expr_add_subContext::expr_mul_div() {
  return getRuleContext<IDLParser::Expr_mul_divContext>(0);
}

IDLParser::Expr_add_subContext* IDLParser::Expr_add_subContext::expr_add_sub() {
  return getRuleContext<IDLParser::Expr_add_subContext>(0);
}

tree::TerminalNode* IDLParser::Expr_add_subContext::PLUS() {
  return getToken(IDLParser::PLUS, 0);
}

tree::TerminalNode* IDLParser::Expr_add_subContext::MINUS() {
  return getToken(IDLParser::MINUS, 0);
}


size_t IDLParser::Expr_add_subContext::getRuleIndex() const {
  return IDLParser::RuleExpr_add_sub;
}

antlrcpp::Any IDLParser::Expr_add_subContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitExpr_add_sub(this);
  else
    return visitor->visitChildren(this);
}


IDLParser::Expr_add_subContext* IDLParser::expr_add_sub() {
   return expr_add_sub(0);
}

IDLParser::Expr_add_subContext* IDLParser::expr_add_sub(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IDLParser::Expr_add_subContext *_localctx = _tracker.createInstance<Expr_add_subContext>(_ctx, parentState);
  IDLParser::Expr_add_subContext *previousContext = _localctx;
  size_t startState = 94;
  enterRecursionRule(_localctx, 94, IDLParser::RuleExpr_add_sub, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(462);
    expr_mul_div(0);
    _ctx->stop = _input->LT(-1);
    setState(472);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(470);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Expr_add_subContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_add_sub);
          setState(464);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(465);
          match(IDLParser::PLUS);
          setState(466);
          expr_mul_div(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Expr_add_subContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_add_sub);
          setState(467);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(468);
          match(IDLParser::MINUS);
          setState(469);
          expr_mul_div(0);
          break;
        }

        } 
      }
      setState(474);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Expr_mul_divContext ------------------------------------------------------------------

IDLParser::Expr_mul_divContext::Expr_mul_divContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Expr_shiftContext* IDLParser::Expr_mul_divContext::expr_shift() {
  return getRuleContext<IDLParser::Expr_shiftContext>(0);
}

IDLParser::Expr_mul_divContext* IDLParser::Expr_mul_divContext::expr_mul_div() {
  return getRuleContext<IDLParser::Expr_mul_divContext>(0);
}

tree::TerminalNode* IDLParser::Expr_mul_divContext::STAR() {
  return getToken(IDLParser::STAR, 0);
}

tree::TerminalNode* IDLParser::Expr_mul_divContext::SLASH() {
  return getToken(IDLParser::SLASH, 0);
}


size_t IDLParser::Expr_mul_divContext::getRuleIndex() const {
  return IDLParser::RuleExpr_mul_div;
}

antlrcpp::Any IDLParser::Expr_mul_divContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitExpr_mul_div(this);
  else
    return visitor->visitChildren(this);
}


IDLParser::Expr_mul_divContext* IDLParser::expr_mul_div() {
   return expr_mul_div(0);
}

IDLParser::Expr_mul_divContext* IDLParser::expr_mul_div(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IDLParser::Expr_mul_divContext *_localctx = _tracker.createInstance<Expr_mul_divContext>(_ctx, parentState);
  IDLParser::Expr_mul_divContext *previousContext = _localctx;
  size_t startState = 96;
  enterRecursionRule(_localctx, 96, IDLParser::RuleExpr_mul_div, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(476);
    expr_shift(0);
    _ctx->stop = _input->LT(-1);
    setState(486);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(484);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Expr_mul_divContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_mul_div);
          setState(478);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(479);
          match(IDLParser::STAR);
          setState(480);
          expr_shift(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Expr_mul_divContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_mul_div);
          setState(481);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(482);
          match(IDLParser::SLASH);
          setState(483);
          expr_shift(0);
          break;
        }

        } 
      }
      setState(488);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Expr_shiftContext ------------------------------------------------------------------

IDLParser::Expr_shiftContext::Expr_shiftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Expr_logicalContext* IDLParser::Expr_shiftContext::expr_logical() {
  return getRuleContext<IDLParser::Expr_logicalContext>(0);
}

IDLParser::Expr_shiftContext* IDLParser::Expr_shiftContext::expr_shift() {
  return getRuleContext<IDLParser::Expr_shiftContext>(0);
}

tree::TerminalNode* IDLParser::Expr_shiftContext::LSHIFT() {
  return getToken(IDLParser::LSHIFT, 0);
}

tree::TerminalNode* IDLParser::Expr_shiftContext::RSHIFT() {
  return getToken(IDLParser::RSHIFT, 0);
}


size_t IDLParser::Expr_shiftContext::getRuleIndex() const {
  return IDLParser::RuleExpr_shift;
}

antlrcpp::Any IDLParser::Expr_shiftContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitExpr_shift(this);
  else
    return visitor->visitChildren(this);
}


IDLParser::Expr_shiftContext* IDLParser::expr_shift() {
   return expr_shift(0);
}

IDLParser::Expr_shiftContext* IDLParser::expr_shift(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IDLParser::Expr_shiftContext *_localctx = _tracker.createInstance<Expr_shiftContext>(_ctx, parentState);
  IDLParser::Expr_shiftContext *previousContext = _localctx;
  size_t startState = 98;
  enterRecursionRule(_localctx, 98, IDLParser::RuleExpr_shift, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(490);
    expr_logical(0);
    _ctx->stop = _input->LT(-1);
    setState(500);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(498);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Expr_shiftContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_shift);
          setState(492);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(493);
          match(IDLParser::LSHIFT);
          setState(494);
          expr_logical(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Expr_shiftContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_shift);
          setState(495);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(496);
          match(IDLParser::RSHIFT);
          setState(497);
          expr_logical(0);
          break;
        }

        } 
      }
      setState(502);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Expr_logicalContext ------------------------------------------------------------------

IDLParser::Expr_logicalContext::Expr_logicalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Expr_valueContext* IDLParser::Expr_logicalContext::expr_value() {
  return getRuleContext<IDLParser::Expr_valueContext>(0);
}

IDLParser::Expr_logicalContext* IDLParser::Expr_logicalContext::expr_logical() {
  return getRuleContext<IDLParser::Expr_logicalContext>(0);
}

tree::TerminalNode* IDLParser::Expr_logicalContext::PIPE() {
  return getToken(IDLParser::PIPE, 0);
}


size_t IDLParser::Expr_logicalContext::getRuleIndex() const {
  return IDLParser::RuleExpr_logical;
}

antlrcpp::Any IDLParser::Expr_logicalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitExpr_logical(this);
  else
    return visitor->visitChildren(this);
}


IDLParser::Expr_logicalContext* IDLParser::expr_logical() {
   return expr_logical(0);
}

IDLParser::Expr_logicalContext* IDLParser::expr_logical(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IDLParser::Expr_logicalContext *_localctx = _tracker.createInstance<Expr_logicalContext>(_ctx, parentState);
  IDLParser::Expr_logicalContext *previousContext = _localctx;
  size_t startState = 100;
  enterRecursionRule(_localctx, 100, IDLParser::RuleExpr_logical, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(504);
    expr_value();
    _ctx->stop = _input->LT(-1);
    setState(511);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Expr_logicalContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpr_logical);
        setState(506);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(507);
        match(IDLParser::PIPE);
        setState(508);
        expr_value(); 
      }
      setState(513);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Expr_valueContext ------------------------------------------------------------------

IDLParser::Expr_valueContext::Expr_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Integer_litContext* IDLParser::Expr_valueContext::integer_lit() {
  return getRuleContext<IDLParser::Integer_litContext>(0);
}

IDLParser::Qualified_identContext* IDLParser::Expr_valueContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

tree::TerminalNode* IDLParser::Expr_valueContext::LPAREN() {
  return getToken(IDLParser::LPAREN, 0);
}

IDLParser::Enum_exprContext* IDLParser::Expr_valueContext::enum_expr() {
  return getRuleContext<IDLParser::Enum_exprContext>(0);
}

tree::TerminalNode* IDLParser::Expr_valueContext::RPAREN() {
  return getToken(IDLParser::RPAREN, 0);
}


size_t IDLParser::Expr_valueContext::getRuleIndex() const {
  return IDLParser::RuleExpr_value;
}

antlrcpp::Any IDLParser::Expr_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitExpr_value(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Expr_valueContext* IDLParser::expr_value() {
  Expr_valueContext *_localctx = _tracker.createInstance<Expr_valueContext>(_ctx, getState());
  enterRule(_localctx, 102, IDLParser::RuleExpr_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(520);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::OCT_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(514);
        integer_lit();
        break;
      }

      case IDLParser::COLON:
      case IDLParser::IDENT: {
        enterOuterAlt(_localctx, 2);
        setState(515);
        qualified_ident();
        break;
      }

      case IDLParser::LPAREN: {
        enterOuterAlt(_localctx, 3);
        setState(516);
        match(IDLParser::LPAREN);
        setState(517);
        enum_expr();
        setState(518);
        match(IDLParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Any_literalContext ------------------------------------------------------------------

IDLParser::Any_literalContext::Any_literalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Numeric_litContext* IDLParser::Any_literalContext::numeric_lit() {
  return getRuleContext<IDLParser::Numeric_litContext>(0);
}

IDLParser::String_litContext* IDLParser::Any_literalContext::string_lit() {
  return getRuleContext<IDLParser::String_litContext>(0);
}


size_t IDLParser::Any_literalContext::getRuleIndex() const {
  return IDLParser::RuleAny_literal;
}

antlrcpp::Any IDLParser::Any_literalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitAny_literal(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Any_literalContext* IDLParser::any_literal() {
  Any_literalContext *_localctx = _tracker.createInstance<Any_literalContext>(_ctx, getState());
  enterRule(_localctx, 104, IDLParser::RuleAny_literal);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(524);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::OCT_LIT:
      case IDLParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(522);
        numeric_lit();
        break;
      }

      case IDLParser::STRING_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(523);
        string_lit();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Numeric_litContext ------------------------------------------------------------------

IDLParser::Numeric_litContext::Numeric_litContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Integer_litContext* IDLParser::Numeric_litContext::integer_lit() {
  return getRuleContext<IDLParser::Integer_litContext>(0);
}

IDLParser::Float_litContext* IDLParser::Numeric_litContext::float_lit() {
  return getRuleContext<IDLParser::Float_litContext>(0);
}


size_t IDLParser::Numeric_litContext::getRuleIndex() const {
  return IDLParser::RuleNumeric_lit;
}

antlrcpp::Any IDLParser::Numeric_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitNumeric_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Numeric_litContext* IDLParser::numeric_lit() {
  Numeric_litContext *_localctx = _tracker.createInstance<Numeric_litContext>(_ctx, getState());
  enterRule(_localctx, 106, IDLParser::RuleNumeric_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(528);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::OCT_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(526);
        integer_lit();
        break;
      }

      case IDLParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(527);
        float_lit();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Integer_litContext ------------------------------------------------------------------

IDLParser::Integer_litContext::Integer_litContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Integer_litContext::DECIMAL_LIT() {
  return getToken(IDLParser::DECIMAL_LIT, 0);
}

tree::TerminalNode* IDLParser::Integer_litContext::HEX_LIT() {
  return getToken(IDLParser::HEX_LIT, 0);
}

tree::TerminalNode* IDLParser::Integer_litContext::OCT_LIT() {
  return getToken(IDLParser::OCT_LIT, 0);
}

tree::TerminalNode* IDLParser::Integer_litContext::BIN_LIT() {
  return getToken(IDLParser::BIN_LIT, 0);
}


size_t IDLParser::Integer_litContext::getRuleIndex() const {
  return IDLParser::RuleInteger_lit;
}

antlrcpp::Any IDLParser::Integer_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInteger_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Integer_litContext* IDLParser::integer_lit() {
  Integer_litContext *_localctx = _tracker.createInstance<Integer_litContext>(_ctx, getState());
  enterRule(_localctx, 108, IDLParser::RuleInteger_lit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(530);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::DECIMAL_LIT)
      | (1ULL << IDLParser::HEX_LIT)
      | (1ULL << IDLParser::BIN_LIT)
      | (1ULL << IDLParser::OCT_LIT))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Float_litContext ------------------------------------------------------------------

IDLParser::Float_litContext::Float_litContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Float_litContext::FLOAT_LIT() {
  return getToken(IDLParser::FLOAT_LIT, 0);
}


size_t IDLParser::Float_litContext::getRuleIndex() const {
  return IDLParser::RuleFloat_lit;
}

antlrcpp::Any IDLParser::Float_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFloat_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Float_litContext* IDLParser::float_lit() {
  Float_litContext *_localctx = _tracker.createInstance<Float_litContext>(_ctx, getState());
  enterRule(_localctx, 110, IDLParser::RuleFloat_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(532);
    match(IDLParser::FLOAT_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- String_litContext ------------------------------------------------------------------

IDLParser::String_litContext::String_litContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::String_litContext::STRING_LIT() {
  return getToken(IDLParser::STRING_LIT, 0);
}


size_t IDLParser::String_litContext::getRuleIndex() const {
  return IDLParser::RuleString_lit;
}

antlrcpp::Any IDLParser::String_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitString_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::String_litContext* IDLParser::string_lit() {
  String_litContext *_localctx = _tracker.createInstance<String_litContext>(_ctx, getState());
  enterRule(_localctx, 112, IDLParser::RuleString_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(534);
    match(IDLParser::STRING_LIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Qualified_identContext ------------------------------------------------------------------

IDLParser::Qualified_identContext::Qualified_identContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Qualified_identContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

IDLParser::Qualified_separatorContext* IDLParser::Qualified_identContext::qualified_separator() {
  return getRuleContext<IDLParser::Qualified_separatorContext>(0);
}

std::vector<IDLParser::Qualified_partContext *> IDLParser::Qualified_identContext::qualified_part() {
  return getRuleContexts<IDLParser::Qualified_partContext>();
}

IDLParser::Qualified_partContext* IDLParser::Qualified_identContext::qualified_part(size_t i) {
  return getRuleContext<IDLParser::Qualified_partContext>(i);
}


size_t IDLParser::Qualified_identContext::getRuleIndex() const {
  return IDLParser::RuleQualified_ident;
}

antlrcpp::Any IDLParser::Qualified_identContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitQualified_ident(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Qualified_identContext* IDLParser::qualified_ident() {
  Qualified_identContext *_localctx = _tracker.createInstance<Qualified_identContext>(_ctx, getState());
  enterRule(_localctx, 114, IDLParser::RuleQualified_ident);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(537);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(536);
      qualified_separator();
    }
    setState(539);
    match(IDLParser::IDENT);
    setState(543);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(540);
        qualified_part(); 
      }
      setState(545);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Qualified_partContext ------------------------------------------------------------------

IDLParser::Qualified_partContext::Qualified_partContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Qualified_separatorContext* IDLParser::Qualified_partContext::qualified_separator() {
  return getRuleContext<IDLParser::Qualified_separatorContext>(0);
}

tree::TerminalNode* IDLParser::Qualified_partContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}


size_t IDLParser::Qualified_partContext::getRuleIndex() const {
  return IDLParser::RuleQualified_part;
}

antlrcpp::Any IDLParser::Qualified_partContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitQualified_part(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Qualified_partContext* IDLParser::qualified_part() {
  Qualified_partContext *_localctx = _tracker.createInstance<Qualified_partContext>(_ctx, getState());
  enterRule(_localctx, 116, IDLParser::RuleQualified_part);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(546);
    qualified_separator();
    setState(547);
    match(IDLParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Qualified_separatorContext ------------------------------------------------------------------

IDLParser::Qualified_separatorContext::Qualified_separatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> IDLParser::Qualified_separatorContext::COLON() {
  return getTokens(IDLParser::COLON);
}

tree::TerminalNode* IDLParser::Qualified_separatorContext::COLON(size_t i) {
  return getToken(IDLParser::COLON, i);
}


size_t IDLParser::Qualified_separatorContext::getRuleIndex() const {
  return IDLParser::RuleQualified_separator;
}

antlrcpp::Any IDLParser::Qualified_separatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitQualified_separator(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Qualified_separatorContext* IDLParser::qualified_separator() {
  Qualified_separatorContext *_localctx = _tracker.createInstance<Qualified_separatorContext>(_ctx, getState());
  enterRule(_localctx, 118, IDLParser::RuleQualified_separator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(549);
    match(IDLParser::COLON);
    setState(550);
    match(IDLParser::COLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- All_or_identContext ------------------------------------------------------------------

IDLParser::All_or_identContext::All_or_identContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::All_or_identContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::All_or_identContext::STAR() {
  return getToken(IDLParser::STAR, 0);
}


size_t IDLParser::All_or_identContext::getRuleIndex() const {
  return IDLParser::RuleAll_or_ident;
}

antlrcpp::Any IDLParser::All_or_identContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitAll_or_ident(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::All_or_identContext* IDLParser::all_or_ident() {
  All_or_identContext *_localctx = _tracker.createInstance<All_or_identContext>(_ctx, getState());
  enterRule(_localctx, 120, IDLParser::RuleAll_or_ident);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(552);
    _la = _input->LA(1);
    if (!(_la == IDLParser::STAR

    || _la == IDLParser::IDENT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Member_declContext ------------------------------------------------------------------

IDLParser::Member_declContext::Member_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Type_declContext* IDLParser::Member_declContext::type_decl() {
  return getRuleContext<IDLParser::Type_declContext>(0);
}

tree::TerminalNode* IDLParser::Member_declContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Member_declContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}

tree::TerminalNode* IDLParser::Member_declContext::LBRACKET() {
  return getToken(IDLParser::LBRACKET, 0);
}

IDLParser::Integer_litContext* IDLParser::Member_declContext::integer_lit() {
  return getRuleContext<IDLParser::Integer_litContext>(0);
}

tree::TerminalNode* IDLParser::Member_declContext::RBRACKET() {
  return getToken(IDLParser::RBRACKET, 0);
}

IDLParser::Member_initContext* IDLParser::Member_declContext::member_init() {
  return getRuleContext<IDLParser::Member_initContext>(0);
}


size_t IDLParser::Member_declContext::getRuleIndex() const {
  return IDLParser::RuleMember_decl;
}

antlrcpp::Any IDLParser::Member_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitMember_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Member_declContext* IDLParser::member_decl() {
  Member_declContext *_localctx = _tracker.createInstance<Member_declContext>(_ctx, getState());
  enterRule(_localctx, 122, IDLParser::RuleMember_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(554);
    type_decl();
    setState(555);
    match(IDLParser::IDENT);
    setState(560);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::LBRACKET) {
      setState(556);
      match(IDLParser::LBRACKET);
      setState(557);
      integer_lit();
      setState(558);
      match(IDLParser::RBRACKET);
    }
    setState(563);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::EQUALS) {
      setState(562);
      member_init();
    }
    setState(565);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Member_initContext ------------------------------------------------------------------

IDLParser::Member_initContext::Member_initContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Member_initContext::EQUALS() {
  return getToken(IDLParser::EQUALS, 0);
}

std::vector<IDLParser::Member_init_valueContext *> IDLParser::Member_initContext::member_init_value() {
  return getRuleContexts<IDLParser::Member_init_valueContext>();
}

IDLParser::Member_init_valueContext* IDLParser::Member_initContext::member_init_value(size_t i) {
  return getRuleContext<IDLParser::Member_init_valueContext>(i);
}

tree::TerminalNode* IDLParser::Member_initContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

tree::TerminalNode* IDLParser::Member_initContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> IDLParser::Member_initContext::COMMA() {
  return getTokens(IDLParser::COMMA);
}

tree::TerminalNode* IDLParser::Member_initContext::COMMA(size_t i) {
  return getToken(IDLParser::COMMA, i);
}


size_t IDLParser::Member_initContext::getRuleIndex() const {
  return IDLParser::RuleMember_init;
}

antlrcpp::Any IDLParser::Member_initContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitMember_init(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Member_initContext* IDLParser::member_init() {
  Member_initContext *_localctx = _tracker.createInstance<Member_initContext>(_ctx, getState());
  enterRule(_localctx, 124, IDLParser::RuleMember_init);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(581);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(567);
      match(IDLParser::EQUALS);
      setState(568);
      member_init_value();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(569);
      match(IDLParser::EQUALS);
      setState(570);
      match(IDLParser::LBRACE);
      setState(577);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << IDLParser::COLON)
        | (1ULL << IDLParser::IDENT)
        | (1ULL << IDLParser::DECIMAL_LIT)
        | (1ULL << IDLParser::HEX_LIT)
        | (1ULL << IDLParser::BIN_LIT)
        | (1ULL << IDLParser::OCT_LIT)
        | (1ULL << IDLParser::STRING_LIT)
        | (1ULL << IDLParser::FLOAT_LIT))) != 0)) {
        setState(571);
        member_init_value();
        setState(573);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == IDLParser::COMMA) {
          setState(572);
          match(IDLParser::COMMA);
        }
        setState(579);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(580);
      match(IDLParser::RBRACE);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Member_init_valueContext ------------------------------------------------------------------

IDLParser::Member_init_valueContext::Member_init_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Qualified_identContext* IDLParser::Member_init_valueContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}

IDLParser::Integer_litContext* IDLParser::Member_init_valueContext::integer_lit() {
  return getRuleContext<IDLParser::Integer_litContext>(0);
}

IDLParser::Float_litContext* IDLParser::Member_init_valueContext::float_lit() {
  return getRuleContext<IDLParser::Float_litContext>(0);
}

IDLParser::String_litContext* IDLParser::Member_init_valueContext::string_lit() {
  return getRuleContext<IDLParser::String_litContext>(0);
}


size_t IDLParser::Member_init_valueContext::getRuleIndex() const {
  return IDLParser::RuleMember_init_value;
}

antlrcpp::Any IDLParser::Member_init_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitMember_init_value(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Member_init_valueContext* IDLParser::member_init_value() {
  Member_init_valueContext *_localctx = _tracker.createInstance<Member_init_valueContext>(_ctx, getState());
  enterRule(_localctx, 126, IDLParser::RuleMember_init_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(587);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::COLON:
      case IDLParser::IDENT: {
        enterOuterAlt(_localctx, 1);
        setState(583);
        qualified_ident();
        break;
      }

      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::OCT_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(584);
        integer_lit();
        break;
      }

      case IDLParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 3);
        setState(585);
        float_lit();
        break;
      }

      case IDLParser::STRING_LIT: {
        enterOuterAlt(_localctx, 4);
        setState(586);
        string_lit();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_declContext ------------------------------------------------------------------

IDLParser::Type_declContext::Type_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Any_typeContext* IDLParser::Type_declContext::any_type() {
  return getRuleContext<IDLParser::Any_typeContext>(0);
}

IDLParser::Type_modifierContext* IDLParser::Type_declContext::type_modifier() {
  return getRuleContext<IDLParser::Type_modifierContext>(0);
}

IDLParser::Pointer_typeContext* IDLParser::Type_declContext::pointer_type() {
  return getRuleContext<IDLParser::Pointer_typeContext>(0);
}


size_t IDLParser::Type_declContext::getRuleIndex() const {
  return IDLParser::RuleType_decl;
}

antlrcpp::Any IDLParser::Type_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitType_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Type_declContext* IDLParser::type_decl() {
  Type_declContext *_localctx = _tracker.createInstance<Type_declContext>(_ctx, getState());
  enterRule(_localctx, 128, IDLParser::RuleType_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(590);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::Const) {
      setState(589);
      type_modifier();
    }
    setState(592);
    any_type();
    setState(594);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::STAR

    || _la == IDLParser::Const) {
      setState(593);
      pointer_type();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_modifierContext ------------------------------------------------------------------

IDLParser::Type_modifierContext::Type_modifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Type_modifierContext::Const() {
  return getToken(IDLParser::Const, 0);
}


size_t IDLParser::Type_modifierContext::getRuleIndex() const {
  return IDLParser::RuleType_modifier;
}

antlrcpp::Any IDLParser::Type_modifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitType_modifier(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Type_modifierContext* IDLParser::type_modifier() {
  Type_modifierContext *_localctx = _tracker.createInstance<Type_modifierContext>(_ctx, getState());
  enterRule(_localctx, 130, IDLParser::RuleType_modifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(596);
    match(IDLParser::Const);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pointer_typeContext ------------------------------------------------------------------

IDLParser::Pointer_typeContext::Pointer_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IDLParser::Pointer_declContext *> IDLParser::Pointer_typeContext::pointer_decl() {
  return getRuleContexts<IDLParser::Pointer_declContext>();
}

IDLParser::Pointer_declContext* IDLParser::Pointer_typeContext::pointer_decl(size_t i) {
  return getRuleContext<IDLParser::Pointer_declContext>(i);
}


size_t IDLParser::Pointer_typeContext::getRuleIndex() const {
  return IDLParser::RulePointer_type;
}

antlrcpp::Any IDLParser::Pointer_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitPointer_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Pointer_typeContext* IDLParser::pointer_type() {
  Pointer_typeContext *_localctx = _tracker.createInstance<Pointer_typeContext>(_ctx, getState());
  enterRule(_localctx, 132, IDLParser::RulePointer_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(599); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(598);
      pointer_decl();
      setState(601); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == IDLParser::STAR

    || _la == IDLParser::Const);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pointer_declContext ------------------------------------------------------------------

IDLParser::Pointer_declContext::Pointer_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Pointer_declContext::STAR() {
  return getToken(IDLParser::STAR, 0);
}

tree::TerminalNode* IDLParser::Pointer_declContext::Const() {
  return getToken(IDLParser::Const, 0);
}


size_t IDLParser::Pointer_declContext::getRuleIndex() const {
  return IDLParser::RulePointer_decl;
}

antlrcpp::Any IDLParser::Pointer_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitPointer_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Pointer_declContext* IDLParser::pointer_decl() {
  Pointer_declContext *_localctx = _tracker.createInstance<Pointer_declContext>(_ctx, getState());
  enterRule(_localctx, 134, IDLParser::RulePointer_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(604);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::Const) {
      setState(603);
      match(IDLParser::Const);
    }
    setState(606);
    match(IDLParser::STAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Any_typeContext ------------------------------------------------------------------

IDLParser::Any_typeContext::Any_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Integral_typeContext* IDLParser::Any_typeContext::integral_type() {
  return getRuleContext<IDLParser::Integral_typeContext>(0);
}

IDLParser::Float_typeContext* IDLParser::Any_typeContext::float_type() {
  return getRuleContext<IDLParser::Float_typeContext>(0);
}

IDLParser::Utility_typeContext* IDLParser::Any_typeContext::utility_type() {
  return getRuleContext<IDLParser::Utility_typeContext>(0);
}

IDLParser::Qualified_identContext* IDLParser::Any_typeContext::qualified_ident() {
  return getRuleContext<IDLParser::Qualified_identContext>(0);
}


size_t IDLParser::Any_typeContext::getRuleIndex() const {
  return IDLParser::RuleAny_type;
}

antlrcpp::Any IDLParser::Any_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitAny_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Any_typeContext* IDLParser::any_type() {
  Any_typeContext *_localctx = _tracker.createInstance<Any_typeContext>(_ctx, getState());
  enterRule(_localctx, 136, IDLParser::RuleAny_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(612);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::U8:
      case IDLParser::S8:
      case IDLParser::U16:
      case IDLParser::S16:
      case IDLParser::U32:
      case IDLParser::S32:
      case IDLParser::U64:
      case IDLParser::S64: {
        enterOuterAlt(_localctx, 1);
        setState(608);
        integral_type();
        break;
      }

      case IDLParser::F32:
      case IDLParser::F64: {
        enterOuterAlt(_localctx, 2);
        setState(609);
        float_type();
        break;
      }

      case IDLParser::Void:
      case IDLParser::RESULT: {
        enterOuterAlt(_localctx, 3);
        setState(610);
        utility_type();
        break;
      }

      case IDLParser::COLON:
      case IDLParser::IDENT: {
        enterOuterAlt(_localctx, 4);
        setState(611);
        qualified_ident();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Utility_typeContext ------------------------------------------------------------------

IDLParser::Utility_typeContext::Utility_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Utility_typeContext::Void() {
  return getToken(IDLParser::Void, 0);
}

tree::TerminalNode* IDLParser::Utility_typeContext::RESULT() {
  return getToken(IDLParser::RESULT, 0);
}


size_t IDLParser::Utility_typeContext::getRuleIndex() const {
  return IDLParser::RuleUtility_type;
}

antlrcpp::Any IDLParser::Utility_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitUtility_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Utility_typeContext* IDLParser::utility_type() {
  Utility_typeContext *_localctx = _tracker.createInstance<Utility_typeContext>(_ctx, getState());
  enterRule(_localctx, 138, IDLParser::RuleUtility_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(614);
    _la = _input->LA(1);
    if (!(_la == IDLParser::Void

    || _la == IDLParser::RESULT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Integral_typeContext ------------------------------------------------------------------

IDLParser::Integral_typeContext::Integral_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Integral_typeContext::U8() {
  return getToken(IDLParser::U8, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::S8() {
  return getToken(IDLParser::S8, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::U16() {
  return getToken(IDLParser::U16, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::S16() {
  return getToken(IDLParser::S16, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::U32() {
  return getToken(IDLParser::U32, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::S32() {
  return getToken(IDLParser::S32, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::U64() {
  return getToken(IDLParser::U64, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::S64() {
  return getToken(IDLParser::S64, 0);
}


size_t IDLParser::Integral_typeContext::getRuleIndex() const {
  return IDLParser::RuleIntegral_type;
}

antlrcpp::Any IDLParser::Integral_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitIntegral_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Integral_typeContext* IDLParser::integral_type() {
  Integral_typeContext *_localctx = _tracker.createInstance<Integral_typeContext>(_ctx, getState());
  enterRule(_localctx, 140, IDLParser::RuleIntegral_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(616);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Float_typeContext ------------------------------------------------------------------

IDLParser::Float_typeContext::Float_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Float_typeContext::F32() {
  return getToken(IDLParser::F32, 0);
}

tree::TerminalNode* IDLParser::Float_typeContext::F64() {
  return getToken(IDLParser::F64, 0);
}


size_t IDLParser::Float_typeContext::getRuleIndex() const {
  return IDLParser::RuleFloat_type;
}

antlrcpp::Any IDLParser::Float_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFloat_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Float_typeContext* IDLParser::float_type() {
  Float_typeContext *_localctx = _tracker.createInstance<Float_typeContext>(_ctx, getState());
  enterRule(_localctx, 142, IDLParser::RuleFloat_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(618);
    _la = _input->LA(1);
    if (!(_la == IDLParser::F32

    || _la == IDLParser::F64)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool IDLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 47: return expr_add_subSempred(dynamic_cast<Expr_add_subContext *>(context), predicateIndex);
    case 48: return expr_mul_divSempred(dynamic_cast<Expr_mul_divContext *>(context), predicateIndex);
    case 49: return expr_shiftSempred(dynamic_cast<Expr_shiftContext *>(context), predicateIndex);
    case 50: return expr_logicalSempred(dynamic_cast<Expr_logicalContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool IDLParser::expr_add_subSempred(Expr_add_subContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool IDLParser::expr_mul_divSempred(Expr_mul_divContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 3);
    case 3: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool IDLParser::expr_shiftSempred(Expr_shiftContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 3);
    case 5: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool IDLParser::expr_logicalSempred(Expr_logicalContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 6: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> IDLParser::_decisionToDFA;
atn::PredictionContextCache IDLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN IDLParser::_atn;
std::vector<uint16_t> IDLParser::_serializedATN;

std::vector<std::string> IDLParser::_ruleNames = {
  "main", "global_statements", "global_statement", "empty_stmt", "module_stmt", 
  "error_code_stmt", "success_stmt", "failure_stmt", "import_from_stmt", 
  "import_stmt", "struct_stmt", "struct_decl", "struct_fwd", "defaults_stmt", 
  "defaults_item", "defaults_array", "defaults_value", "union_stmt", "union_decl", 
  "union_fwd", "struct_block", "struct_item", "os_specific", "os_tag", "interface_stmt", 
  "interface_fwd", "interface_decl", "interface_super", "interface_block", 
  "interface_item", "function_decl", "function_param_list", "function_param", 
  "param_dir_qualifier", "const_def", "const_integral_def", "const_float_def", 
  "const_string_def", "const_class_id_def", "enum_fwd", "enum_def", "flags_fwd", 
  "flags_def", "enum_type", "enum_elements", "enum_item", "enum_expr", "expr_add_sub", 
  "expr_mul_div", "expr_shift", "expr_logical", "expr_value", "any_literal", 
  "numeric_lit", "integer_lit", "float_lit", "string_lit", "qualified_ident", 
  "qualified_part", "qualified_separator", "all_or_ident", "member_decl", 
  "member_init", "member_init_value", "type_decl", "type_modifier", "pointer_type", 
  "pointer_decl", "any_type", "utility_type", "integral_type", "float_type"
};

std::vector<std::string> IDLParser::_literalNames = {
  "", "'WINDOWS'", "'DARWIN'", "'import'", "'struct'", "'defaults'", "'union'", 
  "'interface'", "'enum'", "'flags'", "'module'", "'from'", "'in'", "'out'", 
  "':'", "';'", "'*'", "'/'", "'.'", "','", "'='", "'\"'", "'{'", "'}'", 
  "'('", "')'", "'['", "']'", "'<'", "'>'", "'+'", "'-'", "'<<'", "'>>'", 
  "'|'", "'const'", "'void'", "'result'", "'success'", "'failure'", "'class_id'", 
  "'string'", "'u8'", "'s8'", "'u16'", "'s16'", "'u32'", "'s32'", "'u64'", 
  "'s64'", "'f32'", "'f64'"
};

std::vector<std::string> IDLParser::_symbolicNames = {
  "", "Windows", "Darwin", "IMPORT", "STRUCT", "DEFAULTS", "UNION", "INTERFACE", 
  "ENUM", "FLAGS", "MODULE", "FROM", "IN", "OUT", "COLON", "SEMICOLON", 
  "STAR", "SLASH", "DOT", "COMMA", "EQUALS", "QUOTE", "LBRACE", "RBRACE", 
  "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LT", "GT", "PLUS", "MINUS", 
  "LSHIFT", "RSHIFT", "PIPE", "Const", "Void", "RESULT", "SUCCESS", "FAILURE", 
  "CLASS_ID", "STRING", "U8", "S8", "U16", "S16", "U32", "S32", "U64", "S64", 
  "F32", "F64", "IDENT", "DECIMAL_LIT", "HEX_LIT", "BIN_LIT", "OCT_LIT", 
  "STRING_LIT", "FLOAT_LIT", "WHITE_SPACE", "BLOCK_COMMENT", "LINE_COMMENT"
};

dfa::Vocabulary IDLParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> IDLParser::_tokenNames;

IDLParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x3f, 0x26f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x3, 0x2, 0x5, 0x2, 0x94, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x6, 0x3, 0x99, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x9a, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0xac, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0xb6, 0xa, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xd4, 
    0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 
    0xe2, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0xe5, 0xb, 0xf, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 
    0xf5, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xf9, 0xa, 0x11, 0x7, 
    0x11, 0xfb, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0xfe, 0xb, 0x11, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x103, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 
    0x5, 0x13, 0x107, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x7, 
    0x16, 0x113, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x116, 0xb, 0x16, 0x3, 
    0x16, 0x7, 0x16, 0x119, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x11c, 0xb, 
    0x16, 0x5, 0x16, 0x11e, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x125, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x7, 0x18, 0x12a, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 0x12d, 
    0xb, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 
    0x1a, 0x5, 0x1a, 0x135, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x13e, 0xa, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 
    0x1e, 0x7, 0x1e, 0x147, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x14a, 0xb, 
    0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 
    0x151, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 
    0x157, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x15b, 0xa, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x7, 0x21, 0x162, 
    0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x165, 0xb, 0x21, 0x3, 0x22, 0x5, 0x22, 
    0x168, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x178, 0xa, 0x23, 0x3, 0x24, 
    0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x17e, 0xa, 0x24, 0x3, 0x25, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 
    0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x1a0, 
    0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 
    0x2a, 0x1a7, 0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
    0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x1b0, 0xa, 0x2b, 0x3, 0x2b, 
    0x3, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x1b7, 0xa, 0x2c, 
    0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
    0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x1c3, 0xa, 0x2e, 
    0xc, 0x2e, 0xe, 0x2e, 0x1c6, 0xb, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 
    0x3, 0x2f, 0x5, 0x2f, 0x1cc, 0xa, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x31, 
    0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 
    0x31, 0x3, 0x31, 0x7, 0x31, 0x1d9, 0xa, 0x31, 0xc, 0x31, 0xe, 0x31, 
    0x1dc, 0xb, 0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x7, 0x32, 0x1e7, 0xa, 0x32, 
    0xc, 0x32, 0xe, 0x32, 0x1ea, 0xb, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 
    0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x7, 
    0x33, 0x1f5, 0xa, 0x33, 0xc, 0x33, 0xe, 0x33, 0x1f8, 0xb, 0x33, 0x3, 
    0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x7, 0x34, 
    0x200, 0xa, 0x34, 0xc, 0x34, 0xe, 0x34, 0x203, 0xb, 0x34, 0x3, 0x35, 
    0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 0x20b, 
    0xa, 0x35, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x20f, 0xa, 0x36, 0x3, 0x37, 
    0x3, 0x37, 0x5, 0x37, 0x213, 0xa, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3b, 0x5, 0x3b, 0x21c, 0xa, 0x3b, 
    0x3, 0x3b, 0x3, 0x3b, 0x7, 0x3b, 0x220, 0xa, 0x3b, 0xc, 0x3b, 0xe, 0x3b, 
    0x223, 0xb, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 
    0x3, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 
    0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x233, 0xa, 0x3f, 0x3, 0x3f, 
    0x5, 0x3f, 0x236, 0xa, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x5, 0x40, 0x240, 0xa, 0x40, 
    0x7, 0x40, 0x242, 0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 0x245, 0xb, 0x40, 
    0x3, 0x40, 0x5, 0x40, 0x248, 0xa, 0x40, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 
    0x3, 0x41, 0x5, 0x41, 0x24e, 0xa, 0x41, 0x3, 0x42, 0x5, 0x42, 0x251, 
    0xa, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x255, 0xa, 0x42, 0x3, 0x43, 
    0x3, 0x43, 0x3, 0x44, 0x6, 0x44, 0x25a, 0xa, 0x44, 0xd, 0x44, 0xe, 0x44, 
    0x25b, 0x3, 0x45, 0x5, 0x45, 0x25f, 0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 
    0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x5, 0x46, 0x267, 0xa, 0x46, 
    0x3, 0x47, 0x3, 0x47, 0x3, 0x48, 0x3, 0x48, 0x3, 0x49, 0x3, 0x49, 0x3, 
    0x49, 0x2, 0x6, 0x60, 0x62, 0x64, 0x66, 0x4a, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
    0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 
    0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 
    0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 
    0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80, 0x82, 
    0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x2, 0x8, 0x3, 0x2, 0x3, 0x4, 
    0x3, 0x2, 0x37, 0x3a, 0x4, 0x2, 0x12, 0x12, 0x36, 0x36, 0x3, 0x2, 0x26, 
    0x27, 0x3, 0x2, 0x2c, 0x33, 0x3, 0x2, 0x34, 0x35, 0x2, 0x274, 0x2, 0x93, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x98, 0x3, 0x2, 0x2, 0x2, 0x6, 0xab, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0xad, 0x3, 0x2, 0x2, 0x2, 0xa, 0xaf, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xe, 0xb7, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0xbf, 0x3, 0x2, 0x2, 0x2, 0x12, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x14, 0xcd, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x18, 0xd5, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0xd9, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xdd, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0xf4, 0x3, 0x2, 0x2, 0x2, 0x20, 0xfc, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x102, 0x3, 0x2, 0x2, 0x2, 0x24, 0x106, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0x108, 0x3, 0x2, 0x2, 0x2, 0x28, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x110, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x124, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x126, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x130, 0x3, 0x2, 0x2, 0x2, 0x32, 0x134, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x136, 0x3, 0x2, 0x2, 0x2, 0x36, 0x13a, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x141, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x144, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x150, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x152, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x42, 0x167, 0x3, 0x2, 0x2, 0x2, 0x44, 
    0x177, 0x3, 0x2, 0x2, 0x2, 0x46, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x48, 0x17f, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x186, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x18d, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x194, 0x3, 0x2, 0x2, 0x2, 0x50, 0x19c, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x54, 0x1ac, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x58, 0x1bc, 0x3, 0x2, 0x2, 0x2, 
    0x5a, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x5e, 
    0x1cd, 0x3, 0x2, 0x2, 0x2, 0x60, 0x1cf, 0x3, 0x2, 0x2, 0x2, 0x62, 0x1dd, 
    0x3, 0x2, 0x2, 0x2, 0x64, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x66, 0x1f9, 0x3, 
    0x2, 0x2, 0x2, 0x68, 0x20a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x20e, 0x3, 0x2, 
    0x2, 0x2, 0x6c, 0x212, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x214, 0x3, 0x2, 0x2, 
    0x2, 0x70, 0x216, 0x3, 0x2, 0x2, 0x2, 0x72, 0x218, 0x3, 0x2, 0x2, 0x2, 
    0x74, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x76, 0x224, 0x3, 0x2, 0x2, 0x2, 0x78, 
    0x227, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x22a, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x22c, 
    0x3, 0x2, 0x2, 0x2, 0x7e, 0x247, 0x3, 0x2, 0x2, 0x2, 0x80, 0x24d, 0x3, 
    0x2, 0x2, 0x2, 0x82, 0x250, 0x3, 0x2, 0x2, 0x2, 0x84, 0x256, 0x3, 0x2, 
    0x2, 0x2, 0x86, 0x259, 0x3, 0x2, 0x2, 0x2, 0x88, 0x25e, 0x3, 0x2, 0x2, 
    0x2, 0x8a, 0x266, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x268, 0x3, 0x2, 0x2, 0x2, 
    0x8e, 0x26a, 0x3, 0x2, 0x2, 0x2, 0x90, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x92, 
    0x94, 0x5, 0x4, 0x3, 0x2, 0x93, 0x92, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 
    0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x7, 
    0x2, 0x2, 0x3, 0x96, 0x3, 0x3, 0x2, 0x2, 0x2, 0x97, 0x99, 0x5, 0x6, 
    0x4, 0x2, 0x98, 0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 0x3, 0x2, 0x2, 
    0x2, 0x9a, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x3, 0x2, 0x2, 0x2, 
    0x9b, 0x5, 0x3, 0x2, 0x2, 0x2, 0x9c, 0xac, 0x5, 0x14, 0xb, 0x2, 0x9d, 
    0xac, 0x5, 0x16, 0xc, 0x2, 0x9e, 0xac, 0x5, 0x1c, 0xf, 0x2, 0x9f, 0xac, 
    0x5, 0x24, 0x13, 0x2, 0xa0, 0xac, 0x5, 0x32, 0x1a, 0x2, 0xa1, 0xac, 
    0x5, 0x46, 0x24, 0x2, 0xa2, 0xac, 0x5, 0x52, 0x2a, 0x2, 0xa3, 0xac, 
    0x5, 0x54, 0x2b, 0x2, 0xa4, 0xac, 0x5, 0x56, 0x2c, 0x2, 0xa5, 0xac, 
    0x5, 0x50, 0x29, 0x2, 0xa6, 0xac, 0x5, 0xa, 0x6, 0x2, 0xa7, 0xac, 0x5, 
    0xc, 0x7, 0x2, 0xa8, 0xac, 0x5, 0x8, 0x5, 0x2, 0xa9, 0xac, 0x5, 0x14, 
    0xb, 0x2, 0xaa, 0xac, 0x5, 0x12, 0xa, 0x2, 0xab, 0x9c, 0x3, 0x2, 0x2, 
    0x2, 0xab, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xab, 0x9e, 0x3, 0x2, 0x2, 0x2, 
    0xab, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xab, 
    0xa1, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa3, 
    0x3, 0x2, 0x2, 0x2, 0xab, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa5, 0x3, 
    0x2, 0x2, 0x2, 0xab, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa7, 0x3, 0x2, 
    0x2, 0x2, 0xab, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa9, 0x3, 0x2, 0x2, 
    0x2, 0xab, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xac, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0xad, 0xae, 0x7, 0x11, 0x2, 0x2, 0xae, 0x9, 0x3, 0x2, 0x2, 0x2, 0xaf, 
    0xb0, 0x7, 0xc, 0x2, 0x2, 0xb0, 0xb1, 0x5, 0x74, 0x3b, 0x2, 0xb1, 0xb2, 
    0x7, 0x11, 0x2, 0x2, 0xb2, 0xb, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb6, 0x5, 
    0xe, 0x8, 0x2, 0xb4, 0xb6, 0x5, 0x10, 0x9, 0x2, 0xb5, 0xb3, 0x3, 0x2, 
    0x2, 0x2, 0xb5, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0xb7, 0xb8, 0x7, 0x28, 0x2, 0x2, 0xb8, 0xb9, 0x7, 0x36, 0x2, 0x2, 
    0xb9, 0xba, 0x7, 0x1a, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x3b, 0x2, 0x2, 0xbb, 
    0xbc, 0x7, 0x15, 0x2, 0x2, 0xbc, 0xbd, 0x7, 0x3b, 0x2, 0x2, 0xbd, 0xbe, 
    0x7, 0x1b, 0x2, 0x2, 0xbe, 0xf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x7, 
    0x29, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x36, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0x1a, 
    0x2, 0x2, 0xc2, 0xc3, 0x7, 0x3b, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x15, 0x2, 
    0x2, 0xc4, 0xc5, 0x7, 0x3b, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0x1b, 0x2, 0x2, 
    0xc6, 0x11, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x7, 0x5, 0x2, 0x2, 0xc8, 
    0xc9, 0x5, 0x7a, 0x3e, 0x2, 0xc9, 0xca, 0x7, 0xd, 0x2, 0x2, 0xca, 0xcb, 
    0x5, 0x74, 0x3b, 0x2, 0xcb, 0xcc, 0x7, 0x11, 0x2, 0x2, 0xcc, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0xcd, 0xce, 0x7, 0x5, 0x2, 0x2, 0xce, 0xcf, 0x7, 0x36, 
    0x2, 0x2, 0xcf, 0xd0, 0x7, 0x11, 0x2, 0x2, 0xd0, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0xd1, 0xd4, 0x5, 0x18, 0xd, 0x2, 0xd2, 0xd4, 0x5, 0x1a, 0xe, 0x2, 
    0xd3, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd4, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0x6, 0x2, 0x2, 0xd6, 0xd7, 
    0x7, 0x36, 0x2, 0x2, 0xd7, 0xd8, 0x5, 0x2a, 0x16, 0x2, 0xd8, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0xd9, 0xda, 0x7, 0x6, 0x2, 0x2, 0xda, 0xdb, 0x5, 0x74, 
    0x3b, 0x2, 0xdb, 0xdc, 0x7, 0x11, 0x2, 0x2, 0xdc, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0xdd, 0xde, 0x7, 0x7, 0x2, 0x2, 0xde, 0xdf, 0x7, 0x36, 0x2, 0x2, 
    0xdf, 0xe3, 0x7, 0x18, 0x2, 0x2, 0xe0, 0xe2, 0x5, 0x1e, 0x10, 0x2, 0xe1, 
    0xe0, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe1, 
    0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe6, 0x3, 
    0x2, 0x2, 0x2, 0xe5, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x7, 0x19, 
    0x2, 0x2, 0xe7, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x7, 0x36, 0x2, 
    0x2, 0xe9, 0xea, 0x7, 0x10, 0x2, 0x2, 0xea, 0xeb, 0x5, 0x22, 0x12, 0x2, 
    0xeb, 0xec, 0x7, 0x11, 0x2, 0x2, 0xec, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xed, 
    0xee, 0x7, 0x36, 0x2, 0x2, 0xee, 0xef, 0x7, 0x10, 0x2, 0x2, 0xef, 0xf0, 
    0x7, 0x18, 0x2, 0x2, 0xf0, 0xf1, 0x5, 0x20, 0x11, 0x2, 0xf1, 0xf2, 0x7, 
    0x19, 0x2, 0x2, 0xf2, 0xf3, 0x7, 0x11, 0x2, 0x2, 0xf3, 0xf5, 0x3, 0x2, 
    0x2, 0x2, 0xf4, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xed, 0x3, 0x2, 0x2, 
    0x2, 0xf5, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf8, 0x5, 0x22, 0x12, 0x2, 
    0xf7, 0xf9, 0x7, 0x15, 0x2, 0x2, 0xf8, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf8, 
    0xf9, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xf6, 
    0x3, 0x2, 0x2, 0x2, 0xfb, 0xfe, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xfa, 0x3, 
    0x2, 0x2, 0x2, 0xfc, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfd, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0xfe, 0xfc, 0x3, 0x2, 0x2, 0x2, 0xff, 0x103, 0x5, 0x74, 0x3b, 
    0x2, 0x100, 0x101, 0x7, 0x7, 0x2, 0x2, 0x101, 0x103, 0x5, 0x74, 0x3b, 
    0x2, 0x102, 0xff, 0x3, 0x2, 0x2, 0x2, 0x102, 0x100, 0x3, 0x2, 0x2, 0x2, 
    0x103, 0x23, 0x3, 0x2, 0x2, 0x2, 0x104, 0x107, 0x5, 0x26, 0x14, 0x2, 
    0x105, 0x107, 0x5, 0x28, 0x15, 0x2, 0x106, 0x104, 0x3, 0x2, 0x2, 0x2, 
    0x106, 0x105, 0x3, 0x2, 0x2, 0x2, 0x107, 0x25, 0x3, 0x2, 0x2, 0x2, 0x108, 
    0x109, 0x7, 0x8, 0x2, 0x2, 0x109, 0x10a, 0x7, 0x36, 0x2, 0x2, 0x10a, 
    0x10b, 0x5, 0x2a, 0x16, 0x2, 0x10b, 0x27, 0x3, 0x2, 0x2, 0x2, 0x10c, 
    0x10d, 0x7, 0x8, 0x2, 0x2, 0x10d, 0x10e, 0x5, 0x74, 0x3b, 0x2, 0x10e, 
    0x10f, 0x7, 0x11, 0x2, 0x2, 0x10f, 0x29, 0x3, 0x2, 0x2, 0x2, 0x110, 
    0x11d, 0x7, 0x18, 0x2, 0x2, 0x111, 0x113, 0x5, 0x2c, 0x17, 0x2, 0x112, 
    0x111, 0x3, 0x2, 0x2, 0x2, 0x113, 0x116, 0x3, 0x2, 0x2, 0x2, 0x114, 
    0x112, 0x3, 0x2, 0x2, 0x2, 0x114, 0x115, 0x3, 0x2, 0x2, 0x2, 0x115, 
    0x11e, 0x3, 0x2, 0x2, 0x2, 0x116, 0x114, 0x3, 0x2, 0x2, 0x2, 0x117, 
    0x119, 0x5, 0x2e, 0x18, 0x2, 0x118, 0x117, 0x3, 0x2, 0x2, 0x2, 0x119, 
    0x11c, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x118, 0x3, 0x2, 0x2, 0x2, 0x11a, 
    0x11b, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x11c, 
    0x11a, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x114, 0x3, 0x2, 0x2, 0x2, 0x11d, 
    0x11a, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11f, 
    0x120, 0x7, 0x19, 0x2, 0x2, 0x120, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x121, 
    0x125, 0x5, 0x7c, 0x3f, 0x2, 0x122, 0x125, 0x5, 0x46, 0x24, 0x2, 0x123, 
    0x125, 0x5, 0x52, 0x2a, 0x2, 0x124, 0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 
    0x122, 0x3, 0x2, 0x2, 0x2, 0x124, 0x123, 0x3, 0x2, 0x2, 0x2, 0x125, 
    0x2d, 0x3, 0x2, 0x2, 0x2, 0x126, 0x127, 0x5, 0x30, 0x19, 0x2, 0x127, 
    0x12b, 0x7, 0x18, 0x2, 0x2, 0x128, 0x12a, 0x5, 0x2c, 0x17, 0x2, 0x129, 
    0x128, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x12b, 
    0x129, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12c, 
    0x12e, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12e, 
    0x12f, 0x7, 0x19, 0x2, 0x2, 0x12f, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x130, 
    0x131, 0x9, 0x2, 0x2, 0x2, 0x131, 0x31, 0x3, 0x2, 0x2, 0x2, 0x132, 0x135, 
    0x5, 0x36, 0x1c, 0x2, 0x133, 0x135, 0x5, 0x34, 0x1b, 0x2, 0x134, 0x132, 
    0x3, 0x2, 0x2, 0x2, 0x134, 0x133, 0x3, 0x2, 0x2, 0x2, 0x135, 0x33, 0x3, 
    0x2, 0x2, 0x2, 0x136, 0x137, 0x7, 0x9, 0x2, 0x2, 0x137, 0x138, 0x5, 
    0x74, 0x3b, 0x2, 0x138, 0x139, 0x7, 0x11, 0x2, 0x2, 0x139, 0x35, 0x3, 
    0x2, 0x2, 0x2, 0x13a, 0x13b, 0x7, 0x9, 0x2, 0x2, 0x13b, 0x13d, 0x7, 
    0x36, 0x2, 0x2, 0x13c, 0x13e, 0x5, 0x38, 0x1d, 0x2, 0x13d, 0x13c, 0x3, 
    0x2, 0x2, 0x2, 0x13d, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x13f, 0x3, 
    0x2, 0x2, 0x2, 0x13f, 0x140, 0x5, 0x3a, 0x1e, 0x2, 0x140, 0x37, 0x3, 
    0x2, 0x2, 0x2, 0x141, 0x142, 0x7, 0x10, 0x2, 0x2, 0x142, 0x143, 0x5, 
    0x74, 0x3b, 0x2, 0x143, 0x39, 0x3, 0x2, 0x2, 0x2, 0x144, 0x148, 0x7, 
    0x18, 0x2, 0x2, 0x145, 0x147, 0x5, 0x3c, 0x1f, 0x2, 0x146, 0x145, 0x3, 
    0x2, 0x2, 0x2, 0x147, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x148, 0x146, 0x3, 
    0x2, 0x2, 0x2, 0x148, 0x149, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14b, 0x3, 
    0x2, 0x2, 0x2, 0x14a, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x14c, 0x7, 
    0x19, 0x2, 0x2, 0x14c, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x151, 0x5, 
    0x3e, 0x20, 0x2, 0x14e, 0x151, 0x5, 0x46, 0x24, 0x2, 0x14f, 0x151, 0x5, 
    0x52, 0x2a, 0x2, 0x150, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x150, 0x14e, 0x3, 
    0x2, 0x2, 0x2, 0x150, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x151, 0x3d, 0x3, 0x2, 
    0x2, 0x2, 0x152, 0x153, 0x5, 0x82, 0x42, 0x2, 0x153, 0x154, 0x7, 0x36, 
    0x2, 0x2, 0x154, 0x156, 0x7, 0x1a, 0x2, 0x2, 0x155, 0x157, 0x5, 0x40, 
    0x21, 0x2, 0x156, 0x155, 0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 0x3, 0x2, 
    0x2, 0x2, 0x157, 0x158, 0x3, 0x2, 0x2, 0x2, 0x158, 0x15a, 0x7, 0x1b, 
    0x2, 0x2, 0x159, 0x15b, 0x7, 0x25, 0x2, 0x2, 0x15a, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x15a, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 0x3, 0x2, 
    0x2, 0x2, 0x15c, 0x15d, 0x7, 0x11, 0x2, 0x2, 0x15d, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0x15e, 0x163, 0x5, 0x42, 0x22, 0x2, 0x15f, 0x160, 0x7, 0x15, 
    0x2, 0x2, 0x160, 0x162, 0x5, 0x42, 0x22, 0x2, 0x161, 0x15f, 0x3, 0x2, 
    0x2, 0x2, 0x162, 0x165, 0x3, 0x2, 0x2, 0x2, 0x163, 0x161, 0x3, 0x2, 
    0x2, 0x2, 0x163, 0x164, 0x3, 0x2, 0x2, 0x2, 0x164, 0x41, 0x3, 0x2, 0x2, 
    0x2, 0x165, 0x163, 0x3, 0x2, 0x2, 0x2, 0x166, 0x168, 0x5, 0x44, 0x23, 
    0x2, 0x167, 0x166, 0x3, 0x2, 0x2, 0x2, 0x167, 0x168, 0x3, 0x2, 0x2, 
    0x2, 0x168, 0x169, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16a, 0x5, 0x82, 0x42, 
    0x2, 0x16a, 0x16b, 0x7, 0x36, 0x2, 0x2, 0x16b, 0x43, 0x3, 0x2, 0x2, 
    0x2, 0x16c, 0x16d, 0x7, 0x1c, 0x2, 0x2, 0x16d, 0x16e, 0x7, 0xe, 0x2, 
    0x2, 0x16e, 0x178, 0x7, 0x1d, 0x2, 0x2, 0x16f, 0x170, 0x7, 0x1c, 0x2, 
    0x2, 0x170, 0x171, 0x7, 0xf, 0x2, 0x2, 0x171, 0x178, 0x7, 0x1d, 0x2, 
    0x2, 0x172, 0x173, 0x7, 0x1c, 0x2, 0x2, 0x173, 0x174, 0x7, 0xe, 0x2, 
    0x2, 0x174, 0x175, 0x7, 0x15, 0x2, 0x2, 0x175, 0x176, 0x7, 0xf, 0x2, 
    0x2, 0x176, 0x178, 0x7, 0x1d, 0x2, 0x2, 0x177, 0x16c, 0x3, 0x2, 0x2, 
    0x2, 0x177, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x177, 0x172, 0x3, 0x2, 0x2, 
    0x2, 0x178, 0x45, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17e, 0x5, 0x48, 0x25, 
    0x2, 0x17a, 0x17e, 0x5, 0x4a, 0x26, 0x2, 0x17b, 0x17e, 0x5, 0x4c, 0x27, 
    0x2, 0x17c, 0x17e, 0x5, 0x4e, 0x28, 0x2, 0x17d, 0x179, 0x3, 0x2, 0x2, 
    0x2, 0x17d, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x17d, 0x17b, 0x3, 0x2, 0x2, 
    0x2, 0x17d, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x47, 0x3, 0x2, 0x2, 0x2, 
    0x17f, 0x180, 0x7, 0x25, 0x2, 0x2, 0x180, 0x181, 0x5, 0x8e, 0x48, 0x2, 
    0x181, 0x182, 0x7, 0x36, 0x2, 0x2, 0x182, 0x183, 0x7, 0x16, 0x2, 0x2, 
    0x183, 0x184, 0x5, 0x6e, 0x38, 0x2, 0x184, 0x185, 0x7, 0x11, 0x2, 0x2, 
    0x185, 0x49, 0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x7, 0x25, 0x2, 0x2, 
    0x187, 0x188, 0x5, 0x90, 0x49, 0x2, 0x188, 0x189, 0x7, 0x36, 0x2, 0x2, 
    0x189, 0x18a, 0x7, 0x16, 0x2, 0x2, 0x18a, 0x18b, 0x5, 0x70, 0x39, 0x2, 
    0x18b, 0x18c, 0x7, 0x11, 0x2, 0x2, 0x18c, 0x4b, 0x3, 0x2, 0x2, 0x2, 
    0x18d, 0x18e, 0x7, 0x25, 0x2, 0x2, 0x18e, 0x18f, 0x7, 0x2b, 0x2, 0x2, 
    0x18f, 0x190, 0x7, 0x36, 0x2, 0x2, 0x190, 0x191, 0x7, 0x16, 0x2, 0x2, 
    0x191, 0x192, 0x5, 0x72, 0x3a, 0x2, 0x192, 0x193, 0x7, 0x11, 0x2, 0x2, 
    0x193, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x194, 0x195, 0x7, 0x25, 0x2, 0x2, 
    0x195, 0x196, 0x7, 0x2a, 0x2, 0x2, 0x196, 0x197, 0x7, 0x36, 0x2, 0x2, 
    0x197, 0x198, 0x7, 0x1a, 0x2, 0x2, 0x198, 0x199, 0x5, 0x72, 0x3a, 0x2, 
    0x199, 0x19a, 0x7, 0x1b, 0x2, 0x2, 0x19a, 0x19b, 0x7, 0x11, 0x2, 0x2, 
    0x19b, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19d, 0x7, 0xa, 0x2, 0x2, 0x19d, 
    0x19f, 0x7, 0x36, 0x2, 0x2, 0x19e, 0x1a0, 0x5, 0x58, 0x2d, 0x2, 0x19f, 
    0x19e, 0x3, 0x2, 0x2, 0x2, 0x19f, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1a0, 
    0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x1a2, 0x7, 0x11, 0x2, 0x2, 0x1a2, 
    0x51, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 0x7, 0xa, 0x2, 0x2, 0x1a4, 0x1a6, 
    0x7, 0x36, 0x2, 0x2, 0x1a5, 0x1a7, 0x5, 0x58, 0x2d, 0x2, 0x1a6, 0x1a5, 
    0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1a8, 
    0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1a9, 0x7, 0x18, 0x2, 0x2, 0x1a9, 0x1aa, 
    0x5, 0x5a, 0x2e, 0x2, 0x1aa, 0x1ab, 0x7, 0x19, 0x2, 0x2, 0x1ab, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1ad, 0x7, 0xb, 0x2, 0x2, 0x1ad, 0x1af, 
    0x7, 0x36, 0x2, 0x2, 0x1ae, 0x1b0, 0x5, 0x58, 0x2d, 0x2, 0x1af, 0x1ae, 
    0x3, 0x2, 0x2, 0x2, 0x1af, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1b1, 
    0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1b2, 0x7, 0x11, 0x2, 0x2, 0x1b2, 0x55, 
    0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b4, 0x7, 0xb, 0x2, 0x2, 0x1b4, 0x1b6, 
    0x7, 0x36, 0x2, 0x2, 0x1b5, 0x1b7, 0x5, 0x58, 0x2d, 0x2, 0x1b6, 0x1b5, 
    0x3, 0x2, 0x2, 0x2, 0x1b6, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b8, 
    0x3, 0x2, 0x2, 0x2, 0x1b8, 0x1b9, 0x7, 0x18, 0x2, 0x2, 0x1b9, 0x1ba, 
    0x5, 0x5a, 0x2e, 0x2, 0x1ba, 0x1bb, 0x7, 0x19, 0x2, 0x2, 0x1bb, 0x57, 
    0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bd, 0x7, 0x10, 0x2, 0x2, 0x1bd, 0x1be, 
    0x5, 0x8e, 0x48, 0x2, 0x1be, 0x59, 0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c4, 
    0x5, 0x5c, 0x2f, 0x2, 0x1c0, 0x1c1, 0x7, 0x15, 0x2, 0x2, 0x1c1, 0x1c3, 
    0x5, 0x5c, 0x2f, 0x2, 0x1c2, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c6, 
    0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c5, 
    0x3, 0x2, 0x2, 0x2, 0x1c5, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1c4, 0x3, 
    0x2, 0x2, 0x2, 0x1c7, 0x1cc, 0x7, 0x36, 0x2, 0x2, 0x1c8, 0x1c9, 0x7, 
    0x36, 0x2, 0x2, 0x1c9, 0x1ca, 0x7, 0x16, 0x2, 0x2, 0x1ca, 0x1cc, 0x5, 
    0x5e, 0x30, 0x2, 0x1cb, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1c8, 0x3, 
    0x2, 0x2, 0x2, 0x1cc, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1ce, 0x5, 0x60, 
    0x31, 0x2, 0x1ce, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1d0, 0x8, 0x31, 
    0x1, 0x2, 0x1d0, 0x1d1, 0x5, 0x62, 0x32, 0x2, 0x1d1, 0x1da, 0x3, 0x2, 
    0x2, 0x2, 0x1d2, 0x1d3, 0xc, 0x5, 0x2, 0x2, 0x1d3, 0x1d4, 0x7, 0x20, 
    0x2, 0x2, 0x1d4, 0x1d9, 0x5, 0x62, 0x32, 0x2, 0x1d5, 0x1d6, 0xc, 0x4, 
    0x2, 0x2, 0x1d6, 0x1d7, 0x7, 0x21, 0x2, 0x2, 0x1d7, 0x1d9, 0x5, 0x62, 
    0x32, 0x2, 0x1d8, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1d5, 0x3, 0x2, 
    0x2, 0x2, 0x1d9, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1d8, 0x3, 0x2, 
    0x2, 0x2, 0x1da, 0x1db, 0x3, 0x2, 0x2, 0x2, 0x1db, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x1dc, 0x1da, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1de, 0x8, 0x32, 0x1, 
    0x2, 0x1de, 0x1df, 0x5, 0x64, 0x33, 0x2, 0x1df, 0x1e8, 0x3, 0x2, 0x2, 
    0x2, 0x1e0, 0x1e1, 0xc, 0x5, 0x2, 0x2, 0x1e1, 0x1e2, 0x7, 0x12, 0x2, 
    0x2, 0x1e2, 0x1e7, 0x5, 0x64, 0x33, 0x2, 0x1e3, 0x1e4, 0xc, 0x4, 0x2, 
    0x2, 0x1e4, 0x1e5, 0x7, 0x13, 0x2, 0x2, 0x1e5, 0x1e7, 0x5, 0x64, 0x33, 
    0x2, 0x1e6, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e3, 0x3, 0x2, 0x2, 
    0x2, 0x1e7, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e6, 0x3, 0x2, 0x2, 
    0x2, 0x1e8, 0x1e9, 0x3, 0x2, 0x2, 0x2, 0x1e9, 0x63, 0x3, 0x2, 0x2, 0x2, 
    0x1ea, 0x1e8, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ec, 0x8, 0x33, 0x1, 0x2, 
    0x1ec, 0x1ed, 0x5, 0x66, 0x34, 0x2, 0x1ed, 0x1f6, 0x3, 0x2, 0x2, 0x2, 
    0x1ee, 0x1ef, 0xc, 0x5, 0x2, 0x2, 0x1ef, 0x1f0, 0x7, 0x22, 0x2, 0x2, 
    0x1f0, 0x1f5, 0x5, 0x66, 0x34, 0x2, 0x1f1, 0x1f2, 0xc, 0x4, 0x2, 0x2, 
    0x1f2, 0x1f3, 0x7, 0x23, 0x2, 0x2, 0x1f3, 0x1f5, 0x5, 0x66, 0x34, 0x2, 
    0x1f4, 0x1ee, 0x3, 0x2, 0x2, 0x2, 0x1f4, 0x1f1, 0x3, 0x2, 0x2, 0x2, 
    0x1f5, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1f6, 0x1f4, 0x3, 0x2, 0x2, 0x2, 
    0x1f6, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x65, 0x3, 0x2, 0x2, 0x2, 0x1f8, 
    0x1f6, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1fa, 0x8, 0x34, 0x1, 0x2, 0x1fa, 
    0x1fb, 0x5, 0x68, 0x35, 0x2, 0x1fb, 0x201, 0x3, 0x2, 0x2, 0x2, 0x1fc, 
    0x1fd, 0xc, 0x4, 0x2, 0x2, 0x1fd, 0x1fe, 0x7, 0x24, 0x2, 0x2, 0x1fe, 
    0x200, 0x5, 0x68, 0x35, 0x2, 0x1ff, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x200, 
    0x203, 0x3, 0x2, 0x2, 0x2, 0x201, 0x1ff, 0x3, 0x2, 0x2, 0x2, 0x201, 
    0x202, 0x3, 0x2, 0x2, 0x2, 0x202, 0x67, 0x3, 0x2, 0x2, 0x2, 0x203, 0x201, 
    0x3, 0x2, 0x2, 0x2, 0x204, 0x20b, 0x5, 0x6e, 0x38, 0x2, 0x205, 0x20b, 
    0x5, 0x74, 0x3b, 0x2, 0x206, 0x207, 0x7, 0x1a, 0x2, 0x2, 0x207, 0x208, 
    0x5, 0x5e, 0x30, 0x2, 0x208, 0x209, 0x7, 0x1b, 0x2, 0x2, 0x209, 0x20b, 
    0x3, 0x2, 0x2, 0x2, 0x20a, 0x204, 0x3, 0x2, 0x2, 0x2, 0x20a, 0x205, 
    0x3, 0x2, 0x2, 0x2, 0x20a, 0x206, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x69, 0x3, 
    0x2, 0x2, 0x2, 0x20c, 0x20f, 0x5, 0x6c, 0x37, 0x2, 0x20d, 0x20f, 0x5, 
    0x72, 0x3a, 0x2, 0x20e, 0x20c, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20d, 0x3, 
    0x2, 0x2, 0x2, 0x20f, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x210, 0x213, 0x5, 0x6e, 
    0x38, 0x2, 0x211, 0x213, 0x5, 0x70, 0x39, 0x2, 0x212, 0x210, 0x3, 0x2, 
    0x2, 0x2, 0x212, 0x211, 0x3, 0x2, 0x2, 0x2, 0x213, 0x6d, 0x3, 0x2, 0x2, 
    0x2, 0x214, 0x215, 0x9, 0x3, 0x2, 0x2, 0x215, 0x6f, 0x3, 0x2, 0x2, 0x2, 
    0x216, 0x217, 0x7, 0x3c, 0x2, 0x2, 0x217, 0x71, 0x3, 0x2, 0x2, 0x2, 
    0x218, 0x219, 0x7, 0x3b, 0x2, 0x2, 0x219, 0x73, 0x3, 0x2, 0x2, 0x2, 
    0x21a, 0x21c, 0x5, 0x78, 0x3d, 0x2, 0x21b, 0x21a, 0x3, 0x2, 0x2, 0x2, 
    0x21b, 0x21c, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x21d, 0x3, 0x2, 0x2, 0x2, 
    0x21d, 0x221, 0x7, 0x36, 0x2, 0x2, 0x21e, 0x220, 0x5, 0x76, 0x3c, 0x2, 
    0x21f, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x220, 0x223, 0x3, 0x2, 0x2, 0x2, 
    0x221, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x221, 0x222, 0x3, 0x2, 0x2, 0x2, 
    0x222, 0x75, 0x3, 0x2, 0x2, 0x2, 0x223, 0x221, 0x3, 0x2, 0x2, 0x2, 0x224, 
    0x225, 0x5, 0x78, 0x3d, 0x2, 0x225, 0x226, 0x7, 0x36, 0x2, 0x2, 0x226, 
    0x77, 0x3, 0x2, 0x2, 0x2, 0x227, 0x228, 0x7, 0x10, 0x2, 0x2, 0x228, 
    0x229, 0x7, 0x10, 0x2, 0x2, 0x229, 0x79, 0x3, 0x2, 0x2, 0x2, 0x22a, 
    0x22b, 0x9, 0x4, 0x2, 0x2, 0x22b, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x22c, 0x22d, 
    0x5, 0x82, 0x42, 0x2, 0x22d, 0x232, 0x7, 0x36, 0x2, 0x2, 0x22e, 0x22f, 
    0x7, 0x1c, 0x2, 0x2, 0x22f, 0x230, 0x5, 0x6e, 0x38, 0x2, 0x230, 0x231, 
    0x7, 0x1d, 0x2, 0x2, 0x231, 0x233, 0x3, 0x2, 0x2, 0x2, 0x232, 0x22e, 
    0x3, 0x2, 0x2, 0x2, 0x232, 0x233, 0x3, 0x2, 0x2, 0x2, 0x233, 0x235, 
    0x3, 0x2, 0x2, 0x2, 0x234, 0x236, 0x5, 0x7e, 0x40, 0x2, 0x235, 0x234, 
    0x3, 0x2, 0x2, 0x2, 0x235, 0x236, 0x3, 0x2, 0x2, 0x2, 0x236, 0x237, 
    0x3, 0x2, 0x2, 0x2, 0x237, 0x238, 0x7, 0x11, 0x2, 0x2, 0x238, 0x7d, 
    0x3, 0x2, 0x2, 0x2, 0x239, 0x23a, 0x7, 0x16, 0x2, 0x2, 0x23a, 0x248, 
    0x5, 0x80, 0x41, 0x2, 0x23b, 0x23c, 0x7, 0x16, 0x2, 0x2, 0x23c, 0x243, 
    0x7, 0x18, 0x2, 0x2, 0x23d, 0x23f, 0x5, 0x80, 0x41, 0x2, 0x23e, 0x240, 
    0x7, 0x15, 0x2, 0x2, 0x23f, 0x23e, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x240, 
    0x3, 0x2, 0x2, 0x2, 0x240, 0x242, 0x3, 0x2, 0x2, 0x2, 0x241, 0x23d, 
    0x3, 0x2, 0x2, 0x2, 0x242, 0x245, 0x3, 0x2, 0x2, 0x2, 0x243, 0x241, 
    0x3, 0x2, 0x2, 0x2, 0x243, 0x244, 0x3, 0x2, 0x2, 0x2, 0x244, 0x246, 
    0x3, 0x2, 0x2, 0x2, 0x245, 0x243, 0x3, 0x2, 0x2, 0x2, 0x246, 0x248, 
    0x7, 0x19, 0x2, 0x2, 0x247, 0x239, 0x3, 0x2, 0x2, 0x2, 0x247, 0x23b, 
    0x3, 0x2, 0x2, 0x2, 0x248, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x249, 0x24e, 0x5, 
    0x74, 0x3b, 0x2, 0x24a, 0x24e, 0x5, 0x6e, 0x38, 0x2, 0x24b, 0x24e, 0x5, 
    0x70, 0x39, 0x2, 0x24c, 0x24e, 0x5, 0x72, 0x3a, 0x2, 0x24d, 0x249, 0x3, 
    0x2, 0x2, 0x2, 0x24d, 0x24a, 0x3, 0x2, 0x2, 0x2, 0x24d, 0x24b, 0x3, 
    0x2, 0x2, 0x2, 0x24d, 0x24c, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x81, 0x3, 0x2, 
    0x2, 0x2, 0x24f, 0x251, 0x5, 0x84, 0x43, 0x2, 0x250, 0x24f, 0x3, 0x2, 
    0x2, 0x2, 0x250, 0x251, 0x3, 0x2, 0x2, 0x2, 0x251, 0x252, 0x3, 0x2, 
    0x2, 0x2, 0x252, 0x254, 0x5, 0x8a, 0x46, 0x2, 0x253, 0x255, 0x5, 0x86, 
    0x44, 0x2, 0x254, 0x253, 0x3, 0x2, 0x2, 0x2, 0x254, 0x255, 0x3, 0x2, 
    0x2, 0x2, 0x255, 0x83, 0x3, 0x2, 0x2, 0x2, 0x256, 0x257, 0x7, 0x25, 
    0x2, 0x2, 0x257, 0x85, 0x3, 0x2, 0x2, 0x2, 0x258, 0x25a, 0x5, 0x88, 
    0x45, 0x2, 0x259, 0x258, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x25b, 0x3, 0x2, 
    0x2, 0x2, 0x25b, 0x259, 0x3, 0x2, 0x2, 0x2, 0x25b, 0x25c, 0x3, 0x2, 
    0x2, 0x2, 0x25c, 0x87, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x25f, 0x7, 0x25, 
    0x2, 0x2, 0x25e, 0x25d, 0x3, 0x2, 0x2, 0x2, 0x25e, 0x25f, 0x3, 0x2, 
    0x2, 0x2, 0x25f, 0x260, 0x3, 0x2, 0x2, 0x2, 0x260, 0x261, 0x7, 0x12, 
    0x2, 0x2, 0x261, 0x89, 0x3, 0x2, 0x2, 0x2, 0x262, 0x267, 0x5, 0x8e, 
    0x48, 0x2, 0x263, 0x267, 0x5, 0x90, 0x49, 0x2, 0x264, 0x267, 0x5, 0x8c, 
    0x47, 0x2, 0x265, 0x267, 0x5, 0x74, 0x3b, 0x2, 0x266, 0x262, 0x3, 0x2, 
    0x2, 0x2, 0x266, 0x263, 0x3, 0x2, 0x2, 0x2, 0x266, 0x264, 0x3, 0x2, 
    0x2, 0x2, 0x266, 0x265, 0x3, 0x2, 0x2, 0x2, 0x267, 0x8b, 0x3, 0x2, 0x2, 
    0x2, 0x268, 0x269, 0x9, 0x5, 0x2, 0x2, 0x269, 0x8d, 0x3, 0x2, 0x2, 0x2, 
    0x26a, 0x26b, 0x9, 0x6, 0x2, 0x2, 0x26b, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x26c, 
    0x26d, 0x9, 0x7, 0x2, 0x2, 0x26d, 0x91, 0x3, 0x2, 0x2, 0x2, 0x39, 0x93, 
    0x9a, 0xab, 0xb5, 0xd3, 0xe3, 0xf4, 0xf8, 0xfc, 0x102, 0x106, 0x114, 
    0x11a, 0x11d, 0x124, 0x12b, 0x134, 0x13d, 0x148, 0x150, 0x156, 0x15a, 
    0x163, 0x167, 0x177, 0x17d, 0x19f, 0x1a6, 0x1af, 0x1b6, 0x1c4, 0x1cb, 
    0x1d8, 0x1da, 0x1e6, 0x1e8, 0x1f4, 0x1f6, 0x201, 0x20a, 0x20e, 0x212, 
    0x21b, 0x221, 0x232, 0x235, 0x23f, 0x243, 0x247, 0x24d, 0x250, 0x254, 
    0x25b, 0x25e, 0x266, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

IDLParser::Initializer IDLParser::_init;
