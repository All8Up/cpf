
// Generated from C:/Projects/cpf/Cpf/Support/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    IMPORT = 1, NAMESPACE = 2, STRUCT = 3, INTERFACE = 4, ENUM = 5, MODULE = 6, 
    FROM = 7, IN = 8, OUT = 9, COLON = 10, SEMICOLON = 11, STAR = 12, SLASH = 13, 
    DOT = 14, COMMA = 15, EQUALS = 16, QUOTE = 17, LBRACE = 18, RBRACE = 19, 
    LPAREN = 20, RPAREN = 21, LBRACKET = 22, RBRACKET = 23, LT = 24, GT = 25, 
    PLUS = 26, MINUS = 27, LSHIFT = 28, RSHIFT = 29, CONST = 30, VOID = 31, 
    RESULT = 32, SUCCESS = 33, FAILURE = 34, CLASS_ID = 35, STRING = 36, 
    U8 = 37, S8 = 38, U16 = 39, S16 = 40, U32 = 41, S32 = 42, U64 = 43, 
    S64 = 44, F32 = 45, F64 = 46, IDENT = 47, DECIMAL_LIT = 48, HEX_LIT = 49, 
    BIN_LIT = 50, OCT_LIT = 51, STRING_LIT = 52, FLOAT_LIT = 53, WHITE_SPACE = 54, 
    BLOCK_COMMENT = 55, LINE_COMMENT = 56
  };

  IDLLexer(antlr4::CharStream *input);
  ~IDLLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

