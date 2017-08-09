
// Generated from C:/Projects/cpf/Cpf/Support/idl\IDLLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLLexer : public antlr4::Lexer {
public:
  enum {
    IMPORT = 1, NAMESPACE = 2, STRUCT = 3, INTERFACE = 4, ENUM = 5, IN = 6, 
    OUT = 7, COLON = 8, SEMICOLON = 9, STAR = 10, DOT = 11, COMMA = 12, 
    EQUALS = 13, QUOTE = 14, LBRACE = 15, RBRACE = 16, LPAREN = 17, RPAREN = 18, 
    LBRACKET = 19, RBRACKET = 20, LT = 21, GT = 22, CONST = 23, VOID = 24, 
    RESULT = 25, CLASS_ID = 26, STRING = 27, U8 = 28, S8 = 29, U16 = 30, 
    S16 = 31, U32 = 32, S32 = 33, U64 = 34, S64 = 35, F32 = 36, F64 = 37, 
    IDENT = 38, DECIMAL_LIT = 39, HEX_LIT = 40, OCT_LIT = 41, BIN_LIT = 42, 
    STRING_LIT = 43, FLOAT_LIT = 44, WHITE_SPACE = 45, BLOCK_COMMENT = 46, 
    LINE_COMMENT = 47
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

