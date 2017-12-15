
// Generated from C:/Projects/cpf_dev/CPF/Tools/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, DEFAULT = 5, UNION = 6, 
    EVENT = 7, INTERFACE = 8, ENUM = 9, FLAGS = 10, MODULE = 11, FROM = 12, 
    AS = 13, In = 14, Out = 15, COLON = 16, SEMICOLON = 17, STAR = 18, SLASH = 19, 
    DOT = 20, COMMA = 21, EQUALS = 22, QUOTE = 23, SQUOTE = 24, LBRACE = 25, 
    RBRACE = 26, LPAREN = 27, RPAREN = 28, LBRACKET = 29, RBRACKET = 30, 
    LT = 31, GT = 32, PLUS = 33, MINUS = 34, LSHIFT = 35, RSHIFT = 36, PIPE = 37, 
    Const = 38, Void = 39, RESULT = 40, SUCCESS = 41, FAILURE = 42, CLASS_ID = 43, 
    STRING = 44, U8 = 45, S8 = 46, U16 = 47, S16 = 48, U32 = 49, S32 = 50, 
    U64 = 51, S64 = 52, F32 = 53, F64 = 54, IDENT = 55, DECIMAL_LIT = 56, 
    HEX_LIT = 57, BIN_LIT = 58, OCT_LIT = 59, STRING_LIT = 60, CHAR_LIT = 61, 
    FLOAT_LIT = 62, WHITE_SPACE = 63, BLOCK_COMMENT = 64, LINE_COMMENT = 65
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

