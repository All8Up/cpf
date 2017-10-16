
// Generated from C:/Projects/Cpf/Tools/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, DEFAULT = 5, UNION = 6, 
    INTERFACE = 7, ENUM = 8, FLAGS = 9, MODULE = 10, FROM = 11, AS = 12, 
    IN = 13, OUT = 14, COLON = 15, SEMICOLON = 16, STAR = 17, SLASH = 18, 
    DOT = 19, COMMA = 20, EQUALS = 21, QUOTE = 22, SQUOTE = 23, LBRACE = 24, 
    RBRACE = 25, LPAREN = 26, RPAREN = 27, LBRACKET = 28, RBRACKET = 29, 
    LT = 30, GT = 31, PLUS = 32, MINUS = 33, LSHIFT = 34, RSHIFT = 35, PIPE = 36, 
    Const = 37, Void = 38, RESULT = 39, SUCCESS = 40, FAILURE = 41, CLASS_ID = 42, 
    STRING = 43, U8 = 44, S8 = 45, U16 = 46, S16 = 47, U32 = 48, S32 = 49, 
    U64 = 50, S64 = 51, F32 = 52, F64 = 53, IDENT = 54, DECIMAL_LIT = 55, 
    HEX_LIT = 56, BIN_LIT = 57, OCT_LIT = 58, STRING_LIT = 59, CHAR_LIT = 60, 
    FLOAT_LIT = 61, WHITE_SPACE = 62, BLOCK_COMMENT = 63, LINE_COMMENT = 64
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

