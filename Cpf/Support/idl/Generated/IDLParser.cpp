
// Generated from C:/Projects/cpf/Cpf/Support/idl\IDLParser.g4 by ANTLR 4.7


#include "IDLParserListener.h"
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

void IDLParser::MainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMain(this);
}

void IDLParser::MainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMain(this);
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
    setState(117);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE)
      | (1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::MODULE)
      | (1ULL << IDLParser::SEMICOLON)
      | (1ULL << IDLParser::Const)
      | (1ULL << IDLParser::SUCCESS)
      | (1ULL << IDLParser::FAILURE))) != 0)) {
      setState(116);
      global_statements();
    }
    setState(119);
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

void IDLParser::Global_statementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_statements(this);
}

void IDLParser::Global_statementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_statements(this);
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
    setState(122); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(121);
      global_statement();
      setState(124); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE)
      | (1ULL << IDLParser::ENUM)
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

IDLParser::Interface_stmtContext* IDLParser::Global_statementContext::interface_stmt() {
  return getRuleContext<IDLParser::Interface_stmtContext>(0);
}

IDLParser::Const_defContext* IDLParser::Global_statementContext::const_def() {
  return getRuleContext<IDLParser::Const_defContext>(0);
}

IDLParser::Enum_defContext* IDLParser::Global_statementContext::enum_def() {
  return getRuleContext<IDLParser::Enum_defContext>(0);
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

void IDLParser::Global_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_statement(this);
}

void IDLParser::Global_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_statement(this);
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
    setState(136);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(126);
      import_stmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(127);
      struct_stmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(128);
      interface_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(129);
      const_def();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(130);
      enum_def();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(131);
      enum_fwd();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(132);
      module_stmt();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(133);
      error_code_stmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(134);
      empty_stmt();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(135);
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

void IDLParser::Empty_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmpty_stmt(this);
}

void IDLParser::Empty_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmpty_stmt(this);
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
    setState(138);
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

void IDLParser::Module_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModule_stmt(this);
}

void IDLParser::Module_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModule_stmt(this);
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
    setState(140);
    match(IDLParser::MODULE);
    setState(141);
    qualified_ident();
    setState(142);
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

void IDLParser::Error_code_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterError_code_stmt(this);
}

void IDLParser::Error_code_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitError_code_stmt(this);
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
    setState(146);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::SUCCESS: {
        enterOuterAlt(_localctx, 1);
        setState(144);
        success_stmt();
        break;
      }

      case IDLParser::FAILURE: {
        enterOuterAlt(_localctx, 2);
        setState(145);
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

void IDLParser::Success_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSuccess_stmt(this);
}

void IDLParser::Success_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSuccess_stmt(this);
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
    setState(148);
    match(IDLParser::SUCCESS);
    setState(149);
    match(IDLParser::IDENT);
    setState(150);
    match(IDLParser::LPAREN);
    setState(151);
    match(IDLParser::STRING_LIT);
    setState(152);
    match(IDLParser::COMMA);
    setState(153);
    match(IDLParser::STRING_LIT);
    setState(154);
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

void IDLParser::Failure_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFailure_stmt(this);
}

void IDLParser::Failure_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFailure_stmt(this);
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
    setState(156);
    match(IDLParser::FAILURE);
    setState(157);
    match(IDLParser::IDENT);
    setState(158);
    match(IDLParser::LPAREN);
    setState(159);
    match(IDLParser::STRING_LIT);
    setState(160);
    match(IDLParser::COMMA);
    setState(161);
    match(IDLParser::STRING_LIT);
    setState(162);
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

void IDLParser::Import_from_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_from_stmt(this);
}

void IDLParser::Import_from_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_from_stmt(this);
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
    setState(164);
    match(IDLParser::IMPORT);
    setState(165);
    all_or_ident();
    setState(166);
    match(IDLParser::FROM);
    setState(167);
    qualified_ident();
    setState(168);
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

IDLParser::String_litContext* IDLParser::Import_stmtContext::string_lit() {
  return getRuleContext<IDLParser::String_litContext>(0);
}

tree::TerminalNode* IDLParser::Import_stmtContext::SEMICOLON() {
  return getToken(IDLParser::SEMICOLON, 0);
}


size_t IDLParser::Import_stmtContext::getRuleIndex() const {
  return IDLParser::RuleImport_stmt;
}

void IDLParser::Import_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_stmt(this);
}

void IDLParser::Import_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_stmt(this);
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
    setState(170);
    match(IDLParser::IMPORT);
    setState(171);
    string_lit();
    setState(172);
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

void IDLParser::Struct_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_stmt(this);
}

void IDLParser::Struct_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_stmt(this);
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
    setState(176);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(174);
      struct_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(175);
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

void IDLParser::Struct_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_decl(this);
}

void IDLParser::Struct_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_decl(this);
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
    setState(178);
    match(IDLParser::STRUCT);
    setState(179);
    match(IDLParser::IDENT);
    setState(180);
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

void IDLParser::Struct_fwdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_fwd(this);
}

void IDLParser::Struct_fwdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_fwd(this);
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
    setState(182);
    match(IDLParser::STRUCT);
    setState(183);
    qualified_ident();
    setState(184);
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


size_t IDLParser::Struct_blockContext::getRuleIndex() const {
  return IDLParser::RuleStruct_block;
}

void IDLParser::Struct_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_block(this);
}

void IDLParser::Struct_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_block(this);
}


antlrcpp::Any IDLParser::Struct_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_block(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_blockContext* IDLParser::struct_block() {
  Struct_blockContext *_localctx = _tracker.createInstance<Struct_blockContext>(_ctx, getState());
  enterRule(_localctx, 26, IDLParser::RuleStruct_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    match(IDLParser::LBRACE);
    setState(190);
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
      setState(187);
      struct_item();
      setState(192);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(193);
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

void IDLParser::Struct_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_item(this);
}

void IDLParser::Struct_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_item(this);
}


antlrcpp::Any IDLParser::Struct_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_itemContext* IDLParser::struct_item() {
  Struct_itemContext *_localctx = _tracker.createInstance<Struct_itemContext>(_ctx, getState());
  enterRule(_localctx, 28, IDLParser::RuleStruct_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(198);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(195);
      member_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(196);
      const_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(197);
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

void IDLParser::Interface_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterface_stmt(this);
}

void IDLParser::Interface_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterface_stmt(this);
}


antlrcpp::Any IDLParser::Interface_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_stmtContext* IDLParser::interface_stmt() {
  Interface_stmtContext *_localctx = _tracker.createInstance<Interface_stmtContext>(_ctx, getState());
  enterRule(_localctx, 30, IDLParser::RuleInterface_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(202);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(200);
      interface_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(201);
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

void IDLParser::Interface_fwdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterface_fwd(this);
}

void IDLParser::Interface_fwdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterface_fwd(this);
}


antlrcpp::Any IDLParser::Interface_fwdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_fwd(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_fwdContext* IDLParser::interface_fwd() {
  Interface_fwdContext *_localctx = _tracker.createInstance<Interface_fwdContext>(_ctx, getState());
  enterRule(_localctx, 32, IDLParser::RuleInterface_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    match(IDLParser::INTERFACE);
    setState(205);
    qualified_ident();
    setState(206);
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

void IDLParser::Interface_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterface_decl(this);
}

void IDLParser::Interface_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterface_decl(this);
}


antlrcpp::Any IDLParser::Interface_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_declContext* IDLParser::interface_decl() {
  Interface_declContext *_localctx = _tracker.createInstance<Interface_declContext>(_ctx, getState());
  enterRule(_localctx, 34, IDLParser::RuleInterface_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(IDLParser::INTERFACE);
    setState(209);
    match(IDLParser::IDENT);
    setState(211);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(210);
      interface_super();
    }
    setState(213);
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

void IDLParser::Interface_superContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterface_super(this);
}

void IDLParser::Interface_superContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterface_super(this);
}


antlrcpp::Any IDLParser::Interface_superContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_super(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_superContext* IDLParser::interface_super() {
  Interface_superContext *_localctx = _tracker.createInstance<Interface_superContext>(_ctx, getState());
  enterRule(_localctx, 36, IDLParser::RuleInterface_super);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    match(IDLParser::COLON);
    setState(216);
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

void IDLParser::Interface_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterface_block(this);
}

void IDLParser::Interface_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterface_block(this);
}


antlrcpp::Any IDLParser::Interface_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_block(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_blockContext* IDLParser::interface_block() {
  Interface_blockContext *_localctx = _tracker.createInstance<Interface_blockContext>(_ctx, getState());
  enterRule(_localctx, 38, IDLParser::RuleInterface_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(IDLParser::LBRACE);
    setState(222);
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
      setState(219);
      interface_item();
      setState(224);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(225);
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

void IDLParser::Interface_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterface_item(this);
}

void IDLParser::Interface_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterface_item(this);
}


antlrcpp::Any IDLParser::Interface_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInterface_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Interface_itemContext* IDLParser::interface_item() {
  Interface_itemContext *_localctx = _tracker.createInstance<Interface_itemContext>(_ctx, getState());
  enterRule(_localctx, 40, IDLParser::RuleInterface_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(230);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(227);
      function_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(228);
      const_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(229);
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

void IDLParser::Function_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_decl(this);
}

void IDLParser::Function_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_decl(this);
}


antlrcpp::Any IDLParser::Function_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFunction_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Function_declContext* IDLParser::function_decl() {
  Function_declContext *_localctx = _tracker.createInstance<Function_declContext>(_ctx, getState());
  enterRule(_localctx, 42, IDLParser::RuleFunction_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    type_decl();
    setState(233);
    match(IDLParser::IDENT);
    setState(234);
    match(IDLParser::LPAREN);
    setState(236);
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
      setState(235);
      function_param_list();
    }
    setState(238);
    match(IDLParser::RPAREN);
    setState(240);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::Const) {
      setState(239);
      match(IDLParser::Const);
    }
    setState(242);
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

void IDLParser::Function_param_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_param_list(this);
}

void IDLParser::Function_param_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_param_list(this);
}


