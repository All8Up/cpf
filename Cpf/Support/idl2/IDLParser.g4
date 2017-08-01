parser grammar IDLParser;

options { tokenVocab = IDLLexer; }

main                    : global_statements? EOF;

// Statements allowed in global scope.
global_statements       : global_statement+;
global_statement        : import_stmt
                        | namespace_stmt
                        | struct_stmt
                        | interface_stmt
                        | const_def
                        | enum_def;

// Import.
import_stmt             : IMPORT STRING_LIT SEMICOLON;

// Namespaces
namespace_stmt          : NAMESPACE IDENT namespace_block;
namespace_block         : LBRACE namespace_item* RBRACE;
// Statements allowed at namespace scope.
namespace_item          : struct_stmt
                        | namespace_stmt
                        | interface_stmt
                        | const_def
                        | enum_def;

// Structures
struct_stmt             : struct_decl
                        | struct_fwd;
struct_decl             : STRUCT IDENT struct_block;
struct_fwd              : STRUCT IDENT SEMICOLON;

struct_block            : LBRACE struct_item* RBRACE;
// Statements allowed at struct scope.
struct_item             : member_decl
                        | const_def
                        | enum_def;

// Interfaces
interface_stmt          : interface_decl
                        | interface_fwd;

interface_fwd           : INTERFACE IDENT SEMICOLON;
interface_decl          : INTERFACE IDENT interface_super? interface_block;
interface_super         : COLON qualified_ident;

interface_block         : LBRACE interface_item* RBRACE;
// Statements allowed at interface scope.
interface_item          : function_decl
                        | const_def
                        | enum_def;

// Function declarations.
function_decl           : type_decl IDENT LPAREN function_param_list? RPAREN SEMICOLON;

function_param_list     : function_param (COMMA function_param)*;

function_param          : param_dir_qualifier? any_type pointer_type? IDENT;

param_dir_qualifier     : LBRACKET IN RBRACKET
                        | LBRACKET OUT RBRACKET
                        | LBRACKET IN COMMA OUT RBRACKET;

// Constant definitions.
const_def               : CONST integral_type IDENT EQUALS integer_lit SEMICOLON
                        | CONST float_type IDENT EQUALS float_lit SEMICOLON
                        | CONST STRING IDENT EQUALS string_lit SEMICOLON
                        | CONST CLASS_ID IDENT EQUALS string_lit SEMICOLON;

// Enumerations.
enum_def                : ENUM IDENT enum_type? LBRACE enum_elements RBRACE;
enum_type               : COLON integral_type;
enum_elements           : enum_item (COMMA enum_item)*;
enum_item               : IDENT
                        | IDENT EQUALS integer_lit;

// Literals.
any_literal             : numeric_lit
                        | string_lit;
numeric_lit             : integer_lit
                        | float_lit;
integer_lit             : DECIMAL_LIT
                        | HEX_LIT
                        | OCT_LIT
                        | BIN_LIT;
float_lit               : FLOAT_LIT;
string_lit              : STRING_LIT;

// Qualified identifiers.
qualified_ident         : qualified_separator? IDENT qualified_part?;
qualified_part          : qualified_separator IDENT;
qualified_separator     : COLON COLON;

// Data member declaration.
member_decl             : type_decl IDENT SEMICOLON;

// Type declarations.
type_decl               : type_modifier? any_type pointer_type?;

type_modifier           : CONST;

pointer_type            : STAR+;

// Any valid type.
any_type                : integral_type
                        | float_type
                        | utility_type
                        | IDENT;

utility_type            : VOID
                        | RESULT;

integral_type           : U8 | S8 | CHAR | BYTE
                        | U16 | S16 | SHORT
                        | U32 | S32 | INT
                        | U64 | S64
                        ;

float_type              : F32 | FLOAT
                        | F64 | DOUBLE;
