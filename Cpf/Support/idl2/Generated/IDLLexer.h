
// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    IMPORT = 1, NAMESPACE = 2, STRUCT = 3, INTERFACE = 4, IN = 5, OUT = 6, 
    COLON = 7, SEMICOLON = 8, STAR = 9, DOT = 10, COMMA = 11, QUOTE = 12, 
    LBRACE = 13, RBRACE = 14, LPAREN = 15, RPAREN = 16, LBRACKET = 17, RBRACKET = 18, 
    LT = 19, GT = 20, CONST = 21, VOID = 22, RESULT = 23, U8 = 24, S8 = 25, 
    U16 = 26, S16 = 27, U32 = 28, S32 = 29, U64 = 30, S64 = 31, F32 = 32, 
    F64 = 33, BYTE = 34, CHAR = 35, SHORT = 36, LONG = 37, INT = 38, FLOAT = 39, 
    DOUBLE = 40, IDENT = 41, NUMERIC_LIT = 42, DECIMAL_LIT = 43, HEX_LIT = 44, 
    OCT_LIT = 45, BIN_LIT = 46, STRING_LIT = 47, FLOAT_LIT = 48, WHITE_SPACE = 49, 
    BLOCK_COMMENT = 50, LINE_COMMENT = 51
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

