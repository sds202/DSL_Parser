module;
#include "EcoBotBaseVisitor.h"

export module EcoBotInterpreter;

export class  EcoBotInterpreter : public EcoBotBaseVisitor {
public:

    virtual std::any visitProgram(EcoBotParser::ProgramContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitIntentDef(EcoBotParser::IntentDefContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitStmtList(EcoBotParser::StmtListContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitStmt(EcoBotParser::StmtContext* ctx) override {
        return visitChildren(ctx);
    }

    std::any visitReplyStmt(EcoBotParser::ReplyStmtContext* ctx) override {
        std::string text = ctx->STRING()->getText();
        text = text.substr(1, text.length() - 2);
        std::cout << "Robot: " << text << std::endl;
        return 0;
    }

    virtual std::any visitRequireStmt(EcoBotParser::RequireStmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitCallStmt(EcoBotParser::CallStmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitServiceCall(EcoBotParser::ServiceCallContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitIfStmt(EcoBotParser::IfStmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitExitStmt(EcoBotParser::ExitStmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitBlock(EcoBotParser::BlockContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitCondition(EcoBotParser::ConditionContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitValue(EcoBotParser::ValueContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual std::any visitArgList(EcoBotParser::ArgListContext* ctx) override {
        return visitChildren(ctx);
    }

};