antlrcpp::Any IDLParser::Function_param_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFunction_param_list(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Function_param_listContext* IDLParser::function_param_list() {
  Function_param_listContext *_localctx = _tracker.createInstance<Function_param_listContext>(_ctx, getState());
  enterRule(_localctx, 44, IDLParser::RuleFunction_param_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    function_param();
    setState(249);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COMMA) {
      setState(245);
      match(IDLParser::COMMA);
      setState(246);
      function_param();
      setState(251);
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

void IDLParser::Function_paramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_param(this);
}

void IDLParser::Function_paramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_param(this);
}


antlrcpp::Any IDLParser::Function_paramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFunction_param(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Function_paramContext* IDLParser::function_param() {
  Function_paramContext *_localctx = _tracker.createInstance<Function_paramContext>(_ctx, getState());
  enterRule(_localctx, 46, IDLParser::RuleFunction_param);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::LBRACKET) {
      setState(252);
      param_dir_qualifier();
    }
    setState(255);
    type_decl();
    setState(256);
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

void IDLParser::Param_dir_qualifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_dir_qualifier(this);
}

void IDLParser::Param_dir_qualifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_dir_qualifier(this);
}


antlrcpp::Any IDLParser::Param_dir_qualifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitParam_dir_qualifier(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Param_dir_qualifierContext* IDLParser::param_dir_qualifier() {
  Param_dir_qualifierContext *_localctx = _tracker.createInstance<Param_dir_qualifierContext>(_ctx, getState());
  enterRule(_localctx, 48, IDLParser::RuleParam_dir_qualifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(269);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(258);
      match(IDLParser::LBRACKET);
      setState(259);
      match(IDLParser::IN);
      setState(260);
      match(IDLParser::RBRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(261);
      match(IDLParser::LBRACKET);
      setState(262);
      match(IDLParser::OUT);
      setState(263);
      match(IDLParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(264);
      match(IDLParser::LBRACKET);
      setState(265);
      match(IDLParser::IN);
      setState(266);
      match(IDLParser::COMMA);
      setState(267);
      match(IDLParser::OUT);
      setState(268);
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

void IDLParser::Const_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_def(this);
}

void IDLParser::Const_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_def(this);
}


antlrcpp::Any IDLParser::Const_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_defContext* IDLParser::const_def() {
  Const_defContext *_localctx = _tracker.createInstance<Const_defContext>(_ctx, getState());
  enterRule(_localctx, 50, IDLParser::RuleConst_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(275);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(271);
      const_integral_def();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(272);
      const_float_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(273);
      const_string_def();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(274);
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

void IDLParser::Const_integral_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_integral_def(this);
}

void IDLParser::Const_integral_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_integral_def(this);
}


antlrcpp::Any IDLParser::Const_integral_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_integral_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_integral_defContext* IDLParser::const_integral_def() {
  Const_integral_defContext *_localctx = _tracker.createInstance<Const_integral_defContext>(_ctx, getState());
  enterRule(_localctx, 52, IDLParser::RuleConst_integral_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(277);
    match(IDLParser::Const);
    setState(278);
    integral_type();
    setState(279);
    match(IDLParser::IDENT);
    setState(280);
    match(IDLParser::EQUALS);
    setState(281);
    integer_lit();
    setState(282);
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

void IDLParser::Const_float_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_float_def(this);
}

void IDLParser::Const_float_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_float_def(this);
}


antlrcpp::Any IDLParser::Const_float_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_float_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_float_defContext* IDLParser::const_float_def() {
  Const_float_defContext *_localctx = _tracker.createInstance<Const_float_defContext>(_ctx, getState());
  enterRule(_localctx, 54, IDLParser::RuleConst_float_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(284);
    match(IDLParser::Const);
    setState(285);
    float_type();
    setState(286);
    match(IDLParser::IDENT);
    setState(287);
    match(IDLParser::EQUALS);
    setState(288);
    float_lit();
    setState(289);
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

void IDLParser::Const_string_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_string_def(this);
}

void IDLParser::Const_string_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_string_def(this);
}


antlrcpp::Any IDLParser::Const_string_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_string_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_string_defContext* IDLParser::const_string_def() {
  Const_string_defContext *_localctx = _tracker.createInstance<Const_string_defContext>(_ctx, getState());
  enterRule(_localctx, 56, IDLParser::RuleConst_string_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    match(IDLParser::Const);
    setState(292);
    match(IDLParser::STRING);
    setState(293);
    match(IDLParser::IDENT);
    setState(294);
    match(IDLParser::EQUALS);
    setState(295);
    string_lit();
    setState(296);
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

void IDLParser::Const_class_id_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_class_id_def(this);
}

void IDLParser::Const_class_id_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_class_id_def(this);
}


antlrcpp::Any IDLParser::Const_class_id_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitConst_class_id_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Const_class_id_defContext* IDLParser::const_class_id_def() {
  Const_class_id_defContext *_localctx = _tracker.createInstance<Const_class_id_defContext>(_ctx, getState());
  enterRule(_localctx, 58, IDLParser::RuleConst_class_id_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    match(IDLParser::Const);
    setState(299);
    match(IDLParser::CLASS_ID);
    setState(300);
    match(IDLParser::IDENT);
    setState(301);
    match(IDLParser::LPAREN);
    setState(302);
    string_lit();
    setState(303);
    match(IDLParser::RPAREN);
    setState(304);
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

void IDLParser::Enum_fwdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_fwd(this);
}

void IDLParser::Enum_fwdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_fwd(this);
}


antlrcpp::Any IDLParser::Enum_fwdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_fwd(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_fwdContext* IDLParser::enum_fwd() {
  Enum_fwdContext *_localctx = _tracker.createInstance<Enum_fwdContext>(_ctx, getState());
  enterRule(_localctx, 60, IDLParser::RuleEnum_fwd);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(306);
    match(IDLParser::ENUM);
    setState(307);
    match(IDLParser::IDENT);
    setState(309);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(308);
      enum_type();
    }
    setState(311);
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

void IDLParser::Enum_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_def(this);
}

void IDLParser::Enum_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_def(this);
}


antlrcpp::Any IDLParser::Enum_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_def(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_defContext* IDLParser::enum_def() {
  Enum_defContext *_localctx = _tracker.createInstance<Enum_defContext>(_ctx, getState());
  enterRule(_localctx, 62, IDLParser::RuleEnum_def);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(313);
    match(IDLParser::ENUM);
    setState(314);
    match(IDLParser::IDENT);
    setState(316);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(315);
      enum_type();
    }
    setState(318);
    match(IDLParser::LBRACE);
    setState(319);
    enum_elements();
    setState(320);
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

void IDLParser::Enum_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_type(this);
}

void IDLParser::Enum_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_type(this);
}


antlrcpp::Any IDLParser::Enum_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_typeContext* IDLParser::enum_type() {
  Enum_typeContext *_localctx = _tracker.createInstance<Enum_typeContext>(_ctx, getState());
  enterRule(_localctx, 64, IDLParser::RuleEnum_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(322);
    match(IDLParser::COLON);
    setState(323);
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

void IDLParser::Enum_elementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_elements(this);
}

void IDLParser::Enum_elementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_elements(this);
}


antlrcpp::Any IDLParser::Enum_elementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_elements(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_elementsContext* IDLParser::enum_elements() {
  Enum_elementsContext *_localctx = _tracker.createInstance<Enum_elementsContext>(_ctx, getState());
  enterRule(_localctx, 66, IDLParser::RuleEnum_elements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    enum_item();
    setState(330);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COMMA) {
      setState(326);
      match(IDLParser::COMMA);
      setState(327);
      enum_item();
      setState(332);
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

void IDLParser::Enum_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_item(this);
}

void IDLParser::Enum_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_item(this);
}


antlrcpp::Any IDLParser::Enum_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_itemContext* IDLParser::enum_item() {
  Enum_itemContext *_localctx = _tracker.createInstance<Enum_itemContext>(_ctx, getState());
  enterRule(_localctx, 68, IDLParser::RuleEnum_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(337);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(333);
      match(IDLParser::IDENT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(334);
      match(IDLParser::IDENT);
      setState(335);
      match(IDLParser::EQUALS);
      setState(336);
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

void IDLParser::Enum_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_expr(this);
}

void IDLParser::Enum_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_expr(this);
}


antlrcpp::Any IDLParser::Enum_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitEnum_expr(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Enum_exprContext* IDLParser::enum_expr() {
  Enum_exprContext *_localctx = _tracker.createInstance<Enum_exprContext>(_ctx, getState());
  enterRule(_localctx, 70, IDLParser::RuleEnum_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
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

void IDLParser::Expr_add_subContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr_add_sub(this);
}

void IDLParser::Expr_add_subContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr_add_sub(this);
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
  size_t startState = 72;
  enterRecursionRule(_localctx, 72, IDLParser::RuleExpr_add_sub, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(342);
    expr_mul_div(0);
    _ctx->stop = _input->LT(-1);
    setState(352);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(350);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Expr_add_subContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_add_sub);
          setState(344);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(345);
          match(IDLParser::PLUS);
          setState(346);
          expr_mul_div(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Expr_add_subContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_add_sub);
          setState(347);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(348);
          match(IDLParser::MINUS);
          setState(349);
          expr_mul_div(0);
          break;
        }

        } 
      }
      setState(354);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
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

void IDLParser::Expr_mul_divContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr_mul_div(this);
}

void IDLParser::Expr_mul_divContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr_mul_div(this);
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
  size_t startState = 74;
  enterRecursionRule(_localctx, 74, IDLParser::RuleExpr_mul_div, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(356);
    expr_shift(0);
    _ctx->stop = _input->LT(-1);
    setState(366);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(364);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Expr_mul_divContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_mul_div);
          setState(358);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(359);
          match(IDLParser::STAR);
          setState(360);
          expr_shift(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Expr_mul_divContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_mul_div);
          setState(361);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(362);
          match(IDLParser::SLASH);
          setState(363);
          expr_shift(0);
          break;
        }

        } 
      }
      setState(368);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
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

