grammar EcoBot;

// --- 语法规则 (Parser Rules) ---

// 程序入口：由多个 intent 块组成
program: intentDef* EOF;

// Intent 定义块
intentDef: 'intent' ID '{' stmtList '}';

// 语句列表
stmtList: stmt*;

// 单条语句
stmt: replyStmt | requireStmt | callStmt | ifStmt | exitStmt;

// 1. reply "..." ;
replyStmt: 'reply' STRING ';';

// 2. require order_id "..." ;
requireStmt: 'require' ID STRING ';';

// 3. 函数调用 (赋值型或独立型) status = call Service.method(args); 或者 call Service.method(args);
callStmt: (ID '=')? 'call' serviceCall ';';

// 辅助规则：服务调用的核心结构 Service.method(arg1, arg2)
serviceCall: ID '.' ID '(' argList? ')';

// 4. if-else 结构
ifStmt:
	'if' '(' condition ')' block (
		'else' 'if' '(' condition ')' block
	)* // 支持 else if
	('else' block)? ; // 支持 else

// 5. exit;
exitStmt: 'exit' ';';

// 代码块 { ... }
block: '{' stmtList '}';

// 条件表达式：var == "value"
condition: ID op = ('==' | '!=' | '>' | '<') value;

// 值（可以是变量，也可以是字符串字面量，还可以是数字）
value: ID | STRING | NUM;

// 参数列表：var1, var2
argList: ID (',' ID)*;

// --- 词法规则 (Lexer Rules) ---

// 关键字 (Keywords)
K_INTENT: 'intent';
K_REPLY: 'reply';
K_REQUIRE: 'require';
K_CALL: 'call';
K_IF: 'if';
K_ELSE: 'else';
K_EXIT: 'exit';

// 标识符 (Identifier)：必须以字母或下划线开头
ID: [a-zA-Z_] [a-zA-Z0-9_]*;

// 字符串字面量 (String Literal)：支持双引号
STRING: '"' ( '\\"' | .)*? '"';

NUM: [0]|([1-9][0-9]*);

// 忽略空白字符 (Whitespace) -> skip 表示解析时丢弃
WS: [ \t\r\n]+ -> skip;

// 单行注释 //... -> skip
COMMENT: '//' ~[\r\n]* -> skip;