
// Generated from EcoBot.g4 by ANTLR 4.13.2


#include "EcoBotListener.h"

#include "EcoBotParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct EcoBotParserStaticData final {
  EcoBotParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  EcoBotParserStaticData(const EcoBotParserStaticData&) = delete;
  EcoBotParserStaticData(EcoBotParserStaticData&&) = delete;
  EcoBotParserStaticData& operator=(const EcoBotParserStaticData&) = delete;
  EcoBotParserStaticData& operator=(EcoBotParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ecobotParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<EcoBotParserStaticData> ecobotParserStaticData = nullptr;

void ecobotParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ecobotParserStaticData != nullptr) {
    return;
  }
#else
  assert(ecobotParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<EcoBotParserStaticData>(
    std::vector<std::string>{
      "program", "intentDef", "stmtList", "stmt", "replyStmt", "requireStmt", 
      "callStmt", "serviceCall", "ifStmt", "exitStmt", "block", "condition", 
      "value", "argList"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "';'", "'='", "'.'", "'('", "')'", "'=='", "'!='", 
      "'>'", "'<'", "','", "'intent'", "'reply'", "'require'", "'call'", 
      "'if'", "'else'", "'exit'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "K_INTENT", "K_REPLY", 
      "K_REQUIRE", "K_CALL", "K_IF", "K_ELSE", "K_EXIT", "ID", "STRING", 
      "WS", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,23,124,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,1,0,5,0,
  	30,8,0,10,0,12,0,33,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,5,2,44,8,
  	2,10,2,12,2,47,9,2,1,3,1,3,1,3,1,3,1,3,3,3,54,8,3,1,4,1,4,1,4,1,4,1,5,
  	1,5,1,5,1,5,1,5,1,6,1,6,3,6,67,8,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,
  	7,3,7,78,8,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	5,8,94,8,8,10,8,12,8,97,9,8,1,8,1,8,3,8,101,8,8,1,9,1,9,1,9,1,10,1,10,
  	1,10,1,10,1,11,1,11,1,11,1,11,1,12,1,12,1,13,1,13,1,13,5,13,119,8,13,
  	10,13,12,13,122,9,13,1,13,0,0,14,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	0,2,1,0,8,11,1,0,20,21,120,0,31,1,0,0,0,2,36,1,0,0,0,4,45,1,0,0,0,6,53,
  	1,0,0,0,8,55,1,0,0,0,10,59,1,0,0,0,12,66,1,0,0,0,14,72,1,0,0,0,16,81,
  	1,0,0,0,18,102,1,0,0,0,20,105,1,0,0,0,22,109,1,0,0,0,24,113,1,0,0,0,26,
  	115,1,0,0,0,28,30,3,2,1,0,29,28,1,0,0,0,30,33,1,0,0,0,31,29,1,0,0,0,31,
  	32,1,0,0,0,32,34,1,0,0,0,33,31,1,0,0,0,34,35,5,0,0,1,35,1,1,0,0,0,36,
  	37,5,13,0,0,37,38,5,20,0,0,38,39,5,1,0,0,39,40,3,4,2,0,40,41,5,2,0,0,
  	41,3,1,0,0,0,42,44,3,6,3,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,0,0,
  	45,46,1,0,0,0,46,5,1,0,0,0,47,45,1,0,0,0,48,54,3,8,4,0,49,54,3,10,5,0,
  	50,54,3,12,6,0,51,54,3,16,8,0,52,54,3,18,9,0,53,48,1,0,0,0,53,49,1,0,
  	0,0,53,50,1,0,0,0,53,51,1,0,0,0,53,52,1,0,0,0,54,7,1,0,0,0,55,56,5,14,
  	0,0,56,57,5,21,0,0,57,58,5,3,0,0,58,9,1,0,0,0,59,60,5,15,0,0,60,61,5,
  	20,0,0,61,62,5,21,0,0,62,63,5,3,0,0,63,11,1,0,0,0,64,65,5,20,0,0,65,67,
  	5,4,0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,68,1,0,0,0,68,69,5,16,0,0,69,70,
  	3,14,7,0,70,71,5,3,0,0,71,13,1,0,0,0,72,73,5,20,0,0,73,74,5,5,0,0,74,
  	75,5,20,0,0,75,77,5,6,0,0,76,78,3,26,13,0,77,76,1,0,0,0,77,78,1,0,0,0,
  	78,79,1,0,0,0,79,80,5,7,0,0,80,15,1,0,0,0,81,82,5,17,0,0,82,83,5,6,0,
  	0,83,84,3,22,11,0,84,85,5,7,0,0,85,95,3,20,10,0,86,87,5,18,0,0,87,88,
  	5,17,0,0,88,89,5,6,0,0,89,90,3,22,11,0,90,91,5,7,0,0,91,92,3,20,10,0,
  	92,94,1,0,0,0,93,86,1,0,0,0,94,97,1,0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,
  	96,100,1,0,0,0,97,95,1,0,0,0,98,99,5,18,0,0,99,101,3,20,10,0,100,98,1,
  	0,0,0,100,101,1,0,0,0,101,17,1,0,0,0,102,103,5,19,0,0,103,104,5,3,0,0,
  	104,19,1,0,0,0,105,106,5,1,0,0,106,107,3,4,2,0,107,108,5,2,0,0,108,21,
  	1,0,0,0,109,110,5,20,0,0,110,111,7,0,0,0,111,112,3,24,12,0,112,23,1,0,
  	0,0,113,114,7,1,0,0,114,25,1,0,0,0,115,120,5,20,0,0,116,117,5,12,0,0,
  	117,119,5,20,0,0,118,116,1,0,0,0,119,122,1,0,0,0,120,118,1,0,0,0,120,
  	121,1,0,0,0,121,27,1,0,0,0,122,120,1,0,0,0,8,31,45,53,66,77,95,100,120
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ecobotParserStaticData = std::move(staticData);
}

}

EcoBotParser::EcoBotParser(TokenStream *input) : EcoBotParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

EcoBotParser::EcoBotParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  EcoBotParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ecobotParserStaticData->atn, ecobotParserStaticData->decisionToDFA, ecobotParserStaticData->sharedContextCache, options);
}

