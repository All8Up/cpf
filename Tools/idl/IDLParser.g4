parser grammar IDLParser;

options { tokenVocab = IDLLexer; }

main                    : global_statements? EOF;

// Statements allowed in global scope.
global_statements       : global_statement+;
global_statement        : import_stmt
                        | struct_stmt
                        | union_stmt
                        | interface_stmt
                        | event_decl
                        | const_def
                        | enum_def
                        | flags_fwd
                        | flags_def
                        | enum_fwd

                        | module_stmt
                        | error_code_stmt
                        | empty_stmt
                        | import_stmt
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
import_from_stmt        : IMPORT all_or_ident FROM qualified_ident SEMICOLON;

// Import.
import_stmt             : IMPORT IDENT SEMICOLON;

// Structures
struct_stmt             : struct_decl
                        | struct_fwd;
struct_decl             : STRUCT IDENT struct_block;
struct_fwd              : STRUCT qualified_ident SEMICOLON;

// Unions
union_stmt              : union_decl
                        | union_fwd;
union_decl              : UNION IDENT struct_block;
union_fwd               : UNION qualified_ident SEMICOLON;

// Union/Struct data block.
struct_block            : LBRACE (struct_item* | os_specific*) RBRACE;

// Statements allowed at struct scope.
struct_item             : member_decl
                        | const_def
                        | enum_def;

os_specific             : os_tag LBRACE struct_item* RBRACE;
os_tag                  : Windows
                        | Darwin;

// Interfaces
interface_stmt          : interface_decl
                        | interface_fwd;

interface_fwd           : INTERFACE qualified_ident SEMICOLON;
interface_decl          : INTERFACE IDENT interface_super? interface_block;
interface_super         : COLON qualified_ident;

interface_block         : LBRACE interface_item* RBRACE;
// Statements allowed at interface scope.
interface_item          : function_decl
                        | const_def
                        | enum_def
                        | event_decl;

// Function declarations.
function_decl           : type_decl IDENT LPAREN function_param_list? RPAREN Const? SEMICOLON;

function_param_list     : function_param (COMMA function_param)*;

function_param          : param_dir_qualifier? type_decl IDENT;

param_dir_qualifier     : LBRACKET IN RBRACKET
                        | LBRACKET OUT RBRACKET
                        | LBRACKET IN COMMA OUT RBRACKET;

// Event declarations.
event_decl              : EVENT IDENT EQUALS type_decl LPAREN function_param_list? RPAREN SEMICOLON;

// Constant definitions.
const_def               : const_integral_def
                        | const_float_def
                        | const_string_def
                        | const_class_id_def;

const_integral_def      : Const integral_type IDENT EQUALS integer_lit SEMICOLON;
const_float_def         : Const float_type IDENT EQUALS float_lit SEMICOLON;
const_string_def        : Const STRING IDENT EQUALS string_lit SEMICOLON;
const_class_id_def      : Const CLASS_ID IDENT LPAREN string_lit RPAREN SEMICOLON;

// Enumerations.
enum_fwd                : ENUM IDENT enum_type? SEMICOLON;
enum_def                : ENUM IDENT enum_type? LBRACE enum_elements COMMA? RBRACE;
flags_fwd               : FLAGS IDENT enum_type? SEMICOLON;
flags_def               : FLAGS IDENT enum_type? LBRACE enum_elements RBRACE;
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
expr_shift              : expr_shift LSHIFT expr_logical
                        | expr_shift RSHIFT expr_logical
                        | expr_logical;
expr_logical            : expr_logical PIPE expr_value
                        | expr_value;
expr_value              : integer_lit
                        | qualified_ident
                        | LPAREN enum_expr RPAREN;

// Literals.
any_literal             : numeric_lit
                        | string_lit;
numeric_lit             : integer_lit
                        | float_lit;
integer_lit             : DECIMAL_LIT
                        | HEX_LIT
                        | OCT_LIT
                        | BIN_LIT
                        | char_lit;
float_lit               : FLOAT_LIT;
string_lit              : STRING_LIT;
char_lit                : CHAR_LIT;

// Qualified identifiers.
qualified_ident         : qualified_separator? IDENT qualified_part*;
qualified_part          : qualified_separator IDENT;
qualified_separator     : COLON COLON;

// All or identifier.
all_or_ident            : IDENT
                        | STAR;

// Data member declaration.
member_decl             : type_decl IDENT (LBRACKET (integer_lit | qualified_ident) RBRACKET)? member_init? SEMICOLON;
member_init             : EQUALS member_init_value
                        | EQUALS LBRACE (member_init_value COMMA?)* RBRACE;
member_init_value       : DEFAULT qualified_ident
                        | integer_lit init_as_type?
                        | float_lit init_as_type?
                        | string_lit
                        | qualified_ident init_as_type?;
init_as_type            : AS integral_type
                        | AS float_type;

// Type declarations.
type_decl               : type_modifier? any_type pointer_type?;

type_modifier           : Const;

pointer_type            : pointer_decl+;
pointer_decl             : Const? STAR;

// Any valid type.
any_type                : integral_type
                        | float_type
                        | utility_type
                        | qualified_ident
                        | template_type;

utility_type            : Void
                        | RESULT;

integral_type           : U8 | S8
                        | U16 | S16
                        | U32 | S32
                        | U64 | S64
                        ;

float_type              : F32 | F64;

template_type           : qualified_ident LT template_params GT;
template_params         : template_params COMMA template_params
                        | template_param;
template_param          : any_type;
