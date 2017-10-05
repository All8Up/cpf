// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLParser.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link IDLParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface IDLParserVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link IDLParser#main}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMain(IDLParser.MainContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#global_statements}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGlobal_statements(IDLParser.Global_statementsContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#global_statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGlobal_statement(IDLParser.Global_statementContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#import_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitImport_stmt(IDLParser.Import_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#namespace_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_stmt(IDLParser.Namespace_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#namespace_block}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_block(IDLParser.Namespace_blockContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#namespace_item}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_item(IDLParser.Namespace_itemContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#struct_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStruct_stmt(IDLParser.Struct_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#struct_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStruct_decl(IDLParser.Struct_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#struct_fwd}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStruct_fwd(IDLParser.Struct_fwdContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#struct_block}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStruct_block(IDLParser.Struct_blockContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#struct_item}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStruct_item(IDLParser.Struct_itemContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#interface_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInterface_stmt(IDLParser.Interface_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#interface_fwd}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInterface_fwd(IDLParser.Interface_fwdContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#interface_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInterface_decl(IDLParser.Interface_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#interface_super}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInterface_super(IDLParser.Interface_superContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#interface_block}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInterface_block(IDLParser.Interface_blockContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#interface_item}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInterface_item(IDLParser.Interface_itemContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#function_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction_decl(IDLParser.Function_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#function_param_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction_param_list(IDLParser.Function_param_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#function_param}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction_param(IDLParser.Function_paramContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#param_dir_qualifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParam_dir_qualifier(IDLParser.Param_dir_qualifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#const_def}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConst_def(IDLParser.Const_defContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#enum_def}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnum_def(IDLParser.Enum_defContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#enum_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnum_type(IDLParser.Enum_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#enum_elements}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnum_elements(IDLParser.Enum_elementsContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#enum_item}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnum_item(IDLParser.Enum_itemContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#any_literal}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAny_literal(IDLParser.Any_literalContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#numeric_lit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNumeric_lit(IDLParser.Numeric_litContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#integer_lit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInteger_lit(IDLParser.Integer_litContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#float_lit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFloat_lit(IDLParser.Float_litContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#string_lit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitString_lit(IDLParser.String_litContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#qualified_ident}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitQualified_ident(IDLParser.Qualified_identContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#qualified_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitQualified_part(IDLParser.Qualified_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#qualified_separator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitQualified_separator(IDLParser.Qualified_separatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#member_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMember_decl(IDLParser.Member_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#type_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_decl(IDLParser.Type_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#type_modifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_modifier(IDLParser.Type_modifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#pointer_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPointer_type(IDLParser.Pointer_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#any_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAny_type(IDLParser.Any_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#utility_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUtility_type(IDLParser.Utility_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#integral_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIntegral_type(IDLParser.Integral_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#float_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFloat_type(IDLParser.Float_typeContext ctx);
}