EcoBotParser::~EcoBotParser() {
  delete _interpreter;
}

const atn::ATN& EcoBotParser::getATN() const {
  return *ecobotParserStaticData->atn;
}

std::string EcoBotParser::getGrammarFileName() const {
  return "EcoBot.g4";
}

const std::vector<std::string>& EcoBotParser::getRuleNames() const {
  return ecobotParserStaticData->ruleNames;
}

const dfa::Vocabulary& EcoBotParser::getVocabulary() const {
  return ecobotParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView EcoBotParser::getSerializedATN() const {
  return ecobotParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

EcoBotParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::ProgramContext::EOF() {
  return getToken(EcoBotParser::EOF, 0);
}

std::vector<EcoBotParser::IntentDefContext *> EcoBotParser::ProgramContext::intentDef() {
  return getRuleContexts<EcoBotParser::IntentDefContext>();
}

EcoBotParser::IntentDefContext* EcoBotParser::ProgramContext::intentDef(size_t i) {
  return getRuleContext<EcoBotParser::IntentDefContext>(i);
}


size_t EcoBotParser::ProgramContext::getRuleIndex() const {
  return EcoBotParser::RuleProgram;
}

void EcoBotParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void EcoBotParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

EcoBotParser::ProgramContext* EcoBotParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, EcoBotParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(31);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == EcoBotParser::K_INTENT) {
      setState(28);
      intentDef();
      setState(33);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(34);
    match(EcoBotParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntentDefContext ------------------------------------------------------------------

EcoBotParser::IntentDefContext::IntentDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::IntentDefContext::K_INTENT() {
  return getToken(EcoBotParser::K_INTENT, 0);
}

tree::TerminalNode* EcoBotParser::IntentDefContext::ID() {
  return getToken(EcoBotParser::ID, 0);
}

EcoBotParser::StmtListContext* EcoBotParser::IntentDefContext::stmtList() {
  return getRuleContext<EcoBotParser::StmtListContext>(0);
}


size_t EcoBotParser::IntentDefContext::getRuleIndex() const {
  return EcoBotParser::RuleIntentDef;
}

void EcoBotParser::IntentDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntentDef(this);
}

void EcoBotParser::IntentDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntentDef(this);
}

EcoBotParser::IntentDefContext* EcoBotParser::intentDef() {
  IntentDefContext *_localctx = _tracker.createInstance<IntentDefContext>(_ctx, getState());
  enterRule(_localctx, 2, EcoBotParser::RuleIntentDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    match(EcoBotParser::K_INTENT);
    setState(37);
    match(EcoBotParser::ID);
    setState(38);
    match(EcoBotParser::T__0);
    setState(39);
    stmtList();
    setState(40);
    match(EcoBotParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtListContext ------------------------------------------------------------------

EcoBotParser::StmtListContext::StmtListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EcoBotParser::StmtContext *> EcoBotParser::StmtListContext::stmt() {
  return getRuleContexts<EcoBotParser::StmtContext>();
}

EcoBotParser::StmtContext* EcoBotParser::StmtListContext::stmt(size_t i) {
  return getRuleContext<EcoBotParser::StmtContext>(i);
}


size_t EcoBotParser::StmtListContext::getRuleIndex() const {
  return EcoBotParser::RuleStmtList;
}

void EcoBotParser::StmtListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtList(this);
}

void EcoBotParser::StmtListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtList(this);
}

EcoBotParser::StmtListContext* EcoBotParser::stmtList() {
  StmtListContext *_localctx = _tracker.createInstance<StmtListContext>(_ctx, getState());
  enterRule(_localctx, 4, EcoBotParser::RuleStmtList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1818624) != 0)) {
      setState(42);
      stmt();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

EcoBotParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EcoBotParser::ReplyStmtContext* EcoBotParser::StmtContext::replyStmt() {
  return getRuleContext<EcoBotParser::ReplyStmtContext>(0);
}

EcoBotParser::RequireStmtContext* EcoBotParser::StmtContext::requireStmt() {
  return getRuleContext<EcoBotParser::RequireStmtContext>(0);
}

EcoBotParser::CallStmtContext* EcoBotParser::StmtContext::callStmt() {
  return getRuleContext<EcoBotParser::CallStmtContext>(0);
}

EcoBotParser::IfStmtContext* EcoBotParser::StmtContext::ifStmt() {
  return getRuleContext<EcoBotParser::IfStmtContext>(0);
}

EcoBotParser::ExitStmtContext* EcoBotParser::StmtContext::exitStmt() {
  return getRuleContext<EcoBotParser::ExitStmtContext>(0);
}


size_t EcoBotParser::StmtContext::getRuleIndex() const {
  return EcoBotParser::RuleStmt;
}

void EcoBotParser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void EcoBotParser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}

EcoBotParser::StmtContext* EcoBotParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 6, EcoBotParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(53);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case EcoBotParser::K_REPLY: {
        enterOuterAlt(_localctx, 1);
        setState(48);
        replyStmt();
        break;
      }

      case EcoBotParser::K_REQUIRE: {
        enterOuterAlt(_localctx, 2);
        setState(49);
        requireStmt();
        break;
      }

      case EcoBotParser::K_CALL:
      case EcoBotParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(50);
        callStmt();
        break;
      }

      case EcoBotParser::K_IF: {
        enterOuterAlt(_localctx, 4);
        setState(51);
        ifStmt();
        break;
      }

      case EcoBotParser::K_EXIT: {
        enterOuterAlt(_localctx, 5);
        setState(52);
        exitStmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplyStmtContext ------------------------------------------------------------------

EcoBotParser::ReplyStmtContext::ReplyStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::ReplyStmtContext::K_REPLY() {
  return getToken(EcoBotParser::K_REPLY, 0);
}

tree::TerminalNode* EcoBotParser::ReplyStmtContext::STRING() {
  return getToken(EcoBotParser::STRING, 0);
}


size_t EcoBotParser::ReplyStmtContext::getRuleIndex() const {
  return EcoBotParser::RuleReplyStmt;
}

void EcoBotParser::ReplyStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReplyStmt(this);
}

