
// Generated from C:/Projects/Cpf/Cpf/Support/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, UNION = 5, INTERFACE = 6, 
    ENUM = 7, MODULE = 8, FROM = 9, IN = 10, OUT = 11, COLON = 12, SEMICOLON = 13, 
    STAR = 14, SLASH = 15, DOT = 16, COMMA = 17, EQUALS = 18, QUOTE = 19, 
    LBRACE = 20, RBRACE = 21, LPAREN = 22, RPAREN = 23, LBRACKET = 24, RBRACKET = 25, 
    LT = 26, GT = 27, PLUS = 28, MINUS = 29, LSHIFT = 30, RSHIFT = 31, Const = 32, 
    Void = 33, RESULT = 34, SUCCESS = 35, FAILURE = 36, CLASS_ID = 37, STRING = 38, 
    U8 = 39, S8 = 40, U16 = 41, S16 = 42, U32 = 43, S32 = 44, U64 = 45, 
    S64 = 46, F32 = 47, F64 = 48, IDENT = 49, DECIMAL_LIT = 50, HEX_LIT = 51, 
    BIN_LIT = 52, OCT_LIT = 53, STRING_LIT = 54, FLOAT_LIT = 55, WHITE_SPACE = 56, 
    BLOCK_COMMENT = 57, LINE_COMMENT = 58
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

