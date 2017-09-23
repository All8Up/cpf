
// Generated from C:/Projects/Cpf/Cpf/Support/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, DEFAULT = 5, UNION = 6, 
    INTERFACE = 7, ENUM = 8, FLAGS = 9, MODULE = 10, FROM = 11, AS = 12, 
    IN = 13, OUT = 14, COLON = 15, SEMICOLON = 16, STAR = 17, SLASH = 18, 
    DOT = 19, COMMA = 20, EQUALS = 21, QUOTE = 22, LBRACE = 23, RBRACE = 24, 
    LPAREN = 25, RPAREN = 26, LBRACKET = 27, RBRACKET = 28, LT = 29, GT = 30, 
    PLUS = 31, MINUS = 32, LSHIFT = 33, RSHIFT = 34, PIPE = 35, Const = 36, 
    Void = 37, RESULT = 38, SUCCESS = 39, FAILURE = 40, CLASS_ID = 41, STRING = 42, 
    U8 = 43, S8 = 44, U16 = 45, S16 = 46, U32 = 47, S32 = 48, U64 = 49, 
    S64 = 50, F32 = 51, F64 = 52, IDENT = 53, DECIMAL_LIT = 54, HEX_LIT = 55, 
    BIN_LIT = 56, OCT_LIT = 57, STRING_LIT = 58, FLOAT_LIT = 59, WHITE_SPACE = 60, 
    BLOCK_COMMENT = 61, LINE_COMMENT = 62
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

