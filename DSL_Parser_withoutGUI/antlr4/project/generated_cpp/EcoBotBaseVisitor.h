
// Generated from EcoBot.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "EcoBotVisitor.h"


/**
 * This class provides an empty implementation of EcoBotVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  EcoBotBaseVisitor : public EcoBotVisitor {
public:

  virtual std::any visitProgram(EcoBotParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntentDef(EcoBotParser::IntentDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmtList(EcoBotParser::StmtListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(EcoBotParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReplyStmt(EcoBotParser::ReplyStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequireStmt(EcoBotParser::RequireStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallStmt(EcoBotParser::CallStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitServiceCall(EcoBotParser::ServiceCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(EcoBotParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExitStmt(EcoBotParser::ExitStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(EcoBotParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(EcoBotParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue(EcoBotParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgList(EcoBotParser::ArgListContext *ctx) override {
    return visitChildren(ctx);
  }


};

