
// Generated from MITScript.g by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  MITScript : public antlr4::Lexer {
public:
  enum {
    INT_CONSTANT = 1, TRUE_KEY = 2, FALSE_KEY = 3, BOOL_CONSTANT = 4, NONE_CONSTANT = 5, 
    ADD_KEY = 6, SUB_KEY = 7, MUL_KEY = 8, EQ_KEY = 9, LT_KEY = 10, ASSIGN_KEY = 11, 
    IF_KEY = 12, SCOLON_KEY = 13, OPAREN_KEY = 14, CPAREN_KEY = 15, OBRACK_KEY = 16, 
    CBRACK_KEY = 17, NAME = 18, COMMENT = 19, WHITESPACE = 20, ERROR = 21
  };

  MITScript(antlr4::CharStream *input);
  ~MITScript();

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

