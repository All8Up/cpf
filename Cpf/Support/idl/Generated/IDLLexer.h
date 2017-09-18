
// Generated from C:/Projects/Cpf/Cpf/Support/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, UNION = 5, INTERFACE = 6, 
    ENUM = 7, FLAGS = 8, MODULE = 9, FROM = 10, IN = 11, OUT = 12, COLON = 13, 
    SEMICOLON = 14, STAR = 15, SLASH = 16, DOT = 17, COMMA = 18, EQUALS = 19, 
    QUOTE = 20, LBRACE = 21, RBRACE = 22, LPAREN = 23, RPAREN = 24, LBRACKET = 25, 
    RBRACKET = 26, LT = 27, GT = 28, PLUS = 29, MINUS = 30, LSHIFT = 31, 
    RSHIFT = 32, PIPE = 33, Const = 34, Void = 35, RESULT = 36, SUCCESS = 37, 
    FAILURE = 38, CLASS_ID = 39, STRING = 40, U8 = 41, S8 = 42, U16 = 43, 
    S16 = 44, U32 = 45, S32 = 46, U64 = 47, S64 = 48, F32 = 49, F64 = 50, 
    IDENT = 51, DECIMAL_LIT = 52, HEX_LIT = 53, BIN_LIT = 54, OCT_LIT = 55, 
    STRING_LIT = 56, FLOAT_LIT = 57, WHITE_SPACE = 58, BLOCK_COMMENT = 59, 
    LINE_COMMENT = 60
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

