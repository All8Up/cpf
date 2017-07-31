
// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLParser.g4 by ANTLR 4.7


#include "IDLParserListener.h"

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

IDLParser::MainContext* IDLParser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 0, IDLParser::RuleMain);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::NAMESPACE)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE))) != 0)) {
      setState(68);
      global_statements();
    }
    setState(71);
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

IDLParser::Global_statementsContext* IDLParser::global_statements() {
  Global_statementsContext *_localctx = _tracker.createInstance<Global_statementsContext>(_ctx, getState());
  enterRule(_localctx, 2, IDLParser::RuleGlobal_statements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(73);
      global_statement();
      setState(76); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IMPORT)
      | (1ULL << IDLParser::NAMESPACE)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE))) != 0));
   
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

IDLParser::Global_statementContext* IDLParser::global_statement() {
  Global_statementContext *_localctx = _tracker.createInstance<Global_statementContext>(_ctx, getState());
  enterRule(_localctx, 4, IDLParser::RuleGlobal_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(82);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::IMPORT: {
        enterOuterAlt(_localctx, 1);
        setState(78);
        import_stmt();
        break;
      }

      case IDLParser::NAMESPACE: {
        enterOuterAlt(_localctx, 2);
        setState(79);
        namespace_stmt();
        break;
      }

      case IDLParser::STRUCT: {
        enterOuterAlt(_localctx, 3);
        setState(80);
        struct_stmt();
        break;
      }

      case IDLParser::INTERFACE: {
        enterOuterAlt(_localctx, 4);
        setState(81);
        interface_stmt();
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

//----------------- Import_stmtContext ------------------------------------------------------------------

IDLParser::Import_stmtContext::Import_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Import_stmtContext::IMPORT() {
  return getToken(IDLParser::IMPORT, 0);
}

tree::TerminalNode* IDLParser::Import_stmtContext::STRING_LIT() {
  return getToken(IDLParser::STRING_LIT, 0);
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

IDLParser::Import_stmtContext* IDLParser::import_stmt() {
  Import_stmtContext *_localctx = _tracker.createInstance<Import_stmtContext>(_ctx, getState());
  enterRule(_localctx, 6, IDLParser::RuleImport_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(IDLParser::IMPORT);
    setState(85);
    match(IDLParser::STRING_LIT);
    setState(86);
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

tree::TerminalNode* IDLParser::Namespace_stmtContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
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

IDLParser::Namespace_stmtContext* IDLParser::namespace_stmt() {
  Namespace_stmtContext *_localctx = _tracker.createInstance<Namespace_stmtContext>(_ctx, getState());
  enterRule(_localctx, 8, IDLParser::RuleNamespace_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(IDLParser::NAMESPACE);
    setState(89);
    match(IDLParser::IDENT);
    setState(90);
    namespace_block();
   
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

IDLParser::Namespace_blockContext* IDLParser::namespace_block() {
  Namespace_blockContext *_localctx = _tracker.createInstance<Namespace_blockContext>(_ctx, getState());
  enterRule(_localctx, 10, IDLParser::RuleNamespace_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(IDLParser::LBRACE);
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::NAMESPACE)
      | (1ULL << IDLParser::STRUCT)
      | (1ULL << IDLParser::INTERFACE))) != 0)) {
      setState(93);
      namespace_item();
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(99);
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

IDLParser::Namespace_itemContext* IDLParser::namespace_item() {
  Namespace_itemContext *_localctx = _tracker.createInstance<Namespace_itemContext>(_ctx, getState());
  enterRule(_localctx, 12, IDLParser::RuleNamespace_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(104);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::STRUCT: {
        enterOuterAlt(_localctx, 1);
        setState(101);
        struct_stmt();
        break;
      }

      case IDLParser::NAMESPACE: {
        enterOuterAlt(_localctx, 2);
        setState(102);
        namespace_stmt();
        break;
      }

      case IDLParser::INTERFACE: {
        enterOuterAlt(_localctx, 3);
        setState(103);
        interface_stmt();
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

IDLParser::Struct_stmtContext* IDLParser::struct_stmt() {
  Struct_stmtContext *_localctx = _tracker.createInstance<Struct_stmtContext>(_ctx, getState());
  enterRule(_localctx, 14, IDLParser::RuleStruct_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(106);
      struct_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(107);
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

IDLParser::Struct_declContext* IDLParser::struct_decl() {
  Struct_declContext *_localctx = _tracker.createInstance<Struct_declContext>(_ctx, getState());
  enterRule(_localctx, 16, IDLParser::RuleStruct_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(IDLParser::STRUCT);
    setState(111);
    match(IDLParser::IDENT);
    setState(112);
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

IDLParser::Struct_fwdContext* IDLParser::struct_fwd() {
  Struct_fwdContext *_localctx = _tracker.createInstance<Struct_fwdContext>(_ctx, getState());
  enterRule(_localctx, 18, IDLParser::RuleStruct_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(IDLParser::STRUCT);
    setState(115);
    match(IDLParser::IDENT);
    setState(116);
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

IDLParser::Struct_blockContext* IDLParser::struct_block() {
  Struct_blockContext *_localctx = _tracker.createInstance<Struct_blockContext>(_ctx, getState());
  enterRule(_localctx, 20, IDLParser::RuleStruct_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(IDLParser::LBRACE);
    setState(122);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IDENT)
      | (1ULL << IDLParser::CONST)
      | (1ULL << IDLParser::VOID)
      | (1ULL << IDLParser::RESULT)
      | (1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::INT)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64)
      | (1ULL << IDLParser::F32)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::F64)
      | (1ULL << IDLParser::DOUBLE))) != 0)) {
      setState(119);
      struct_item();
      setState(124);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(125);
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

IDLParser::Struct_itemContext* IDLParser::struct_item() {
  Struct_itemContext *_localctx = _tracker.createInstance<Struct_itemContext>(_ctx, getState());
  enterRule(_localctx, 22, IDLParser::RuleStruct_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    member_decl();
   
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

IDLParser::Interface_stmtContext* IDLParser::interface_stmt() {
  Interface_stmtContext *_localctx = _tracker.createInstance<Interface_stmtContext>(_ctx, getState());
  enterRule(_localctx, 24, IDLParser::RuleInterface_stmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(129);
      interface_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(130);
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

IDLParser::Interface_fwdContext* IDLParser::interface_fwd() {
  Interface_fwdContext *_localctx = _tracker.createInstance<Interface_fwdContext>(_ctx, getState());
  enterRule(_localctx, 26, IDLParser::RuleInterface_fwd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(IDLParser::INTERFACE);
    setState(134);
    match(IDLParser::IDENT);
    setState(135);
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

IDLParser::Interface_declContext* IDLParser::interface_decl() {
  Interface_declContext *_localctx = _tracker.createInstance<Interface_declContext>(_ctx, getState());
  enterRule(_localctx, 28, IDLParser::RuleInterface_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(IDLParser::INTERFACE);
    setState(138);
    match(IDLParser::IDENT);
    setState(140);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(139);
      interface_super();
    }
    setState(142);
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

IDLParser::Interface_superContext* IDLParser::interface_super() {
  Interface_superContext *_localctx = _tracker.createInstance<Interface_superContext>(_ctx, getState());
  enterRule(_localctx, 30, IDLParser::RuleInterface_super);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    match(IDLParser::COLON);
    setState(145);
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

IDLParser::Interface_blockContext* IDLParser::interface_block() {
  Interface_blockContext *_localctx = _tracker.createInstance<Interface_blockContext>(_ctx, getState());
  enterRule(_localctx, 32, IDLParser::RuleInterface_block);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(IDLParser::LBRACE);
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IDENT)
      | (1ULL << IDLParser::CONST)
      | (1ULL << IDLParser::VOID)
      | (1ULL << IDLParser::RESULT)
      | (1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::INT)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64)
      | (1ULL << IDLParser::F32)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::F64)
      | (1ULL << IDLParser::DOUBLE))) != 0)) {
      setState(148);
      interface_item();
      setState(153);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(154);
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

IDLParser::Interface_itemContext* IDLParser::interface_item() {
  Interface_itemContext *_localctx = _tracker.createInstance<Interface_itemContext>(_ctx, getState());
  enterRule(_localctx, 34, IDLParser::RuleInterface_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    function_decl();
   
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

IDLParser::Function_declContext* IDLParser::function_decl() {
  Function_declContext *_localctx = _tracker.createInstance<Function_declContext>(_ctx, getState());
  enterRule(_localctx, 36, IDLParser::RuleFunction_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    type_decl();
    setState(159);
    match(IDLParser::IDENT);
    setState(160);
    match(IDLParser::LPAREN);
    setState(162);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::IDENT)
      | (1ULL << IDLParser::LBRACKET)
      | (1ULL << IDLParser::VOID)
      | (1ULL << IDLParser::RESULT)
      | (1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::INT)
      | (1ULL << IDLParser::U64)
      | (1ULL << IDLParser::S64)
      | (1ULL << IDLParser::F32)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::F64)
      | (1ULL << IDLParser::DOUBLE))) != 0)) {
      setState(161);
      function_param_list();
    }
    setState(164);
    match(IDLParser::RPAREN);
    setState(165);
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

IDLParser::Function_param_listContext* IDLParser::function_param_list() {
  Function_param_listContext *_localctx = _tracker.createInstance<Function_param_listContext>(_ctx, getState());
  enterRule(_localctx, 38, IDLParser::RuleFunction_param_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    function_param();
    setState(172);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IDLParser::COMMA) {
      setState(168);
      match(IDLParser::COMMA);
      setState(169);
      function_param();
      setState(174);
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

IDLParser::Pointer_opt_typeContext* IDLParser::Function_paramContext::pointer_opt_type() {
  return getRuleContext<IDLParser::Pointer_opt_typeContext>(0);
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

IDLParser::Function_paramContext* IDLParser::function_param() {
  Function_paramContext *_localctx = _tracker.createInstance<Function_paramContext>(_ctx, getState());
  enterRule(_localctx, 40, IDLParser::RuleFunction_param);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::LBRACKET) {
      setState(175);
      param_dir_qualifier();
    }
    setState(178);
    pointer_opt_type();
    setState(179);
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

IDLParser::Param_dir_qualifierContext* IDLParser::param_dir_qualifier() {
  Param_dir_qualifierContext *_localctx = _tracker.createInstance<Param_dir_qualifierContext>(_ctx, getState());
  enterRule(_localctx, 42, IDLParser::RuleParam_dir_qualifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(192);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(181);
      match(IDLParser::LBRACKET);
      setState(182);
      match(IDLParser::IN);
      setState(183);
      match(IDLParser::RBRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(184);
      match(IDLParser::LBRACKET);
      setState(185);
      match(IDLParser::OUT);
      setState(186);
      match(IDLParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(187);
      match(IDLParser::LBRACKET);
      setState(188);
      match(IDLParser::IN);
      setState(189);
      match(IDLParser::COMMA);
      setState(190);
      match(IDLParser::OUT);
      setState(191);
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

//----------------- Qualified_identContext ------------------------------------------------------------------

IDLParser::Qualified_identContext::Qualified_identContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::Qualified_identContext::IDENT() {
  return getToken(IDLParser::IDENT, 0);
}

IDLParser::Qualified_part_optContext* IDLParser::Qualified_identContext::qualified_part_opt() {
  return getRuleContext<IDLParser::Qualified_part_optContext>(0);
}

IDLParser::Qualified_separatorContext* IDLParser::Qualified_identContext::qualified_separator() {
  return getRuleContext<IDLParser::Qualified_separatorContext>(0);
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

IDLParser::Qualified_identContext* IDLParser::qualified_ident() {
  Qualified_identContext *_localctx = _tracker.createInstance<Qualified_identContext>(_ctx, getState());
  enterRule(_localctx, 44, IDLParser::RuleQualified_ident);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(194);
      qualified_separator();
    }
    setState(197);
    match(IDLParser::IDENT);
    setState(198);
    qualified_part_opt();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Qualified_part_optContext ------------------------------------------------------------------

IDLParser::Qualified_part_optContext::Qualified_part_optContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Qualified_partContext* IDLParser::Qualified_part_optContext::qualified_part() {
  return getRuleContext<IDLParser::Qualified_partContext>(0);
}


size_t IDLParser::Qualified_part_optContext::getRuleIndex() const {
  return IDLParser::RuleQualified_part_opt;
}

void IDLParser::Qualified_part_optContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualified_part_opt(this);
}

void IDLParser::Qualified_part_optContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualified_part_opt(this);
}

IDLParser::Qualified_part_optContext* IDLParser::qualified_part_opt() {
  Qualified_part_optContext *_localctx = _tracker.createInstance<Qualified_part_optContext>(_ctx, getState());
  enterRule(_localctx, 46, IDLParser::RuleQualified_part_opt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::COLON) {
      setState(200);
      qualified_part();
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

IDLParser::Qualified_partContext* IDLParser::qualified_part() {
  Qualified_partContext *_localctx = _tracker.createInstance<Qualified_partContext>(_ctx, getState());
  enterRule(_localctx, 48, IDLParser::RuleQualified_part);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    qualified_separator();
    setState(204);
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

IDLParser::Qualified_separatorContext* IDLParser::qualified_separator() {
  Qualified_separatorContext *_localctx = _tracker.createInstance<Qualified_separatorContext>(_ctx, getState());
  enterRule(_localctx, 50, IDLParser::RuleQualified_separator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    match(IDLParser::COLON);
    setState(207);
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

IDLParser::Member_declContext* IDLParser::member_decl() {
  Member_declContext *_localctx = _tracker.createInstance<Member_declContext>(_ctx, getState());
  enterRule(_localctx, 52, IDLParser::RuleMember_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    type_decl();
    setState(210);
    match(IDLParser::IDENT);
    setState(211);
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

IDLParser::Pointer_opt_typeContext* IDLParser::Type_declContext::pointer_opt_type() {
  return getRuleContext<IDLParser::Pointer_opt_typeContext>(0);
}

IDLParser::Type_modifierContext* IDLParser::Type_declContext::type_modifier() {
  return getRuleContext<IDLParser::Type_modifierContext>(0);
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

IDLParser::Type_declContext* IDLParser::type_decl() {
  Type_declContext *_localctx = _tracker.createInstance<Type_declContext>(_ctx, getState());
  enterRule(_localctx, 54, IDLParser::RuleType_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::CONST) {
      setState(213);
      type_modifier();
    }
    setState(216);
    pointer_opt_type();
   
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

IDLParser::Type_modifierContext* IDLParser::type_modifier() {
  Type_modifierContext *_localctx = _tracker.createInstance<Type_modifierContext>(_ctx, getState());
  enterRule(_localctx, 56, IDLParser::RuleType_modifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(IDLParser::CONST);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pointer_opt_typeContext ------------------------------------------------------------------

IDLParser::Pointer_opt_typeContext::Pointer_opt_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::Any_typeContext* IDLParser::Pointer_opt_typeContext::any_type() {
  return getRuleContext<IDLParser::Any_typeContext>(0);
}

std::vector<tree::TerminalNode *> IDLParser::Pointer_opt_typeContext::STAR() {
  return getTokens(IDLParser::STAR);
}

tree::TerminalNode* IDLParser::Pointer_opt_typeContext::STAR(size_t i) {
  return getToken(IDLParser::STAR, i);
}


size_t IDLParser::Pointer_opt_typeContext::getRuleIndex() const {
  return IDLParser::RulePointer_opt_type;
}

void IDLParser::Pointer_opt_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointer_opt_type(this);
}

void IDLParser::Pointer_opt_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IDLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointer_opt_type(this);
}

IDLParser::Pointer_opt_typeContext* IDLParser::pointer_opt_type() {
  Pointer_opt_typeContext *_localctx = _tracker.createInstance<Pointer_opt_typeContext>(_ctx, getState());
  enterRule(_localctx, 58, IDLParser::RulePointer_opt_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
    any_type();
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IDLParser::STAR) {
      setState(222); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(221);
        match(IDLParser::STAR);
        setState(224); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == IDLParser::STAR);
    }
   
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

IDLParser::Any_typeContext* IDLParser::any_type() {
  Any_typeContext *_localctx = _tracker.createInstance<Any_typeContext>(_ctx, getState());
  enterRule(_localctx, 60, IDLParser::RuleAny_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::U8:
      case IDLParser::S8:
      case IDLParser::CHAR:
      case IDLParser::BYTE:
      case IDLParser::U16:
      case IDLParser::S16:
      case IDLParser::SHORT:
      case IDLParser::U32:
      case IDLParser::S32:
      case IDLParser::INT:
      case IDLParser::U64:
      case IDLParser::S64: {
        enterOuterAlt(_localctx, 1);
        setState(228);
        integral_type();
        break;
      }

      case IDLParser::F32:
      case IDLParser::FLOAT:
      case IDLParser::F64:
      case IDLParser::DOUBLE: {
        enterOuterAlt(_localctx, 2);
        setState(229);
        float_type();
        break;
      }

      case IDLParser::VOID:
      case IDLParser::RESULT: {
        enterOuterAlt(_localctx, 3);
        setState(230);
        utility_type();
        break;
      }

      case IDLParser::IDENT: {
        enterOuterAlt(_localctx, 4);
        setState(231);
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

IDLParser::Utility_typeContext* IDLParser::utility_type() {
  Utility_typeContext *_localctx = _tracker.createInstance<Utility_typeContext>(_ctx, getState());
  enterRule(_localctx, 62, IDLParser::RuleUtility_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
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

IDLParser::Integral_typeContext* IDLParser::integral_type() {
  Integral_typeContext *_localctx = _tracker.createInstance<Integral_typeContext>(_ctx, getState());
  enterRule(_localctx, 64, IDLParser::RuleIntegral_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(236);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::U8)
      | (1ULL << IDLParser::S8)
      | (1ULL << IDLParser::CHAR)
      | (1ULL << IDLParser::BYTE)
      | (1ULL << IDLParser::U16)
      | (1ULL << IDLParser::S16)
      | (1ULL << IDLParser::SHORT)
      | (1ULL << IDLParser::U32)
      | (1ULL << IDLParser::S32)
      | (1ULL << IDLParser::INT)
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

IDLParser::Float_typeContext* IDLParser::float_type() {
  Float_typeContext *_localctx = _tracker.createInstance<Float_typeContext>(_ctx, getState());
  enterRule(_localctx, 66, IDLParser::RuleFloat_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::F32)
      | (1ULL << IDLParser::FLOAT)
      | (1ULL << IDLParser::F64)
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
  "namespace_block", "namespace_item", "struct_stmt", "struct_decl", "struct_fwd", 
  "struct_block", "struct_item", "interface_stmt", "interface_fwd", "interface_decl", 
  "interface_super", "interface_block", "interface_item", "function_decl", 
  "function_param_list", "function_param", "param_dir_qualifier", "qualified_ident", 
  "qualified_part_opt", "qualified_part", "qualified_separator", "member_decl", 
  "type_decl", "type_modifier", "pointer_opt_type", "any_type", "utility_type", 
  "integral_type", "float_type"
};

std::vector<std::string> IDLParser::_literalNames = {
};

std::vector<std::string> IDLParser::_symbolicNames = {
  "", "IMPORT", "STRING_LIT", "SEMICOLON", "NAMESPACE", "IDENT", "LBRACE", 
  "RBRACE", "STRUCT", "INTERFACE", "COLON", "LPAREN", "RPAREN", "COMMA", 
  "LBRACKET", "IN", "RBRACKET", "OUT", "CONST", "STAR", "VOID", "RESULT", 
  "U8", "S8", "CHAR", "BYTE", "U16", "S16", "SHORT", "U32", "S32", "INT", 
  "U64", "S64", "F32", "FLOAT", "F64", "DOUBLE"
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
    0x3, 0x27, 0xf3, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 
    0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 
    0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 
    0x22, 0x4, 0x23, 0x9, 0x23, 0x3, 0x2, 0x5, 0x2, 0x48, 0xa, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x6, 0x3, 0x4d, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0x4e, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x55, 0xa, 0x4, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x61, 0xa, 0x7, 0xc, 0x7, 0xe, 
    0x7, 0x64, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x5, 0x8, 0x6b, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x6f, 0xa, 0x9, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x7b, 0xa, 0xc, 0xc, 0xc, 0xe, 
    0xc, 0x7e, 0xb, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 
    0x3, 0xe, 0x5, 0xe, 0x86, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x8f, 0xa, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 
    0x7, 0x12, 0x98, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x9b, 0xb, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0xa5, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x7, 0x15, 0xad, 0xa, 0x15, 0xc, 0x15, 
    0xe, 0x15, 0xb0, 0xb, 0x15, 0x3, 0x16, 0x5, 0x16, 0xb3, 0xa, 0x16, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x5, 0x17, 0xc3, 0xa, 0x17, 0x3, 0x18, 0x5, 0x18, 0xc6, 0xa, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x5, 0x19, 0xcc, 0xa, 0x19, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x5, 0x1d, 0xd9, 0xa, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 
    0x6, 0x1f, 0xe1, 0xa, 0x1f, 0xd, 0x1f, 0xe, 0x1f, 0xe2, 0x5, 0x1f, 0xe5, 
    0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0xeb, 
    0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x2, 0x2, 0x24, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 
    0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 
    0x40, 0x42, 0x44, 0x2, 0x5, 0x3, 0x2, 0x16, 0x17, 0x3, 0x2, 0x18, 0x23, 
    0x3, 0x2, 0x24, 0x27, 0x2, 0xea, 0x2, 0x47, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x4c, 0x3, 0x2, 0x2, 0x2, 0x6, 0x54, 0x3, 0x2, 0x2, 0x2, 0x8, 0x56, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x5a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x5e, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x10, 0x6e, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x70, 0x3, 0x2, 0x2, 0x2, 0x14, 0x74, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x78, 0x3, 0x2, 0x2, 0x2, 0x18, 0x81, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x85, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x87, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x8b, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x92, 0x3, 0x2, 0x2, 0x2, 0x22, 0x95, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x26, 0xa0, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xb2, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0xc2, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xc5, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x32, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x34, 
    0xd0, 0x3, 0x2, 0x2, 0x2, 0x36, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x38, 0xd8, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0xdc, 0x3, 0x2, 0x2, 0x2, 0x3c, 0xde, 0x3, 
    0x2, 0x2, 0x2, 0x3e, 0xea, 0x3, 0x2, 0x2, 0x2, 0x40, 0xec, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0xee, 0x3, 0x2, 0x2, 0x2, 0x44, 0xf0, 0x3, 0x2, 0x2, 
    0x2, 0x46, 0x48, 0x5, 0x4, 0x3, 0x2, 0x47, 0x46, 0x3, 0x2, 0x2, 0x2, 
    0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x4a, 0x7, 0x2, 0x2, 0x3, 0x4a, 0x3, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4d, 
    0x5, 0x6, 0x4, 0x2, 0x4c, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x4f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x50, 0x55, 0x5, 0x8, 0x5, 
    0x2, 0x51, 0x55, 0x5, 0xa, 0x6, 0x2, 0x52, 0x55, 0x5, 0x10, 0x9, 0x2, 
    0x53, 0x55, 0x5, 0x1a, 0xe, 0x2, 0x54, 0x50, 0x3, 0x2, 0x2, 0x2, 0x54, 
    0x51, 0x3, 0x2, 0x2, 0x2, 0x54, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x55, 0x7, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x7, 
    0x3, 0x2, 0x2, 0x57, 0x58, 0x7, 0x4, 0x2, 0x2, 0x58, 0x59, 0x7, 0x5, 
    0x2, 0x2, 0x59, 0x9, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x7, 0x6, 0x2, 
    0x2, 0x5b, 0x5c, 0x7, 0x7, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0xc, 0x7, 0x2, 
    0x5d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x62, 0x7, 0x8, 0x2, 0x2, 0x5f, 
    0x61, 0x5, 0xe, 0x8, 0x2, 0x60, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 0x64, 
    0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 
    0x2, 0x2, 0x2, 0x63, 0x65, 0x3, 0x2, 0x2, 0x2, 0x64, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0x65, 0x66, 0x7, 0x9, 0x2, 0x2, 0x66, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x67, 0x6b, 0x5, 0x10, 0x9, 0x2, 0x68, 0x6b, 0x5, 0xa, 0x6, 0x2, 
    0x69, 0x6b, 0x5, 0x1a, 0xe, 0x2, 0x6a, 0x67, 0x3, 0x2, 0x2, 0x2, 0x6a, 
    0x68, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6b, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x6c, 0x6f, 0x5, 0x12, 0xa, 0x2, 0x6d, 0x6f, 0x5, 
    0x14, 0xb, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6d, 0x3, 0x2, 
    0x2, 0x2, 0x6f, 0x11, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x7, 0xa, 0x2, 
    0x2, 0x71, 0x72, 0x7, 0x7, 0x2, 0x2, 0x72, 0x73, 0x5, 0x16, 0xc, 0x2, 
    0x73, 0x13, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x7, 0xa, 0x2, 0x2, 0x75, 
    0x76, 0x7, 0x7, 0x2, 0x2, 0x76, 0x77, 0x7, 0x5, 0x2, 0x2, 0x77, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x7c, 0x7, 0x8, 0x2, 0x2, 0x79, 0x7b, 0x5, 
    0x18, 0xd, 0x2, 0x7a, 0x79, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7e, 0x3, 0x2, 
    0x2, 0x2, 0x7c, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x3, 0x2, 0x2, 
    0x2, 0x7d, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 
    0x7f, 0x80, 0x7, 0x9, 0x2, 0x2, 0x80, 0x17, 0x3, 0x2, 0x2, 0x2, 0x81, 
    0x82, 0x5, 0x36, 0x1c, 0x2, 0x82, 0x19, 0x3, 0x2, 0x2, 0x2, 0x83, 0x86, 
    0x5, 0x1e, 0x10, 0x2, 0x84, 0x86, 0x5, 0x1c, 0xf, 0x2, 0x85, 0x83, 0x3, 
    0x2, 0x2, 0x2, 0x85, 0x84, 0x3, 0x2, 0x2, 0x2, 0x86, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x87, 0x88, 0x7, 0xb, 0x2, 0x2, 0x88, 0x89, 0x7, 0x7, 0x2, 
    0x2, 0x89, 0x8a, 0x7, 0x5, 0x2, 0x2, 0x8a, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x8b, 0x8c, 0x7, 0xb, 0x2, 0x2, 0x8c, 0x8e, 0x7, 0x7, 0x2, 0x2, 0x8d, 
    0x8f, 0x5, 0x20, 0x11, 0x2, 0x8e, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 
    0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x5, 
    0x22, 0x12, 0x2, 0x91, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x7, 0xc, 
    0x2, 0x2, 0x93, 0x94, 0x5, 0x2e, 0x18, 0x2, 0x94, 0x21, 0x3, 0x2, 0x2, 
    0x2, 0x95, 0x99, 0x7, 0x8, 0x2, 0x2, 0x96, 0x98, 0x5, 0x24, 0x13, 0x2, 
    0x97, 0x96, 0x3, 0x2, 0x2, 0x2, 0x98, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x99, 
    0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9c, 
    0x3, 0x2, 0x2, 0x2, 0x9b, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 
    0x9, 0x2, 0x2, 0x9d, 0x23, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x5, 0x26, 
    0x14, 0x2, 0x9f, 0x25, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x5, 0x38, 0x1d, 
    0x2, 0xa1, 0xa2, 0x7, 0x7, 0x2, 0x2, 0xa2, 0xa4, 0x7, 0xd, 0x2, 0x2, 
    0xa3, 0xa5, 0x5, 0x28, 0x15, 0x2, 0xa4, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa4, 
    0xa5, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 
    0x7, 0xe, 0x2, 0x2, 0xa7, 0xa8, 0x7, 0x5, 0x2, 0x2, 0xa8, 0x27, 0x3, 
    0x2, 0x2, 0x2, 0xa9, 0xae, 0x5, 0x2a, 0x16, 0x2, 0xaa, 0xab, 0x7, 0xf, 
    0x2, 0x2, 0xab, 0xad, 0x5, 0x2a, 0x16, 0x2, 0xac, 0xaa, 0x3, 0x2, 0x2, 
    0x2, 0xad, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xae, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0xae, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xaf, 0x29, 0x3, 0x2, 0x2, 0x2, 0xb0, 
    0xae, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb3, 0x5, 0x2c, 0x17, 0x2, 0xb2, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x3, 
    0x2, 0x2, 0x2, 0xb4, 0xb5, 0x5, 0x3c, 0x1f, 0x2, 0xb5, 0xb6, 0x7, 0x7, 
    0x2, 0x2, 0xb6, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x7, 0x10, 0x2, 
    0x2, 0xb8, 0xb9, 0x7, 0x11, 0x2, 0x2, 0xb9, 0xc3, 0x7, 0x12, 0x2, 0x2, 
    0xba, 0xbb, 0x7, 0x10, 0x2, 0x2, 0xbb, 0xbc, 0x7, 0x13, 0x2, 0x2, 0xbc, 
    0xc3, 0x7, 0x12, 0x2, 0x2, 0xbd, 0xbe, 0x7, 0x10, 0x2, 0x2, 0xbe, 0xbf, 
    0x7, 0x11, 0x2, 0x2, 0xbf, 0xc0, 0x7, 0xf, 0x2, 0x2, 0xc0, 0xc1, 0x7, 
    0x13, 0x2, 0x2, 0xc1, 0xc3, 0x7, 0x12, 0x2, 0x2, 0xc2, 0xb7, 0x3, 0x2, 
    0x2, 0x2, 0xc2, 0xba, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xbd, 0x3, 0x2, 0x2, 
    0x2, 0xc3, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc6, 0x5, 0x34, 0x1b, 0x2, 
    0xc5, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 
    0xc7, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x7, 0x7, 0x2, 0x2, 0xc8, 0xc9, 
    0x5, 0x30, 0x19, 0x2, 0xc9, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcc, 0x5, 
    0x32, 0x1a, 0x2, 0xcb, 0xca, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 
    0x2, 0x2, 0xcc, 0x31, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x5, 0x34, 0x1b, 
    0x2, 0xce, 0xcf, 0x7, 0x7, 0x2, 0x2, 0xcf, 0x33, 0x3, 0x2, 0x2, 0x2, 
    0xd0, 0xd1, 0x7, 0xc, 0x2, 0x2, 0xd1, 0xd2, 0x7, 0xc, 0x2, 0x2, 0xd2, 
    0x35, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0x5, 0x38, 0x1d, 0x2, 0xd4, 0xd5, 
    0x7, 0x7, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0x5, 0x2, 0x2, 0xd6, 0x37, 0x3, 
    0x2, 0x2, 0x2, 0xd7, 0xd9, 0x5, 0x3a, 0x1e, 0x2, 0xd8, 0xd7, 0x3, 0x2, 
    0x2, 0x2, 0xd8, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 0x2, 0x2, 
    0x2, 0xda, 0xdb, 0x5, 0x3c, 0x1f, 0x2, 0xdb, 0x39, 0x3, 0x2, 0x2, 0x2, 
    0xdc, 0xdd, 0x7, 0x14, 0x2, 0x2, 0xdd, 0x3b, 0x3, 0x2, 0x2, 0x2, 0xde, 
    0xe4, 0x5, 0x3e, 0x20, 0x2, 0xdf, 0xe1, 0x7, 0x15, 0x2, 0x2, 0xe0, 0xdf, 
    0x3, 0x2, 0x2, 0x2, 0xe1, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe0, 0x3, 
    0x2, 0x2, 0x2, 0xe2, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe5, 0x3, 0x2, 
    0x2, 0x2, 0xe4, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe5, 0x3, 0x2, 0x2, 
    0x2, 0xe5, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xeb, 0x5, 0x42, 0x22, 0x2, 
    0xe7, 0xeb, 0x5, 0x44, 0x23, 0x2, 0xe8, 0xeb, 0x5, 0x40, 0x21, 0x2, 
    0xe9, 0xeb, 0x7, 0x7, 0x2, 0x2, 0xea, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xea, 
    0xe7, 0x3, 0x2, 0x2, 0x2, 0xea, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xea, 0xe9, 
    0x3, 0x2, 0x2, 0x2, 0xeb, 0x3f, 0x3, 0x2, 0x2, 0x2, 0xec, 0xed, 0x9, 
    0x2, 0x2, 0x2, 0xed, 0x41, 0x3, 0x2, 0x2, 0x2, 0xee, 0xef, 0x9, 0x3, 
    0x2, 0x2, 0xef, 0x43, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf1, 0x9, 0x4, 0x2, 
    0x2, 0xf1, 0x45, 0x3, 0x2, 0x2, 0x2, 0x16, 0x47, 0x4e, 0x54, 0x62, 0x6a, 
    0x6e, 0x7c, 0x85, 0x8e, 0x99, 0xa4, 0xae, 0xb2, 0xc2, 0xc5, 0xcb, 0xd8, 
    0xe2, 0xe4, 0xea, 
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