IDLParser::Expr_valueContext* IDLParser::Expr_shiftContext::expr_value() {
  return getRuleContext<IDLParser::Expr_valueContext>(0);
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

void IDLParser::Expr_shiftContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr_shift(this);
}

void IDLParser::Expr_shiftContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr_shift(this);
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
  size_t startState = 76;
  enterRecursionRule(_localctx, 76, IDLParser::RuleExpr_shift, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(370);
    expr_value();
    _ctx->stop = _input->LT(-1);
    setState(380);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(378);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Expr_shiftContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_shift);
          setState(372);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(373);
          match(IDLParser::LSHIFT);
          setState(374);
          expr_value();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Expr_shiftContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr_shift);
          setState(375);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(376);
          match(IDLParser::RSHIFT);
          setState(377);
          expr_value();
          break;
        }

        } 
      }
      setState(382);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
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

void IDLParser::Expr_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr_value(this);
}

void IDLParser::Expr_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr_value(this);
}


antlrcpp::Any IDLParser::Expr_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitExpr_value(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Expr_valueContext* IDLParser::expr_value() {
  Expr_valueContext *_localctx = _tracker.createInstance<Expr_valueContext>(_ctx, getState());
  enterRule(_localctx, 78, IDLParser::RuleExpr_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(388);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::OCT_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(383);
        integer_lit();
        break;
      }

      case IDLParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(384);
        match(IDLParser::LPAREN);
        setState(385);
        enum_expr();
        setState(386);
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

void IDLParser::Any_literalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAny_literal(this);
}

void IDLParser::Any_literalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAny_literal(this);
}


antlrcpp::Any IDLParser::Any_literalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitAny_literal(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Any_literalContext* IDLParser::any_literal() {
  Any_literalContext *_localctx = _tracker.createInstance<Any_literalContext>(_ctx, getState());
  enterRule(_localctx, 80, IDLParser::RuleAny_literal);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(392);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::OCT_LIT:
      case IDLParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(390);
        numeric_lit();
        break;
      }

      case IDLParser::STRING_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(391);
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

void IDLParser::Numeric_litContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric_lit(this);
}

void IDLParser::Numeric_litContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric_lit(this);
}


antlrcpp::Any IDLParser::Numeric_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitNumeric_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Numeric_litContext* IDLParser::numeric_lit() {
  Numeric_litContext *_localctx = _tracker.createInstance<Numeric_litContext>(_ctx, getState());
  enterRule(_localctx, 82, IDLParser::RuleNumeric_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(396);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::OCT_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(394);
        integer_lit();
        break;
      }

      case IDLParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(395);
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

void IDLParser::Integer_litContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInteger_lit(this);
}

void IDLParser::Integer_litContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInteger_lit(this);
}


antlrcpp::Any IDLParser::Integer_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitInteger_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Integer_litContext* IDLParser::integer_lit() {
  Integer_litContext *_localctx = _tracker.createInstance<Integer_litContext>(_ctx, getState());
  enterRule(_localctx, 84, IDLParser::RuleInteger_lit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(398);
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

void IDLParser::Float_litContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat_lit(this);
}

void IDLParser::Float_litContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat_lit(this);
}


antlrcpp::Any IDLParser::Float_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFloat_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Float_litContext* IDLParser::float_lit() {
  Float_litContext *_localctx = _tracker.createInstance<Float_litContext>(_ctx, getState());
  enterRule(_localctx, 86, IDLParser::RuleFloat_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(400);
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

void IDLParser::String_litContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString_lit(this);
}

void IDLParser::String_litContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString_lit(this);
}


