
// Generated from EcoBot.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "EcoBotListener.h"


/**
 * This class provides an empty implementation of EcoBotListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  EcoBotBaseListener : public EcoBotListener {
public:

  virtual void enterProgram(EcoBotParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(EcoBotParser::ProgramContext * /*ctx*/) override { }

  virtual void enterIntentDef(EcoBotParser::IntentDefContext * /*ctx*/) override { }
  virtual void exitIntentDef(EcoBotParser::IntentDefContext * /*ctx*/) override { }

  virtual void enterStmtList(EcoBotParser::StmtListContext * /*ctx*/) override { }
  virtual void exitStmtList(EcoBotParser::StmtListContext * /*ctx*/) override { }

  virtual void enterStmt(EcoBotParser::StmtContext * /*ctx*/) override { }
  virtual void exitStmt(EcoBotParser::StmtContext * /*ctx*/) override { }

  virtual void enterReplyStmt(EcoBotParser::ReplyStmtContext * /*ctx*/) override { }
  virtual void exitReplyStmt(EcoBotParser::ReplyStmtContext * /*ctx*/) override { }

  virtual void enterRequireStmt(EcoBotParser::RequireStmtContext * /*ctx*/) override { }
  virtual void exitRequireStmt(EcoBotParser::RequireStmtContext * /*ctx*/) override { }

  virtual void enterCallStmt(EcoBotParser::CallStmtContext * /*ctx*/) override { }
  virtual void exitCallStmt(EcoBotParser::CallStmtContext * /*ctx*/) override { }

  virtual void enterServiceCall(EcoBotParser::ServiceCallContext * /*ctx*/) override { }
  virtual void exitServiceCall(EcoBotParser::ServiceCallContext * /*ctx*/) override { }

  virtual void enterIfStmt(EcoBotParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(EcoBotParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterExitStmt(EcoBotParser::ExitStmtContext * /*ctx*/) override { }
  virtual void exitExitStmt(EcoBotParser::ExitStmtContext * /*ctx*/) override { }

  virtual void enterBlock(EcoBotParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(EcoBotParser::BlockContext * /*ctx*/) override { }

  virtual void enterCondition(EcoBotParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(EcoBotParser::ConditionContext * /*ctx*/) override { }

  virtual void enterValue(EcoBotParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(EcoBotParser::ValueContext * /*ctx*/) override { }

  virtual void enterArgList(EcoBotParser::ArgListContext * /*ctx*/) override { }
  virtual void exitArgList(EcoBotParser::ArgListContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

