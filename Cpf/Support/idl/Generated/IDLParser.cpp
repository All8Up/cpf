
// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLParser.g4 by ANTLR 4.7


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
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::NAMESPACE)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE)
      | (1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::CONST))) != 0)) {
      setState(100);
      global_statements();
    }
    setState(103);
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
    setState(106); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(105);
      global_statement();
      setState(108); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::NAMESPACE)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE)
      | (1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::CONST))) != 0));
   
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

IDLParser::Namespace_stmtContext* IDLParser::Global_statementContext::namespace_stmt() {
  return getRuleContext<IDLParser::Namespace_stmtContext>(0);
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
    setState(117);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(110);
      import_stmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(111);
      namespace_stmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(112);
      struct_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(113);
      interface_stmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(114);
      const_def();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(115);
      enum_def();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(116);
      enum_fwd();
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
  enterRule(_localctx, 6, IDLParser::RuleImport_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    match(IDLParser::IMPORT);
    setState(120);
    string_lit();
    setState(121);
    match(IDLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Namespace_stmtContext ------------------------------------------------------------------

IDLParser::Namespace_stmtContext::Namespace_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Namespace_stmtContext::NAMESPACE() {
  return getToken(IDLParser::NAMESPACE, 0);
}

IDLParser::Namespace_nameContext* IDLParser::Namespace_stmtContext::namespace_name() {
  return getRuleContext<IDLParser::Namespace_nameContext>(0);
}

IDLParser::Namespace_blockContext* IDLParser::Namespace_stmtContext::namespace_block() {
  return getRuleContext<IDLParser::Namespace_blockContext>(0);
}


size_t IDLParser::Namespace_stmtContext::getRuleIndex() const {
  return IDLParser::RuleNamespace_stmt;
}

void IDLParser::Namespace_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespace_stmt(this);
}

void IDLParser::Namespace_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespace_stmt(this);
}


antlrcpp::Any IDLParser::Namespace_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitNamespace_stmt(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Namespace_stmtContext* IDLParser::namespace_stmt() {
  Namespace_stmtContext *_localctx = _tracker.createInstance<Namespace_stmtContext>(_ctx, getState());
  enterRule(_localctx, 8, IDLParser::RuleNamespace_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    match(IDLParser::NAMESPACE);
    setState(124);
    namespace_name();
    setState(125);
    namespace_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Namespace_nameContext ------------------------------------------------------------------

IDLParser::Namespace_nameContext::Namespace_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Namespace_nameContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}


size_t IDLParser::Namespace_nameContext::getRuleIndex() const {
  return IDLParser::RuleNamespace_name;
}

void IDLParser::Namespace_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespace_name(this);
}

void IDLParser::Namespace_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespace_name(this);
}


antlrcpp::Any IDLParser::Namespace_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitNamespace_name(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Namespace_nameContext* IDLParser::namespace_name() {
  Namespace_nameContext *_localctx = _tracker.createInstance<Namespace_nameContext>(_ctx, getState());
  enterRule(_localctx, 10, IDLParser::RuleNamespace_name);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    match(IDLParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Namespace_blockContext ------------------------------------------------------------------

IDLParser::Namespace_blockContext::Namespace_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Namespace_blockContext::LBRACE() {
  return getToken(IDLParser::LBRACE, 0);
}

tree::TerminalNode* IDLParser::Namespace_blockContext::RBRACE() {
  return getToken(IDLParser::RBRACE, 0);
}

std::vector<IDLParser::Namespace_itemContext *> IDLParser::Namespace_blockContext::namespace_item() {
  return getRuleContexts<IDLParser::Namespace_itemContext>();
}

IDLParser::Namespace_itemContext* IDLParser::Namespace_blockContext::namespace_item(size_t i) {
  return getRuleContext<IDLParser::Namespace_itemContext>(i);
}


size_t IDLParser::Namespace_blockContext::getRuleIndex() const {
  return IDLParser::RuleNamespace_block;
}

void IDLParser::Namespace_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespace_block(this);
}

void IDLParser::Namespace_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespace_block(this);
}


antlrcpp::Any IDLParser::Namespace_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitNamespace_block(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Namespace_blockContext* IDLParser::namespace_block() {
  Namespace_blockContext *_localctx = _tracker.createInstance<Namespace_blockContext>(_ctx, getState());
  enterRule(_localctx, 12, IDLParser::RuleNamespace_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    match(IDLParser::LBRACE);
    setState(133);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::NAMESPACE)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE)
      | (1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::CONST))) != 0)) {
      setState(130);
      namespace_item();
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(136);
    match(IDLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Namespace_itemContext ------------------------------------------------------------------

IDLParser::Namespace_itemContext::Namespace_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Struct_stmtContext* IDLParser::Namespace_itemContext::struct_stmt() {
  return getRuleContext<IDLParser::Struct_stmtContext>(0);
}

IDLParser::Namespace_stmtContext* IDLParser::Namespace_itemContext::namespace_stmt() {
  return getRuleContext<IDLParser::Namespace_stmtContext>(0);
}

IDLParser::Interface_stmtContext* IDLParser::Namespace_itemContext::interface_stmt() {
  return getRuleContext<IDLParser::Interface_stmtContext>(0);
}

IDLParser::Const_defContext* IDLParser::Namespace_itemContext::const_def() {
  return getRuleContext<IDLParser::Const_defContext>(0);
}

IDLParser::Enum_defContext* IDLParser::Namespace_itemContext::enum_def() {
  return getRuleContext<IDLParser::Enum_defContext>(0);
}

IDLParser::Enum_fwdContext* IDLParser::Namespace_itemContext::enum_fwd() {
  return getRuleContext<IDLParser::Enum_fwdContext>(0);
}


size_t IDLParser::Namespace_itemContext::getRuleIndex() const {
  return IDLParser::RuleNamespace_item;
}

void IDLParser::Namespace_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespace_item(this);
}

void IDLParser::Namespace_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespace_item(this);
}


