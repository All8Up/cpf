
// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    IMPORT = 1, NAMESPACE = 2, STRUCT = 3, INTERFACE = 4, ENUM = 5, IN = 6, 
    OUT = 7, COLON = 8, SEMICOLON = 9, STAR = 10, DOT = 11, COMMA = 12, 
    EQUALS = 13, QUOTE = 14, LBRACE = 15, RBRACE = 16, LPAREN = 17, RPAREN = 18, 
    LBRACKET = 19, RBRACKET = 20, LT = 21, GT = 22, CONST = 23, VOID = 24, 
    RESULT = 25, CLASS_ID = 26, U8 = 27, S8 = 28, U16 = 29, S16 = 30, U32 = 31, 
    S32 = 32, U64 = 33, S64 = 34, F32 = 35, F64 = 36, BYTE = 37, CHAR = 38, 
    SHORT = 39, LONG = 40, INT = 41, FLOAT = 42, DOUBLE = 43, STRING = 44, 
    IDENT = 45, DECIMAL_LIT = 46, HEX_LIT = 47, OCT_LIT = 48, BIN_LIT = 49, 
    STRING_LIT = 50, FLOAT_LIT = 51, WHITE_SPACE = 52, BLOCK_COMMENT = 53, 
    LINE_COMMENT = 54
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

