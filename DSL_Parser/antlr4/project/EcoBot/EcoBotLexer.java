// Generated from EcoBot.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class EcoBotLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, K_INTENT=13, K_REPLY=14, K_REQUIRE=15, K_CALL=16, 
		K_IF=17, K_ELSE=18, K_EXIT=19, ID=20, STRING=21, WS=22, COMMENT=23;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "K_INTENT", "K_REPLY", "K_REQUIRE", "K_CALL", 
			"K_IF", "K_ELSE", "K_EXIT", "ID", "STRING", "WS", "COMMENT"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'{'", "'}'", "';'", "'='", "'.'", "'('", "')'", "'=='", "'!='", 
			"'>'", "'<'", "','", "'intent'", "'reply'", "'require'", "'call'", "'if'", 
			"'else'", "'exit'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, "K_INTENT", "K_REPLY", "K_REQUIRE", "K_CALL", "K_IF", "K_ELSE", 
			"K_EXIT", "ID", "STRING", "WS", "COMMENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public EcoBotLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "EcoBot.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0017\u0094\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002"+
		"\u0001\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002"+
		"\u0004\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002"+
		"\u0007\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002"+
		"\u000b\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e"+
		"\u0002\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011"+
		"\u0002\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014"+
		"\u0002\u0015\u0007\u0015\u0002\u0016\u0007\u0016\u0001\u0000\u0001\u0000"+
		"\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003"+
		"\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001\t\u0001"+
		"\t\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0001\f\u0001\f\u0001\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001"+
		"\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0001\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011"+
		"\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012"+
		"\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0005\u0013s\b\u0013"+
		"\n\u0013\f\u0013v\t\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0005\u0014|\b\u0014\n\u0014\f\u0014\u007f\t\u0014\u0001\u0014\u0001"+
		"\u0014\u0001\u0015\u0004\u0015\u0084\b\u0015\u000b\u0015\f\u0015\u0085"+
		"\u0001\u0015\u0001\u0015\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0005\u0016\u008e\b\u0016\n\u0016\f\u0016\u0091\t\u0016\u0001\u0016\u0001"+
		"\u0016\u0001}\u0000\u0017\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004"+
		"\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017"+
		"\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\'"+
		"\u0014)\u0015+\u0016-\u0017\u0001\u0000\u0004\u0003\u0000AZ__az\u0004"+
		"\u000009AZ__az\u0003\u0000\t\n\r\r  \u0002\u0000\n\n\r\r\u0098\u0000\u0001"+
		"\u0001\u0000\u0000\u0000\u0000\u0003\u0001\u0000\u0000\u0000\u0000\u0005"+
		"\u0001\u0000\u0000\u0000\u0000\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001"+
		"\u0000\u0000\u0000\u0000\u000b\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000"+
		"\u0000\u0000\u0000\u000f\u0001\u0000\u0000\u0000\u0000\u0011\u0001\u0000"+
		"\u0000\u0000\u0000\u0013\u0001\u0000\u0000\u0000\u0000\u0015\u0001\u0000"+
		"\u0000\u0000\u0000\u0017\u0001\u0000\u0000\u0000\u0000\u0019\u0001\u0000"+
		"\u0000\u0000\u0000\u001b\u0001\u0000\u0000\u0000\u0000\u001d\u0001\u0000"+
		"\u0000\u0000\u0000\u001f\u0001\u0000\u0000\u0000\u0000!\u0001\u0000\u0000"+
		"\u0000\u0000#\u0001\u0000\u0000\u0000\u0000%\u0001\u0000\u0000\u0000\u0000"+
		"\'\u0001\u0000\u0000\u0000\u0000)\u0001\u0000\u0000\u0000\u0000+\u0001"+
		"\u0000\u0000\u0000\u0000-\u0001\u0000\u0000\u0000\u0001/\u0001\u0000\u0000"+
		"\u0000\u00031\u0001\u0000\u0000\u0000\u00053\u0001\u0000\u0000\u0000\u0007"+
		"5\u0001\u0000\u0000\u0000\t7\u0001\u0000\u0000\u0000\u000b9\u0001\u0000"+
		"\u0000\u0000\r;\u0001\u0000\u0000\u0000\u000f=\u0001\u0000\u0000\u0000"+
		"\u0011@\u0001\u0000\u0000\u0000\u0013C\u0001\u0000\u0000\u0000\u0015E"+
		"\u0001\u0000\u0000\u0000\u0017G\u0001\u0000\u0000\u0000\u0019I\u0001\u0000"+
		"\u0000\u0000\u001bP\u0001\u0000\u0000\u0000\u001dV\u0001\u0000\u0000\u0000"+
		"\u001f^\u0001\u0000\u0000\u0000!c\u0001\u0000\u0000\u0000#f\u0001\u0000"+
		"\u0000\u0000%k\u0001\u0000\u0000\u0000\'p\u0001\u0000\u0000\u0000)w\u0001"+
		"\u0000\u0000\u0000+\u0083\u0001\u0000\u0000\u0000-\u0089\u0001\u0000\u0000"+
		"\u0000/0\u0005{\u0000\u00000\u0002\u0001\u0000\u0000\u000012\u0005}\u0000"+
		"\u00002\u0004\u0001\u0000\u0000\u000034\u0005;\u0000\u00004\u0006\u0001"+
		"\u0000\u0000\u000056\u0005=\u0000\u00006\b\u0001\u0000\u0000\u000078\u0005"+
		".\u0000\u00008\n\u0001\u0000\u0000\u00009:\u0005(\u0000\u0000:\f\u0001"+
		"\u0000\u0000\u0000;<\u0005)\u0000\u0000<\u000e\u0001\u0000\u0000\u0000"+
		"=>\u0005=\u0000\u0000>?\u0005=\u0000\u0000?\u0010\u0001\u0000\u0000\u0000"+
		"@A\u0005!\u0000\u0000AB\u0005=\u0000\u0000B\u0012\u0001\u0000\u0000\u0000"+
		"CD\u0005>\u0000\u0000D\u0014\u0001\u0000\u0000\u0000EF\u0005<\u0000\u0000"+
		"F\u0016\u0001\u0000\u0000\u0000GH\u0005,\u0000\u0000H\u0018\u0001\u0000"+
		"\u0000\u0000IJ\u0005i\u0000\u0000JK\u0005n\u0000\u0000KL\u0005t\u0000"+
		"\u0000LM\u0005e\u0000\u0000MN\u0005n\u0000\u0000NO\u0005t\u0000\u0000"+
		"O\u001a\u0001\u0000\u0000\u0000PQ\u0005r\u0000\u0000QR\u0005e\u0000\u0000"+
		"RS\u0005p\u0000\u0000ST\u0005l\u0000\u0000TU\u0005y\u0000\u0000U\u001c"+
		"\u0001\u0000\u0000\u0000VW\u0005r\u0000\u0000WX\u0005e\u0000\u0000XY\u0005"+
		"q\u0000\u0000YZ\u0005u\u0000\u0000Z[\u0005i\u0000\u0000[\\\u0005r\u0000"+
		"\u0000\\]\u0005e\u0000\u0000]\u001e\u0001\u0000\u0000\u0000^_\u0005c\u0000"+
		"\u0000_`\u0005a\u0000\u0000`a\u0005l\u0000\u0000ab\u0005l\u0000\u0000"+
		"b \u0001\u0000\u0000\u0000cd\u0005i\u0000\u0000de\u0005f\u0000\u0000e"+
		"\"\u0001\u0000\u0000\u0000fg\u0005e\u0000\u0000gh\u0005l\u0000\u0000h"+
		"i\u0005s\u0000\u0000ij\u0005e\u0000\u0000j$\u0001\u0000\u0000\u0000kl"+
		"\u0005e\u0000\u0000lm\u0005x\u0000\u0000mn\u0005i\u0000\u0000no\u0005"+
		"t\u0000\u0000o&\u0001\u0000\u0000\u0000pt\u0007\u0000\u0000\u0000qs\u0007"+
		"\u0001\u0000\u0000rq\u0001\u0000\u0000\u0000sv\u0001\u0000\u0000\u0000"+
		"tr\u0001\u0000\u0000\u0000tu\u0001\u0000\u0000\u0000u(\u0001\u0000\u0000"+
		"\u0000vt\u0001\u0000\u0000\u0000w}\u0005\"\u0000\u0000xy\u0005\\\u0000"+
		"\u0000y|\u0005\"\u0000\u0000z|\t\u0000\u0000\u0000{x\u0001\u0000\u0000"+
		"\u0000{z\u0001\u0000\u0000\u0000|\u007f\u0001\u0000\u0000\u0000}~\u0001"+
		"\u0000\u0000\u0000}{\u0001\u0000\u0000\u0000~\u0080\u0001\u0000\u0000"+
		"\u0000\u007f}\u0001\u0000\u0000\u0000\u0080\u0081\u0005\"\u0000\u0000"+
		"\u0081*\u0001\u0000\u0000\u0000\u0082\u0084\u0007\u0002\u0000\u0000\u0083"+
		"\u0082\u0001\u0000\u0000\u0000\u0084\u0085\u0001\u0000\u0000\u0000\u0085"+
		"\u0083\u0001\u0000\u0000\u0000\u0085\u0086\u0001\u0000\u0000\u0000\u0086"+
		"\u0087\u0001\u0000\u0000\u0000\u0087\u0088\u0006\u0015\u0000\u0000\u0088"+
		",\u0001\u0000\u0000\u0000\u0089\u008a\u0005/\u0000\u0000\u008a\u008b\u0005"+
		"/\u0000\u0000\u008b\u008f\u0001\u0000\u0000\u0000\u008c\u008e\b\u0003"+
		"\u0000\u0000\u008d\u008c\u0001\u0000\u0000\u0000\u008e\u0091\u0001\u0000"+
		"\u0000\u0000\u008f\u008d\u0001\u0000\u0000\u0000\u008f\u0090\u0001\u0000"+
		"\u0000\u0000\u0090\u0092\u0001\u0000\u0000\u0000\u0091\u008f\u0001\u0000"+
		"\u0000\u0000\u0092\u0093\u0006\u0016\u0000\u0000\u0093.\u0001\u0000\u0000"+
		"\u0000\u0006\u0000t{}\u0085\u008f\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}