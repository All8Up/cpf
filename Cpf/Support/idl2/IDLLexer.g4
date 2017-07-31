lexer grammar IDLLexer;

fragment ALPHA              : [a-zA-Z];
fragment ALPHA_             : [a-zA-Z_];
fragment DIGIT              : [0-9];
fragment HEX_DIGIT          : [0-9a-fA-F];
fragment BIN_DIGIT          : [0-1];
fragment OCT_DIGIT          : [0-7];
fragment WS                 : [ \r\n\t];

IMPORT                      : 'import';
NAMESPACE                   : 'namespace';
STRUCT                      : 'struct';
INTERFACE                   : 'interface';
ENUM                        : 'enum';

IN                          : 'in';
OUT                         : 'out';

COLON                       : ':';
SEMICOLON                   : ';';
STAR                        : '*';
DOT                         : '.';
COMMA                       : ',';
EQUALS                      : '=';
QUOTE                       : '"';
LBRACE                      : '{';
RBRACE                      : '}';
LPAREN                      : '(';
RPAREN                      : ')';
LBRACKET                    : '[';
RBRACKET                    : ']';
LT                          : '<';
GT                          : '>';

// Type modifiers.
CONST                       : 'const';

// Types.
VOID                        : 'void';
RESULT                      : 'result';
CLASS_ID                    : 'class_id';

U8                          : 'u8';
S8                          : 's8';
U16                         : 'u16';
S16                         : 's16';
U32                         : 'u32';
S32                         : 's32';
U64                         : 'u64';
S64                         : 's64';

// Float types.
F32                         : 'f32';
F64                         : 'f64';

// Alias's
BYTE                        : 'byte';
CHAR                        : 'char';
SHORT                       : 'short';
LONG                        : 'long';
INT                         : 'int';
FLOAT                       : 'float';
DOUBLE                      : 'double';
STRING                      : 'string';

// Identifiers.
IDENT                       : ALPHA_ (ALPHA_ | DIGIT)*;

// Literals.
DECIMAL_LIT                 : [1-9] DIGIT*;
HEX_LIT                     : ('0x' | '0X') HEX_DIGIT+;
OCT_LIT                     : '0' OCT_DIGIT+;
BIN_LIT                     : ('0b' | '0B') BIN_DIGIT+;

// String literal.
STRING_LIT                  : QUOTE QUOTED_TEXT? QUOTE;
fragment QUOTED_TEXT        : QUOTED_ITEM+;
fragment QUOTED_ITEM        : ~["\n\r\\]
                            | ESC_CHAR;
fragment ESC_CHAR           : '\\' [0\\tnr"']
                            | '\\x' HEX_DIGIT HEX_DIGIT
                            | '\\u' '{' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT '}'
                            | '\\u' '{' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT '}'
                            ;

// Floating point literal.
FLOAT_LIT                   : DIGIT_SEQ? '.' DIGIT_SEQ DECIMAL_EXP?
                            | DIGIT_SEQ '.' DECIMAL_EXP?;
fragment DIGIT_SEQ          : DIGIT+;
fragment DECIMAL_EXP        : FLOAT_EXP SIGN? DECIMAL_LIT;
fragment FLOAT_EXP          : [eE];
fragment SIGN               : [+\-];

// Ignored.
WHITE_SPACE                 : WS+ -> skip;
BLOCK_COMMENT               : '/*' (BLOCK_COMMENT|.)*? '*/'	-> skip;
LINE_COMMENT                : '//' .*? ('\n'|EOF) -> skip;