antlrcpp::Any IDLParser::String_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitString_lit(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::String_litContext* IDLParser::string_lit() {
  String_litContext *_localctx = _tracker.createInstance<String_litContext>(_ctx, getState());
  enterRule(_localctx, 88, IDLParser::RuleString_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(402);
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

void IDLParser::Qualified_identContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualified_ident(this);
}

void IDLParser::Qualified_identContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualified_ident(this);
}


antlrcpp::Any IDLParser::Qualified_identContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitQualified_ident(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Qualified_identContext* IDLParser::qualified_ident() {
  Qualified_identContext *_localctx = _tracker.createInstance<Qualified_identContext>(_ctx, getState());
  enterRule(_localctx, 90, IDLParser::RuleQualified_ident);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(405);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(404);
      qualified_separator();
    }
    setState(407);
    match(IDLParser::IDENT);
    setState(411);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COLON) {
      setState(408);
      qualified_part();
      setState(413);
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

void IDLParser::Qualified_partContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualified_part(this);
}

void IDLParser::Qualified_partContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualified_part(this);
}


antlrcpp::Any IDLParser::Qualified_partContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitQualified_part(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Qualified_partContext* IDLParser::qualified_part() {
  Qualified_partContext *_localctx = _tracker.createInstance<Qualified_partContext>(_ctx, getState());
  enterRule(_localctx, 92, IDLParser::RuleQualified_part);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
    qualified_separator();
    setState(415);
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

void IDLParser::Qualified_separatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualified_separator(this);
}

void IDLParser::Qualified_separatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualified_separator(this);
}


antlrcpp::Any IDLParser::Qualified_separatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitQualified_separator(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Qualified_separatorContext* IDLParser::qualified_separator() {
  Qualified_separatorContext *_localctx = _tracker.createInstance<Qualified_separatorContext>(_ctx, getState());
  enterRule(_localctx, 94, IDLParser::RuleQualified_separator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(417);
    match(IDLParser::COLON);
    setState(418);
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

void IDLParser::All_or_identContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAll_or_ident(this);
}

void IDLParser::All_or_identContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAll_or_ident(this);
}


antlrcpp::Any IDLParser::All_or_identContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitAll_or_ident(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::All_or_identContext* IDLParser::all_or_ident() {
  All_or_identContext *_localctx = _tracker.createInstance<All_or_identContext>(_ctx, getState());
  enterRule(_localctx, 96, IDLParser::RuleAll_or_ident);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(420);
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


size_t IDLParser::Member_declContext::getRuleIndex() const {
  return IDLParser::RuleMember_decl;
}

void IDLParser::Member_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMember_decl(this);
}

void IDLParser::Member_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMember_decl(this);
}


antlrcpp::Any IDLParser::Member_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitMember_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Member_declContext* IDLParser::member_decl() {
  Member_declContext *_localctx = _tracker.createInstance<Member_declContext>(_ctx, getState());
  enterRule(_localctx, 98, IDLParser::RuleMember_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(422);
    type_decl();
    setState(423);
    match(IDLParser::IDENT);
    setState(424);
    match(IDLParser::SEMICOLON);
   
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

void IDLParser::Type_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_decl(this);
}

void IDLParser::Type_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_decl(this);
}


antlrcpp::Any IDLParser::Type_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitType_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Type_declContext* IDLParser::type_decl() {
  Type_declContext *_localctx = _tracker.createInstance<Type_declContext>(_ctx, getState());
  enterRule(_localctx, 100, IDLParser::RuleType_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::Const) {
      setState(426);
      type_modifier();
    }
    setState(429);
    any_type();
    setState(431);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::STAR

    || _la == IDLParser::Const) {
      setState(430);
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

void IDLParser::Type_modifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_modifier(this);
}

void IDLParser::Type_modifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_modifier(this);
}


