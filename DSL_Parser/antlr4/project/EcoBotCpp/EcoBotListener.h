
// Generated from EcoBot.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "EcoBotParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by EcoBotParser.
 */
class  EcoBotListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(EcoBotParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(EcoBotParser::ProgramContext *ctx) = 0;

  virtual void enterIntentDef(EcoBotParser::IntentDefContext *ctx) = 0;
  virtual void exitIntentDef(EcoBotParser::IntentDefContext *ctx) = 0;

  virtual void enterStmtList(EcoBotParser::StmtListContext *ctx) = 0;
  virtual void exitStmtList(EcoBotParser::StmtListContext *ctx) = 0;

  virtual void enterStmt(EcoBotParser::StmtContext *ctx) = 0;
  virtual void exitStmt(EcoBotParser::StmtContext *ctx) = 0;

  virtual void enterReplyStmt(EcoBotParser::ReplyStmtContext *ctx) = 0;
  virtual void exitReplyStmt(EcoBotParser::ReplyStmtContext *ctx) = 0;

  virtual void enterRequireStmt(EcoBotParser::RequireStmtContext *ctx) = 0;
  virtual void exitRequireStmt(EcoBotParser::RequireStmtContext *ctx) = 0;

  virtual void enterCallStmt(EcoBotParser::CallStmtContext *ctx) = 0;
  virtual void exitCallStmt(EcoBotParser::CallStmtContext *ctx) = 0;

  virtual void enterServiceCall(EcoBotParser::ServiceCallContext *ctx) = 0;
  virtual void exitServiceCall(EcoBotParser::ServiceCallContext *ctx) = 0;

  virtual void enterIfStmt(EcoBotParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(EcoBotParser::IfStmtContext *ctx) = 0;

  virtual void enterExitStmt(EcoBotParser::ExitStmtContext *ctx) = 0;
  virtual void exitExitStmt(EcoBotParser::ExitStmtContext *ctx) = 0;

  virtual void enterBlock(EcoBotParser::BlockContext *ctx) = 0;
  virtual void exitBlock(EcoBotParser::BlockContext *ctx) = 0;

  virtual void enterCondition(EcoBotParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(EcoBotParser::ConditionContext *ctx) = 0;

  virtual void enterValue(EcoBotParser::ValueContext *ctx) = 0;
  virtual void exitValue(EcoBotParser::ValueContext *ctx) = 0;

  virtual void enterArgList(EcoBotParser::ArgListContext *ctx) = 0;
  virtual void exitArgList(EcoBotParser::ArgListContext *ctx) = 0;


};

