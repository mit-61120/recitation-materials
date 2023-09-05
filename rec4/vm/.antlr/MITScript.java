// Generated from /home/mitscript-dev/recitations/rec6/vm/MITScript.g by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class MITScript extends Lexer {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		INT_CONSTANT=1, TRUE_KEY=2, FALSE_KEY=3, BOOL_CONSTANT=4, NONE_CONSTANT=5, 
		ADD_KEY=6, SUB_KEY=7, MUL_KEY=8, EQ_KEY=9, LT_KEY=10, ASSIGN_KEY=11, IF_KEY=12, 
		SCOLON_KEY=13, OPAREN_KEY=14, CPAREN_KEY=15, OBRACK_KEY=16, CBRACK_KEY=17, 
		NAME=18, COMMENT=19, WHITESPACE=20, ERROR=21;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"INT_CONSTANT", "TRUE_KEY", "FALSE_KEY", "BOOL_CONSTANT", "NONE_CONSTANT", 
			"ADD_KEY", "SUB_KEY", "MUL_KEY", "EQ_KEY", "LT_KEY", "ASSIGN_KEY", "IF_KEY", 
			"SCOLON_KEY", "OPAREN_KEY", "CPAREN_KEY", "OBRACK_KEY", "CBRACK_KEY", 
			"NAME", "COMMENT", "WHITESPACE", "ERROR"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, "'true'", "'false'", null, "'None'", "'+'", "'-'", "'*'", 
			"'=='", "'<'", "'='", "'if'", "';'", "'('", "')'", "'{'", "'}'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "INT_CONSTANT", "TRUE_KEY", "FALSE_KEY", "BOOL_CONSTANT", "NONE_CONSTANT", 
			"ADD_KEY", "SUB_KEY", "MUL_KEY", "EQ_KEY", "LT_KEY", "ASSIGN_KEY", "IF_KEY", 
			"SCOLON_KEY", "OPAREN_KEY", "CPAREN_KEY", "OBRACK_KEY", "CBRACK_KEY", 
			"NAME", "COMMENT", "WHITESPACE", "ERROR"
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


	public MITScript(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "MITScript.g"; }

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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\27{\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\3\2\6\2/\n\2\r\2\16\2\60\3\3"+
		"\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\4\3\5\3\5\5\5@\n\5\3\6\3\6\3\6"+
		"\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\n\3\13\3\13\3\f\3\f\3\r\3\r"+
		"\3\r\3\16\3\16\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\7\23"+
		"c\n\23\f\23\16\23f\13\23\3\24\3\24\3\24\3\24\7\24l\n\24\f\24\16\24o\13"+
		"\24\3\24\3\24\3\25\6\25t\n\25\r\25\16\25u\3\25\3\25\3\26\3\26\2\2\27\3"+
		"\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37"+
		"\21!\22#\23%\24\'\25)\26+\27\3\2\7\3\2\62;\5\2C\\aac|\6\2\62;C\\aac|\4"+
		"\2\f\f\17\17\5\2\13\f\16\17\"\"\2\177\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2"+
		"\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2"+
		"\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3"+
		"\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3"+
		"\2\2\2\2+\3\2\2\2\3.\3\2\2\2\5\62\3\2\2\2\7\67\3\2\2\2\t?\3\2\2\2\13A"+
		"\3\2\2\2\rF\3\2\2\2\17H\3\2\2\2\21J\3\2\2\2\23L\3\2\2\2\25O\3\2\2\2\27"+
		"Q\3\2\2\2\31S\3\2\2\2\33V\3\2\2\2\35X\3\2\2\2\37Z\3\2\2\2!\\\3\2\2\2#"+
		"^\3\2\2\2%`\3\2\2\2\'g\3\2\2\2)s\3\2\2\2+y\3\2\2\2-/\t\2\2\2.-\3\2\2\2"+
		"/\60\3\2\2\2\60.\3\2\2\2\60\61\3\2\2\2\61\4\3\2\2\2\62\63\7v\2\2\63\64"+
		"\7t\2\2\64\65\7w\2\2\65\66\7g\2\2\66\6\3\2\2\2\678\7h\2\289\7c\2\29:\7"+
		"n\2\2:;\7u\2\2;<\7g\2\2<\b\3\2\2\2=@\5\5\3\2>@\5\7\4\2?=\3\2\2\2?>\3\2"+
		"\2\2@\n\3\2\2\2AB\7P\2\2BC\7q\2\2CD\7p\2\2DE\7g\2\2E\f\3\2\2\2FG\7-\2"+
		"\2G\16\3\2\2\2HI\7/\2\2I\20\3\2\2\2JK\7,\2\2K\22\3\2\2\2LM\7?\2\2MN\7"+
		"?\2\2N\24\3\2\2\2OP\7>\2\2P\26\3\2\2\2QR\7?\2\2R\30\3\2\2\2ST\7k\2\2T"+
		"U\7h\2\2U\32\3\2\2\2VW\7=\2\2W\34\3\2\2\2XY\7*\2\2Y\36\3\2\2\2Z[\7+\2"+
		"\2[ \3\2\2\2\\]\7}\2\2]\"\3\2\2\2^_\7\177\2\2_$\3\2\2\2`d\t\3\2\2ac\t"+
		"\4\2\2ba\3\2\2\2cf\3\2\2\2db\3\2\2\2de\3\2\2\2e&\3\2\2\2fd\3\2\2\2gh\7"+
		"\61\2\2hi\7\61\2\2im\3\2\2\2jl\n\5\2\2kj\3\2\2\2lo\3\2\2\2mk\3\2\2\2m"+
		"n\3\2\2\2np\3\2\2\2om\3\2\2\2pq\b\24\2\2q(\3\2\2\2rt\t\6\2\2sr\3\2\2\2"+
		"tu\3\2\2\2us\3\2\2\2uv\3\2\2\2vw\3\2\2\2wx\b\25\2\2x*\3\2\2\2yz\13\2\2"+
		"\2z,\3\2\2\2\b\2\60?dmu\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}