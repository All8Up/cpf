parser grammar IDLParser;

main                    : global_statements? EOF;

// Statements allowed in global scope.
global_statements       : global_statement+;
global_statement        : import_stmt
                        | namespace_stmt
                        | struct_stmt
                        | interface_stmt;

// Import.
import_stmt             : IMPORT STRING_LIT SEMICOLON;

// Namespaces
namespace_stmt          : NAMESPACE IDENT namespace_block;
namespace_block         : LBRACE namespace_item* RBRACE;
// Statements allowed at namespace scope.
namespace_item          : struct_stmt
                        | namespace_stmt
                        | interface_stmt;

// Structures
struct_stmt             : struct_decl
                        | struct_fwd;
struct_decl             : STRUCT IDENT struct_block;
struct_fwd              : STRUCT IDENT SEMICOLON;

struct_block            : LBRACE struct_item* RBRACE;
// Statements allowed at struct scope.
struct_item             : member_decl;

// Interfaces
interface_stmt          : interface_decl
                        | interface_fwd;

interface_fwd           : INTERFACE IDENT SEMICOLON;
interface_decl          : INTERFACE IDENT interface_super? interface_block;
interface_super         : COLON qualified_ident;

interface_block         : LBRACE interface_item* RBRACE;
// Statements allowed at interface scope.
interface_item          : function_decl;

// Function declarations.
function_decl           : type_decl IDENT LPAREN function_param_list? RPAREN SEMICOLON;

function_param_list     : function_param (COMMA function_param)*;

function_param          : param_dir_qualifier? pointer_opt_type IDENT;

param_dir_qualifier     : LBRACKET IN RBRACKET
                        | LBRACKET OUT RBRACKET
                        | LBRACKET IN COMMA OUT RBRACKET;

// Qualified identifiers.
qualified_ident         : qualified_separator? IDENT qualified_part_opt;
qualified_part_opt      : qualified_part?;
qualified_part          : qualified_separator IDENT;
qualified_separator     : COLON COLON;

// Data member declaration.
member_decl             : type_decl IDENT SEMICOLON;

// Type declarations.
type_decl               : type_modifier? pointer_opt_type;

type_modifier           : CONST;

pointer_opt_type        : any_type (STAR+)?;

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
