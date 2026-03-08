// Generated from EcoBot.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link EcoBotParser}.
 */
public interface EcoBotListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(EcoBotParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(EcoBotParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#intentDef}.
	 * @param ctx the parse tree
	 */
	void enterIntentDef(EcoBotParser.IntentDefContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#intentDef}.
	 * @param ctx the parse tree
	 */
	void exitIntentDef(EcoBotParser.IntentDefContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#stmtList}.
	 * @param ctx the parse tree
	 */
	void enterStmtList(EcoBotParser.StmtListContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#stmtList}.
	 * @param ctx the parse tree
	 */
	void exitStmtList(EcoBotParser.StmtListContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#stmt}.
	 * @param ctx the parse tree
	 */
	void enterStmt(EcoBotParser.StmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#stmt}.
	 * @param ctx the parse tree
	 */
	void exitStmt(EcoBotParser.StmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#replyStmt}.
	 * @param ctx the parse tree
	 */
	void enterReplyStmt(EcoBotParser.ReplyStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#replyStmt}.
	 * @param ctx the parse tree
	 */
	void exitReplyStmt(EcoBotParser.ReplyStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#requireStmt}.
	 * @param ctx the parse tree
	 */
	void enterRequireStmt(EcoBotParser.RequireStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#requireStmt}.
	 * @param ctx the parse tree
	 */
	void exitRequireStmt(EcoBotParser.RequireStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#callStmt}.
	 * @param ctx the parse tree
	 */
	void enterCallStmt(EcoBotParser.CallStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#callStmt}.
	 * @param ctx the parse tree
	 */
	void exitCallStmt(EcoBotParser.CallStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#serviceCall}.
	 * @param ctx the parse tree
	 */
	void enterServiceCall(EcoBotParser.ServiceCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#serviceCall}.
	 * @param ctx the parse tree
	 */
	void exitServiceCall(EcoBotParser.ServiceCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void enterIfStmt(EcoBotParser.IfStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void exitIfStmt(EcoBotParser.IfStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#exitStmt}.
	 * @param ctx the parse tree
	 */
	void enterExitStmt(EcoBotParser.ExitStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#exitStmt}.
	 * @param ctx the parse tree
	 */
	void exitExitStmt(EcoBotParser.ExitStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#block}.
	 * @param ctx the parse tree
	 */
	void enterBlock(EcoBotParser.BlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#block}.
	 * @param ctx the parse tree
	 */
	void exitBlock(EcoBotParser.BlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#condition}.
	 * @param ctx the parse tree
	 */
	void enterCondition(EcoBotParser.ConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#condition}.
	 * @param ctx the parse tree
	 */
	void exitCondition(EcoBotParser.ConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#value}.
	 * @param ctx the parse tree
	 */
	void enterValue(EcoBotParser.ValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#value}.
	 * @param ctx the parse tree
	 */
	void exitValue(EcoBotParser.ValueContext ctx);
	/**
	 * Enter a parse tree produced by {@link EcoBotParser#argList}.
	 * @param ctx the parse tree
	 */
	void enterArgList(EcoBotParser.ArgListContext ctx);
	/**
	 * Exit a parse tree produced by {@link EcoBotParser#argList}.
	 * @param ctx the parse tree
	 */
	void exitArgList(EcoBotParser.ArgListContext ctx);
}