antlrcpp::Any IDLParser::Namespace_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitNamespace_item(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Namespace_itemContext* IDLParser::namespace_item() {
  Namespace_itemContext *_localctx = _tracker.createInstance<Namespace_itemContext>(_ctx, getState());
  enterRule(_localctx, 14, IDLParser::RuleNamespace_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(144);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(138);
      struct_stmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(139);
      namespace_stmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(140);
      interface_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(141);
      const_def();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(142);
      enum_def();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(143);
      enum_fwd();
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
  enterRule(_localctx, 16, IDLParser::RuleStruct_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(148);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(146);
      struct_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(147);
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

IDLParser::Struct_nameContext* IDLParser::Struct_declContext::struct_name() {
  return getRuleContext<IDLParser::Struct_nameContext>(0);
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
  enterRule(_localctx, 18, IDLParser::RuleStruct_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    match(IDLParser::STRUCT);
    setState(151);
    struct_name();
    setState(152);
    struct_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_nameContext ------------------------------------------------------------------

IDLParser::Struct_nameContext::Struct_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Struct_nameContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}


size_t IDLParser::Struct_nameContext::getRuleIndex() const {
  return IDLParser::RuleStruct_name;
}

void IDLParser::Struct_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_name(this);
}

void IDLParser::Struct_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_name(this);
}


antlrcpp::Any IDLParser::Struct_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLParserVisitor*>(visitor))
    return parserVisitor->visitStruct_name(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::Struct_nameContext* IDLParser::struct_name() {
  Struct_nameContext *_localctx = _tracker.createInstance<Struct_nameContext>(_ctx, getState());
  enterRule(_localctx, 20, IDLParser::RuleStruct_name);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    match(IDLParser::IDENT);
   
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

tree::TerminalNode* IDLParser::Struct_fwdContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
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
  enterRule(_localctx, 22, IDLParser::RuleStruct_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    match(IDLParser::STRUCT);
    setState(157);
    match(IDLParser::IDENT);
    setState(158);
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
  enterRule(_localctx, 24, IDLParser::RuleStruct_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(IDLParser::LBRACE);
    setState(164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::CONST)
      | (1ULL << IDLParser::VOID)
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
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::INT)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::DOUBLE)
      | (1ULL << IDLParser::IDENT))) != 0)) {
      setState(161);
      struct_item();
      setState(166);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(167);
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

IDLParser::Enum_fwdContext* IDLParser::Struct_itemContext::enum_fwd() {
  return getRuleContext<IDLParser::Enum_fwdContext>(0);
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
  enterRule(_localctx, 26, IDLParser::RuleStruct_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(173);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(169);
      member_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(170);
      const_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(171);
      enum_def();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(172);
      enum_fwd();
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
  enterRule(_localctx, 28, IDLParser::RuleInterface_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(177);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(175);
      interface_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(176);
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

tree::TerminalNode* IDLParser::Interface_fwdContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
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
  enterRule(_localctx, 30, IDLParser::RuleInterface_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    match(IDLParser::INTERFACE);
    setState(180);
    match(IDLParser::IDENT);
    setState(181);
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
  enterRule(_localctx, 32, IDLParser::RuleInterface_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(IDLParser::INTERFACE);
    setState(184);
    match(IDLParser::IDENT);
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(185);
      interface_super();
    }
    setState(188);
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
  enterRule(_localctx, 34, IDLParser::RuleInterface_super);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(IDLParser::COLON);
    setState(191);
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
  enterRule(_localctx, 36, IDLParser::RuleInterface_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    match(IDLParser::LBRACE);
    setState(197);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::ENUM)
      | (1ULL << IDLParser::CONST)
      | (1ULL << IDLParser::VOID)
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
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::INT)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::DOUBLE)
      | (1ULL << IDLParser::IDENT))) != 0)) {
      setState(194);
      interface_item();
      setState(199);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(200);
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

IDLParser::Enum_fwdContext* IDLParser::Interface_itemContext::enum_fwd() {
  return getRuleContext<IDLParser::Enum_fwdContext>(0);
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
  enterRule(_localctx, 38, IDLParser::RuleInterface_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(202);
      function_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(203);
      const_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(204);
      enum_def();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(205);
      enum_fwd();
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
  enterRule(_localctx, 40, IDLParser::RuleFunction_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    type_decl();
    setState(209);
    match(IDLParser::IDENT);
    setState(210);
    match(IDLParser::LPAREN);
    setState(212);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::LBRACKET)
      | (1ULL << IDLParser::VOID)
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
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::INT)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::DOUBLE)
      | (1ULL << IDLParser::IDENT))) != 0)) {
      setState(211);
      function_param_list();
    }
    setState(214);
    match(IDLParser::RPAREN);
    setState(215);
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
  enterRule(_localctx, 42, IDLParser::RuleFunction_param_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    function_param();
    setState(222);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COMMA) {
      setState(218);
      match(IDLParser::COMMA);
      setState(219);
      function_param();
      setState(224);
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

IDLParser::Any_typeContext* IDLParser::Function_paramContext::any_type() {
  return getRuleContext<IDLParser::Any_typeContext>(0);
}

tree::TerminalNode* IDLParser::Function_paramContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

IDLParser::Param_dir_qualifierContext* IDLParser::Function_paramContext::param_dir_qualifier() {
  return getRuleContext<IDLParser::Param_dir_qualifierContext>(0);
}

IDLParser::Pointer_typeContext* IDLParser::Function_paramContext::pointer_type() {
  return getRuleContext<IDLParser::Pointer_typeContext>(0);
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
  enterRule(_localctx, 44, IDLParser::RuleFunction_param);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::LBRACKET) {
      setState(225);
      param_dir_qualifier();
    }
    setState(228);
    any_type();
    setState(230);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::STAR) {
      setState(229);
      pointer_type();
    }
    setState(232);
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
  enterRule(_localctx, 46, IDLParser::RuleParam_dir_qualifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(245);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(234);
      match(IDLParser::LBRACKET);
      setState(235);
      match(IDLParser::IN);
      setState(236);
      match(IDLParser::RBRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(237);
      match(IDLParser::LBRACKET);
      setState(238);
      match(IDLParser::OUT);
      setState(239);
      match(IDLParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(240);
      match(IDLParser::LBRACKET);
      setState(241);
      match(IDLParser::IN);
      setState(242);
      match(IDLParser::COMMA);
      setState(243);
      match(IDLParser::OUT);
      setState(244);
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
  enterRule(_localctx, 48, IDLParser::RuleConst_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(247);
      const_integral_def();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(248);
      const_float_def();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(249);
      const_string_def();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(250);
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

tree::TerminalNode* IDLParser::Const_integral_defContext::CONST() {
  return getToken(IDLParser::CONST, 0);
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
  enterRule(_localctx, 50, IDLParser::RuleConst_integral_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
    match(IDLParser::CONST);
    setState(254);
    integral_type();
    setState(255);
    match(IDLParser::IDENT);
    setState(256);
    match(IDLParser::EQUALS);
    setState(257);
    integer_lit();
    setState(258);
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

tree::TerminalNode* IDLParser::Const_float_defContext::CONST() {
  return getToken(IDLParser::CONST, 0);
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
  enterRule(_localctx, 52, IDLParser::RuleConst_float_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    match(IDLParser::CONST);
    setState(261);
    float_type();
    setState(262);
    match(IDLParser::IDENT);
    setState(263);
    match(IDLParser::EQUALS);
    setState(264);
    float_lit();
    setState(265);
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

tree::TerminalNode* IDLParser::Const_string_defContext::CONST() {
  return getToken(IDLParser::CONST, 0);
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
  enterRule(_localctx, 54, IDLParser::RuleConst_string_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(267);
    match(IDLParser::CONST);
    setState(268);
    match(IDLParser::STRING);
    setState(269);
    match(IDLParser::IDENT);
    setState(270);
    match(IDLParser::EQUALS);
    setState(271);
    string_lit();
    setState(272);
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

tree::TerminalNode* IDLParser::Const_class_id_defContext::CONST() {
  return getToken(IDLParser::CONST, 0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::CLASS_ID() {
  return getToken(IDLParser::CLASS_ID, 0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

tree::TerminalNode* IDLParser::Const_class_id_defContext::EQUALS() {
  return getToken(IDLParser::EQUALS, 0);
}

IDLParser::String_litContext* IDLParser::Const_class_id_defContext::string_lit() {
  return getRuleContext<IDLParser::String_litContext>(0);
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
  enterRule(_localctx, 56, IDLParser::RuleConst_class_id_def);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(274);
    match(IDLParser::CONST);
    setState(275);
    match(IDLParser::CLASS_ID);
    setState(276);
    match(IDLParser::IDENT);
    setState(277);
    match(IDLParser::EQUALS);
    setState(278);
    string_lit();
    setState(279);
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
  enterRule(_localctx, 58, IDLParser::RuleEnum_fwd);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    match(IDLParser::ENUM);
    setState(282);
    match(IDLParser::IDENT);
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(283);
      enum_type();
    }
    setState(286);
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
  enterRule(_localctx, 60, IDLParser::RuleEnum_def);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    match(IDLParser::ENUM);
    setState(289);
    match(IDLParser::IDENT);
    setState(291);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(290);
      enum_type();
    }
    setState(293);
    match(IDLParser::LBRACE);
    setState(294);
    enum_elements();
    setState(295);
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
  enterRule(_localctx, 62, IDLParser::RuleEnum_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    match(IDLParser::COLON);
    setState(298);
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
  enterRule(_localctx, 64, IDLParser::RuleEnum_elements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(300);
    enum_item();
    setState(305);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COMMA) {
      setState(301);
      match(IDLParser::COMMA);
      setState(302);
      enum_item();
      setState(307);
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

IDLParser::Integer_litContext* IDLParser::Enum_itemContext::integer_lit() {
  return getRuleContext<IDLParser::Integer_litContext>(0);
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
  enterRule(_localctx, 66, IDLParser::RuleEnum_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(312);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(308);
      match(IDLParser::IDENT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(309);
      match(IDLParser::IDENT);
      setState(310);
      match(IDLParser::EQUALS);
      setState(311);
      integer_lit();
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
  enterRule(_localctx, 68, IDLParser::RuleAny_literal);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(316);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::OCT_LIT:
      case IDLParser::BIN_LIT:
      case IDLParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(314);
        numeric_lit();
        break;
      }

      case IDLParser::STRING_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(315);
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
  enterRule(_localctx, 70, IDLParser::RuleNumeric_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(320);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::DECIMAL_LIT:
      case IDLParser::HEX_LIT:
      case IDLParser::OCT_LIT:
      case IDLParser::BIN_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(318);
        integer_lit();
        break;
      }

      case IDLParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(319);
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
  enterRule(_localctx, 72, IDLParser::RuleInteger_lit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(322);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::DECIMAL_LIT)
      | (1ULL << IDLParser::HEX_LIT)
      | (1ULL << IDLParser::OCT_LIT)
      | (1ULL << IDLParser::BIN_LIT))) != 0))) {
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
  enterRule(_localctx, 74, IDLParser::RuleFloat_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
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
  enterRule(_localctx, 76, IDLParser::RuleString_lit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(326);
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
  enterRule(_localctx, 78, IDLParser::RuleQualified_ident);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(328);
      qualified_separator();
    }
    setState(331);
    match(IDLParser::IDENT);
    setState(335);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COLON) {
      setState(332);
      qualified_part();
      setState(337);
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
  enterRule(_localctx, 80, IDLParser::RuleQualified_part);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(338);
    qualified_separator();
    setState(339);
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
  enterRule(_localctx, 82, IDLParser::RuleQualified_separator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    match(IDLParser::COLON);
    setState(342);
    match(IDLParser::COLON);
   
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
  enterRule(_localctx, 84, IDLParser::RuleMember_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(344);
    type_decl();
    setState(345);
    match(IDLParser::IDENT);
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
  enterRule(_localctx, 86, IDLParser::RuleType_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::CONST) {
      setState(348);
      type_modifier();
    }
    setState(351);
    any_type();
    setState(353);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::STAR) {
      setState(352);
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

tree::TerminalNode* IDLParser::Type_modifierContext::CONST() {
  return getToken(IDLParser::CONST, 0);
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
  enterRule(_localctx, 88, IDLParser::RuleType_modifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(355);
    match(IDLParser::CONST);
   
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

std::vector<tree::TerminalNode *> IDLParser::Pointer_typeContext::STAR() {
  return getTokens(IDLParser::STAR);
}

tree::TerminalNode* IDLParser::Pointer_typeContext::STAR(size_t i) {
  return getToken(IDLParser::STAR, i);
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
  enterRule(_localctx, 90, IDLParser::RulePointer_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(357);
      match(IDLParser::STAR);
      setState(360); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == IDLParser::STAR);
   
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

tree::TerminalNode* IDLParser::Any_typeContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
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
  enterRule(_localctx, 92, IDLParser::RuleAny_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(366);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::U8:
      case IDLParser::S8:
      case IDLParser::U16:
      case IDLParser::S16:
      case IDLParser::U32:
      case IDLParser::S32:
      case IDLParser::U64:
      case IDLParser::S64:
      case IDLParser::BYTE:
      case IDLParser::CHAR:
      case IDLParser::SHORT:
      case IDLParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(362);
        integral_type();
        break;
      }

      case IDLParser::F32:
      case IDLParser::F64:
      case IDLParser::FLOAT:
      case IDLParser::DOUBLE: {
        enterOuterAlt(_localctx, 2);
        setState(363);
        float_type();
        break;
      }

      case IDLParser::VOID:
      case IDLParser::RESULT: {
        enterOuterAlt(_localctx, 3);
        setState(364);
        utility_type();
        break;
      }

      case IDLParser::IDENT: {
        enterOuterAlt(_localctx, 4);
        setState(365);
        match(IDLParser::IDENT);
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

tree::TerminalNode* IDLParser::Utility_typeContext::VOID() {
  return getToken(IDLParser::VOID, 0);
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
  enterRule(_localctx, 94, IDLParser::RuleUtility_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(368);
    _la = _input->LA(1);
    if (!(_la == IDLParser::VOID

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

tree::TerminalNode* IDLParser::Integral_typeContext::CHAR() {
  return getToken(IDLParser::CHAR, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::BYTE() {
  return getToken(IDLParser::BYTE, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::U16() {
  return getToken(IDLParser::U16, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::S16() {
  return getToken(IDLParser::S16, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::SHORT() {
  return getToken(IDLParser::SHORT, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::U32() {
  return getToken(IDLParser::U32, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::S32() {
  return getToken(IDLParser::S32, 0);
}

tree::TerminalNode* IDLParser::Integral_typeContext::INT() {
  return getToken(IDLParser::INT, 0);
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
  enterRule(_localctx, 96, IDLParser::RuleIntegral_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(370);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64)
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::INT))) != 0))) {
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

tree::TerminalNode* IDLParser::Float_typeContext::FLOAT() {
  return getToken(IDLParser::FLOAT, 0);
}

tree::TerminalNode* IDLParser::Float_typeContext::F64() {
  return getToken(IDLParser::F64, 0);
}

tree::TerminalNode* IDLParser::Float_typeContext::DOUBLE() {
  return getToken(IDLParser::DOUBLE, 0);
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
  enterRule(_localctx, 98, IDLParser::RuleFloat_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(372);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::F32)
      | (1ULL << IDLParser::F64)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::DOUBLE))) != 0))) {
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

// Static vars and initialization.
std::vector<dfa::DFA> IDLParser::_decisionToDFA;
atn::PredictionContextCache IDLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN IDLParser::_atn;
std::vector<uint16_t> IDLParser::_serializedATN;

std::vector<std::string> IDLParser::_ruleNames = {
  "main", "global_statements", "global_statement", "import_stmt", "namespace_stmt", 
  "namespace_name", "namespace_block", "namespace_item", "struct_stmt", 
  "struct_decl", "struct_name", "struct_fwd", "struct_block", "struct_item", 
  "interface_stmt", "interface_fwd", "interface_decl", "interface_super", 
  "interface_block", "interface_item", "function_decl", "function_param_list", 
  "function_param", "param_dir_qualifier", "const_def", "const_integral_def", 
  "const_float_def", "const_string_def", "const_class_id_def", "enum_fwd", 
  "enum_def", "enum_type", "enum_elements", "enum_item", "any_literal", 
  "numeric_lit", "integer_lit", "float_lit", "string_lit", "qualified_ident", 
  "qualified_part", "qualified_separator", "member_decl", "type_decl", "type_modifier", 
  "pointer_type", "any_type", "utility_type", "integral_type", "float_type"
};

std::vector<std::string> IDLParser::_literalNames = {
  "", "'import'", "'namespace'", "'struct'", "'interface'", "'enum'", "'in'", 
  "'out'", "':'", "';'", "'*'", "'.'", "','", "'='", "'\"'", "'{'", "'}'", 
  "'('", "')'", "'['", "']'", "'<'", "'>'", "'const'", "'void'", "'result'", 
  "'class_id'", "'u8'", "'s8'", "'u16'", "'s16'", "'u32'", "'s32'", "'u64'", 
  "'s64'", "'f32'", "'f64'", "'byte'", "'char'", "'short'", "'long'", "'int'", 
  "'float'", "'double'", "'string'"
};

std::vector<std::string> IDLParser::_symbolicNames = {
  "", "IMPORT", "NAMESPACE", "STRUCT", "INTERFACE", "ENUM", "IN", "OUT", 
  "COLON", "SEMICOLON", "STAR", "DOT", "COMMA", "EQUALS", "QUOTE", "LBRACE", 
  "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LT", "GT", "CONST", 
  "VOID", "RESULT", "CLASS_ID", "U8", "S8", "U16", "S16", "U32", "S32", 
  "U64", "S64", "F32", "F64", "BYTE", "CHAR", "SHORT", "LONG", "INT", "FLOAT", 
  "DOUBLE", "STRING", "IDENT", "DECIMAL_LIT", "HEX_LIT", "OCT_LIT", "BIN_LIT", 
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
    0x3, 0x38, 0x179, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x32, 0x4, 0x33, 0x9, 0x33, 0x3, 0x2, 0x5, 0x2, 0x68, 0xa, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x6, 0x3, 0x6d, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0x6e, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x5, 0x4, 0x78, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 
    0x3, 0x8, 0x7, 0x8, 0x86, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x89, 0xb, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x5, 0x9, 0x93, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x97, 
    0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 
    0xa5, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xa8, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xb0, 0xa, 0xf, 0x3, 
    0x10, 0x3, 0x10, 0x5, 0x10, 0xb4, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xbd, 0xa, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 
    0x3, 0x14, 0x7, 0x14, 0xc6, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0xc9, 0xb, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x5, 0x15, 0xd1, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x5, 0x16, 0xd7, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x7, 0x17, 0xdf, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 
    0xe2, 0xb, 0x17, 0x3, 0x18, 0x5, 0x18, 0xe5, 0xa, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x5, 0x18, 0xe9, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0xf8, 0xa, 0x19, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0xfe, 0xa, 0x1a, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x11f, 0xa, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x126, 
    0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 
    0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x7, 0x22, 0x132, 
    0xa, 0x22, 0xc, 0x22, 0xe, 0x22, 0x135, 0xb, 0x22, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x13b, 0xa, 0x23, 0x3, 0x24, 0x3, 0x24, 
    0x5, 0x24, 0x13f, 0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x143, 
    0xa, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 
    0x28, 0x3, 0x29, 0x5, 0x29, 0x14c, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 
    0x7, 0x29, 0x150, 0xa, 0x29, 0xc, 0x29, 0xe, 0x29, 0x153, 0xb, 0x29, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 
    0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2d, 0x5, 0x2d, 0x160, 
    0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x164, 0xa, 0x2d, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2f, 0x6, 0x2f, 0x169, 0xa, 0x2f, 0xd, 0x2f, 0xe, 0x2f, 
    0x16a, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 0x171, 
    0xa, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x33, 0x3, 
    0x33, 0x3, 0x33, 0x2, 0x2, 0x34, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 
    0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 
    0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 
    0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x2, 0x6, 0x3, 0x2, 0x30, 
    0x33, 0x3, 0x2, 0x1a, 0x1b, 0x5, 0x2, 0x1d, 0x24, 0x27, 0x29, 0x2b, 
    0x2b, 0x4, 0x2, 0x25, 0x26, 0x2c, 0x2d, 0x2, 0x176, 0x2, 0x67, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6, 0x77, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x79, 0x3, 0x2, 0x2, 0x2, 0xa, 0x7d, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0x81, 0x3, 0x2, 0x2, 0x2, 0xe, 0x83, 0x3, 0x2, 0x2, 0x2, 0x10, 0x92, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0x96, 0x3, 0x2, 0x2, 0x2, 0x14, 0x98, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x18, 0x9e, 0x3, 0x2, 
    0x2, 0x2, 0x1a, 0xa2, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xaf, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x20, 0xb5, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x24, 0xc0, 0x3, 0x2, 0x2, 0x2, 0x26, 
    0xc3, 0x3, 0x2, 0x2, 0x2, 0x28, 0xd0, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xd2, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xe4, 0x3, 
    0x2, 0x2, 0x2, 0x30, 0xf7, 0x3, 0x2, 0x2, 0x2, 0x32, 0xfd, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0xff, 0x3, 0x2, 0x2, 0x2, 0x36, 0x106, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x114, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x122, 0x3, 0x2, 0x2, 0x2, 0x40, 
    0x12b, 0x3, 0x2, 0x2, 0x2, 0x42, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x44, 0x13a, 
    0x3, 0x2, 0x2, 0x2, 0x46, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x48, 0x142, 0x3, 
    0x2, 0x2, 0x2, 0x4a, 0x144, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x146, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x148, 0x3, 0x2, 0x2, 0x2, 0x50, 0x14b, 0x3, 0x2, 0x2, 
    0x2, 0x52, 0x154, 0x3, 0x2, 0x2, 0x2, 0x54, 0x157, 0x3, 0x2, 0x2, 0x2, 
    0x56, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x58, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x5a, 
    0x165, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x168, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x170, 
    0x3, 0x2, 0x2, 0x2, 0x60, 0x172, 0x3, 0x2, 0x2, 0x2, 0x62, 0x174, 0x3, 
    0x2, 0x2, 0x2, 0x64, 0x176, 0x3, 0x2, 0x2, 0x2, 0x66, 0x68, 0x5, 0x4, 
    0x3, 0x2, 0x67, 0x66, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x3, 0x2, 0x2, 
    0x2, 0x68, 0x69, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x7, 0x2, 0x2, 0x3, 
    0x6a, 0x3, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6d, 0x5, 0x6, 0x4, 0x2, 0x6c, 
    0x6b, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6c, 
    0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x70, 0x78, 0x5, 0x8, 0x5, 0x2, 0x71, 0x78, 0x5, 0xa, 
    0x6, 0x2, 0x72, 0x78, 0x5, 0x12, 0xa, 0x2, 0x73, 0x78, 0x5, 0x1e, 0x10, 
    0x2, 0x74, 0x78, 0x5, 0x32, 0x1a, 0x2, 0x75, 0x78, 0x5, 0x3e, 0x20, 
    0x2, 0x76, 0x78, 0x5, 0x3c, 0x1f, 0x2, 0x77, 0x70, 0x3, 0x2, 0x2, 0x2, 
    0x77, 0x71, 0x3, 0x2, 0x2, 0x2, 0x77, 0x72, 0x3, 0x2, 0x2, 0x2, 0x77, 
    0x73, 0x3, 0x2, 0x2, 0x2, 0x77, 0x74, 0x3, 0x2, 0x2, 0x2, 0x77, 0x75, 
    0x3, 0x2, 0x2, 0x2, 0x77, 0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x79, 0x7a, 0x7, 0x3, 0x2, 0x2, 0x7a, 0x7b, 0x5, 0x4e, 
    0x28, 0x2, 0x7b, 0x7c, 0x7, 0xb, 0x2, 0x2, 0x7c, 0x9, 0x3, 0x2, 0x2, 
    0x2, 0x7d, 0x7e, 0x7, 0x4, 0x2, 0x2, 0x7e, 0x7f, 0x5, 0xc, 0x7, 0x2, 
    0x7f, 0x80, 0x5, 0xe, 0x8, 0x2, 0x80, 0xb, 0x3, 0x2, 0x2, 0x2, 0x81, 
    0x82, 0x7, 0x2f, 0x2, 0x2, 0x82, 0xd, 0x3, 0x2, 0x2, 0x2, 0x83, 0x87, 
    0x7, 0x11, 0x2, 0x2, 0x84, 0x86, 0x5, 0x10, 0x9, 0x2, 0x85, 0x84, 0x3, 
    0x2, 0x2, 0x2, 0x86, 0x89, 0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 
    0x2, 0x2, 0x87, 0x88, 0x3, 0x2, 0x2, 0x2, 0x88, 0x8a, 0x3, 0x2, 0x2, 
    0x2, 0x89, 0x87, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0x12, 0x2, 0x2, 
    0x8b, 0xf, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x93, 0x5, 0x12, 0xa, 0x2, 0x8d, 
    0x93, 0x5, 0xa, 0x6, 0x2, 0x8e, 0x93, 0x5, 0x1e, 0x10, 0x2, 0x8f, 0x93, 
    0x5, 0x32, 0x1a, 0x2, 0x90, 0x93, 0x5, 0x3e, 0x20, 0x2, 0x91, 0x93, 
    0x5, 0x3c, 0x1f, 0x2, 0x92, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x92, 0x8d, 0x3, 
    0x2, 0x2, 0x2, 0x92, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x92, 0x8f, 0x3, 0x2, 
    0x2, 0x2, 0x92, 0x90, 0x3, 0x2, 0x2, 0x2, 0x92, 0x91, 0x3, 0x2, 0x2, 
    0x2, 0x93, 0x11, 0x3, 0x2, 0x2, 0x2, 0x94, 0x97, 0x5, 0x14, 0xb, 0x2, 
    0x95, 0x97, 0x5, 0x18, 0xd, 0x2, 0x96, 0x94, 0x3, 0x2, 0x2, 0x2, 0x96, 
    0x95, 0x3, 0x2, 0x2, 0x2, 0x97, 0x13, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 
    0x7, 0x5, 0x2, 0x2, 0x99, 0x9a, 0x5, 0x16, 0xc, 0x2, 0x9a, 0x9b, 0x5, 
    0x1a, 0xe, 0x2, 0x9b, 0x15, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x2f, 
    0x2, 0x2, 0x9d, 0x17, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x5, 0x2, 
    0x2, 0x9f, 0xa0, 0x7, 0x2f, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0xb, 0x2, 0x2, 
    0xa1, 0x19, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa6, 0x7, 0x11, 0x2, 0x2, 0xa3, 
    0xa5, 0x5, 0x1c, 0xf, 0x2, 0xa4, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa8, 
    0x3, 0x2, 0x2, 0x2, 0xa6, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x3, 
    0x2, 0x2, 0x2, 0xa7, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa6, 0x3, 0x2, 
    0x2, 0x2, 0xa9, 0xaa, 0x7, 0x12, 0x2, 0x2, 0xaa, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0xab, 0xb0, 0x5, 0x56, 0x2c, 0x2, 0xac, 0xb0, 0x5, 0x32, 0x1a, 
    0x2, 0xad, 0xb0, 0x5, 0x3e, 0x20, 0x2, 0xae, 0xb0, 0x5, 0x3c, 0x1f, 
    0x2, 0xaf, 0xab, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xae, 0x3, 0x2, 0x2, 0x2, 0xb0, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb4, 0x5, 0x22, 0x12, 0x2, 0xb2, 0xb4, 
    0x5, 0x20, 0x11, 0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb2, 0x3, 
    0x2, 0x2, 0x2, 0xb4, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x7, 0x6, 
    0x2, 0x2, 0xb6, 0xb7, 0x7, 0x2f, 0x2, 0x2, 0xb7, 0xb8, 0x7, 0xb, 0x2, 
    0x2, 0xb8, 0x21, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 0x7, 0x6, 0x2, 0x2, 
    0xba, 0xbc, 0x7, 0x2f, 0x2, 0x2, 0xbb, 0xbd, 0x5, 0x24, 0x13, 0x2, 0xbc, 
    0xbb, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 
    0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x5, 0x26, 0x14, 0x2, 0xbf, 0x23, 0x3, 
    0x2, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0xa, 0x2, 0x2, 0xc1, 0xc2, 0x5, 0x50, 
    0x29, 0x2, 0xc2, 0x25, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc7, 0x7, 0x11, 0x2, 
    0x2, 0xc4, 0xc6, 0x5, 0x28, 0x15, 0x2, 0xc5, 0xc4, 0x3, 0x2, 0x2, 0x2, 
    0xc6, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc7, 
    0xc8, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xca, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xc7, 
    0x3, 0x2, 0x2, 0x2, 0xca, 0xcb, 0x7, 0x12, 0x2, 0x2, 0xcb, 0x27, 0x3, 
    0x2, 0x2, 0x2, 0xcc, 0xd1, 0x5, 0x2a, 0x16, 0x2, 0xcd, 0xd1, 0x5, 0x32, 
    0x1a, 0x2, 0xce, 0xd1, 0x5, 0x3e, 0x20, 0x2, 0xcf, 0xd1, 0x5, 0x3c, 
    0x1f, 0x2, 0xd0, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xcd, 0x3, 0x2, 0x2, 
    0x2, 0xd0, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xcf, 0x3, 0x2, 0x2, 0x2, 
    0xd1, 0x29, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 0x5, 0x58, 0x2d, 0x2, 0xd3, 
    0xd4, 0x7, 0x2f, 0x2, 0x2, 0xd4, 0xd6, 0x7, 0x13, 0x2, 0x2, 0xd5, 0xd7, 
    0x5, 0x2c, 0x17, 0x2, 0xd6, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd7, 0x3, 
    0x2, 0x2, 0x2, 0xd7, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x7, 0x14, 
    0x2, 0x2, 0xd9, 0xda, 0x7, 0xb, 0x2, 0x2, 0xda, 0x2b, 0x3, 0x2, 0x2, 
    0x2, 0xdb, 0xe0, 0x5, 0x2e, 0x18, 0x2, 0xdc, 0xdd, 0x7, 0xe, 0x2, 0x2, 
    0xdd, 0xdf, 0x5, 0x2e, 0x18, 0x2, 0xde, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xdf, 
    0xe2, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xde, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 
    0x3, 0x2, 0x2, 0x2, 0xe1, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe0, 0x3, 
    0x2, 0x2, 0x2, 0xe3, 0xe5, 0x5, 0x30, 0x19, 0x2, 0xe4, 0xe3, 0x3, 0x2, 
    0x2, 0x2, 0xe4, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x3, 0x2, 0x2, 
    0x2, 0xe6, 0xe8, 0x5, 0x5e, 0x30, 0x2, 0xe7, 0xe9, 0x5, 0x5c, 0x2f, 
    0x2, 0xe8, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x3, 0x2, 0x2, 0x2, 
    0xe9, 0xea, 0x3, 0x2, 0x2, 0x2, 0xea, 0xeb, 0x7, 0x2f, 0x2, 0x2, 0xeb, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0xec, 0xed, 0x7, 0x15, 0x2, 0x2, 0xed, 0xee, 
    0x7, 0x8, 0x2, 0x2, 0xee, 0xf8, 0x7, 0x16, 0x2, 0x2, 0xef, 0xf0, 0x7, 
    0x15, 0x2, 0x2, 0xf0, 0xf1, 0x7, 0x9, 0x2, 0x2, 0xf1, 0xf8, 0x7, 0x16, 
    0x2, 0x2, 0xf2, 0xf3, 0x7, 0x15, 0x2, 0x2, 0xf3, 0xf4, 0x7, 0x8, 0x2, 
    0x2, 0xf4, 0xf5, 0x7, 0xe, 0x2, 0x2, 0xf5, 0xf6, 0x7, 0x9, 0x2, 0x2, 
    0xf6, 0xf8, 0x7, 0x16, 0x2, 0x2, 0xf7, 0xec, 0x3, 0x2, 0x2, 0x2, 0xf7, 
    0xef, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf8, 0x31, 
    0x3, 0x2, 0x2, 0x2, 0xf9, 0xfe, 0x5, 0x34, 0x1b, 0x2, 0xfa, 0xfe, 0x5, 
    0x36, 0x1c, 0x2, 0xfb, 0xfe, 0x5, 0x38, 0x1d, 0x2, 0xfc, 0xfe, 0x5, 
    0x3a, 0x1e, 0x2, 0xfd, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfa, 0x3, 0x2, 
    0x2, 0x2, 0xfd, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfc, 0x3, 0x2, 0x2, 
    0x2, 0xfe, 0x33, 0x3, 0x2, 0x2, 0x2, 0xff, 0x100, 0x7, 0x19, 0x2, 0x2, 
    0x100, 0x101, 0x5, 0x62, 0x32, 0x2, 0x101, 0x102, 0x7, 0x2f, 0x2, 0x2, 
    0x102, 0x103, 0x7, 0xf, 0x2, 0x2, 0x103, 0x104, 0x5, 0x4a, 0x26, 0x2, 
    0x104, 0x105, 0x7, 0xb, 0x2, 0x2, 0x105, 0x35, 0x3, 0x2, 0x2, 0x2, 0x106, 
    0x107, 0x7, 0x19, 0x2, 0x2, 0x107, 0x108, 0x5, 0x64, 0x33, 0x2, 0x108, 
    0x109, 0x7, 0x2f, 0x2, 0x2, 0x109, 0x10a, 0x7, 0xf, 0x2, 0x2, 0x10a, 
    0x10b, 0x5, 0x4c, 0x27, 0x2, 0x10b, 0x10c, 0x7, 0xb, 0x2, 0x2, 0x10c, 
    0x37, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x7, 0x19, 0x2, 0x2, 0x10e, 
    0x10f, 0x7, 0x2e, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x2f, 0x2, 0x2, 0x110, 
    0x111, 0x7, 0xf, 0x2, 0x2, 0x111, 0x112, 0x5, 0x4e, 0x28, 0x2, 0x112, 
    0x113, 0x7, 0xb, 0x2, 0x2, 0x113, 0x39, 0x3, 0x2, 0x2, 0x2, 0x114, 0x115, 
    0x7, 0x19, 0x2, 0x2, 0x115, 0x116, 0x7, 0x1c, 0x2, 0x2, 0x116, 0x117, 
    0x7, 0x2f, 0x2, 0x2, 0x117, 0x118, 0x7, 0xf, 0x2, 0x2, 0x118, 0x119, 
    0x5, 0x4e, 0x28, 0x2, 0x119, 0x11a, 0x7, 0xb, 0x2, 0x2, 0x11a, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0x11b, 0x11c, 0x7, 0x7, 0x2, 0x2, 0x11c, 0x11e, 
    0x7, 0x2f, 0x2, 0x2, 0x11d, 0x11f, 0x5, 0x40, 0x21, 0x2, 0x11e, 0x11d, 
    0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x120, 
    0x3, 0x2, 0x2, 0x2, 0x120, 0x121, 0x7, 0xb, 0x2, 0x2, 0x121, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x122, 0x123, 0x7, 0x7, 0x2, 0x2, 0x123, 0x125, 0x7, 
    0x2f, 0x2, 0x2, 0x124, 0x126, 0x5, 0x40, 0x21, 0x2, 0x125, 0x124, 0x3, 
    0x2, 0x2, 0x2, 0x125, 0x126, 0x3, 0x2, 0x2, 0x2, 0x126, 0x127, 0x3, 
    0x2, 0x2, 0x2, 0x127, 0x128, 0x7, 0x11, 0x2, 0x2, 0x128, 0x129, 0x5, 
    0x42, 0x22, 0x2, 0x129, 0x12a, 0x7, 0x12, 0x2, 0x2, 0x12a, 0x3f, 0x3, 
    0x2, 0x2, 0x2, 0x12b, 0x12c, 0x7, 0xa, 0x2, 0x2, 0x12c, 0x12d, 0x5, 
    0x62, 0x32, 0x2, 0x12d, 0x41, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x133, 0x5, 
    0x44, 0x23, 0x2, 0x12f, 0x130, 0x7, 0xe, 0x2, 0x2, 0x130, 0x132, 0x5, 
    0x44, 0x23, 0x2, 0x131, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x132, 0x135, 0x3, 
    0x2, 0x2, 0x2, 0x133, 0x131, 0x3, 0x2, 0x2, 0x2, 0x133, 0x134, 0x3, 
    0x2, 0x2, 0x2, 0x134, 0x43, 0x3, 0x2, 0x2, 0x2, 0x135, 0x133, 0x3, 0x2, 
    0x2, 0x2, 0x136, 0x13b, 0x7, 0x2f, 0x2, 0x2, 0x137, 0x138, 0x7, 0x2f, 
    0x2, 0x2, 0x138, 0x139, 0x7, 0xf, 0x2, 0x2, 0x139, 0x13b, 0x5, 0x4a, 
    0x26, 0x2, 0x13a, 0x136, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x137, 0x3, 0x2, 
    0x2, 0x2, 0x13b, 0x45, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13f, 0x5, 0x48, 
    0x25, 0x2, 0x13d, 0x13f, 0x5, 0x4e, 0x28, 0x2, 0x13e, 0x13c, 0x3, 0x2, 
    0x2, 0x2, 0x13e, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x140, 0x143, 0x5, 0x4a, 0x26, 0x2, 0x141, 0x143, 0x5, 0x4c, 0x27, 
    0x2, 0x142, 0x140, 0x3, 0x2, 0x2, 0x2, 0x142, 0x141, 0x3, 0x2, 0x2, 
    0x2, 0x143, 0x49, 0x3, 0x2, 0x2, 0x2, 0x144, 0x145, 0x9, 0x2, 0x2, 0x2, 
    0x145, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0x7, 0x35, 0x2, 0x2, 
    0x147, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x148, 0x149, 0x7, 0x34, 0x2, 0x2, 
    0x149, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14c, 0x5, 0x54, 0x2b, 0x2, 
    0x14b, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x14c, 0x3, 0x2, 0x2, 0x2, 
    0x14c, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x151, 0x7, 0x2f, 0x2, 0x2, 
    0x14e, 0x150, 0x5, 0x52, 0x2a, 0x2, 0x14f, 0x14e, 0x3, 0x2, 0x2, 0x2, 
    0x150, 0x153, 0x3, 0x2, 0x2, 0x2, 0x151, 0x14f, 0x3, 0x2, 0x2, 0x2, 
    0x151, 0x152, 0x3, 0x2, 0x2, 0x2, 0x152, 0x51, 0x3, 0x2, 0x2, 0x2, 0x153, 
    0x151, 0x3, 0x2, 0x2, 0x2, 0x154, 0x155, 0x5, 0x54, 0x2b, 0x2, 0x155, 
    0x156, 0x7, 0x2f, 0x2, 0x2, 0x156, 0x53, 0x3, 0x2, 0x2, 0x2, 0x157, 
    0x158, 0x7, 0xa, 0x2, 0x2, 0x158, 0x159, 0x7, 0xa, 0x2, 0x2, 0x159, 
    0x55, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x15b, 0x5, 0x58, 0x2d, 0x2, 0x15b, 
    0x15c, 0x7, 0x2f, 0x2, 0x2, 0x15c, 0x15d, 0x7, 0xb, 0x2, 0x2, 0x15d, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x160, 0x5, 0x5a, 0x2e, 0x2, 0x15f, 
    0x15e, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 0x3, 0x2, 0x2, 0x2, 0x160, 
    0x161, 0x3, 0x2, 0x2, 0x2, 0x161, 0x163, 0x5, 0x5e, 0x30, 0x2, 0x162, 
    0x164, 0x5, 0x5c, 0x2f, 0x2, 0x163, 0x162, 0x3, 0x2, 0x2, 0x2, 0x163, 
    0x164, 0x3, 0x2, 0x2, 0x2, 0x164, 0x59, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 
    0x7, 0x19, 0x2, 0x2, 0x166, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x167, 0x169, 
    0x7, 0xc, 0x2, 0x2, 0x168, 0x167, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16a, 
    0x3, 0x2, 0x2, 0x2, 0x16a, 0x168, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x16b, 
    0x3, 0x2, 0x2, 0x2, 0x16b, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x171, 0x5, 
    0x62, 0x32, 0x2, 0x16d, 0x171, 0x5, 0x64, 0x33, 0x2, 0x16e, 0x171, 0x5, 
    0x60, 0x31, 0x2, 0x16f, 0x171, 0x7, 0x2f, 0x2, 0x2, 0x170, 0x16c, 0x3, 
    0x2, 0x2, 0x2, 0x170, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x170, 0x16e, 0x3, 
    0x2, 0x2, 0x2, 0x170, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x171, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x172, 0x173, 0x9, 0x3, 0x2, 0x2, 0x173, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x174, 0x175, 0x9, 0x4, 0x2, 0x2, 0x175, 0x63, 0x3, 0x2, 0x2, 0x2, 
    0x176, 0x177, 0x9, 0x5, 0x2, 0x2, 0x177, 0x65, 0x3, 0x2, 0x2, 0x2, 0x20, 
    0x67, 0x6e, 0x77, 0x87, 0x92, 0x96, 0xa6, 0xaf, 0xb3, 0xbc, 0xc7, 0xd0, 
    0xd6, 0xe0, 0xe4, 0xe8, 0xf7, 0xfd, 0x11e, 0x125, 0x133, 0x13a, 0x13e, 
    0x142, 0x14b, 0x151, 0x15f, 0x163, 0x16a, 0x170, 
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
