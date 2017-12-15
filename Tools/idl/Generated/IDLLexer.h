
// Generated from C:/Projects/cpf_dev/CPF/Tools/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, DEFAULT = 5, UNION = 6, 
    EVENT = 7, CALLBACK = 8, INTERFACE = 9, ENUM = 10, FLAGS = 11, MODULE = 12, 
    FROM = 13, AS = 14, In = 15, Out = 16, COLON = 17, SEMICOLON = 18, STAR = 19, 
    SLASH = 20, DOT = 21, COMMA = 22, EQUALS = 23, QUOTE = 24, SQUOTE = 25, 
    LBRACE = 26, RBRACE = 27, LPAREN = 28, RPAREN = 29, LBRACKET = 30, RBRACKET = 31, 
    LT = 32, GT = 33, PLUS = 34, MINUS = 35, LSHIFT = 36, RSHIFT = 37, PIPE = 38, 
    Const = 39, Void = 40, RESULT = 41, SUCCESS = 42, FAILURE = 43, CLASS_ID = 44, 
    STRING = 45, U8 = 46, S8 = 47, U16 = 48, S16 = 49, U32 = 50, S32 = 51, 
    U64 = 52, S64 = 53, F32 = 54, F64 = 55, IDENT = 56, DECIMAL_LIT = 57, 
    HEX_LIT = 58, BIN_LIT = 59, OCT_LIT = 60, STRING_LIT = 61, CHAR_LIT = 62, 
    FLOAT_LIT = 63, WHITE_SPACE = 64, BLOCK_COMMENT = 65, LINE_COMMENT = 66
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

