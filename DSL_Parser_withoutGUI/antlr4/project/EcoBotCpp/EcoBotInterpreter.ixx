module;
#include "EcoBotBaseVisitor.h"

export module EcoBotInterpreter;
import Context;
import DBService;

export class  EcoBotInterpreter : public EcoBotBaseVisitor {
public:
    EcoBotInterpreter(Context& context);
    virtual std::any visitReplyStmt(EcoBotParser::ReplyStmtContext* ctx) override;
    virtual std::any visitRequireStmt(EcoBotParser::RequireStmtContext* ctx) override;
    virtual std::any visitIfStmt(EcoBotParser::IfStmtContext* ctx) override;
    virtual std::any visitCondition(EcoBotParser::ConditionContext* ctx) override;
    virtual std::any visitCallStmt(EcoBotParser::CallStmtContext* ctx) override;
    virtual std::any visitArgList(EcoBotParser::ArgListContext* ctx) override;
private:
    Context &userCtx;
    void handleEscapeSeq(std::string& text);


};


EcoBotInterpreter::EcoBotInterpreter(Context& context)
    :userCtx(context)
{

}


void EcoBotInterpreter::handleEscapeSeq(std::string& text) {

    std::string::size_type startPos;
    std::string::size_type endPos;
    const std::string startStr{ "${" };
    const std::string endStr{ "}" };
    std::string::size_type startPosOfCtx;
    std::string::size_type len;

    while (true) {
        if (((startPos = text.find(startStr)) != std::string::npos) && ((endPos = text.find(endStr)) != std::string::npos) && endPos > startPos + 1) {
            startPosOfCtx = startPos + startStr.size();
            len = endPos - startPosOfCtx;

            std::string key{ text.substr(startPosOfCtx,len) };

            if (userCtx.contains(key)) {
                std::string value{ userCtx.find(key).value() };
                text.replace(startPos, endPos-startPos+1, value);
            }
            else {
                std::cout << "-2-";//debug
                exit(-1); //TODO
            }
        }
        else {
            break;
        }
    }
}

std::any EcoBotInterpreter::visitReplyStmt(EcoBotParser::ReplyStmtContext* ctx)  {
    std::string text = ctx->STRING()->getText();
    text = text.substr(1, text.length() - 2);

    handleEscapeSeq(text);

    //std::cout << "Robot: " << text << std::endl;

    std::cout << "\033[33mRobot: " << text << "\033[0m" << std::endl;

    return 0;
}
std::any EcoBotInterpreter::visitRequireStmt(EcoBotParser::RequireStmtContext* ctx)
{
    std::string requireKey{ ctx->ID()->getText() };
    std::string requireValue;

    std::string requireText{ ctx->STRING()->getText() };
    //std::cout << "Robot: " << requireText << std::endl;
    std::cout << "\033[33mRobot: " << requireText << "\033[0m" << std::endl;
    

    std::getline(std::cin, requireValue);

    userCtx.add(requireKey, requireValue);

    return 0;
}

std::any EcoBotInterpreter::visitIfStmt(EcoBotParser::IfStmtContext* ctx)
{

    size_t conditionNum{ ctx->condition().size() };
    size_t blockNum{ ctx->block().size() };

    auto condition{ ctx->condition() };
    auto block{ ctx->block() };


    for (int i{ 0 }; i < conditionNum; i++) {
        bool conditionResult{std::any_cast<bool>(visit(condition[i]))};

        if (conditionResult) {
            visit(block[i]);
            return 0;
        }
    }

    if (conditionNum < blockNum) {
        visit(block.back());
        return 0;
    }
}

std::any EcoBotInterpreter::visitCondition(EcoBotParser::ConditionContext* ctx)
{
    std::string lID{ ctx->ID()->getText() };
    std::string op{ ctx->op->getText() };
    std::string valueStr;

    if (ctx->value()->ID()) {
        return true; // TODO
    }
    else {
        valueStr = ctx->value()->STRING()->getText();
        std::string rValue{ valueStr.substr(1,valueStr.length() - 2) };
        auto lValue{ userCtx.find(lID) };

        if (lValue && lValue == rValue) {
            return true;
        }
        else {
            return false;
        }
    }
}

std::any EcoBotInterpreter::visitCallStmt(EcoBotParser::CallStmtContext* ctx)
{
    auto serviceCtx{ ctx->serviceCall() };
    auto argListCtx{ serviceCtx->argList() };
    std::string serviceName{ serviceCtx->ID(0)->getText() };
    std::string methodName{ serviceCtx->ID(1)->getText() };
    std::vector<std::string> argList{ std::any_cast<std::vector<std::string>>(visitArgList(argListCtx)) };

    for (auto& arg : argList) {
        auto val = userCtx.find(arg);

        if (!val.has_value()) {
            std::cout << "-1-";//debug
            exit(-1);//TODO
        }

        arg = val.value();
    }

    std::string result{ dispatchService(serviceName, methodName, argList) };
    userCtx.add(ctx->ID()->getText(), result);
    
}

std::any EcoBotInterpreter::visitArgList(EcoBotParser::ArgListContext* ctx)
{
    std::vector<std::string> args;
    for (auto id : ctx->ID()) {
        args.push_back(id->getText());
    }
    return args;
}