void EcoBotParser::ReplyStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReplyStmt(this);
}

EcoBotParser::ReplyStmtContext* EcoBotParser::replyStmt() {
  ReplyStmtContext *_localctx = _tracker.createInstance<ReplyStmtContext>(_ctx, getState());
  enterRule(_localctx, 8, EcoBotParser::RuleReplyStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(55);
    match(EcoBotParser::K_REPLY);
    setState(56);
    match(EcoBotParser::STRING);
    setState(57);
    match(EcoBotParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RequireStmtContext ------------------------------------------------------------------

EcoBotParser::RequireStmtContext::RequireStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::RequireStmtContext::K_REQUIRE() {
  return getToken(EcoBotParser::K_REQUIRE, 0);
}

tree::TerminalNode* EcoBotParser::RequireStmtContext::ID() {
  return getToken(EcoBotParser::ID, 0);
}

tree::TerminalNode* EcoBotParser::RequireStmtContext::STRING() {
  return getToken(EcoBotParser::STRING, 0);
}


size_t EcoBotParser::RequireStmtContext::getRuleIndex() const {
  return EcoBotParser::RuleRequireStmt;
}

void EcoBotParser::RequireStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRequireStmt(this);
}

void EcoBotParser::RequireStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRequireStmt(this);
}

EcoBotParser::RequireStmtContext* EcoBotParser::requireStmt() {
  RequireStmtContext *_localctx = _tracker.createInstance<RequireStmtContext>(_ctx, getState());
  enterRule(_localctx, 10, EcoBotParser::RuleRequireStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(EcoBotParser::K_REQUIRE);
    setState(60);
    match(EcoBotParser::ID);
    setState(61);
    match(EcoBotParser::STRING);
    setState(62);
    match(EcoBotParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallStmtContext ------------------------------------------------------------------

EcoBotParser::CallStmtContext::CallStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::CallStmtContext::K_CALL() {
  return getToken(EcoBotParser::K_CALL, 0);
}

EcoBotParser::ServiceCallContext* EcoBotParser::CallStmtContext::serviceCall() {
  return getRuleContext<EcoBotParser::ServiceCallContext>(0);
}

tree::TerminalNode* EcoBotParser::CallStmtContext::ID() {
  return getToken(EcoBotParser::ID, 0);
}


size_t EcoBotParser::CallStmtContext::getRuleIndex() const {
  return EcoBotParser::RuleCallStmt;
}

void EcoBotParser::CallStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallStmt(this);
}

void EcoBotParser::CallStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallStmt(this);
}

EcoBotParser::CallStmtContext* EcoBotParser::callStmt() {
  CallStmtContext *_localctx = _tracker.createInstance<CallStmtContext>(_ctx, getState());
  enterRule(_localctx, 12, EcoBotParser::RuleCallStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EcoBotParser::ID) {
      setState(64);
      match(EcoBotParser::ID);
      setState(65);
      match(EcoBotParser::T__3);
    }
    setState(68);
    match(EcoBotParser::K_CALL);
    setState(69);
    serviceCall();
    setState(70);
    match(EcoBotParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ServiceCallContext ------------------------------------------------------------------

EcoBotParser::ServiceCallContext::ServiceCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> EcoBotParser::ServiceCallContext::ID() {
  return getTokens(EcoBotParser::ID);
}

tree::TerminalNode* EcoBotParser::ServiceCallContext::ID(size_t i) {
  return getToken(EcoBotParser::ID, i);
}

EcoBotParser::ArgListContext* EcoBotParser::ServiceCallContext::argList() {
  return getRuleContext<EcoBotParser::ArgListContext>(0);
}


size_t EcoBotParser::ServiceCallContext::getRuleIndex() const {
  return EcoBotParser::RuleServiceCall;
}

void EcoBotParser::ServiceCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterServiceCall(this);
}

void EcoBotParser::ServiceCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitServiceCall(this);
}

EcoBotParser::ServiceCallContext* EcoBotParser::serviceCall() {
  ServiceCallContext *_localctx = _tracker.createInstance<ServiceCallContext>(_ctx, getState());
  enterRule(_localctx, 14, EcoBotParser::RuleServiceCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    match(EcoBotParser::ID);
    setState(73);
    match(EcoBotParser::T__4);
    setState(74);
    match(EcoBotParser::ID);
    setState(75);
    match(EcoBotParser::T__5);
    setState(77);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EcoBotParser::ID) {
      setState(76);
      argList();
    }
    setState(79);
    match(EcoBotParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStmtContext ------------------------------------------------------------------

EcoBotParser::IfStmtContext::IfStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> EcoBotParser::IfStmtContext::K_IF() {
  return getTokens(EcoBotParser::K_IF);
}

tree::TerminalNode* EcoBotParser::IfStmtContext::K_IF(size_t i) {
  return getToken(EcoBotParser::K_IF, i);
}

std::vector<EcoBotParser::ConditionContext *> EcoBotParser::IfStmtContext::condition() {
  return getRuleContexts<EcoBotParser::ConditionContext>();
}

EcoBotParser::ConditionContext* EcoBotParser::IfStmtContext::condition(size_t i) {
  return getRuleContext<EcoBotParser::ConditionContext>(i);
}

std::vector<EcoBotParser::BlockContext *> EcoBotParser::IfStmtContext::block() {
  return getRuleContexts<EcoBotParser::BlockContext>();
}

EcoBotParser::BlockContext* EcoBotParser::IfStmtContext::block(size_t i) {
  return getRuleContext<EcoBotParser::BlockContext>(i);
}

std::vector<tree::TerminalNode *> EcoBotParser::IfStmtContext::K_ELSE() {
  return getTokens(EcoBotParser::K_ELSE);
}

tree::TerminalNode* EcoBotParser::IfStmtContext::K_ELSE(size_t i) {
  return getToken(EcoBotParser::K_ELSE, i);
}


size_t EcoBotParser::IfStmtContext::getRuleIndex() const {
  return EcoBotParser::RuleIfStmt;
}

void EcoBotParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}

void EcoBotParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}

EcoBotParser::IfStmtContext* EcoBotParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 16, EcoBotParser::RuleIfStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(EcoBotParser::K_IF);
    setState(82);
    match(EcoBotParser::T__5);
    setState(83);
    condition();
    setState(84);
    match(EcoBotParser::T__6);
    setState(85);
    block();
    setState(95);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(86);
        match(EcoBotParser::K_ELSE);
        setState(87);
        match(EcoBotParser::K_IF);
        setState(88);
        match(EcoBotParser::T__5);
        setState(89);
        condition();
        setState(90);
        match(EcoBotParser::T__6);
        setState(91);
        block(); 
      }
      setState(97);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
    setState(100);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EcoBotParser::K_ELSE) {
      setState(98);
      match(EcoBotParser::K_ELSE);
      setState(99);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExitStmtContext ------------------------------------------------------------------

EcoBotParser::ExitStmtContext::ExitStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::ExitStmtContext::K_EXIT() {
  return getToken(EcoBotParser::K_EXIT, 0);
}


size_t EcoBotParser::ExitStmtContext::getRuleIndex() const {
  return EcoBotParser::RuleExitStmt;
}

void EcoBotParser::ExitStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExitStmt(this);
}

