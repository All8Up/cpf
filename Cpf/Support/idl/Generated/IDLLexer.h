
// Generated from C:/Projects/cpf/Cpf/Support/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, DEFAULT = 5, UNION = 6, 
    INTERFACE = 7, ENUM = 8, FLAGS = 9, MODULE = 10, FROM = 11, IN = 12, 
    OUT = 13, COLON = 14, SEMICOLON = 15, STAR = 16, SLASH = 17, DOT = 18, 
    COMMA = 19, EQUALS = 20, QUOTE = 21, LBRACE = 22, RBRACE = 23, LPAREN = 24, 
    RPAREN = 25, LBRACKET = 26, RBRACKET = 27, LT = 28, GT = 29, PLUS = 30, 
    MINUS = 31, LSHIFT = 32, RSHIFT = 33, PIPE = 34, Const = 35, Void = 36, 
    RESULT = 37, SUCCESS = 38, FAILURE = 39, CLASS_ID = 40, STRING = 41, 
    U8 = 42, S8 = 43, U16 = 44, S16 = 45, U32 = 46, S32 = 47, U64 = 48, 
    S64 = 49, F32 = 50, F64 = 51, IDENT = 52, DECIMAL_LIT = 53, HEX_LIT = 54, 
    BIN_LIT = 55, OCT_LIT = 56, STRING_LIT = 57, FLOAT_LIT = 58, WHITE_SPACE = 59, 
    BLOCK_COMMENT = 60, LINE_COMMENT = 61
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

