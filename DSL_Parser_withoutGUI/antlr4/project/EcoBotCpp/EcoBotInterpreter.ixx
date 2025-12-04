module;
#include "EcoBotBaseVisitor.h"

export module EcoBotInterpreter;
import Context;

export class  EcoBotInterpreter : public EcoBotBaseVisitor {
public:
    EcoBotInterpreter(Context& context);
    std::any visitReplyStmt(EcoBotParser::ReplyStmtContext* ctx) override;

private:
    Context &ctx;
    void handleEscapeSeq(std::string& text);


};

EcoBotInterpreter::EcoBotInterpreter(Context& context)
    :ctx(context)
{

}

std::any EcoBotInterpreter::visitReplyStmt(EcoBotParser::ReplyStmtContext* ctx)  {
    std::string text = ctx->STRING()->getText();
    text = text.substr(1, text.length() - 2);

    handleEscapeSeq(text);

    std::cout << "Robot: " << text << std::endl;
    return 0;
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

            if (ctx.contains(key)) {
                std::string value{ ctx.find(key) };
                text.replace(startPos,endPos,value);
            }
            else {
                exit(-1); //TODO
            }
        }
        else {
            break;
        }
    }
}