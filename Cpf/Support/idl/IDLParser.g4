parser grammar IDLParser;

options { tokenVocab = IDLLexer; }

main                    : global_statements? EOF;

// Statements allowed in global scope.
global_statements       : global_statement+;
global_statement        : import_stmt
                        | import_all_from_stmt
                        | namespace_stmt
                        | struct_stmt
                        | interface_stmt
                        | const_def
                        | enum_def
                        | enum_fwd

                        | module_stmt
                        | error_code_stmt
                        | empty_stmt
                        | import_from_stmt;

// Allow semi-colons even if not needed.
empty_stmt              : SEMICOLON;

// Module support.
module_stmt             : MODULE qualified_ident SEMICOLON;

// Error code handling.
error_code_stmt         : success_stmt
                        | failure_stmt;
success_stmt            : SUCCESS IDENT LPAREN STRING_LIT COMMA STRING_LIT RPAREN;
failure_stmt            : FAILURE IDENT LPAREN STRING_LIT COMMA STRING_LIT RPAREN;

// Symbol import.
import_all_from_stmt    : IMPORT STAR FROM qualified_ident SEMICOLON;
import_from_stmt        : IMPORT IDENT FROM qualified_ident SEMICOLON;

// Import.
import_stmt             : IMPORT string_lit SEMICOLON;

// Namespaces
namespace_stmt          : NAMESPACE namespace_name namespace_block;
namespace_name          : IDENT;
namespace_block         : LBRACE namespace_item* RBRACE;
// Statements allowed at namespace scope.
namespace_item          : struct_stmt
                        | namespace_stmt
                        | interface_stmt
                        | const_def
                        | enum_def
                        | enum_fwd;

// Structures
struct_stmt             : struct_decl
                        | struct_fwd;
struct_decl             : STRUCT struct_name struct_block;
struct_name             : IDENT;
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

function_param          : param_dir_qualifier? type_modifier? any_type pointer_type? IDENT;

param_dir_qualifier     : LBRACKET IN RBRACKET
                        | LBRACKET OUT RBRACKET
                        | LBRACKET IN COMMA OUT RBRACKET;

// Constant definitions.
const_def               : const_integral_def
                        | const_float_def
                        | const_string_def
                        | const_class_id_def;

const_integral_def      : CONST integral_type IDENT EQUALS integer_lit SEMICOLON;
const_float_def         : CONST float_type IDENT EQUALS float_lit SEMICOLON;
const_string_def        : CONST STRING IDENT EQUALS string_lit SEMICOLON;
const_class_id_def      : CONST CLASS_ID IDENT LPAREN string_lit RPAREN SEMICOLON;

// Enumerations.
enum_fwd                : ENUM IDENT enum_type? SEMICOLON;
enum_def                : ENUM IDENT enum_type? LBRACE enum_elements RBRACE;
enum_type               : COLON integral_type;
enum_elements           : enum_item (COMMA enum_item)*;
enum_item               : IDENT
                        | IDENT EQUALS enum_expr;

// Enumeration assignment expression handling.
enum_expr               : expr_add_sub;
expr_add_sub            : expr_add_sub PLUS expr_mul_div
                        | expr_add_sub MINUS expr_mul_div
                        | expr_mul_div;
expr_mul_div            : expr_mul_div STAR expr_shift
                        | expr_mul_div SLASH expr_shift
                        | expr_shift;
expr_shift              : expr_shift LSHIFT expr_value
                        | expr_shift RSHIFT expr_value
                        | expr_value;
expr_value              : integer_lit
                        | LPAREN enum_expr RPAREN;

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
qualified_ident         : qualified_separator? IDENT qualified_part*;
qualified_part          : qualified_separator IDENT;
qualified_separator     : COLON COLON;

// Data member declaration.
member_decl             : type_decl IDENT SEMICOLON;

// Type declarations.
type_decl               : type_modifier? any_type pointer_type?;

type_modifier           : CONST;

pointer_type            : (CONST? STAR)+;

// Any valid type.
any_type                : integral_type
                        | float_type
                        | utility_type
                        | IDENT;

utility_type            : VOID
                        | RESULT;

integral_type           : U8 | S8
                        | U16 | S16
                        | U32 | S32
                        | U64 | S64
                        ;

float_type              : F32 | F64;
