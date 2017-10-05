// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLParser.g4 by ANTLR 4.7
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class IDLParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		IMPORT=1, STRING_LIT=2, SEMICOLON=3, NAMESPACE=4, IDENT=5, LBRACE=6, RBRACE=7, 
		STRUCT=8, INTERFACE=9, COLON=10, LPAREN=11, RPAREN=12, COMMA=13, LBRACKET=14, 
		IN=15, RBRACKET=16, OUT=17, CONST=18, EQUALS=19, STRING=20, CLASS_ID=21, 
		ENUM=22, DECIMAL_LIT=23, HEX_LIT=24, OCT_LIT=25, BIN_LIT=26, FLOAT_LIT=27, 
		STAR=28, VOID=29, RESULT=30, U8=31, S8=32, CHAR=33, BYTE=34, U16=35, S16=36, 
		SHORT=37, U32=38, S32=39, INT=40, U64=41, S64=42, F32=43, FLOAT=44, F64=45, 
		DOUBLE=46;
	public static final int
		RULE_main = 0, RULE_global_statements = 1, RULE_global_statement = 2, 
		RULE_import_stmt = 3, RULE_namespace_stmt = 4, RULE_namespace_block = 5, 
		RULE_namespace_item = 6, RULE_struct_stmt = 7, RULE_struct_decl = 8, RULE_struct_fwd = 9, 
		RULE_struct_block = 10, RULE_struct_item = 11, RULE_interface_stmt = 12, 
		RULE_interface_fwd = 13, RULE_interface_decl = 14, RULE_interface_super = 15, 
		RULE_interface_block = 16, RULE_interface_item = 17, RULE_function_decl = 18, 
		RULE_function_param_list = 19, RULE_function_param = 20, RULE_param_dir_qualifier = 21, 
		RULE_const_def = 22, RULE_enum_def = 23, RULE_enum_type = 24, RULE_enum_elements = 25, 
		RULE_enum_item = 26, RULE_any_literal = 27, RULE_numeric_lit = 28, RULE_integer_lit = 29, 
		RULE_float_lit = 30, RULE_string_lit = 31, RULE_qualified_ident = 32, 
		RULE_qualified_part = 33, RULE_qualified_separator = 34, RULE_member_decl = 35, 
		RULE_type_decl = 36, RULE_type_modifier = 37, RULE_pointer_type = 38, 
		RULE_any_type = 39, RULE_utility_type = 40, RULE_integral_type = 41, RULE_float_type = 42;
	public static final String[] ruleNames = {
		"main", "global_statements", "global_statement", "import_stmt", "namespace_stmt", 
		"namespace_block", "namespace_item", "struct_stmt", "struct_decl", "struct_fwd", 
		"struct_block", "struct_item", "interface_stmt", "interface_fwd", "interface_decl", 
		"interface_super", "interface_block", "interface_item", "function_decl", 
		"function_param_list", "function_param", "param_dir_qualifier", "const_def", 
		"enum_def", "enum_type", "enum_elements", "enum_item", "any_literal", 
		"numeric_lit", "integer_lit", "float_lit", "string_lit", "qualified_ident", 
		"qualified_part", "qualified_separator", "member_decl", "type_decl", "type_modifier", 
		"pointer_type", "any_type", "utility_type", "integral_type", "float_type"
	};

	private static final String[] _LITERAL_NAMES = {
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "IMPORT", "STRING_LIT", "SEMICOLON", "NAMESPACE", "IDENT", "LBRACE", 
		"RBRACE", "STRUCT", "INTERFACE", "COLON", "LPAREN", "RPAREN", "COMMA", 
		"LBRACKET", "IN", "RBRACKET", "OUT", "CONST", "EQUALS", "STRING", "CLASS_ID", 
		"ENUM", "DECIMAL_LIT", "HEX_LIT", "OCT_LIT", "BIN_LIT", "FLOAT_LIT", "STAR", 
		"VOID", "RESULT", "U8", "S8", "CHAR", "BYTE", "U16", "S16", "SHORT", "U32", 
		"S32", "INT", "U64", "S64", "F32", "FLOAT", "F64", "DOUBLE"
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

	@Override
	public String getGrammarFileName() { return "IDLParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public IDLParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class MainContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(IDLParser.EOF, 0); }
		public Global_statementsContext global_statements() {
			return getRuleContext(Global_statementsContext.class,0);
		}
		public MainContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_main; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterMain(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitMain(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitMain(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MainContext main() throws RecognitionException {
		MainContext _localctx = new MainContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_main);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(87);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << IMPORT) | (1L << NAMESPACE) | (1L << STRUCT) | (1L << INTERFACE) | (1L << CONST) | (1L << ENUM))) != 0)) {
				{
				setState(86);
				global_statements();
				}
			}

			setState(89);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Global_statementsContext extends ParserRuleContext {
		public List<Global_statementContext> global_statement() {
			return getRuleContexts(Global_statementContext.class);
		}
		public Global_statementContext global_statement(int i) {
			return getRuleContext(Global_statementContext.class,i);
		}
		public Global_statementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_global_statements; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterGlobal_statements(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitGlobal_statements(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitGlobal_statements(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Global_statementsContext global_statements() throws RecognitionException {
		Global_statementsContext _localctx = new Global_statementsContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_global_statements);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(92); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(91);
				global_statement();
				}
				}
				setState(94); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << IMPORT) | (1L << NAMESPACE) | (1L << STRUCT) | (1L << INTERFACE) | (1L << CONST) | (1L << ENUM))) != 0) );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Global_statementContext extends ParserRuleContext {
		public Import_stmtContext import_stmt() {
			return getRuleContext(Import_stmtContext.class,0);
		}
		public Namespace_stmtContext namespace_stmt() {
			return getRuleContext(Namespace_stmtContext.class,0);
		}
		public Struct_stmtContext struct_stmt() {
			return getRuleContext(Struct_stmtContext.class,0);
		}
		public Interface_stmtContext interface_stmt() {
			return getRuleContext(Interface_stmtContext.class,0);
		}
		public Const_defContext const_def() {
			return getRuleContext(Const_defContext.class,0);
		}
		public Enum_defContext enum_def() {
			return getRuleContext(Enum_defContext.class,0);
		}
		public Global_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_global_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterGlobal_statement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitGlobal_statement(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitGlobal_statement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Global_statementContext global_statement() throws RecognitionException {
		Global_statementContext _localctx = new Global_statementContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_global_statement);
		try {
			setState(102);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IMPORT:
				enterOuterAlt(_localctx, 1);
				{
				setState(96);
				import_stmt();
				}
				break;
			case NAMESPACE:
				enterOuterAlt(_localctx, 2);
				{
				setState(97);
				namespace_stmt();
				}
				break;
			case STRUCT:
				enterOuterAlt(_localctx, 3);
				{
				setState(98);
				struct_stmt();
				}
				break;
			case INTERFACE:
				enterOuterAlt(_localctx, 4);
				{
				setState(99);
				interface_stmt();
				}
				break;
			case CONST:
				enterOuterAlt(_localctx, 5);
				{
				setState(100);
				const_def();
				}
				break;
			case ENUM:
				enterOuterAlt(_localctx, 6);
				{
				setState(101);
				enum_def();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Import_stmtContext extends ParserRuleContext {
		public TerminalNode IMPORT() { return getToken(IDLParser.IMPORT, 0); }
		public TerminalNode STRING_LIT() { return getToken(IDLParser.STRING_LIT, 0); }
		public TerminalNode SEMICOLON() { return getToken(IDLParser.SEMICOLON, 0); }
		public Import_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_import_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterImport_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitImport_stmt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitImport_stmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Import_stmtContext import_stmt() throws RecognitionException {
		Import_stmtContext _localctx = new Import_stmtContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_import_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(104);
			match(IMPORT);
			setState(105);
			match(STRING_LIT);
			setState(106);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Namespace_stmtContext extends ParserRuleContext {
		public TerminalNode NAMESPACE() { return getToken(IDLParser.NAMESPACE, 0); }
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public Namespace_blockContext namespace_block() {
			return getRuleContext(Namespace_blockContext.class,0);
		}
		public Namespace_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterNamespace_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitNamespace_stmt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitNamespace_stmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_stmtContext namespace_stmt() throws RecognitionException {
		Namespace_stmtContext _localctx = new Namespace_stmtContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_namespace_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(108);
			match(NAMESPACE);
			setState(109);
			match(IDENT);
			setState(110);
			namespace_block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Namespace_blockContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(IDLParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(IDLParser.RBRACE, 0); }
		public List<Namespace_itemContext> namespace_item() {
			return getRuleContexts(Namespace_itemContext.class);
		}
		public Namespace_itemContext namespace_item(int i) {
			return getRuleContext(Namespace_itemContext.class,i);
		}
		public Namespace_blockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_block; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterNamespace_block(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitNamespace_block(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitNamespace_block(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_blockContext namespace_block() throws RecognitionException {
		Namespace_blockContext _localctx = new Namespace_blockContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_namespace_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(112);
			match(LBRACE);
			setState(116);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << NAMESPACE) | (1L << STRUCT) | (1L << INTERFACE) | (1L << CONST))) != 0)) {
				{
				{
				setState(113);
				namespace_item();
				}
				}
				setState(118);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(119);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Namespace_itemContext extends ParserRuleContext {
		public Struct_stmtContext struct_stmt() {
			return getRuleContext(Struct_stmtContext.class,0);
		}
		public Namespace_stmtContext namespace_stmt() {
			return getRuleContext(Namespace_stmtContext.class,0);
		}
		public Interface_stmtContext interface_stmt() {
			return getRuleContext(Interface_stmtContext.class,0);
		}
		public Const_defContext const_def() {
			return getRuleContext(Const_defContext.class,0);
		}
		public Namespace_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterNamespace_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitNamespace_item(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitNamespace_item(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_itemContext namespace_item() throws RecognitionException {
		Namespace_itemContext _localctx = new Namespace_itemContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_namespace_item);
		try {
			setState(125);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case STRUCT:
				enterOuterAlt(_localctx, 1);
				{
				setState(121);
				struct_stmt();
				}
				break;
			case NAMESPACE:
				enterOuterAlt(_localctx, 2);
				{
				setState(122);
				namespace_stmt();
				}
				break;
			case INTERFACE:
				enterOuterAlt(_localctx, 3);
				{
				setState(123);
				interface_stmt();
				}
				break;
			case CONST:
				enterOuterAlt(_localctx, 4);
				{
				setState(124);
				const_def();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Struct_stmtContext extends ParserRuleContext {
		public Struct_declContext struct_decl() {
			return getRuleContext(Struct_declContext.class,0);
		}
		public Struct_fwdContext struct_fwd() {
			return getRuleContext(Struct_fwdContext.class,0);
		}
		public Struct_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_struct_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterStruct_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitStruct_stmt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitStruct_stmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Struct_stmtContext struct_stmt() throws RecognitionException {
		Struct_stmtContext _localctx = new Struct_stmtContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_struct_stmt);
		try {
			setState(129);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(127);
				struct_decl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(128);
				struct_fwd();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Struct_declContext extends ParserRuleContext {
		public TerminalNode STRUCT() { return getToken(IDLParser.STRUCT, 0); }
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public Struct_blockContext struct_block() {
			return getRuleContext(Struct_blockContext.class,0);
		}
		public Struct_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_struct_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterStruct_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitStruct_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitStruct_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Struct_declContext struct_decl() throws RecognitionException {
		Struct_declContext _localctx = new Struct_declContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_struct_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(131);
			match(STRUCT);
			setState(132);
			match(IDENT);
			setState(133);
			struct_block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Struct_fwdContext extends ParserRuleContext {
		public TerminalNode STRUCT() { return getToken(IDLParser.STRUCT, 0); }
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public TerminalNode SEMICOLON() { return getToken(IDLParser.SEMICOLON, 0); }
		public Struct_fwdContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_struct_fwd; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterStruct_fwd(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitStruct_fwd(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitStruct_fwd(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Struct_fwdContext struct_fwd() throws RecognitionException {
		Struct_fwdContext _localctx = new Struct_fwdContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_struct_fwd);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(135);
			match(STRUCT);
			setState(136);
			match(IDENT);
			setState(137);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Struct_blockContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(IDLParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(IDLParser.RBRACE, 0); }
		public List<Struct_itemContext> struct_item() {
			return getRuleContexts(Struct_itemContext.class);
		}
		public Struct_itemContext struct_item(int i) {
			return getRuleContext(Struct_itemContext.class,i);
		}
		public Struct_blockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_struct_block; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterStruct_block(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitStruct_block(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitStruct_block(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Struct_blockContext struct_block() throws RecognitionException {
		Struct_blockContext _localctx = new Struct_blockContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_struct_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(139);
			match(LBRACE);
			setState(143);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << IDENT) | (1L << CONST) | (1L << VOID) | (1L << RESULT) | (1L << U8) | (1L << S8) | (1L << CHAR) | (1L << BYTE) | (1L << U16) | (1L << S16) | (1L << SHORT) | (1L << U32) | (1L << S32) | (1L << INT) | (1L << U64) | (1L << S64) | (1L << F32) | (1L << FLOAT) | (1L << F64) | (1L << DOUBLE))) != 0)) {
				{
				{
				setState(140);
				struct_item();
				}
				}
				setState(145);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(146);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Struct_itemContext extends ParserRuleContext {
		public Member_declContext member_decl() {
			return getRuleContext(Member_declContext.class,0);
		}
		public Struct_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_struct_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterStruct_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitStruct_item(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitStruct_item(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Struct_itemContext struct_item() throws RecognitionException {
		Struct_itemContext _localctx = new Struct_itemContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_struct_item);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(148);
			member_decl();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Interface_stmtContext extends ParserRuleContext {
		public Interface_declContext interface_decl() {
			return getRuleContext(Interface_declContext.class,0);
		}
		public Interface_fwdContext interface_fwd() {
			return getRuleContext(Interface_fwdContext.class,0);
		}
		public Interface_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interface_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterInterface_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitInterface_stmt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitInterface_stmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Interface_stmtContext interface_stmt() throws RecognitionException {
		Interface_stmtContext _localctx = new Interface_stmtContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_interface_stmt);
		try {
			setState(152);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(150);
				interface_decl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(151);
				interface_fwd();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Interface_fwdContext extends ParserRuleContext {
		public TerminalNode INTERFACE() { return getToken(IDLParser.INTERFACE, 0); }
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public TerminalNode SEMICOLON() { return getToken(IDLParser.SEMICOLON, 0); }
		public Interface_fwdContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interface_fwd; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterInterface_fwd(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitInterface_fwd(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitInterface_fwd(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Interface_fwdContext interface_fwd() throws RecognitionException {
		Interface_fwdContext _localctx = new Interface_fwdContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_interface_fwd);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(154);
			match(INTERFACE);
			setState(155);
			match(IDENT);
			setState(156);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Interface_declContext extends ParserRuleContext {
		public TerminalNode INTERFACE() { return getToken(IDLParser.INTERFACE, 0); }
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public Interface_blockContext interface_block() {
			return getRuleContext(Interface_blockContext.class,0);
		}
		public Interface_superContext interface_super() {
			return getRuleContext(Interface_superContext.class,0);
		}
		public Interface_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interface_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterInterface_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitInterface_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitInterface_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Interface_declContext interface_decl() throws RecognitionException {
		Interface_declContext _localctx = new Interface_declContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_interface_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(158);
			match(INTERFACE);
			setState(159);
			match(IDENT);
			setState(161);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COLON) {
				{
				setState(160);
				interface_super();
				}
			}

			setState(163);
			interface_block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Interface_superContext extends ParserRuleContext {
		public TerminalNode COLON() { return getToken(IDLParser.COLON, 0); }
		public Qualified_identContext qualified_ident() {
			return getRuleContext(Qualified_identContext.class,0);
		}
		public Interface_superContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interface_super; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterInterface_super(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitInterface_super(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitInterface_super(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Interface_superContext interface_super() throws RecognitionException {
		Interface_superContext _localctx = new Interface_superContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_interface_super);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(165);
			match(COLON);
			setState(166);
			qualified_ident();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Interface_blockContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(IDLParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(IDLParser.RBRACE, 0); }
		public List<Interface_itemContext> interface_item() {
			return getRuleContexts(Interface_itemContext.class);
		}
		public Interface_itemContext interface_item(int i) {
			return getRuleContext(Interface_itemContext.class,i);
		}
		public Interface_blockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interface_block; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterInterface_block(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitInterface_block(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitInterface_block(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Interface_blockContext interface_block() throws RecognitionException {
		Interface_blockContext _localctx = new Interface_blockContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_interface_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(168);
			match(LBRACE);
			setState(172);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << IDENT) | (1L << CONST) | (1L << ENUM) | (1L << VOID) | (1L << RESULT) | (1L << U8) | (1L << S8) | (1L << CHAR) | (1L << BYTE) | (1L << U16) | (1L << S16) | (1L << SHORT) | (1L << U32) | (1L << S32) | (1L << INT) | (1L << U64) | (1L << S64) | (1L << F32) | (1L << FLOAT) | (1L << F64) | (1L << DOUBLE))) != 0)) {
				{
				{
				setState(169);
				interface_item();
				}
				}
				setState(174);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(175);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Interface_itemContext extends ParserRuleContext {
		public Function_declContext function_decl() {
			return getRuleContext(Function_declContext.class,0);
		}
		public Const_defContext const_def() {
			return getRuleContext(Const_defContext.class,0);
		}
		public Enum_defContext enum_def() {
			return getRuleContext(Enum_defContext.class,0);
		}
		public Interface_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interface_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterInterface_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitInterface_item(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitInterface_item(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Interface_itemContext interface_item() throws RecognitionException {
		Interface_itemContext _localctx = new Interface_itemContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_interface_item);
		try {
			setState(180);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(177);
				function_decl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(178);
				const_def();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(179);
				enum_def();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Function_declContext extends ParserRuleContext {
		public Type_declContext type_decl() {
			return getRuleContext(Type_declContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public TerminalNode LPAREN() { return getToken(IDLParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(IDLParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(IDLParser.SEMICOLON, 0); }
		public Function_param_listContext function_param_list() {
			return getRuleContext(Function_param_listContext.class,0);
		}
		public Function_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterFunction_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitFunction_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitFunction_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Function_declContext function_decl() throws RecognitionException {
		Function_declContext _localctx = new Function_declContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_function_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(182);
			type_decl();
			setState(183);
			match(IDENT);
			setState(184);
			match(LPAREN);
			setState(186);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << IDENT) | (1L << LBRACKET) | (1L << VOID) | (1L << RESULT) | (1L << U8) | (1L << S8) | (1L << CHAR) | (1L << BYTE) | (1L << U16) | (1L << S16) | (1L << SHORT) | (1L << U32) | (1L << S32) | (1L << INT) | (1L << U64) | (1L << S64) | (1L << F32) | (1L << FLOAT) | (1L << F64) | (1L << DOUBLE))) != 0)) {
				{
				setState(185);
				function_param_list();
				}
			}

			setState(188);
			match(RPAREN);
			setState(189);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Function_param_listContext extends ParserRuleContext {
		public List<Function_paramContext> function_param() {
			return getRuleContexts(Function_paramContext.class);
		}
		public Function_paramContext function_param(int i) {
			return getRuleContext(Function_paramContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(IDLParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(IDLParser.COMMA, i);
		}
		public Function_param_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function_param_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterFunction_param_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitFunction_param_list(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitFunction_param_list(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Function_param_listContext function_param_list() throws RecognitionException {
		Function_param_listContext _localctx = new Function_param_listContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_function_param_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(191);
			function_param();
			setState(196);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(192);
				match(COMMA);
				setState(193);
				function_param();
				}
				}
				setState(198);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Function_paramContext extends ParserRuleContext {
		public Any_typeContext any_type() {
			return getRuleContext(Any_typeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public Param_dir_qualifierContext param_dir_qualifier() {
			return getRuleContext(Param_dir_qualifierContext.class,0);
		}
		public Pointer_typeContext pointer_type() {
			return getRuleContext(Pointer_typeContext.class,0);
		}
		public Function_paramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function_param; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterFunction_param(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitFunction_param(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitFunction_param(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Function_paramContext function_param() throws RecognitionException {
		Function_paramContext _localctx = new Function_paramContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_function_param);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(200);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LBRACKET) {
				{
				setState(199);
				param_dir_qualifier();
				}
			}

			setState(202);
			any_type();
			setState(204);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==STAR) {
				{
				setState(203);
				pointer_type();
				}
			}

			setState(206);
			match(IDENT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Param_dir_qualifierContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(IDLParser.LBRACKET, 0); }
		public TerminalNode IN() { return getToken(IDLParser.IN, 0); }
		public TerminalNode RBRACKET() { return getToken(IDLParser.RBRACKET, 0); }
		public TerminalNode OUT() { return getToken(IDLParser.OUT, 0); }
		public TerminalNode COMMA() { return getToken(IDLParser.COMMA, 0); }
		public Param_dir_qualifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param_dir_qualifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterParam_dir_qualifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitParam_dir_qualifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitParam_dir_qualifier(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Param_dir_qualifierContext param_dir_qualifier() throws RecognitionException {
		Param_dir_qualifierContext _localctx = new Param_dir_qualifierContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_param_dir_qualifier);
		try {
			setState(219);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(208);
				match(LBRACKET);
				setState(209);
				match(IN);
				setState(210);
				match(RBRACKET);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(211);
				match(LBRACKET);
				setState(212);
				match(OUT);
				setState(213);
				match(RBRACKET);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(214);
				match(LBRACKET);
				setState(215);
				match(IN);
				setState(216);
				match(COMMA);
				setState(217);
				match(OUT);
				setState(218);
				match(RBRACKET);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Const_defContext extends ParserRuleContext {
		public TerminalNode CONST() { return getToken(IDLParser.CONST, 0); }
		public Integral_typeContext integral_type() {
			return getRuleContext(Integral_typeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public TerminalNode EQUALS() { return getToken(IDLParser.EQUALS, 0); }
		public Integer_litContext integer_lit() {
			return getRuleContext(Integer_litContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(IDLParser.SEMICOLON, 0); }
		public Float_typeContext float_type() {
			return getRuleContext(Float_typeContext.class,0);
		}
		public Float_litContext float_lit() {
			return getRuleContext(Float_litContext.class,0);
		}
		public TerminalNode STRING() { return getToken(IDLParser.STRING, 0); }
		public String_litContext string_lit() {
			return getRuleContext(String_litContext.class,0);
		}
		public TerminalNode CLASS_ID() { return getToken(IDLParser.CLASS_ID, 0); }
		public Const_defContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_const_def; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterConst_def(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitConst_def(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitConst_def(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Const_defContext const_def() throws RecognitionException {
		Const_defContext _localctx = new Const_defContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_const_def);
		try {
			setState(249);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(221);
				match(CONST);
				setState(222);
				integral_type();
				setState(223);
				match(IDENT);
				setState(224);
				match(EQUALS);
				setState(225);
				integer_lit();
				setState(226);
				match(SEMICOLON);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(228);
				match(CONST);
				setState(229);
				float_type();
				setState(230);
				match(IDENT);
				setState(231);
				match(EQUALS);
				setState(232);
				float_lit();
				setState(233);
				match(SEMICOLON);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(235);
				match(CONST);
				setState(236);
				match(STRING);
				setState(237);
				match(IDENT);
				setState(238);
				match(EQUALS);
				setState(239);
				string_lit();
				setState(240);
				match(SEMICOLON);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(242);
				match(CONST);
				setState(243);
				match(CLASS_ID);
				setState(244);
				match(IDENT);
				setState(245);
				match(EQUALS);
				setState(246);
				string_lit();
				setState(247);
				match(SEMICOLON);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Enum_defContext extends ParserRuleContext {
		public TerminalNode ENUM() { return getToken(IDLParser.ENUM, 0); }
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public TerminalNode LBRACE() { return getToken(IDLParser.LBRACE, 0); }
		public Enum_elementsContext enum_elements() {
			return getRuleContext(Enum_elementsContext.class,0);
		}
		public TerminalNode RBRACE() { return getToken(IDLParser.RBRACE, 0); }
		public Enum_typeContext enum_type() {
			return getRuleContext(Enum_typeContext.class,0);
		}
		public Enum_defContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enum_def; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterEnum_def(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitEnum_def(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitEnum_def(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Enum_defContext enum_def() throws RecognitionException {
		Enum_defContext _localctx = new Enum_defContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_enum_def);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(251);
			match(ENUM);
			setState(252);
			match(IDENT);
			setState(254);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COLON) {
				{
				setState(253);
				enum_type();
				}
			}

			setState(256);
			match(LBRACE);
			setState(257);
			enum_elements();
			setState(258);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Enum_typeContext extends ParserRuleContext {
		public TerminalNode COLON() { return getToken(IDLParser.COLON, 0); }
		public Integral_typeContext integral_type() {
			return getRuleContext(Integral_typeContext.class,0);
		}
		public Enum_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enum_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterEnum_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitEnum_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitEnum_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Enum_typeContext enum_type() throws RecognitionException {
		Enum_typeContext _localctx = new Enum_typeContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_enum_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(260);
			match(COLON);
			setState(261);
			integral_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Enum_elementsContext extends ParserRuleContext {
		public List<Enum_itemContext> enum_item() {
			return getRuleContexts(Enum_itemContext.class);
		}
		public Enum_itemContext enum_item(int i) {
			return getRuleContext(Enum_itemContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(IDLParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(IDLParser.COMMA, i);
		}
		public Enum_elementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enum_elements; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterEnum_elements(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitEnum_elements(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitEnum_elements(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Enum_elementsContext enum_elements() throws RecognitionException {
		Enum_elementsContext _localctx = new Enum_elementsContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_enum_elements);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(263);
			enum_item();
			setState(268);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(264);
				match(COMMA);
				setState(265);
				enum_item();
				}
				}
				setState(270);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Enum_itemContext extends ParserRuleContext {
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public TerminalNode EQUALS() { return getToken(IDLParser.EQUALS, 0); }
		public Integer_litContext integer_lit() {
			return getRuleContext(Integer_litContext.class,0);
		}
		public Enum_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enum_item; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterEnum_item(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitEnum_item(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitEnum_item(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Enum_itemContext enum_item() throws RecognitionException {
		Enum_itemContext _localctx = new Enum_itemContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_enum_item);
		try {
			setState(275);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(271);
				match(IDENT);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(272);
				match(IDENT);
				setState(273);
				match(EQUALS);
				setState(274);
				integer_lit();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Any_literalContext extends ParserRuleContext {
		public Numeric_litContext numeric_lit() {
			return getRuleContext(Numeric_litContext.class,0);
		}
		public String_litContext string_lit() {
			return getRuleContext(String_litContext.class,0);
		}
		public Any_literalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_any_literal; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterAny_literal(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitAny_literal(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitAny_literal(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Any_literalContext any_literal() throws RecognitionException {
		Any_literalContext _localctx = new Any_literalContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_any_literal);
		try {
			setState(279);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case DECIMAL_LIT:
			case HEX_LIT:
			case OCT_LIT:
			case BIN_LIT:
			case FLOAT_LIT:
				enterOuterAlt(_localctx, 1);
				{
				setState(277);
				numeric_lit();
				}
				break;
			case STRING_LIT:
				enterOuterAlt(_localctx, 2);
				{
				setState(278);
				string_lit();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Numeric_litContext extends ParserRuleContext {
		public Integer_litContext integer_lit() {
			return getRuleContext(Integer_litContext.class,0);
		}
		public Float_litContext float_lit() {
			return getRuleContext(Float_litContext.class,0);
		}
		public Numeric_litContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numeric_lit; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterNumeric_lit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitNumeric_lit(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitNumeric_lit(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Numeric_litContext numeric_lit() throws RecognitionException {
		Numeric_litContext _localctx = new Numeric_litContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_numeric_lit);
		try {
			setState(283);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case DECIMAL_LIT:
			case HEX_LIT:
			case OCT_LIT:
			case BIN_LIT:
				enterOuterAlt(_localctx, 1);
				{
				setState(281);
				integer_lit();
				}
				break;
			case FLOAT_LIT:
				enterOuterAlt(_localctx, 2);
				{
				setState(282);
				float_lit();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Integer_litContext extends ParserRuleContext {
		public TerminalNode DECIMAL_LIT() { return getToken(IDLParser.DECIMAL_LIT, 0); }
		public TerminalNode HEX_LIT() { return getToken(IDLParser.HEX_LIT, 0); }
		public TerminalNode OCT_LIT() { return getToken(IDLParser.OCT_LIT, 0); }
		public TerminalNode BIN_LIT() { return getToken(IDLParser.BIN_LIT, 0); }
		public Integer_litContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_integer_lit; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterInteger_lit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitInteger_lit(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitInteger_lit(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Integer_litContext integer_lit() throws RecognitionException {
		Integer_litContext _localctx = new Integer_litContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_integer_lit);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(285);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << DECIMAL_LIT) | (1L << HEX_LIT) | (1L << OCT_LIT) | (1L << BIN_LIT))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Float_litContext extends ParserRuleContext {
		public TerminalNode FLOAT_LIT() { return getToken(IDLParser.FLOAT_LIT, 0); }
		public Float_litContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_float_lit; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterFloat_lit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitFloat_lit(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitFloat_lit(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Float_litContext float_lit() throws RecognitionException {
		Float_litContext _localctx = new Float_litContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_float_lit);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(287);
			match(FLOAT_LIT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class String_litContext extends ParserRuleContext {
		public TerminalNode STRING_LIT() { return getToken(IDLParser.STRING_LIT, 0); }
		public String_litContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_string_lit; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterString_lit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitString_lit(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitString_lit(this);
			else return visitor.visitChildren(this);
		}
	}

	public final String_litContext string_lit() throws RecognitionException {
		String_litContext _localctx = new String_litContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_string_lit);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(289);
			match(STRING_LIT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Qualified_identContext extends ParserRuleContext {
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public Qualified_separatorContext qualified_separator() {
			return getRuleContext(Qualified_separatorContext.class,0);
		}
		public Qualified_partContext qualified_part() {
			return getRuleContext(Qualified_partContext.class,0);
		}
		public Qualified_identContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qualified_ident; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterQualified_ident(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitQualified_ident(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitQualified_ident(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Qualified_identContext qualified_ident() throws RecognitionException {
		Qualified_identContext _localctx = new Qualified_identContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_qualified_ident);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(292);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COLON) {
				{
				setState(291);
				qualified_separator();
				}
			}

			setState(294);
			match(IDENT);
			setState(296);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COLON) {
				{
				setState(295);
				qualified_part();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Qualified_partContext extends ParserRuleContext {
		public Qualified_separatorContext qualified_separator() {
			return getRuleContext(Qualified_separatorContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public Qualified_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qualified_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterQualified_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitQualified_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitQualified_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Qualified_partContext qualified_part() throws RecognitionException {
		Qualified_partContext _localctx = new Qualified_partContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_qualified_part);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(298);
			qualified_separator();
			setState(299);
			match(IDENT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Qualified_separatorContext extends ParserRuleContext {
		public List<TerminalNode> COLON() { return getTokens(IDLParser.COLON); }
		public TerminalNode COLON(int i) {
			return getToken(IDLParser.COLON, i);
		}
		public Qualified_separatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qualified_separator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterQualified_separator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitQualified_separator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitQualified_separator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Qualified_separatorContext qualified_separator() throws RecognitionException {
		Qualified_separatorContext _localctx = new Qualified_separatorContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_qualified_separator);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(301);
			match(COLON);
			setState(302);
			match(COLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Member_declContext extends ParserRuleContext {
		public Type_declContext type_decl() {
			return getRuleContext(Type_declContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public TerminalNode SEMICOLON() { return getToken(IDLParser.SEMICOLON, 0); }
		public Member_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_member_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterMember_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitMember_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitMember_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Member_declContext member_decl() throws RecognitionException {
		Member_declContext _localctx = new Member_declContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_member_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(304);
			type_decl();
			setState(305);
			match(IDENT);
			setState(306);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Type_declContext extends ParserRuleContext {
		public Any_typeContext any_type() {
			return getRuleContext(Any_typeContext.class,0);
		}
		public Type_modifierContext type_modifier() {
			return getRuleContext(Type_modifierContext.class,0);
		}
		public Pointer_typeContext pointer_type() {
			return getRuleContext(Pointer_typeContext.class,0);
		}
		public Type_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterType_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitType_decl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitType_decl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_declContext type_decl() throws RecognitionException {
		Type_declContext _localctx = new Type_declContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_type_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(309);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==CONST) {
				{
				setState(308);
				type_modifier();
				}
			}

			setState(311);
			any_type();
			setState(313);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==STAR) {
				{
				setState(312);
				pointer_type();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Type_modifierContext extends ParserRuleContext {
		public TerminalNode CONST() { return getToken(IDLParser.CONST, 0); }
		public Type_modifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_modifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterType_modifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitType_modifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitType_modifier(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_modifierContext type_modifier() throws RecognitionException {
		Type_modifierContext _localctx = new Type_modifierContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_type_modifier);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(315);
			match(CONST);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Pointer_typeContext extends ParserRuleContext {
		public List<TerminalNode> STAR() { return getTokens(IDLParser.STAR); }
		public TerminalNode STAR(int i) {
			return getToken(IDLParser.STAR, i);
		}
		public Pointer_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pointer_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterPointer_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitPointer_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitPointer_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Pointer_typeContext pointer_type() throws RecognitionException {
		Pointer_typeContext _localctx = new Pointer_typeContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_pointer_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(318); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(317);
				match(STAR);
				}
				}
				setState(320); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==STAR );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Any_typeContext extends ParserRuleContext {
		public Integral_typeContext integral_type() {
			return getRuleContext(Integral_typeContext.class,0);
		}
		public Float_typeContext float_type() {
			return getRuleContext(Float_typeContext.class,0);
		}
		public Utility_typeContext utility_type() {
			return getRuleContext(Utility_typeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(IDLParser.IDENT, 0); }
		public Any_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_any_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterAny_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitAny_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitAny_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Any_typeContext any_type() throws RecognitionException {
		Any_typeContext _localctx = new Any_typeContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_any_type);
		try {
			setState(326);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case U8:
			case S8:
			case CHAR:
			case BYTE:
			case U16:
			case S16:
			case SHORT:
			case U32:
			case S32:
			case INT:
			case U64:
			case S64:
				enterOuterAlt(_localctx, 1);
				{
				setState(322);
				integral_type();
				}
				break;
			case F32:
			case FLOAT:
			case F64:
			case DOUBLE:
				enterOuterAlt(_localctx, 2);
				{
				setState(323);
				float_type();
				}
				break;
			case VOID:
			case RESULT:
				enterOuterAlt(_localctx, 3);
				{
				setState(324);
				utility_type();
				}
				break;
			case IDENT:
				enterOuterAlt(_localctx, 4);
				{
				setState(325);
				match(IDENT);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Utility_typeContext extends ParserRuleContext {
		public TerminalNode VOID() { return getToken(IDLParser.VOID, 0); }
		public TerminalNode RESULT() { return getToken(IDLParser.RESULT, 0); }
		public Utility_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_utility_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterUtility_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitUtility_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitUtility_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Utility_typeContext utility_type() throws RecognitionException {
		Utility_typeContext _localctx = new Utility_typeContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_utility_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(328);
			_la = _input.LA(1);
			if ( !(_la==VOID || _la==RESULT) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Integral_typeContext extends ParserRuleContext {
		public TerminalNode U8() { return getToken(IDLParser.U8, 0); }
		public TerminalNode S8() { return getToken(IDLParser.S8, 0); }
		public TerminalNode CHAR() { return getToken(IDLParser.CHAR, 0); }
		public TerminalNode BYTE() { return getToken(IDLParser.BYTE, 0); }
		public TerminalNode U16() { return getToken(IDLParser.U16, 0); }
		public TerminalNode S16() { return getToken(IDLParser.S16, 0); }
		public TerminalNode SHORT() { return getToken(IDLParser.SHORT, 0); }
		public TerminalNode U32() { return getToken(IDLParser.U32, 0); }
		public TerminalNode S32() { return getToken(IDLParser.S32, 0); }
		public TerminalNode INT() { return getToken(IDLParser.INT, 0); }
		public TerminalNode U64() { return getToken(IDLParser.U64, 0); }
		public TerminalNode S64() { return getToken(IDLParser.S64, 0); }
		public Integral_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_integral_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterIntegral_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitIntegral_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitIntegral_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Integral_typeContext integral_type() throws RecognitionException {
		Integral_typeContext _localctx = new Integral_typeContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_integral_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(330);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << U8) | (1L << S8) | (1L << CHAR) | (1L << BYTE) | (1L << U16) | (1L << S16) | (1L << SHORT) | (1L << U32) | (1L << S32) | (1L << INT) | (1L << U64) | (1L << S64))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Float_typeContext extends ParserRuleContext {
		public TerminalNode F32() { return getToken(IDLParser.F32, 0); }
		public TerminalNode FLOAT() { return getToken(IDLParser.FLOAT, 0); }
		public TerminalNode F64() { return getToken(IDLParser.F64, 0); }
		public TerminalNode DOUBLE() { return getToken(IDLParser.DOUBLE, 0); }
		public Float_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_float_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).enterFloat_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLParserListener ) ((IDLParserListener)listener).exitFloat_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLParserVisitor ) return ((IDLParserVisitor<? extends T>)visitor).visitFloat_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Float_typeContext float_type() throws RecognitionException {
		Float_typeContext _localctx = new Float_typeContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_float_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(332);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << F32) | (1L << FLOAT) | (1L << F64) | (1L << DOUBLE))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\60\u0151\4\2\t\2"+
		"\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\3\2\5\2Z\n\2\3\2\3\2\3\3\6\3_\n\3\r\3\16\3`\3\4\3\4\3\4\3\4\3\4\3"+
		"\4\5\4i\n\4\3\5\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3\7\3\7\7\7u\n\7\f\7\16\7"+
		"x\13\7\3\7\3\7\3\b\3\b\3\b\3\b\5\b\u0080\n\b\3\t\3\t\5\t\u0084\n\t\3\n"+
		"\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\f\3\f\7\f\u0090\n\f\f\f\16\f\u0093"+
		"\13\f\3\f\3\f\3\r\3\r\3\16\3\16\5\16\u009b\n\16\3\17\3\17\3\17\3\17\3"+
		"\20\3\20\3\20\5\20\u00a4\n\20\3\20\3\20\3\21\3\21\3\21\3\22\3\22\7\22"+
		"\u00ad\n\22\f\22\16\22\u00b0\13\22\3\22\3\22\3\23\3\23\3\23\5\23\u00b7"+
		"\n\23\3\24\3\24\3\24\3\24\5\24\u00bd\n\24\3\24\3\24\3\24\3\25\3\25\3\25"+
		"\7\25\u00c5\n\25\f\25\16\25\u00c8\13\25\3\26\5\26\u00cb\n\26\3\26\3\26"+
		"\5\26\u00cf\n\26\3\26\3\26\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27"+
		"\3\27\3\27\5\27\u00de\n\27\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30"+
		"\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30\3\30"+
		"\3\30\3\30\3\30\3\30\3\30\5\30\u00fc\n\30\3\31\3\31\3\31\5\31\u0101\n"+
		"\31\3\31\3\31\3\31\3\31\3\32\3\32\3\32\3\33\3\33\3\33\7\33\u010d\n\33"+
		"\f\33\16\33\u0110\13\33\3\34\3\34\3\34\3\34\5\34\u0116\n\34\3\35\3\35"+
		"\5\35\u011a\n\35\3\36\3\36\5\36\u011e\n\36\3\37\3\37\3 \3 \3!\3!\3\"\5"+
		"\"\u0127\n\"\3\"\3\"\5\"\u012b\n\"\3#\3#\3#\3$\3$\3$\3%\3%\3%\3%\3&\5"+
		"&\u0138\n&\3&\3&\5&\u013c\n&\3\'\3\'\3(\6(\u0141\n(\r(\16(\u0142\3)\3"+
		")\3)\3)\5)\u0149\n)\3*\3*\3+\3+\3,\3,\3,\2\2-\2\4\6\b\n\f\16\20\22\24"+
		"\26\30\32\34\36 \"$&(*,.\60\62\64\668:<>@BDFHJLNPRTV\2\6\3\2\31\34\3\2"+
		"\37 \3\2!,\3\2-\60\2\u014d\2Y\3\2\2\2\4^\3\2\2\2\6h\3\2\2\2\bj\3\2\2\2"+
		"\nn\3\2\2\2\fr\3\2\2\2\16\177\3\2\2\2\20\u0083\3\2\2\2\22\u0085\3\2\2"+
		"\2\24\u0089\3\2\2\2\26\u008d\3\2\2\2\30\u0096\3\2\2\2\32\u009a\3\2\2\2"+
		"\34\u009c\3\2\2\2\36\u00a0\3\2\2\2 \u00a7\3\2\2\2\"\u00aa\3\2\2\2$\u00b6"+
		"\3\2\2\2&\u00b8\3\2\2\2(\u00c1\3\2\2\2*\u00ca\3\2\2\2,\u00dd\3\2\2\2."+
		"\u00fb\3\2\2\2\60\u00fd\3\2\2\2\62\u0106\3\2\2\2\64\u0109\3\2\2\2\66\u0115"+
		"\3\2\2\28\u0119\3\2\2\2:\u011d\3\2\2\2<\u011f\3\2\2\2>\u0121\3\2\2\2@"+
		"\u0123\3\2\2\2B\u0126\3\2\2\2D\u012c\3\2\2\2F\u012f\3\2\2\2H\u0132\3\2"+
		"\2\2J\u0137\3\2\2\2L\u013d\3\2\2\2N\u0140\3\2\2\2P\u0148\3\2\2\2R\u014a"+
		"\3\2\2\2T\u014c\3\2\2\2V\u014e\3\2\2\2XZ\5\4\3\2YX\3\2\2\2YZ\3\2\2\2Z"+
		"[\3\2\2\2[\\\7\2\2\3\\\3\3\2\2\2]_\5\6\4\2^]\3\2\2\2_`\3\2\2\2`^\3\2\2"+
		"\2`a\3\2\2\2a\5\3\2\2\2bi\5\b\5\2ci\5\n\6\2di\5\20\t\2ei\5\32\16\2fi\5"+
		".\30\2gi\5\60\31\2hb\3\2\2\2hc\3\2\2\2hd\3\2\2\2he\3\2\2\2hf\3\2\2\2h"+
		"g\3\2\2\2i\7\3\2\2\2jk\7\3\2\2kl\7\4\2\2lm\7\5\2\2m\t\3\2\2\2no\7\6\2"+
		"\2op\7\7\2\2pq\5\f\7\2q\13\3\2\2\2rv\7\b\2\2su\5\16\b\2ts\3\2\2\2ux\3"+
		"\2\2\2vt\3\2\2\2vw\3\2\2\2wy\3\2\2\2xv\3\2\2\2yz\7\t\2\2z\r\3\2\2\2{\u0080"+
		"\5\20\t\2|\u0080\5\n\6\2}\u0080\5\32\16\2~\u0080\5.\30\2\177{\3\2\2\2"+
		"\177|\3\2\2\2\177}\3\2\2\2\177~\3\2\2\2\u0080\17\3\2\2\2\u0081\u0084\5"+
		"\22\n\2\u0082\u0084\5\24\13\2\u0083\u0081\3\2\2\2\u0083\u0082\3\2\2\2"+
		"\u0084\21\3\2\2\2\u0085\u0086\7\n\2\2\u0086\u0087\7\7\2\2\u0087\u0088"+
		"\5\26\f\2\u0088\23\3\2\2\2\u0089\u008a\7\n\2\2\u008a\u008b\7\7\2\2\u008b"+
		"\u008c\7\5\2\2\u008c\25\3\2\2\2\u008d\u0091\7\b\2\2\u008e\u0090\5\30\r"+
		"\2\u008f\u008e\3\2\2\2\u0090\u0093\3\2\2\2\u0091\u008f\3\2\2\2\u0091\u0092"+
		"\3\2\2\2\u0092\u0094\3\2\2\2\u0093\u0091\3\2\2\2\u0094\u0095\7\t\2\2\u0095"+
		"\27\3\2\2\2\u0096\u0097\5H%\2\u0097\31\3\2\2\2\u0098\u009b\5\36\20\2\u0099"+
		"\u009b\5\34\17\2\u009a\u0098\3\2\2\2\u009a\u0099\3\2\2\2\u009b\33\3\2"+
		"\2\2\u009c\u009d\7\13\2\2\u009d\u009e\7\7\2\2\u009e\u009f\7\5\2\2\u009f"+
		"\35\3\2\2\2\u00a0\u00a1\7\13\2\2\u00a1\u00a3\7\7\2\2\u00a2\u00a4\5 \21"+
		"\2\u00a3\u00a2\3\2\2\2\u00a3\u00a4\3\2\2\2\u00a4\u00a5\3\2\2\2\u00a5\u00a6"+
		"\5\"\22\2\u00a6\37\3\2\2\2\u00a7\u00a8\7\f\2\2\u00a8\u00a9\5B\"\2\u00a9"+
		"!\3\2\2\2\u00aa\u00ae\7\b\2\2\u00ab\u00ad\5$\23\2\u00ac\u00ab\3\2\2\2"+
		"\u00ad\u00b0\3\2\2\2\u00ae\u00ac\3\2\2\2\u00ae\u00af\3\2\2\2\u00af\u00b1"+
		"\3\2\2\2\u00b0\u00ae\3\2\2\2\u00b1\u00b2\7\t\2\2\u00b2#\3\2\2\2\u00b3"+
		"\u00b7\5&\24\2\u00b4\u00b7\5.\30\2\u00b5\u00b7\5\60\31\2\u00b6\u00b3\3"+
		"\2\2\2\u00b6\u00b4\3\2\2\2\u00b6\u00b5\3\2\2\2\u00b7%\3\2\2\2\u00b8\u00b9"+
		"\5J&\2\u00b9\u00ba\7\7\2\2\u00ba\u00bc\7\r\2\2\u00bb\u00bd\5(\25\2\u00bc"+
		"\u00bb\3\2\2\2\u00bc\u00bd\3\2\2\2\u00bd\u00be\3\2\2\2\u00be\u00bf\7\16"+
		"\2\2\u00bf\u00c0\7\5\2\2\u00c0\'\3\2\2\2\u00c1\u00c6\5*\26\2\u00c2\u00c3"+
		"\7\17\2\2\u00c3\u00c5\5*\26\2\u00c4\u00c2\3\2\2\2\u00c5\u00c8\3\2\2\2"+
		"\u00c6\u00c4\3\2\2\2\u00c6\u00c7\3\2\2\2\u00c7)\3\2\2\2\u00c8\u00c6\3"+
		"\2\2\2\u00c9\u00cb\5,\27\2\u00ca\u00c9\3\2\2\2\u00ca\u00cb\3\2\2\2\u00cb"+
		"\u00cc\3\2\2\2\u00cc\u00ce\5P)\2\u00cd\u00cf\5N(\2\u00ce\u00cd\3\2\2\2"+
		"\u00ce\u00cf\3\2\2\2\u00cf\u00d0\3\2\2\2\u00d0\u00d1\7\7\2\2\u00d1+\3"+
		"\2\2\2\u00d2\u00d3\7\20\2\2\u00d3\u00d4\7\21\2\2\u00d4\u00de\7\22\2\2"+
		"\u00d5\u00d6\7\20\2\2\u00d6\u00d7\7\23\2\2\u00d7\u00de\7\22\2\2\u00d8"+
		"\u00d9\7\20\2\2\u00d9\u00da\7\21\2\2\u00da\u00db\7\17\2\2\u00db\u00dc"+
		"\7\23\2\2\u00dc\u00de\7\22\2\2\u00dd\u00d2\3\2\2\2\u00dd\u00d5\3\2\2\2"+
		"\u00dd\u00d8\3\2\2\2\u00de-\3\2\2\2\u00df\u00e0\7\24\2\2\u00e0\u00e1\5"+
		"T+\2\u00e1\u00e2\7\7\2\2\u00e2\u00e3\7\25\2\2\u00e3\u00e4\5<\37\2\u00e4"+
		"\u00e5\7\5\2\2\u00e5\u00fc\3\2\2\2\u00e6\u00e7\7\24\2\2\u00e7\u00e8\5"+
		"V,\2\u00e8\u00e9\7\7\2\2\u00e9\u00ea\7\25\2\2\u00ea\u00eb\5> \2\u00eb"+
		"\u00ec\7\5\2\2\u00ec\u00fc\3\2\2\2\u00ed\u00ee\7\24\2\2\u00ee\u00ef\7"+
		"\26\2\2\u00ef\u00f0\7\7\2\2\u00f0\u00f1\7\25\2\2\u00f1\u00f2\5@!\2\u00f2"+
		"\u00f3\7\5\2\2\u00f3\u00fc\3\2\2\2\u00f4\u00f5\7\24\2\2\u00f5\u00f6\7"+
		"\27\2\2\u00f6\u00f7\7\7\2\2\u00f7\u00f8\7\25\2\2\u00f8\u00f9\5@!\2\u00f9"+
		"\u00fa\7\5\2\2\u00fa\u00fc\3\2\2\2\u00fb\u00df\3\2\2\2\u00fb\u00e6\3\2"+
		"\2\2\u00fb\u00ed\3\2\2\2\u00fb\u00f4\3\2\2\2\u00fc/\3\2\2\2\u00fd\u00fe"+
		"\7\30\2\2\u00fe\u0100\7\7\2\2\u00ff\u0101\5\62\32\2\u0100\u00ff\3\2\2"+
		"\2\u0100\u0101\3\2\2\2\u0101\u0102\3\2\2\2\u0102\u0103\7\b\2\2\u0103\u0104"+
		"\5\64\33\2\u0104\u0105\7\t\2\2\u0105\61\3\2\2\2\u0106\u0107\7\f\2\2\u0107"+
		"\u0108\5T+\2\u0108\63\3\2\2\2\u0109\u010e\5\66\34\2\u010a\u010b\7\17\2"+
		"\2\u010b\u010d\5\66\34\2\u010c\u010a\3\2\2\2\u010d\u0110\3\2\2\2\u010e"+
		"\u010c\3\2\2\2\u010e\u010f\3\2\2\2\u010f\65\3\2\2\2\u0110\u010e\3\2\2"+
		"\2\u0111\u0116\7\7\2\2\u0112\u0113\7\7\2\2\u0113\u0114\7\25\2\2\u0114"+
		"\u0116\5<\37\2\u0115\u0111\3\2\2\2\u0115\u0112\3\2\2\2\u0116\67\3\2\2"+
		"\2\u0117\u011a\5:\36\2\u0118\u011a\5@!\2\u0119\u0117\3\2\2\2\u0119\u0118"+
		"\3\2\2\2\u011a9\3\2\2\2\u011b\u011e\5<\37\2\u011c\u011e\5> \2\u011d\u011b"+
		"\3\2\2\2\u011d\u011c\3\2\2\2\u011e;\3\2\2\2\u011f\u0120\t\2\2\2\u0120"+
		"=\3\2\2\2\u0121\u0122\7\35\2\2\u0122?\3\2\2\2\u0123\u0124\7\4\2\2\u0124"+
		"A\3\2\2\2\u0125\u0127\5F$\2\u0126\u0125\3\2\2\2\u0126\u0127\3\2\2\2\u0127"+
		"\u0128\3\2\2\2\u0128\u012a\7\7\2\2\u0129\u012b\5D#\2\u012a\u0129\3\2\2"+
		"\2\u012a\u012b\3\2\2\2\u012bC\3\2\2\2\u012c\u012d\5F$\2\u012d\u012e\7"+
		"\7\2\2\u012eE\3\2\2\2\u012f\u0130\7\f\2\2\u0130\u0131\7\f\2\2\u0131G\3"+
		"\2\2\2\u0132\u0133\5J&\2\u0133\u0134\7\7\2\2\u0134\u0135\7\5\2\2\u0135"+
		"I\3\2\2\2\u0136\u0138\5L\'\2\u0137\u0136\3\2\2\2\u0137\u0138\3\2\2\2\u0138"+
		"\u0139\3\2\2\2\u0139\u013b\5P)\2\u013a\u013c\5N(\2\u013b\u013a\3\2\2\2"+
		"\u013b\u013c\3\2\2\2\u013cK\3\2\2\2\u013d\u013e\7\24\2\2\u013eM\3\2\2"+
		"\2\u013f\u0141\7\36\2\2\u0140\u013f\3\2\2\2\u0141\u0142\3\2\2\2\u0142"+
		"\u0140\3\2\2\2\u0142\u0143\3\2\2\2\u0143O\3\2\2\2\u0144\u0149\5T+\2\u0145"+
		"\u0149\5V,\2\u0146\u0149\5R*\2\u0147\u0149\7\7\2\2\u0148\u0144\3\2\2\2"+
		"\u0148\u0145\3\2\2\2\u0148\u0146\3\2\2\2\u0148\u0147\3\2\2\2\u0149Q\3"+
		"\2\2\2\u014a\u014b\t\3\2\2\u014bS\3\2\2\2\u014c\u014d\t\4\2\2\u014dU\3"+
		"\2\2\2\u014e\u014f\t\5\2\2\u014fW\3\2\2\2\36Y`hv\177\u0083\u0091\u009a"+
		"\u00a3\u00ae\u00b6\u00bc\u00c6\u00ca\u00ce\u00dd\u00fb\u0100\u010e\u0115"+
		"\u0119\u011d\u0126\u012a\u0137\u013b\u0142\u0148";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}