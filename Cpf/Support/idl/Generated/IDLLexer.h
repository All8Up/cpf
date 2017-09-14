
// Generated from C:/Projects/cpf/Cpf/Support/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    IMPORT = 1, STRUCT = 2, INTERFACE = 3, ENUM = 4, MODULE = 5, FROM = 6, 
    IN = 7, OUT = 8, COLON = 9, SEMICOLON = 10, STAR = 11, SLASH = 12, DOT = 13, 
    COMMA = 14, EQUALS = 15, QUOTE = 16, LBRACE = 17, RBRACE = 18, LPAREN = 19, 
    RPAREN = 20, LBRACKET = 21, RBRACKET = 22, LT = 23, GT = 24, PLUS = 25, 
    MINUS = 26, LSHIFT = 27, RSHIFT = 28, Const = 29, Void = 30, RESULT = 31, 
    SUCCESS = 32, FAILURE = 33, CLASS_ID = 34, STRING = 35, U8 = 36, S8 = 37, 
    U16 = 38, S16 = 39, U32 = 40, S32 = 41, U64 = 42, S64 = 43, F32 = 44, 
    F64 = 45, IDENT = 46, DECIMAL_LIT = 47, HEX_LIT = 48, BIN_LIT = 49, 
    OCT_LIT = 50, STRING_LIT = 51, FLOAT_LIT = 52, WHITE_SPACE = 53, BLOCK_COMMENT = 54, 
    LINE_COMMENT = 55
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

