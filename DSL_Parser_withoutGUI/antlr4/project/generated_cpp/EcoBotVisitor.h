
// Generated from EcoBot.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "EcoBotParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by EcoBotParser.
 */
class  EcoBotVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by EcoBotParser.
   */
    virtual std::any visitProgram(EcoBotParser::ProgramContext *context) = 0;

    virtual std::any visitIntentDef(EcoBotParser::IntentDefContext *context) = 0;

    virtual std::any visitStmtList(EcoBotParser::StmtListContext *context) = 0;

    virtual std::any visitStmt(EcoBotParser::StmtContext *context) = 0;

    virtual std::any visitReplyStmt(EcoBotParser::ReplyStmtContext *context) = 0;

    virtual std::any visitRequireStmt(EcoBotParser::RequireStmtContext *context) = 0;

    virtual std::any visitCallStmt(EcoBotParser::CallStmtContext *context) = 0;

    virtual std::any visitServiceCall(EcoBotParser::ServiceCallContext *context) = 0;

    virtual std::any visitIfStmt(EcoBotParser::IfStmtContext *context) = 0;

    virtual std::any visitExitStmt(EcoBotParser::ExitStmtContext *context) = 0;

    virtual std::any visitBlock(EcoBotParser::BlockContext *context) = 0;

    virtual std::any visitCondition(EcoBotParser::ConditionContext *context) = 0;

    virtual std::any visitValue(EcoBotParser::ValueContext *context) = 0;

    virtual std::any visitArgList(EcoBotParser::ArgListContext *context) = 0;


};