void EcoBotParser::ExitStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExitStmt(this);
}

EcoBotParser::ExitStmtContext* EcoBotParser::exitStmt() {
  ExitStmtContext *_localctx = _tracker.createInstance<ExitStmtContext>(_ctx, getState());
  enterRule(_localctx, 18, EcoBotParser::RuleExitStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(EcoBotParser::K_EXIT);
    setState(103);
    match(EcoBotParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

EcoBotParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EcoBotParser::StmtListContext* EcoBotParser::BlockContext::stmtList() {
  return getRuleContext<EcoBotParser::StmtListContext>(0);
}


size_t EcoBotParser::BlockContext::getRuleIndex() const {
  return EcoBotParser::RuleBlock;
}

void EcoBotParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void EcoBotParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

EcoBotParser::BlockContext* EcoBotParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 20, EcoBotParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    match(EcoBotParser::T__0);
    setState(106);
    stmtList();
    setState(107);
    match(EcoBotParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

EcoBotParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::ConditionContext::ID() {
  return getToken(EcoBotParser::ID, 0);
}

EcoBotParser::ValueContext* EcoBotParser::ConditionContext::value() {
  return getRuleContext<EcoBotParser::ValueContext>(0);
}


size_t EcoBotParser::ConditionContext::getRuleIndex() const {
  return EcoBotParser::RuleCondition;
}

void EcoBotParser::ConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition(this);
}

void EcoBotParser::ConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition(this);
}

EcoBotParser::ConditionContext* EcoBotParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 22, EcoBotParser::RuleCondition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(EcoBotParser::ID);
    setState(110);
    antlrcpp::downCast<ConditionContext *>(_localctx)->op = _input->LT(1);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3840) != 0))) {
      antlrcpp::downCast<ConditionContext *>(_localctx)->op = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(111);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

EcoBotParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EcoBotParser::ValueContext::ID() {
  return getToken(EcoBotParser::ID, 0);
}

tree::TerminalNode* EcoBotParser::ValueContext::STRING() {
  return getToken(EcoBotParser::STRING, 0);
}


size_t EcoBotParser::ValueContext::getRuleIndex() const {
  return EcoBotParser::RuleValue;
}

void EcoBotParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void EcoBotParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

EcoBotParser::ValueContext* EcoBotParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 24, EcoBotParser::RuleValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    _la = _input->LA(1);
    if (!(_la == EcoBotParser::ID

    || _la == EcoBotParser::STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgListContext ------------------------------------------------------------------

EcoBotParser::ArgListContext::ArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> EcoBotParser::ArgListContext::ID() {
  return getTokens(EcoBotParser::ID);
}

tree::TerminalNode* EcoBotParser::ArgListContext::ID(size_t i) {
  return getToken(EcoBotParser::ID, i);
}


size_t EcoBotParser::ArgListContext::getRuleIndex() const {
  return EcoBotParser::RuleArgList;
}

void EcoBotParser::ArgListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgList(this);
}

void EcoBotParser::ArgListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EcoBotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgList(this);
}

EcoBotParser::ArgListContext* EcoBotParser::argList() {
  ArgListContext *_localctx = _tracker.createInstance<ArgListContext>(_ctx, getState());
  enterRule(_localctx, 26, EcoBotParser::RuleArgList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    match(EcoBotParser::ID);
    setState(120);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == EcoBotParser::T__11) {
      setState(116);
      match(EcoBotParser::T__11);
      setState(117);
      match(EcoBotParser::ID);
      setState(122);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void EcoBotParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ecobotParserInitialize();
#else
  ::antlr4::internal::call_once(ecobotParserOnceFlag, ecobotParserInitialize);
#endif
}
