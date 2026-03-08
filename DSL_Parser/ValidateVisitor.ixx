module;
#include "antlr4/project/EcoBotCpp/EcoBotBaseVisitor.h"

export module ValidateVisitor;
import DBService;

export class ValidatorVisitor : public EcoBotBaseVisitor {
public:
    virtual std::any visitCallStmt(EcoBotParser::CallStmtContext* ctx) override;
    virtual std::any visitBlock(EcoBotParser::BlockContext* ctx) override;
    virtual std::any visitIfStmt(EcoBotParser::IfStmtContext* ctx) override;
    virtual std::any visitIntentDef(EcoBotParser::IntentDefContext* ctx) override;
};

//implementations

std::any ValidatorVisitor::visitCallStmt(EcoBotParser::CallStmtContext* ctx)  {
    auto serviceCtx = ctx->serviceCall();
    std::string serviceName = serviceCtx->ID(0)->getText();
    std::string methodName = serviceCtx->ID(1)->getText();
    std::string funcFullName = serviceName + "." + methodName;

    size_t actualArgCount = 0;
    if (serviceCtx->argList()) {
        actualArgCount = serviceCtx->argList()->ID().size();
    }

    int expectedArgCount{ ServiceRegistry::getExpectedArgCount(funcFullName) };

    if (expectedArgCount == -1) {
        std::string errorMsg = "Static Check Error: Undefined service function '" + funcFullName +
            "' at line " + std::to_string(ctx->getStart()->getLine());
        throw std::runtime_error(errorMsg);
    }

    if (actualArgCount != expectedArgCount) {
        std::string errorMsg = "Static Check Error: Function '" + funcFullName +
            "' expects " + std::to_string(expectedArgCount) +
            " arguments, but got " + std::to_string(actualArgCount) +
            " at line " + std::to_string(ctx->getStart()->getLine());
        throw std::runtime_error(errorMsg);
    }

    return std::any();
}

std::any ValidatorVisitor::visitBlock(EcoBotParser::BlockContext* ctx)  {
    return visitChildren(ctx);
}

std::any ValidatorVisitor::visitIfStmt(EcoBotParser::IfStmtContext* ctx)  {
    return visitChildren(ctx);
}

std::any ValidatorVisitor::visitIntentDef(EcoBotParser::IntentDefContext* ctx)  {
    return visitChildren(ctx);
}