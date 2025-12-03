
// Generated from EcoBot.g4 by ANTLR 4.13.2


#include "EcoBotLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct EcoBotLexerStaticData final {
  EcoBotLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  EcoBotLexerStaticData(const EcoBotLexerStaticData&) = delete;
  EcoBotLexerStaticData(EcoBotLexerStaticData&&) = delete;
  EcoBotLexerStaticData& operator=(const EcoBotLexerStaticData&) = delete;
  EcoBotLexerStaticData& operator=(EcoBotLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ecobotlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<EcoBotLexerStaticData> ecobotlexerLexerStaticData = nullptr;

void ecobotlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ecobotlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(ecobotlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<EcoBotLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "K_INTENT", "K_REPLY", "K_REQUIRE", "K_CALL", 
      "K_IF", "K_ELSE", "K_EXIT", "ID", "STRING", "WS", "COMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,23,148,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,
  	6,1,7,1,7,1,7,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,17,1,17,
  	1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,19,1,19,5,19,115,8,19,10,19,
  	12,19,118,9,19,1,20,1,20,1,20,1,20,5,20,124,8,20,10,20,12,20,127,9,20,
  	1,20,1,20,1,21,4,21,132,8,21,11,21,12,21,133,1,21,1,21,1,22,1,22,1,22,
  	1,22,5,22,142,8,22,10,22,12,22,145,9,22,1,22,1,22,1,125,0,23,1,1,3,2,
  	5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,
  	16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,1,0,4,3,0,65,90,95,95,97,
  	122,4,0,48,57,65,90,95,95,97,122,3,0,9,10,13,13,32,32,2,0,10,10,13,13,
  	152,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,
  	1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,
  	0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,
  	0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,
  	1,0,0,0,0,45,1,0,0,0,1,47,1,0,0,0,3,49,1,0,0,0,5,51,1,0,0,0,7,53,1,0,
  	0,0,9,55,1,0,0,0,11,57,1,0,0,0,13,59,1,0,0,0,15,61,1,0,0,0,17,64,1,0,
  	0,0,19,67,1,0,0,0,21,69,1,0,0,0,23,71,1,0,0,0,25,73,1,0,0,0,27,80,1,0,
  	0,0,29,86,1,0,0,0,31,94,1,0,0,0,33,99,1,0,0,0,35,102,1,0,0,0,37,107,1,
  	0,0,0,39,112,1,0,0,0,41,119,1,0,0,0,43,131,1,0,0,0,45,137,1,0,0,0,47,
  	48,5,123,0,0,48,2,1,0,0,0,49,50,5,125,0,0,50,4,1,0,0,0,51,52,5,59,0,0,
  	52,6,1,0,0,0,53,54,5,61,0,0,54,8,1,0,0,0,55,56,5,46,0,0,56,10,1,0,0,0,
  	57,58,5,40,0,0,58,12,1,0,0,0,59,60,5,41,0,0,60,14,1,0,0,0,61,62,5,61,
  	0,0,62,63,5,61,0,0,63,16,1,0,0,0,64,65,5,33,0,0,65,66,5,61,0,0,66,18,
  	1,0,0,0,67,68,5,62,0,0,68,20,1,0,0,0,69,70,5,60,0,0,70,22,1,0,0,0,71,
  	72,5,44,0,0,72,24,1,0,0,0,73,74,5,105,0,0,74,75,5,110,0,0,75,76,5,116,
  	0,0,76,77,5,101,0,0,77,78,5,110,0,0,78,79,5,116,0,0,79,26,1,0,0,0,80,
  	81,5,114,0,0,81,82,5,101,0,0,82,83,5,112,0,0,83,84,5,108,0,0,84,85,5,
  	121,0,0,85,28,1,0,0,0,86,87,5,114,0,0,87,88,5,101,0,0,88,89,5,113,0,0,
  	89,90,5,117,0,0,90,91,5,105,0,0,91,92,5,114,0,0,92,93,5,101,0,0,93,30,
  	1,0,0,0,94,95,5,99,0,0,95,96,5,97,0,0,96,97,5,108,0,0,97,98,5,108,0,0,
  	98,32,1,0,0,0,99,100,5,105,0,0,100,101,5,102,0,0,101,34,1,0,0,0,102,103,
  	5,101,0,0,103,104,5,108,0,0,104,105,5,115,0,0,105,106,5,101,0,0,106,36,
  	1,0,0,0,107,108,5,101,0,0,108,109,5,120,0,0,109,110,5,105,0,0,110,111,
  	5,116,0,0,111,38,1,0,0,0,112,116,7,0,0,0,113,115,7,1,0,0,114,113,1,0,
  	0,0,115,118,1,0,0,0,116,114,1,0,0,0,116,117,1,0,0,0,117,40,1,0,0,0,118,
  	116,1,0,0,0,119,125,5,34,0,0,120,121,5,92,0,0,121,124,5,34,0,0,122,124,
  	9,0,0,0,123,120,1,0,0,0,123,122,1,0,0,0,124,127,1,0,0,0,125,126,1,0,0,
  	0,125,123,1,0,0,0,126,128,1,0,0,0,127,125,1,0,0,0,128,129,5,34,0,0,129,
  	42,1,0,0,0,130,132,7,2,0,0,131,130,1,0,0,0,132,133,1,0,0,0,133,131,1,
  	0,0,0,133,134,1,0,0,0,134,135,1,0,0,0,135,136,6,21,0,0,136,44,1,0,0,0,
  	137,138,5,47,0,0,138,139,5,47,0,0,139,143,1,0,0,0,140,142,8,3,0,0,141,
  	140,1,0,0,0,142,145,1,0,0,0,143,141,1,0,0,0,143,144,1,0,0,0,144,146,1,
  	0,0,0,145,143,1,0,0,0,146,147,6,22,0,0,147,46,1,0,0,0,6,0,116,123,125,
  	133,143,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ecobotlexerLexerStaticData = std::move(staticData);
}

}

EcoBotLexer::EcoBotLexer(CharStream *input) : Lexer(input) {
  EcoBotLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ecobotlexerLexerStaticData->atn, ecobotlexerLexerStaticData->decisionToDFA, ecobotlexerLexerStaticData->sharedContextCache);
}

EcoBotLexer::~EcoBotLexer() {
  delete _interpreter;
}

std::string EcoBotLexer::getGrammarFileName() const {
  return "EcoBot.g4";
}

const std::vector<std::string>& EcoBotLexer::getRuleNames() const {
  return ecobotlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& EcoBotLexer::getChannelNames() const {
  return ecobotlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& EcoBotLexer::getModeNames() const {
  return ecobotlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& EcoBotLexer::getVocabulary() const {
  return ecobotlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView EcoBotLexer::getSerializedATN() const {
  return ecobotlexerLexerStaticData->serializedATN;
}

const atn::ATN& EcoBotLexer::getATN() const {
  return *ecobotlexerLexerStaticData->atn;
}




void EcoBotLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ecobotlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(ecobotlexerLexerOnceFlag, ecobotlexerLexerInitialize);
#endif
}