antlrcpp::Any IDLParser::Type_modifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitType_modifier(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Type_modifierContext* IDLParser::type_modifier() {
  Type_modifierContext *_localctx = _tracker.createInstance<Type_modifierContext>(_ctx, getState());
  enterRule(_localctx, 102, IDLParser::RuleType_modifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(433);
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

void IDLParser::Pointer_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointer_type(this);
}

void IDLParser::Pointer_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointer_type(this);
}


antlrcpp::Any IDLParser::Pointer_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitPointer_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Pointer_typeContext* IDLParser::pointer_type() {
  Pointer_typeContext *_localctx = _tracker.createInstance<Pointer_typeContext>(_ctx, getState());
  enterRule(_localctx, 104, IDLParser::RulePointer_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(435);
      pointer_decl();
      setState(438); 
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

void IDLParser::Pointer_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointer_decl(this);
}

void IDLParser::Pointer_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointer_decl(this);
}


antlrcpp::Any IDLParser::Pointer_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitPointer_decl(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Pointer_declContext* IDLParser::pointer_decl() {
  Pointer_declContext *_localctx = _tracker.createInstance<Pointer_declContext>(_ctx, getState());
  enterRule(_localctx, 106, IDLParser::RulePointer_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(441);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::Const) {
      setState(440);
      match(IDLParser::Const);
    }
    setState(443);
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

void IDLParser::Any_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAny_type(this);
}

void IDLParser::Any_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAny_type(this);
}


antlrcpp::Any IDLParser::Any_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitAny_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Any_typeContext* IDLParser::any_type() {
  Any_typeContext *_localctx = _tracker.createInstance<Any_typeContext>(_ctx, getState());
  enterRule(_localctx, 108, IDLParser::RuleAny_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(449);
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
        setState(445);
        integral_type();
        break;
      }

      case IDLParser::F32:
      case IDLParser::F64: {
        enterOuterAlt(_localctx, 2);
        setState(446);
        float_type();
        break;
      }

      case IDLParser::Void:
      case IDLParser::RESULT: {
        enterOuterAlt(_localctx, 3);
        setState(447);
        utility_type();
        break;
      }

      case IDLParser::COLON:
      case IDLParser::IDENT: {
        enterOuterAlt(_localctx, 4);
        setState(448);
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

void IDLParser::Utility_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUtility_type(this);
}

void IDLParser::Utility_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUtility_type(this);
}


antlrcpp::Any IDLParser::Utility_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitUtility_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Utility_typeContext* IDLParser::utility_type() {
  Utility_typeContext *_localctx = _tracker.createInstance<Utility_typeContext>(_ctx, getState());
  enterRule(_localctx, 110, IDLParser::RuleUtility_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(451);
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

void IDLParser::Integral_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegral_type(this);
}

void IDLParser::Integral_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegral_type(this);
}


antlrcpp::Any IDLParser::Integral_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitIntegral_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Integral_typeContext* IDLParser::integral_type() {
  Integral_typeContext *_localctx = _tracker.createInstance<Integral_typeContext>(_ctx, getState());
  enterRule(_localctx, 112, IDLParser::RuleIntegral_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(453);
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

void IDLParser::Float_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat_type(this);
}

void IDLParser::Float_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat_type(this);
}


antlrcpp::Any IDLParser::Float_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitFloat_type(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Float_typeContext* IDLParser::float_type() {
  Float_typeContext *_localctx = _tracker.createInstance<Float_typeContext>(_ctx, getState());
  enterRule(_localctx, 114, IDLParser::RuleFloat_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(455);
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
    case 36: return expr_add_subSempred(dynamic_cast<Expr_add_subContext *>(context), predicateIndex);
    case 37: return expr_mul_divSempred(dynamic_cast<Expr_mul_divContext *>(context), predicateIndex);
    case 38: return expr_shiftSempred(dynamic_cast<Expr_shiftContext *>(context), predicateIndex);

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

// Static vars and initialization.
std::vector<dfa::DFA> IDLParser::_decisionToDFA;
atn::PredictionContextCache IDLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN IDLParser::_atn;
std::vector<uint16_t> IDLParser::_serializedATN;

std::vector<std::string> IDLParser::_ruleNames = {
  "main", "global_statements", "global_statement", "empty_stmt", "module_stmt", 
  "error_code_stmt", "success_stmt", "failure_stmt", "import_from_stmt", 
  "import_stmt", "struct_stmt", "struct_decl", "struct_fwd", "struct_block", 
  "struct_item", "interface_stmt", "interface_fwd", "interface_decl", "interface_super", 
  "interface_block", "interface_item", "function_decl", "function_param_list", 
  "function_param", "param_dir_qualifier", "const_def", "const_integral_def", 
  "const_float_def", "const_string_def", "const_class_id_def", "enum_fwd", 
  "enum_def", "enum_type", "enum_elements", "enum_item", "enum_expr", "expr_add_sub", 
  "expr_mul_div", "expr_shift", "expr_value", "any_literal", "numeric_lit", 
  "integer_lit", "float_lit", "string_lit", "qualified_ident", "qualified_part", 
  "qualified_separator", "all_or_ident", "member_decl", "type_decl", "type_modifier", 
  "pointer_type", "pointer_decl", "any_type", "utility_type", "integral_type", 
  "float_type"
};

std::vector<std::string> IDLParser::_literalNames = {
  "", "'import'", "'struct'", "'interface'", "'enum'", "'module'", "'from'", 
  "'in'", "'out'", "':'", "';'", "'*'", "'/'", "'.'", "','", "'='", "'\"'", 
  "'{'", "'}'", "'('", "')'", "'['", "']'", "'<'", "'>'", "'+'", "'-'", 
  "'<<'", "'>>'", "'const'", "'void'", "'result'", "'success'", "'failure'", 
  "'class_id'", "'string'", "'u8'", "'s8'", "'u16'", "'s16'", "'u32'", "'s32'", 
  "'u64'", "'s64'", "'f32'", "'f64'"
};

std::vector<std::string> IDLParser::_symbolicNames = {
  "", "IMPORT", "STRUCT", "INTERFACE", "ENUM", "MODULE", "FROM", "IN", "OUT", 
  "COLON", "SEMICOLON", "STAR", "SLASH", "DOT", "COMMA", "EQUALS", "QUOTE", 
  "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LT", 
  "GT", "PLUS", "MINUS", "LSHIFT", "RSHIFT", "Const", "Void", "RESULT", 
  "SUCCESS", "FAILURE", "CLASS_ID", "STRING", "U8", "S8", "U16", "S16", 
  "U32", "S32", "U64", "S64", "F32", "F64", "IDENT", "DECIMAL_LIT", "HEX_LIT", 
  "BIN_LIT", "OCT_LIT", "STRING_LIT", "FLOAT_LIT", "WHITE_SPACE", "BLOCK_COMMENT", 
  "LINE_COMMENT"
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
    0x3, 0x39, 0x1cc, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x3, 0x2, 
    0x5, 0x2, 0x78, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x6, 0x3, 0x7d, 
    0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x7e, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0x8b, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x95, 0xa, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xb3, 
    0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0xbf, 0xa, 0xf, 0xc, 
    0xf, 0xe, 0xf, 0xc2, 0xb, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x5, 0x10, 0xc9, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 
    0xcd, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xd6, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x7, 0x15, 0xdf, 
    0xa, 0x15, 0xc, 0x15, 0xe, 0x15, 0xe2, 0xb, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0xe9, 0xa, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0xef, 0xa, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x5, 0x17, 0xf3, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x7, 0x18, 0xfa, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 
    0xfd, 0xb, 0x18, 0x3, 0x19, 0x5, 0x19, 0x100, 0xa, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x5, 0x1a, 0x110, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x5, 0x1b, 0x116, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x138, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x13f, 0xa, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x7, 0x23, 0x14b, 0xa, 0x23, 0xc, 0x23, 
    0xe, 0x23, 0x14e, 0xb, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 
    0x5, 0x24, 0x154, 0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 
    0x26, 0x7, 0x26, 0x161, 0xa, 0x26, 0xc, 0x26, 0xe, 0x26, 0x164, 0xb, 
    0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x7, 0x27, 0x16f, 0xa, 0x27, 0xc, 0x27, 
    0xe, 0x27, 0x172, 0xb, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x7, 0x28, 0x17d, 
    0xa, 0x28, 0xc, 0x28, 0xe, 0x28, 0x180, 0xb, 0x28, 0x3, 0x29, 0x3, 0x29, 
    0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x187, 0xa, 0x29, 0x3, 0x2a, 
    0x3, 0x2a, 0x5, 0x2a, 0x18b, 0xa, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 
    0x18f, 0xa, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2f, 0x5, 0x2f, 0x198, 0xa, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 
    0x7, 0x2f, 0x19c, 0xa, 0x2f, 0xc, 0x2f, 0xe, 0x2f, 0x19f, 0xb, 0x2f, 
    0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 
    0x32, 0x3, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 
    0x5, 0x34, 0x1ae, 0xa, 0x34, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 0x1b2, 
    0xa, 0x34, 0x3, 0x35, 0x3, 0x35, 0x3, 0x36, 0x6, 0x36, 0x1b7, 0xa, 0x36, 
    0xd, 0x36, 0xe, 0x36, 0x1b8, 0x3, 0x37, 0x5, 0x37, 0x1bc, 0xa, 0x37, 
    0x3, 0x37, 0x3, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x5, 
    0x38, 0x1c4, 0xa, 0x38, 0x3, 0x39, 0x3, 0x39, 0x3, 0x3a, 0x3, 0x3a, 
    0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x2, 0x5, 0x4a, 0x4c, 0x4e, 0x3c, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
    0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 
    0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 
    0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 
    0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x2, 0x7, 0x3, 0x2, 
    0x31, 0x34, 0x4, 0x2, 0xd, 0xd, 0x30, 0x30, 0x3, 0x2, 0x20, 0x21, 0x3, 
    0x2, 0x26, 0x2d, 0x3, 0x2, 0x2e, 0x2f, 0x2, 0x1c5, 0x2, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x6, 0x8a, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x8c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x8e, 0x3, 0x2, 0x2, 0x2, 0xc, 0x94, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x96, 0x3, 0x2, 0x2, 0x2, 0x10, 0x9e, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0xa6, 0x3, 0x2, 0x2, 0x2, 0x14, 0xac, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0xb2, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb4, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xbc, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0xc8, 0x3, 0x2, 0x2, 0x2, 0x20, 0xcc, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0xce, 0x3, 0x2, 0x2, 0x2, 0x24, 0xd2, 0x3, 0x2, 0x2, 0x2, 0x26, 0xd9, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0xdc, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xe8, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0xea, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xf6, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0xff, 0x3, 0x2, 0x2, 0x2, 0x32, 0x10f, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x115, 0x3, 0x2, 0x2, 0x2, 0x36, 0x117, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x125, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x12c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x134, 0x3, 0x2, 0x2, 0x2, 0x40, 0x13b, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x144, 0x3, 0x2, 0x2, 0x2, 0x44, 0x147, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x153, 0x3, 0x2, 0x2, 0x2, 0x48, 0x155, 0x3, 0x2, 
    0x2, 0x2, 0x4a, 0x157, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x165, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x173, 0x3, 0x2, 0x2, 0x2, 0x50, 0x186, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x54, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x190, 0x3, 0x2, 0x2, 0x2, 0x58, 0x192, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x194, 
    0x3, 0x2, 0x2, 0x2, 0x5c, 0x197, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x1a0, 0x3, 
    0x2, 0x2, 0x2, 0x60, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x62, 0x1a6, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x66, 0x1ad, 0x3, 0x2, 0x2, 
    0x2, 0x68, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x1b6, 0x3, 0x2, 0x2, 0x2, 
    0x6c, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x70, 
    0x1c5, 0x3, 0x2, 0x2, 0x2, 0x72, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x74, 0x1c9, 
    0x3, 0x2, 0x2, 0x2, 0x76, 0x78, 0x5, 0x4, 0x3, 0x2, 0x77, 0x76, 0x3, 
    0x2, 0x2, 0x2, 0x77, 0x78, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x3, 0x2, 
    0x2, 0x2, 0x79, 0x7a, 0x7, 0x2, 0x2, 0x3, 0x7a, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x7b, 0x7d, 0x5, 0x6, 0x4, 0x2, 0x7c, 0x7b, 0x3, 0x2, 0x2, 0x2, 
    0x7d, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7e, 
    0x7f, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x80, 0x8b, 
    0x5, 0x14, 0xb, 0x2, 0x81, 0x8b, 0x5, 0x16, 0xc, 0x2, 0x82, 0x8b, 0x5, 
    0x20, 0x11, 0x2, 0x83, 0x8b, 0x5, 0x34, 0x1b, 0x2, 0x84, 0x8b, 0x5, 
    0x40, 0x21, 0x2, 0x85, 0x8b, 0x5, 0x3e, 0x20, 0x2, 0x86, 0x8b, 0x5, 
    0xa, 0x6, 0x2, 0x87, 0x8b, 0x5, 0xc, 0x7, 0x2, 0x88, 0x8b, 0x5, 0x8, 
    0x5, 0x2, 0x89, 0x8b, 0x5, 0x12, 0xa, 0x2, 0x8a, 0x80, 0x3, 0x2, 0x2, 
    0x2, 0x8a, 0x81, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x82, 0x3, 0x2, 0x2, 0x2, 
    0x8a, 0x83, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x84, 0x3, 0x2, 0x2, 0x2, 0x8a, 
    0x85, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x86, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x87, 
    0x3, 0x2, 0x2, 0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x89, 0x3, 
    0x2, 0x2, 0x2, 0x8b, 0x7, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0xc, 
    0x2, 0x2, 0x8d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x7, 0x7, 0x2, 
    0x2, 0x8f, 0x90, 0x5, 0x5c, 0x2f, 0x2, 0x90, 0x91, 0x7, 0xc, 0x2, 0x2, 
    0x91, 0xb, 0x3, 0x2, 0x2, 0x2, 0x92, 0x95, 0x5, 0xe, 0x8, 0x2, 0x93, 
    0x95, 0x5, 0x10, 0x9, 0x2, 0x94, 0x92, 0x3, 0x2, 0x2, 0x2, 0x94, 0x93, 
    0x3, 0x2, 0x2, 0x2, 0x95, 0xd, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x7, 
    0x22, 0x2, 0x2, 0x97, 0x98, 0x7, 0x30, 0x2, 0x2, 0x98, 0x99, 0x7, 0x15, 
    0x2, 0x2, 0x99, 0x9a, 0x7, 0x35, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x10, 0x2, 
    0x2, 0x9b, 0x9c, 0x7, 0x35, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x16, 0x2, 0x2, 
    0x9d, 0xf, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x23, 0x2, 0x2, 0x9f, 
    0xa0, 0x7, 0x30, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x15, 0x2, 0x2, 0xa1, 0xa2, 
    0x7, 0x35, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x10, 0x2, 0x2, 0xa3, 0xa4, 0x7, 
    0x35, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0x16, 0x2, 0x2, 0xa5, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0xa6, 0xa7, 0x7, 0x3, 0x2, 0x2, 0xa7, 0xa8, 0x5, 0x62, 0x32, 
    0x2, 0xa8, 0xa9, 0x7, 0x8, 0x2, 0x2, 0xa9, 0xaa, 0x5, 0x5c, 0x2f, 0x2, 
    0xaa, 0xab, 0x7, 0xc, 0x2, 0x2, 0xab, 0x13, 0x3, 0x2, 0x2, 0x2, 0xac, 
    0xad, 0x7, 0x3, 0x2, 0x2, 0xad, 0xae, 0x5, 0x5a, 0x2e, 0x2, 0xae, 0xaf, 
    0x7, 0xc, 0x2, 0x2, 0xaf, 0x15, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb3, 0x5, 
    0x18, 0xd, 0x2, 0xb1, 0xb3, 0x5, 0x1a, 0xe, 0x2, 0xb2, 0xb0, 0x3, 0x2, 
    0x2, 0x2, 0xb2, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb3, 0x17, 0x3, 0x2, 0x2, 
    0x2, 0xb4, 0xb5, 0x7, 0x4, 0x2, 0x2, 0xb5, 0xb6, 0x7, 0x30, 0x2, 0x2, 
    0xb6, 0xb7, 0x5, 0x1c, 0xf, 0x2, 0xb7, 0x19, 0x3, 0x2, 0x2, 0x2, 0xb8, 
    0xb9, 0x7, 0x4, 0x2, 0x2, 0xb9, 0xba, 0x5, 0x5c, 0x2f, 0x2, 0xba, 0xbb, 
    0x7, 0xc, 0x2, 0x2, 0xbb, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xc0, 0x7, 
    0x13, 0x2, 0x2, 0xbd, 0xbf, 0x5, 0x1e, 0x10, 0x2, 0xbe, 0xbd, 0x3, 0x2, 
    0x2, 0x2, 0xbf, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xbe, 0x3, 0x2, 0x2, 
    0x2, 0xc0, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc3, 0x3, 0x2, 0x2, 0x2, 
    0xc2, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x14, 0x2, 0x2, 0xc4, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc9, 0x5, 0x64, 0x33, 0x2, 0xc6, 0xc9, 
    0x5, 0x34, 0x1b, 0x2, 0xc7, 0xc9, 0x5, 0x40, 0x21, 0x2, 0xc8, 0xc5, 
    0x3, 0x2, 0x2, 0x2, 0xc8, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xc7, 0x3, 
    0x2, 0x2, 0x2, 0xc9, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcd, 0x5, 0x24, 
    0x13, 0x2, 0xcb, 0xcd, 0x5, 0x22, 0x12, 0x2, 0xcc, 0xca, 0x3, 0x2, 0x2, 
    0x2, 0xcc, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0xce, 0xcf, 0x7, 0x5, 0x2, 0x2, 0xcf, 0xd0, 0x5, 0x5c, 0x2f, 0x2, 0xd0, 
    0xd1, 0x7, 0xc, 0x2, 0x2, 0xd1, 0x23, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 
    0x7, 0x5, 0x2, 0x2, 0xd3, 0xd5, 0x7, 0x30, 0x2, 0x2, 0xd4, 0xd6, 0x5, 
    0x26, 0x14, 0x2, 0xd5, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd6, 0x3, 0x2, 
    0x2, 0x2, 0xd6, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd8, 0x5, 0x28, 0x15, 
    0x2, 0xd8, 0x25, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x7, 0xb, 0x2, 0x2, 
    0xda, 0xdb, 0x5, 0x5c, 0x2f, 0x2, 0xdb, 0x27, 0x3, 0x2, 0x2, 0x2, 0xdc, 
    0xe0, 0x7, 0x13, 0x2, 0x2, 0xdd, 0xdf, 0x5, 0x2a, 0x16, 0x2, 0xde, 0xdd, 
    0x3, 0x2, 0x2, 0x2, 0xdf, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xde, 0x3, 
    0x2, 0x2, 0x2, 0xe0, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe3, 0x3, 0x2, 
    0x2, 0x2, 0xe2, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x7, 0x14, 0x2, 
    0x2, 0xe4, 0x29, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe9, 0x5, 0x2c, 0x17, 0x2, 
    0xe6, 0xe9, 0x5, 0x34, 0x1b, 0x2, 0xe7, 0xe9, 0x5, 0x40, 0x21, 0x2, 
    0xe8, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe8, 
    0xe7, 0x3, 0x2, 0x2, 0x2, 0xe9, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xea, 0xeb, 
    0x5, 0x66, 0x34, 0x2, 0xeb, 0xec, 0x7, 0x30, 0x2, 0x2, 0xec, 0xee, 0x7, 
    0x15, 0x2, 0x2, 0xed, 0xef, 0x5, 0x2e, 0x18, 0x2, 0xee, 0xed, 0x3, 0x2, 
    0x2, 0x2, 0xee, 0xef, 0x3, 0x2, 0x2, 0x2, 0xef, 0xf0, 0x3, 0x2, 0x2, 
    0x2, 0xf0, 0xf2, 0x7, 0x16, 0x2, 0x2, 0xf1, 0xf3, 0x7, 0x1f, 0x2, 0x2, 
    0xf2, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf3, 
    0xf4, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf5, 0x7, 0xc, 0x2, 0x2, 0xf5, 0x2d, 
    0x3, 0x2, 0x2, 0x2, 0xf6, 0xfb, 0x5, 0x30, 0x19, 0x2, 0xf7, 0xf8, 0x7, 
    0x10, 0x2, 0x2, 0xf8, 0xfa, 0x5, 0x30, 0x19, 0x2, 0xf9, 0xf7, 0x3, 0x2, 
    0x2, 0x2, 0xfa, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xf9, 0x3, 0x2, 0x2, 
    0x2, 0xfb, 0xfc, 0x3, 0x2, 0x2, 0x2, 0xfc, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0xfd, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x100, 0x5, 0x32, 0x1a, 0x2, 0xff, 
    0xfe, 0x3, 0x2, 0x2, 0x2, 0xff, 0x100, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 
    0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x5, 0x66, 0x34, 0x2, 0x102, 0x103, 
    0x7, 0x30, 0x2, 0x2, 0x103, 0x31, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 
    0x7, 0x17, 0x2, 0x2, 0x105, 0x106, 0x7, 0x9, 0x2, 0x2, 0x106, 0x110, 
    0x7, 0x18, 0x2, 0x2, 0x107, 0x108, 0x7, 0x17, 0x2, 0x2, 0x108, 0x109, 
    0x7, 0xa, 0x2, 0x2, 0x109, 0x110, 0x7, 0x18, 0x2, 0x2, 0x10a, 0x10b, 
    0x7, 0x17, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x9, 0x2, 0x2, 0x10c, 0x10d, 
    0x7, 0x10, 0x2, 0x2, 0x10d, 0x10e, 0x7, 0xa, 0x2, 0x2, 0x10e, 0x110, 
    0x7, 0x18, 0x2, 0x2, 0x10f, 0x104, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x107, 
    0x3, 0x2, 0x2, 0x2, 0x10f, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x110, 0x33, 0x3, 
    0x2, 0x2, 0x2, 0x111, 0x116, 0x5, 0x36, 0x1c, 0x2, 0x112, 0x116, 0x5, 
    0x38, 0x1d, 0x2, 0x113, 0x116, 0x5, 0x3a, 0x1e, 0x2, 0x114, 0x116, 0x5, 
    0x3c, 0x1f, 0x2, 0x115, 0x111, 0x3, 0x2, 0x2, 0x2, 0x115, 0x112, 0x3, 
    0x2, 0x2, 0x2, 0x115, 0x113, 0x3, 0x2, 0x2, 0x2, 0x115, 0x114, 0x3, 
    0x2, 0x2, 0x2, 0x116, 0x35, 0x3, 0x2, 0x2, 0x2, 0x117, 0x118, 0x7, 0x1f, 
    0x2, 0x2, 0x118, 0x119, 0x5, 0x72, 0x3a, 0x2, 0x119, 0x11a, 0x7, 0x30, 
    0x2, 0x2, 0x11a, 0x11b, 0x7, 0x11, 0x2, 0x2, 0x11b, 0x11c, 0x5, 0x56, 
    0x2c, 0x2, 0x11c, 0x11d, 0x7, 0xc, 0x2, 0x2, 0x11d, 0x37, 0x3, 0x2, 
    0x2, 0x2, 0x11e, 0x11f, 0x7, 0x1f, 0x2, 0x2, 0x11f, 0x120, 0x5, 0x74, 
    0x3b, 0x2, 0x120, 0x121, 0x7, 0x30, 0x2, 0x2, 0x121, 0x122, 0x7, 0x11, 
    0x2, 0x2, 0x122, 0x123, 0x5, 0x58, 0x2d, 0x2, 0x123, 0x124, 0x7, 0xc, 
    0x2, 0x2, 0x124, 0x39, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x7, 0x1f, 
    0x2, 0x2, 0x126, 0x127, 0x7, 0x25, 0x2, 0x2, 0x127, 0x128, 0x7, 0x30, 
    0x2, 0x2, 0x128, 0x129, 0x7, 0x11, 0x2, 0x2, 0x129, 0x12a, 0x5, 0x5a, 
    0x2e, 0x2, 0x12a, 0x12b, 0x7, 0xc, 0x2, 0x2, 0x12b, 0x3b, 0x3, 0x2, 
    0x2, 0x2, 0x12c, 0x12d, 0x7, 0x1f, 0x2, 0x2, 0x12d, 0x12e, 0x7, 0x24, 
    0x2, 0x2, 0x12e, 0x12f, 0x7, 0x30, 0x2, 0x2, 0x12f, 0x130, 0x7, 0x15, 
    0x2, 0x2, 0x130, 0x131, 0x5, 0x5a, 0x2e, 0x2, 0x131, 0x132, 0x7, 0x16, 
    0x2, 0x2, 0x132, 0x133, 0x7, 0xc, 0x2, 0x2, 0x133, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0x134, 0x135, 0x7, 0x6, 0x2, 0x2, 0x135, 0x137, 0x7, 0x30, 0x2, 
    0x2, 0x136, 0x138, 0x5, 0x42, 0x22, 0x2, 0x137, 0x136, 0x3, 0x2, 0x2, 
    0x2, 0x137, 0x138, 0x3, 0x2, 0x2, 0x2, 0x138, 0x139, 0x3, 0x2, 0x2, 
    0x2, 0x139, 0x13a, 0x7, 0xc, 0x2, 0x2, 0x13a, 0x3f, 0x3, 0x2, 0x2, 0x2, 
    0x13b, 0x13c, 0x7, 0x6, 0x2, 0x2, 0x13c, 0x13e, 0x7, 0x30, 0x2, 0x2, 
    0x13d, 0x13f, 0x5, 0x42, 0x22, 0x2, 0x13e, 0x13d, 0x3, 0x2, 0x2, 0x2, 
    0x13e, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x3, 0x2, 0x2, 0x2, 
    0x140, 0x141, 0x7, 0x13, 0x2, 0x2, 0x141, 0x142, 0x5, 0x44, 0x23, 0x2, 
    0x142, 0x143, 0x7, 0x14, 0x2, 0x2, 0x143, 0x41, 0x3, 0x2, 0x2, 0x2, 
    0x144, 0x145, 0x7, 0xb, 0x2, 0x2, 0x145, 0x146, 0x5, 0x72, 0x3a, 0x2, 
    0x146, 0x43, 0x3, 0x2, 0x2, 0x2, 0x147, 0x14c, 0x5, 0x46, 0x24, 0x2, 
    0x148, 0x149, 0x7, 0x10, 0x2, 0x2, 0x149, 0x14b, 0x5, 0x46, 0x24, 0x2, 
    0x14a, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x14e, 0x3, 0x2, 0x2, 0x2, 
    0x14c, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x14d, 0x3, 0x2, 0x2, 0x2, 
    0x14d, 0x45, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14f, 
    0x154, 0x7, 0x30, 0x2, 0x2, 0x150, 0x151, 0x7, 0x30, 0x2, 0x2, 0x151, 
    0x152, 0x7, 0x11, 0x2, 0x2, 0x152, 0x154, 0x5, 0x48, 0x25, 0x2, 0x153, 
    0x14f, 0x3, 0x2, 0x2, 0x2, 0x153, 0x150, 0x3, 0x2, 0x2, 0x2, 0x154, 
    0x47, 0x3, 0x2, 0x2, 0x2, 0x155, 0x156, 0x5, 0x4a, 0x26, 0x2, 0x156, 
    0x49, 0x3, 0x2, 0x2, 0x2, 0x157, 0x158, 0x8, 0x26, 0x1, 0x2, 0x158, 
    0x159, 0x5, 0x4c, 0x27, 0x2, 0x159, 0x162, 0x3, 0x2, 0x2, 0x2, 0x15a, 
    0x15b, 0xc, 0x5, 0x2, 0x2, 0x15b, 0x15c, 0x7, 0x1b, 0x2, 0x2, 0x15c, 
    0x161, 0x5, 0x4c, 0x27, 0x2, 0x15d, 0x15e, 0xc, 0x4, 0x2, 0x2, 0x15e, 
    0x15f, 0x7, 0x1c, 0x2, 0x2, 0x15f, 0x161, 0x5, 0x4c, 0x27, 0x2, 0x160, 
    0x15a, 0x3, 0x2, 0x2, 0x2, 0x160, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x161, 
    0x164, 0x3, 0x2, 0x2, 0x2, 0x162, 0x160, 0x3, 0x2, 0x2, 0x2, 0x162, 
    0x163, 0x3, 0x2, 0x2, 0x2, 0x163, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x164, 0x162, 
    0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 0x8, 0x27, 0x1, 0x2, 0x166, 0x167, 
    0x5, 0x4e, 0x28, 0x2, 0x167, 0x170, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 
    0xc, 0x5, 0x2, 0x2, 0x169, 0x16a, 0x7, 0xd, 0x2, 0x2, 0x16a, 0x16f, 
    0x5, 0x4e, 0x28, 0x2, 0x16b, 0x16c, 0xc, 0x4, 0x2, 0x2, 0x16c, 0x16d, 
    0x7, 0xe, 0x2, 0x2, 0x16d, 0x16f, 0x5, 0x4e, 0x28, 0x2, 0x16e, 0x168, 
    0x3, 0x2, 0x2, 0x2, 0x16e, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x172, 
    0x3, 0x2, 0x2, 0x2, 0x170, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x170, 0x171, 
    0x3, 0x2, 0x2, 0x2, 0x171, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x172, 0x170, 0x3, 
    0x2, 0x2, 0x2, 0x173, 0x174, 0x8, 0x28, 0x1, 0x2, 0x174, 0x175, 0x5, 
    0x50, 0x29, 0x2, 0x175, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x176, 0x177, 0xc, 
    0x5, 0x2, 0x2, 0x177, 0x178, 0x7, 0x1d, 0x2, 0x2, 0x178, 0x17d, 0x5, 
    0x50, 0x29, 0x2, 0x179, 0x17a, 0xc, 0x4, 0x2, 0x2, 0x17a, 0x17b, 0x7, 
    0x1e, 0x2, 0x2, 0x17b, 0x17d, 0x5, 0x50, 0x29, 0x2, 0x17c, 0x176, 0x3, 
    0x2, 0x2, 0x2, 0x17c, 0x179, 0x3, 0x2, 0x2, 0x2, 0x17d, 0x180, 0x3, 
    0x2, 0x2, 0x2, 0x17e, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 0x3, 
    0x2, 0x2, 0x2, 0x17f, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x180, 0x17e, 0x3, 0x2, 
    0x2, 0x2, 0x181, 0x187, 0x5, 0x56, 0x2c, 0x2, 0x182, 0x183, 0x7, 0x15, 
    0x2, 0x2, 0x183, 0x184, 0x5, 0x48, 0x25, 0x2, 0x184, 0x185, 0x7, 0x16, 
    0x2, 0x2, 0x185, 0x187, 0x3, 0x2, 0x2, 0x2, 0x186, 0x181, 0x3, 0x2, 
    0x2, 0x2, 0x186, 0x182, 0x3, 0x2, 0x2, 0x2, 0x187, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x188, 0x18b, 0x5, 0x54, 0x2b, 0x2, 0x189, 0x18b, 0x5, 0x5a, 0x2e, 
    0x2, 0x18a, 0x188, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x189, 0x3, 0x2, 0x2, 
    0x2, 0x18b, 0x53, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x18f, 0x5, 0x56, 0x2c, 
    0x2, 0x18d, 0x18f, 0x5, 0x58, 0x2d, 0x2, 0x18e, 0x18c, 0x3, 0x2, 0x2, 
    0x2, 0x18e, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x55, 0x3, 0x2, 0x2, 0x2, 
    0x190, 0x191, 0x9, 0x2, 0x2, 0x2, 0x191, 0x57, 0x3, 0x2, 0x2, 0x2, 0x192, 
    0x193, 0x7, 0x36, 0x2, 0x2, 0x193, 0x59, 0x3, 0x2, 0x2, 0x2, 0x194, 
    0x195, 0x7, 0x35, 0x2, 0x2, 0x195, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x196, 
    0x198, 0x5, 0x60, 0x31, 0x2, 0x197, 0x196, 0x3, 0x2, 0x2, 0x2, 0x197, 
    0x198, 0x3, 0x2, 0x2, 0x2, 0x198, 0x199, 0x3, 0x2, 0x2, 0x2, 0x199, 
    0x19d, 0x7, 0x30, 0x2, 0x2, 0x19a, 0x19c, 0x5, 0x5e, 0x30, 0x2, 0x19b, 
    0x19a, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x19d, 
    0x19b, 0x3, 0x2, 0x2, 0x2, 0x19d, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19e, 
    0x5d, 0x3, 0x2, 0x2, 0x2, 0x19f, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x1a1, 
    0x5, 0x60, 0x31, 0x2, 0x1a1, 0x1a2, 0x7, 0x30, 0x2, 0x2, 0x1a2, 0x5f, 
    0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 0x7, 0xb, 0x2, 0x2, 0x1a4, 0x1a5, 
    0x7, 0xb, 0x2, 0x2, 0x1a5, 0x61, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a7, 0x9, 
    0x3, 0x2, 0x2, 0x1a7, 0x63, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1a9, 0x5, 0x66, 
    0x34, 0x2, 0x1a9, 0x1aa, 0x7, 0x30, 0x2, 0x2, 0x1aa, 0x1ab, 0x7, 0xc, 
    0x2, 0x2, 0x1ab, 0x65, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1ae, 0x5, 0x68, 
    0x35, 0x2, 0x1ad, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1ae, 0x3, 0x2, 
    0x2, 0x2, 0x1ae, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1af, 0x1b1, 0x5, 0x6e, 
    0x38, 0x2, 0x1b0, 0x1b2, 0x5, 0x6a, 0x36, 0x2, 0x1b1, 0x1b0, 0x3, 0x2, 
    0x2, 0x2, 0x1b1, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x67, 0x3, 0x2, 0x2, 
    0x2, 0x1b3, 0x1b4, 0x7, 0x1f, 0x2, 0x2, 0x1b4, 0x69, 0x3, 0x2, 0x2, 
    0x2, 0x1b5, 0x1b7, 0x5, 0x6c, 0x37, 0x2, 0x1b6, 0x1b5, 0x3, 0x2, 0x2, 
    0x2, 0x1b7, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x1b6, 0x3, 0x2, 0x2, 
    0x2, 0x1b8, 0x1b9, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0x1ba, 0x1bc, 0x7, 0x1f, 0x2, 0x2, 0x1bb, 0x1ba, 0x3, 0x2, 0x2, 0x2, 
    0x1bb, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bd, 0x3, 0x2, 0x2, 0x2, 
    0x1bd, 0x1be, 0x7, 0xd, 0x2, 0x2, 0x1be, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x1bf, 
    0x1c4, 0x5, 0x72, 0x3a, 0x2, 0x1c0, 0x1c4, 0x5, 0x74, 0x3b, 0x2, 0x1c1, 
    0x1c4, 0x5, 0x70, 0x39, 0x2, 0x1c2, 0x1c4, 0x5, 0x5c, 0x2f, 0x2, 0x1c3, 
    0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c3, 
    0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c4, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c6, 0x9, 0x4, 0x2, 0x2, 0x1c6, 0x71, 
    0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c8, 0x9, 0x5, 0x2, 0x2, 0x1c8, 0x73, 0x3, 
    0x2, 0x2, 0x2, 0x1c9, 0x1ca, 0x9, 0x6, 0x2, 0x2, 0x1ca, 0x75, 0x3, 0x2, 
    0x2, 0x2, 0x27, 0x77, 0x7e, 0x8a, 0x94, 0xb2, 0xc0, 0xc8, 0xcc, 0xd5, 
    0xe0, 0xe8, 0xee, 0xf2, 0xfb, 0xff, 0x10f, 0x115, 0x137, 0x13e, 0x14c, 
    0x153, 0x160, 0x162, 0x16e, 0x170, 0x17c, 0x17e, 0x186, 0x18a, 0x18e, 
    0x197, 0x19d, 0x1ad, 0x1b1, 0x1b8, 0x1bb, 0x1c3, 
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
