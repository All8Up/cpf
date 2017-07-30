lexer grammar IDLLexer;

LINE_COMMENT    :   '//' .*? EOF ;
BLOCK_COMMENT   :   '/*' .*? '*/' ;

fragment
ALPHA           :   [a-zA-Z] ;
fragment
ALPHANUMERIC    :   [a-zA-Z0-9] ;
fragment
HEXDIGIT        :   [a-fA-F0-9] ;
fragment
DIGIT           :   [0-9] ;

INTERFACE       :   'interface' ;
STRUCT          :   'struct' ;

U8              :   'u8' ;
I8              :   'i8' ;
U16             :   'u16' ;
I16             :   'i16' ;
U32             :   'u32' ;
I32             :   'i32' ;
U64             :   'u64' ;
I64             :   'i64' ;
FLOAT           :   'f32' ;
DOUBLE          :   'f64' ;
CHAR            :   'char' ;

DOT             :   '.' ;
COMMA           :   ',' ;
COLON           :   ':' ;
SEMICOLON       :   ';' ;
QUOTE           :   '"' ;
SINGLQUOTE      :   '\'' ;
LESS            :   '<' ;
GREATER         :   '>' ;

LPAREN          :   '(' ;
RPAREN          :   ')' ;
LBRACE          :   '{' ;
RBRACE          :   '}' ;
LBRACKET        :   '[' ;
RBRACKET        :   ']' ;
