// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLLexer.g4 by ANTLR 4.7
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class IDLLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		IMPORT=1, NAMESPACE=2, STRUCT=3, INTERFACE=4, ENUM=5, IN=6, OUT=7, COLON=8, 
		SEMICOLON=9, STAR=10, DOT=11, COMMA=12, EQUALS=13, QUOTE=14, LBRACE=15, 
		RBRACE=16, LPAREN=17, RPAREN=18, LBRACKET=19, RBRACKET=20, LT=21, GT=22, 
		CONST=23, VOID=24, RESULT=25, CLASS_ID=26, U8=27, S8=28, U16=29, S16=30, 
		U32=31, S32=32, U64=33, S64=34, F32=35, F64=36, BYTE=37, CHAR=38, SHORT=39, 
		LONG=40, INT=41, FLOAT=42, DOUBLE=43, STRING=44, IDENT=45, DECIMAL_LIT=46, 
		HEX_LIT=47, OCT_LIT=48, BIN_LIT=49, STRING_LIT=50, FLOAT_LIT=51, WHITE_SPACE=52, 
		BLOCK_COMMENT=53, LINE_COMMENT=54;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"ALPHA", "ALPHA_", "DIGIT", "HEX_DIGIT", "BIN_DIGIT", "OCT_DIGIT", "WS", 
		"IMPORT", "NAMESPACE", "STRUCT", "INTERFACE", "ENUM", "IN", "OUT", "COLON", 
		"SEMICOLON", "STAR", "DOT", "COMMA", "EQUALS", "QUOTE", "LBRACE", "RBRACE", 
		"LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LT", "GT", "CONST", "VOID", 
		"RESULT", "CLASS_ID", "U8", "S8", "U16", "S16", "U32", "S32", "U64", "S64", 
		"F32", "F64", "BYTE", "CHAR", "SHORT", "LONG", "INT", "FLOAT", "DOUBLE", 
		"STRING", "IDENT", "DECIMAL_LIT", "HEX_LIT", "OCT_LIT", "BIN_LIT", "STRING_LIT", 
		"QUOTED_TEXT", "QUOTED_ITEM", "ESC_CHAR", "FLOAT_LIT", "DIGIT_SEQ", "DECIMAL_EXP", 
		"FLOAT_EXP", "SIGN", "WHITE_SPACE", "BLOCK_COMMENT", "LINE_COMMENT"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'import'", "'namespace'", "'struct'", "'interface'", "'enum'", 
		"'in'", "'out'", "':'", "';'", "'*'", "'.'", "','", "'='", "'\"'", "'{'", 
		"'}'", "'('", "')'", "'['", "']'", "'<'", "'>'", "'const'", "'void'", 
		"'result'", "'class_id'", "'u8'", "'s8'", "'u16'", "'s16'", "'u32'", "'s32'", 
		"'u64'", "'s64'", "'f32'", "'f64'", "'byte'", "'char'", "'short'", "'long'", 
		"'int'", "'float'", "'double'", "'string'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "IMPORT", "NAMESPACE", "STRUCT", "INTERFACE", "ENUM", "IN", "OUT", 
		"COLON", "SEMICOLON", "STAR", "DOT", "COMMA", "EQUALS", "QUOTE", "LBRACE", 
		"RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LT", "GT", "CONST", 
		"VOID", "RESULT", "CLASS_ID", "U8", "S8", "U16", "S16", "U32", "S32", 
		"U64", "S64", "F32", "F64", "BYTE", "CHAR", "SHORT", "LONG", "INT", "FLOAT", 
		"DOUBLE", "STRING", "IDENT", "DECIMAL_LIT", "HEX_LIT", "OCT_LIT", "BIN_LIT", 
		"STRING_LIT", "FLOAT_LIT", "WHITE_SPACE", "BLOCK_COMMENT", "LINE_COMMENT"
	};
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


	public IDLLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "IDLLexer.g4"; }

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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\28\u01f1\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t="+
		"\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\3\2\3\2\3\3\3\3\3\4\3"+
		"\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n"+
		"\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3"+
		"\f\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\r\3\r\3\r\3\16\3\16\3"+
		"\16\3\17\3\17\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\3\24\3"+
		"\24\3\25\3\25\3\26\3\26\3\27\3\27\3\30\3\30\3\31\3\31\3\32\3\32\3\33\3"+
		"\33\3\34\3\34\3\35\3\35\3\36\3\36\3\37\3\37\3\37\3\37\3\37\3\37\3 \3 "+
		"\3 \3 \3 \3!\3!\3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3#"+
		"\3#\3#\3$\3$\3$\3%\3%\3%\3%\3&\3&\3&\3&\3\'\3\'\3\'\3\'\3(\3(\3(\3(\3"+
		")\3)\3)\3)\3*\3*\3*\3*\3+\3+\3+\3+\3,\3,\3,\3,\3-\3-\3-\3-\3-\3.\3.\3"+
		".\3.\3.\3/\3/\3/\3/\3/\3/\3\60\3\60\3\60\3\60\3\60\3\61\3\61\3\61\3\61"+
		"\3\62\3\62\3\62\3\62\3\62\3\62\3\63\3\63\3\63\3\63\3\63\3\63\3\63\3\64"+
		"\3\64\3\64\3\64\3\64\3\64\3\64\3\65\3\65\3\65\7\65\u0157\n\65\f\65\16"+
		"\65\u015a\13\65\3\66\3\66\7\66\u015e\n\66\f\66\16\66\u0161\13\66\3\67"+
		"\3\67\3\67\3\67\5\67\u0167\n\67\3\67\6\67\u016a\n\67\r\67\16\67\u016b"+
		"\38\38\68\u0170\n8\r8\168\u0171\39\39\39\39\59\u0178\n9\39\69\u017b\n"+
		"9\r9\169\u017c\3:\3:\5:\u0181\n:\3:\3:\3;\6;\u0186\n;\r;\16;\u0187\3<"+
		"\3<\5<\u018c\n<\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3="+
		"\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\3=\5=\u01ae\n=\3>\5>\u01b1\n>"+
		"\3>\3>\3>\5>\u01b6\n>\3>\3>\3>\5>\u01bb\n>\5>\u01bd\n>\3?\6?\u01c0\n?"+
		"\r?\16?\u01c1\3@\3@\5@\u01c6\n@\3@\3@\3A\3A\3B\3B\3C\6C\u01cf\nC\rC\16"+
		"C\u01d0\3C\3C\3D\3D\3D\3D\3D\7D\u01da\nD\fD\16D\u01dd\13D\3D\3D\3D\3D"+
		"\3D\3E\3E\3E\3E\7E\u01e8\nE\fE\16E\u01eb\13E\3E\5E\u01ee\nE\3E\3E\4\u01db"+
		"\u01e9\2F\3\2\5\2\7\2\t\2\13\2\r\2\17\2\21\3\23\4\25\5\27\6\31\7\33\b"+
		"\35\t\37\n!\13#\f%\r\'\16)\17+\20-\21/\22\61\23\63\24\65\25\67\269\27"+
		";\30=\31?\32A\33C\34E\35G\36I\37K M!O\"Q#S$U%W&Y\'[(])_*a+c,e-g.i/k\60"+
		"m\61o\62q\63s\64u\2w\2y\2{\65}\2\177\2\u0081\2\u0083\2\u0085\66\u0087"+
		"\67\u00898\3\2\17\4\2C\\c|\5\2C\\aac|\3\2\62;\5\2\62;CHch\3\2\62\63\3"+
		"\2\629\5\2\13\f\17\17\"\"\3\2\63;\6\2\f\f\17\17$$^^\t\2$$))\62\62^^pp"+
		"ttvv\4\2GGgg\4\2--//\3\3\f\f\2\u01fa\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3"+
		"\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2"+
		"\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2"+
		"\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2"+
		"\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2"+
		"\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q"+
		"\3\2\2\2\2S\3\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2"+
		"\2\2\2_\3\2\2\2\2a\3\2\2\2\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2"+
		"\2k\3\2\2\2\2m\3\2\2\2\2o\3\2\2\2\2q\3\2\2\2\2s\3\2\2\2\2{\3\2\2\2\2\u0085"+
		"\3\2\2\2\2\u0087\3\2\2\2\2\u0089\3\2\2\2\3\u008b\3\2\2\2\5\u008d\3\2\2"+
		"\2\7\u008f\3\2\2\2\t\u0091\3\2\2\2\13\u0093\3\2\2\2\r\u0095\3\2\2\2\17"+
		"\u0097\3\2\2\2\21\u0099\3\2\2\2\23\u00a0\3\2\2\2\25\u00aa\3\2\2\2\27\u00b1"+
		"\3\2\2\2\31\u00bb\3\2\2\2\33\u00c0\3\2\2\2\35\u00c3\3\2\2\2\37\u00c7\3"+
		"\2\2\2!\u00c9\3\2\2\2#\u00cb\3\2\2\2%\u00cd\3\2\2\2\'\u00cf\3\2\2\2)\u00d1"+
		"\3\2\2\2+\u00d3\3\2\2\2-\u00d5\3\2\2\2/\u00d7\3\2\2\2\61\u00d9\3\2\2\2"+
		"\63\u00db\3\2\2\2\65\u00dd\3\2\2\2\67\u00df\3\2\2\29\u00e1\3\2\2\2;\u00e3"+
		"\3\2\2\2=\u00e5\3\2\2\2?\u00eb\3\2\2\2A\u00f0\3\2\2\2C\u00f7\3\2\2\2E"+
		"\u0100\3\2\2\2G\u0103\3\2\2\2I\u0106\3\2\2\2K\u010a\3\2\2\2M\u010e\3\2"+
		"\2\2O\u0112\3\2\2\2Q\u0116\3\2\2\2S\u011a\3\2\2\2U\u011e\3\2\2\2W\u0122"+
		"\3\2\2\2Y\u0126\3\2\2\2[\u012b\3\2\2\2]\u0130\3\2\2\2_\u0136\3\2\2\2a"+
		"\u013b\3\2\2\2c\u013f\3\2\2\2e\u0145\3\2\2\2g\u014c\3\2\2\2i\u0153\3\2"+
		"\2\2k\u015b\3\2\2\2m\u0166\3\2\2\2o\u016d\3\2\2\2q\u0177\3\2\2\2s\u017e"+
		"\3\2\2\2u\u0185\3\2\2\2w\u018b\3\2\2\2y\u01ad\3\2\2\2{\u01bc\3\2\2\2}"+
		"\u01bf\3\2\2\2\177\u01c3\3\2\2\2\u0081\u01c9\3\2\2\2\u0083\u01cb\3\2\2"+
		"\2\u0085\u01ce\3\2\2\2\u0087\u01d4\3\2\2\2\u0089\u01e3\3\2\2\2\u008b\u008c"+
		"\t\2\2\2\u008c\4\3\2\2\2\u008d\u008e\t\3\2\2\u008e\6\3\2\2\2\u008f\u0090"+
		"\t\4\2\2\u0090\b\3\2\2\2\u0091\u0092\t\5\2\2\u0092\n\3\2\2\2\u0093\u0094"+
		"\t\6\2\2\u0094\f\3\2\2\2\u0095\u0096\t\7\2\2\u0096\16\3\2\2\2\u0097\u0098"+
		"\t\b\2\2\u0098\20\3\2\2\2\u0099\u009a\7k\2\2\u009a\u009b\7o\2\2\u009b"+
		"\u009c\7r\2\2\u009c\u009d\7q\2\2\u009d\u009e\7t\2\2\u009e\u009f\7v\2\2"+
		"\u009f\22\3\2\2\2\u00a0\u00a1\7p\2\2\u00a1\u00a2\7c\2\2\u00a2\u00a3\7"+
		"o\2\2\u00a3\u00a4\7g\2\2\u00a4\u00a5\7u\2\2\u00a5\u00a6\7r\2\2\u00a6\u00a7"+
		"\7c\2\2\u00a7\u00a8\7e\2\2\u00a8\u00a9\7g\2\2\u00a9\24\3\2\2\2\u00aa\u00ab"+
		"\7u\2\2\u00ab\u00ac\7v\2\2\u00ac\u00ad\7t\2\2\u00ad\u00ae\7w\2\2\u00ae"+
		"\u00af\7e\2\2\u00af\u00b0\7v\2\2\u00b0\26\3\2\2\2\u00b1\u00b2\7k\2\2\u00b2"+
		"\u00b3\7p\2\2\u00b3\u00b4\7v\2\2\u00b4\u00b5\7g\2\2\u00b5\u00b6\7t\2\2"+
		"\u00b6\u00b7\7h\2\2\u00b7\u00b8\7c\2\2\u00b8\u00b9\7e\2\2\u00b9\u00ba"+
		"\7g\2\2\u00ba\30\3\2\2\2\u00bb\u00bc\7g\2\2\u00bc\u00bd\7p\2\2\u00bd\u00be"+
		"\7w\2\2\u00be\u00bf\7o\2\2\u00bf\32\3\2\2\2\u00c0\u00c1\7k\2\2\u00c1\u00c2"+
		"\7p\2\2\u00c2\34\3\2\2\2\u00c3\u00c4\7q\2\2\u00c4\u00c5\7w\2\2\u00c5\u00c6"+
		"\7v\2\2\u00c6\36\3\2\2\2\u00c7\u00c8\7<\2\2\u00c8 \3\2\2\2\u00c9\u00ca"+
		"\7=\2\2\u00ca\"\3\2\2\2\u00cb\u00cc\7,\2\2\u00cc$\3\2\2\2\u00cd\u00ce"+
		"\7\60\2\2\u00ce&\3\2\2\2\u00cf\u00d0\7.\2\2\u00d0(\3\2\2\2\u00d1\u00d2"+
		"\7?\2\2\u00d2*\3\2\2\2\u00d3\u00d4\7$\2\2\u00d4,\3\2\2\2\u00d5\u00d6\7"+
		"}\2\2\u00d6.\3\2\2\2\u00d7\u00d8\7\177\2\2\u00d8\60\3\2\2\2\u00d9\u00da"+
		"\7*\2\2\u00da\62\3\2\2\2\u00db\u00dc\7+\2\2\u00dc\64\3\2\2\2\u00dd\u00de"+
		"\7]\2\2\u00de\66\3\2\2\2\u00df\u00e0\7_\2\2\u00e08\3\2\2\2\u00e1\u00e2"+
		"\7>\2\2\u00e2:\3\2\2\2\u00e3\u00e4\7@\2\2\u00e4<\3\2\2\2\u00e5\u00e6\7"+
		"e\2\2\u00e6\u00e7\7q\2\2\u00e7\u00e8\7p\2\2\u00e8\u00e9\7u\2\2\u00e9\u00ea"+
		"\7v\2\2\u00ea>\3\2\2\2\u00eb\u00ec\7x\2\2\u00ec\u00ed\7q\2\2\u00ed\u00ee"+
		"\7k\2\2\u00ee\u00ef\7f\2\2\u00ef@\3\2\2\2\u00f0\u00f1\7t\2\2\u00f1\u00f2"+
		"\7g\2\2\u00f2\u00f3\7u\2\2\u00f3\u00f4\7w\2\2\u00f4\u00f5\7n\2\2\u00f5"+
		"\u00f6\7v\2\2\u00f6B\3\2\2\2\u00f7\u00f8\7e\2\2\u00f8\u00f9\7n\2\2\u00f9"+
		"\u00fa\7c\2\2\u00fa\u00fb\7u\2\2\u00fb\u00fc\7u\2\2\u00fc\u00fd\7a\2\2"+
		"\u00fd\u00fe\7k\2\2\u00fe\u00ff\7f\2\2\u00ffD\3\2\2\2\u0100\u0101\7w\2"+
		"\2\u0101\u0102\7:\2\2\u0102F\3\2\2\2\u0103\u0104\7u\2\2\u0104\u0105\7"+
		":\2\2\u0105H\3\2\2\2\u0106\u0107\7w\2\2\u0107\u0108\7\63\2\2\u0108\u0109"+
		"\78\2\2\u0109J\3\2\2\2\u010a\u010b\7u\2\2\u010b\u010c\7\63\2\2\u010c\u010d"+
		"\78\2\2\u010dL\3\2\2\2\u010e\u010f\7w\2\2\u010f\u0110\7\65\2\2\u0110\u0111"+
		"\7\64\2\2\u0111N\3\2\2\2\u0112\u0113\7u\2\2\u0113\u0114\7\65\2\2\u0114"+
		"\u0115\7\64\2\2\u0115P\3\2\2\2\u0116\u0117\7w\2\2\u0117\u0118\78\2\2\u0118"+
		"\u0119\7\66\2\2\u0119R\3\2\2\2\u011a\u011b\7u\2\2\u011b\u011c\78\2\2\u011c"+
		"\u011d\7\66\2\2\u011dT\3\2\2\2\u011e\u011f\7h\2\2\u011f\u0120\7\65\2\2"+
		"\u0120\u0121\7\64\2\2\u0121V\3\2\2\2\u0122\u0123\7h\2\2\u0123\u0124\7"+
		"8\2\2\u0124\u0125\7\66\2\2\u0125X\3\2\2\2\u0126\u0127\7d\2\2\u0127\u0128"+
		"\7{\2\2\u0128\u0129\7v\2\2\u0129\u012a\7g\2\2\u012aZ\3\2\2\2\u012b\u012c"+
		"\7e\2\2\u012c\u012d\7j\2\2\u012d\u012e\7c\2\2\u012e\u012f\7t\2\2\u012f"+
		"\\\3\2\2\2\u0130\u0131\7u\2\2\u0131\u0132\7j\2\2\u0132\u0133\7q\2\2\u0133"+
		"\u0134\7t\2\2\u0134\u0135\7v\2\2\u0135^\3\2\2\2\u0136\u0137\7n\2\2\u0137"+
		"\u0138\7q\2\2\u0138\u0139\7p\2\2\u0139\u013a\7i\2\2\u013a`\3\2\2\2\u013b"+
		"\u013c\7k\2\2\u013c\u013d\7p\2\2\u013d\u013e\7v\2\2\u013eb\3\2\2\2\u013f"+
		"\u0140\7h\2\2\u0140\u0141\7n\2\2\u0141\u0142\7q\2\2\u0142\u0143\7c\2\2"+
		"\u0143\u0144\7v\2\2\u0144d\3\2\2\2\u0145\u0146\7f\2\2\u0146\u0147\7q\2"+
		"\2\u0147\u0148\7w\2\2\u0148\u0149\7d\2\2\u0149\u014a\7n\2\2\u014a\u014b"+
		"\7g\2\2\u014bf\3\2\2\2\u014c\u014d\7u\2\2\u014d\u014e\7v\2\2\u014e\u014f"+
		"\7t\2\2\u014f\u0150\7k\2\2\u0150\u0151\7p\2\2\u0151\u0152\7i\2\2\u0152"+
		"h\3\2\2\2\u0153\u0158\5\5\3\2\u0154\u0157\5\5\3\2\u0155\u0157\5\7\4\2"+
		"\u0156\u0154\3\2\2\2\u0156\u0155\3\2\2\2\u0157\u015a\3\2\2\2\u0158\u0156"+
		"\3\2\2\2\u0158\u0159\3\2\2\2\u0159j\3\2\2\2\u015a\u0158\3\2\2\2\u015b"+
		"\u015f\t\t\2\2\u015c\u015e\5\7\4\2\u015d\u015c\3\2\2\2\u015e\u0161\3\2"+
		"\2\2\u015f\u015d\3\2\2\2\u015f\u0160\3\2\2\2\u0160l\3\2\2\2\u0161\u015f"+
		"\3\2\2\2\u0162\u0163\7\62\2\2\u0163\u0167\7z\2\2\u0164\u0165\7\62\2\2"+
		"\u0165\u0167\7Z\2\2\u0166\u0162\3\2\2\2\u0166\u0164\3\2\2\2\u0167\u0169"+
		"\3\2\2\2\u0168\u016a\5\t\5\2\u0169\u0168\3\2\2\2\u016a\u016b\3\2\2\2\u016b"+
		"\u0169\3\2\2\2\u016b\u016c\3\2\2\2\u016cn\3\2\2\2\u016d\u016f\7\62\2\2"+
		"\u016e\u0170\5\r\7\2\u016f\u016e\3\2\2\2\u0170\u0171\3\2\2\2\u0171\u016f"+
		"\3\2\2\2\u0171\u0172\3\2\2\2\u0172p\3\2\2\2\u0173\u0174\7\62\2\2\u0174"+
		"\u0178\7d\2\2\u0175\u0176\7\62\2\2\u0176\u0178\7D\2\2\u0177\u0173\3\2"+
		"\2\2\u0177\u0175\3\2\2\2\u0178\u017a\3\2\2\2\u0179\u017b\5\13\6\2\u017a"+
		"\u0179\3\2\2\2\u017b\u017c\3\2\2\2\u017c\u017a\3\2\2\2\u017c\u017d\3\2"+
		"\2\2\u017dr\3\2\2\2\u017e\u0180\5+\26\2\u017f\u0181\5u;\2\u0180\u017f"+
		"\3\2\2\2\u0180\u0181\3\2\2\2\u0181\u0182\3\2\2\2\u0182\u0183\5+\26\2\u0183"+
		"t\3\2\2\2\u0184\u0186\5w<\2\u0185\u0184\3\2\2\2\u0186\u0187\3\2\2\2\u0187"+
		"\u0185\3\2\2\2\u0187\u0188\3\2\2\2\u0188v\3\2\2\2\u0189\u018c\n\n\2\2"+
		"\u018a\u018c\5y=\2\u018b\u0189\3\2\2\2\u018b\u018a\3\2\2\2\u018cx\3\2"+
		"\2\2\u018d\u018e\7^\2\2\u018e\u01ae\t\13\2\2\u018f\u0190\7^\2\2\u0190"+
		"\u0191\7z\2\2\u0191\u0192\3\2\2\2\u0192\u0193\5\t\5\2\u0193\u0194\5\t"+
		"\5\2\u0194\u01ae\3\2\2\2\u0195\u0196\7^\2\2\u0196\u0197\7w\2\2\u0197\u0198"+
		"\3\2\2\2\u0198\u0199\7}\2\2\u0199\u019a\5\t\5\2\u019a\u019b\5\t\5\2\u019b"+
		"\u019c\5\t\5\2\u019c\u019d\5\t\5\2\u019d\u019e\7\177\2\2\u019e\u01ae\3"+
		"\2\2\2\u019f\u01a0\7^\2\2\u01a0\u01a1\7w\2\2\u01a1\u01a2\3\2\2\2\u01a2"+
		"\u01a3\7}\2\2\u01a3\u01a4\5\t\5\2\u01a4\u01a5\5\t\5\2\u01a5\u01a6\5\t"+
		"\5\2\u01a6\u01a7\5\t\5\2\u01a7\u01a8\5\t\5\2\u01a8\u01a9\5\t\5\2\u01a9"+
		"\u01aa\5\t\5\2\u01aa\u01ab\5\t\5\2\u01ab\u01ac\7\177\2\2\u01ac\u01ae\3"+
		"\2\2\2\u01ad\u018d\3\2\2\2\u01ad\u018f\3\2\2\2\u01ad\u0195\3\2\2\2\u01ad"+
		"\u019f\3\2\2\2\u01aez\3\2\2\2\u01af\u01b1\5}?\2\u01b0\u01af\3\2\2\2\u01b0"+
		"\u01b1\3\2\2\2\u01b1\u01b2\3\2\2\2\u01b2\u01b3\7\60\2\2\u01b3\u01b5\5"+
		"}?\2\u01b4\u01b6\5\177@\2\u01b5\u01b4\3\2\2\2\u01b5\u01b6\3\2\2\2\u01b6"+
		"\u01bd\3\2\2\2\u01b7\u01b8\5}?\2\u01b8\u01ba\7\60\2\2\u01b9\u01bb\5\177"+
		"@\2\u01ba\u01b9\3\2\2\2\u01ba\u01bb\3\2\2\2\u01bb\u01bd\3\2\2\2\u01bc"+
		"\u01b0\3\2\2\2\u01bc\u01b7\3\2\2\2\u01bd|\3\2\2\2\u01be\u01c0\5\7\4\2"+
		"\u01bf\u01be\3\2\2\2\u01c0\u01c1\3\2\2\2\u01c1\u01bf\3\2\2\2\u01c1\u01c2"+
		"\3\2\2\2\u01c2~\3\2\2\2\u01c3\u01c5\5\u0081A\2\u01c4\u01c6\5\u0083B\2"+
		"\u01c5\u01c4\3\2\2\2\u01c5\u01c6\3\2\2\2\u01c6\u01c7\3\2\2\2\u01c7\u01c8"+
		"\5k\66\2\u01c8\u0080\3\2\2\2\u01c9\u01ca\t\f\2\2\u01ca\u0082\3\2\2\2\u01cb"+
		"\u01cc\t\r\2\2\u01cc\u0084\3\2\2\2\u01cd\u01cf\5\17\b\2\u01ce\u01cd\3"+
		"\2\2\2\u01cf\u01d0\3\2\2\2\u01d0\u01ce\3\2\2\2\u01d0\u01d1\3\2\2\2\u01d1"+
		"\u01d2\3\2\2\2\u01d2\u01d3\bC\2\2\u01d3\u0086\3\2\2\2\u01d4\u01d5\7\61"+
		"\2\2\u01d5\u01d6\7,\2\2\u01d6\u01db\3\2\2\2\u01d7\u01da\5\u0087D\2\u01d8"+
		"\u01da\13\2\2\2\u01d9\u01d7\3\2\2\2\u01d9\u01d8\3\2\2\2\u01da\u01dd\3"+
		"\2\2\2\u01db\u01dc\3\2\2\2\u01db\u01d9\3\2\2\2\u01dc\u01de\3\2\2\2\u01dd"+
		"\u01db\3\2\2\2\u01de\u01df\7,\2\2\u01df\u01e0\7\61\2\2\u01e0\u01e1\3\2"+
		"\2\2\u01e1\u01e2\bD\2\2\u01e2\u0088\3\2\2\2\u01e3\u01e4\7\61\2\2\u01e4"+
		"\u01e5\7\61\2\2\u01e5\u01e9\3\2\2\2\u01e6\u01e8\13\2\2\2\u01e7\u01e6\3"+
		"\2\2\2\u01e8\u01eb\3\2\2\2\u01e9\u01ea\3\2\2\2\u01e9\u01e7\3\2\2\2\u01ea"+
		"\u01ed\3\2\2\2\u01eb\u01e9\3\2\2\2\u01ec\u01ee\t\16\2\2\u01ed\u01ec\3"+
		"\2\2\2\u01ee\u01ef\3\2\2\2\u01ef\u01f0\bE\2\2\u01f0\u008a\3\2\2\2\32\2"+
		"\u0156\u0158\u015f\u0166\u016b\u0171\u0177\u017c\u0180\u0187\u018b\u01ad"+
		"\u01b0\u01b5\u01ba\u01bc\u01c1\u01c5\u01d0\u01d9\u01db\u01e9\u01ed\3\b"+
		"\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}