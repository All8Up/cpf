// Generated from C:/Projects/cpf/Cpf/Support/idl2\IDLParser.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link IDLParser}.
 */
public interface IDLParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link IDLParser#main}.
	 * @param ctx the parse tree
	 */
	void enterMain(IDLParser.MainContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#main}.
	 * @param ctx the parse tree
	 */
	void exitMain(IDLParser.MainContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#global_statements}.
	 * @param ctx the parse tree
	 */
	void enterGlobal_statements(IDLParser.Global_statementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#global_statements}.
	 * @param ctx the parse tree
	 */
	void exitGlobal_statements(IDLParser.Global_statementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#global_statement}.
	 * @param ctx the parse tree
	 */
	void enterGlobal_statement(IDLParser.Global_statementContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#global_statement}.
	 * @param ctx the parse tree
	 */
	void exitGlobal_statement(IDLParser.Global_statementContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#import_stmt}.
	 * @param ctx the parse tree
	 */
	void enterImport_stmt(IDLParser.Import_stmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#import_stmt}.
	 * @param ctx the parse tree
	 */
	void exitImport_stmt(IDLParser.Import_stmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#namespace_stmt}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_stmt(IDLParser.Namespace_stmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#namespace_stmt}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_stmt(IDLParser.Namespace_stmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#namespace_block}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_block(IDLParser.Namespace_blockContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#namespace_block}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_block(IDLParser.Namespace_blockContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#namespace_item}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_item(IDLParser.Namespace_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#namespace_item}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_item(IDLParser.Namespace_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#struct_stmt}.
	 * @param ctx the parse tree
	 */
	void enterStruct_stmt(IDLParser.Struct_stmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#struct_stmt}.
	 * @param ctx the parse tree
	 */
	void exitStruct_stmt(IDLParser.Struct_stmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#struct_decl}.
	 * @param ctx the parse tree
	 */
	void enterStruct_decl(IDLParser.Struct_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#struct_decl}.
	 * @param ctx the parse tree
	 */
	void exitStruct_decl(IDLParser.Struct_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#struct_fwd}.
	 * @param ctx the parse tree
	 */
	void enterStruct_fwd(IDLParser.Struct_fwdContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#struct_fwd}.
	 * @param ctx the parse tree
	 */
	void exitStruct_fwd(IDLParser.Struct_fwdContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#struct_block}.
	 * @param ctx the parse tree
	 */
	void enterStruct_block(IDLParser.Struct_blockContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#struct_block}.
	 * @param ctx the parse tree
	 */
	void exitStruct_block(IDLParser.Struct_blockContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#struct_item}.
	 * @param ctx the parse tree
	 */
	void enterStruct_item(IDLParser.Struct_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#struct_item}.
	 * @param ctx the parse tree
	 */
	void exitStruct_item(IDLParser.Struct_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#interface_stmt}.
	 * @param ctx the parse tree
	 */
	void enterInterface_stmt(IDLParser.Interface_stmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#interface_stmt}.
	 * @param ctx the parse tree
	 */
	void exitInterface_stmt(IDLParser.Interface_stmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#interface_fwd}.
	 * @param ctx the parse tree
	 */
	void enterInterface_fwd(IDLParser.Interface_fwdContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#interface_fwd}.
	 * @param ctx the parse tree
	 */
	void exitInterface_fwd(IDLParser.Interface_fwdContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#interface_decl}.
	 * @param ctx the parse tree
	 */
	void enterInterface_decl(IDLParser.Interface_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#interface_decl}.
	 * @param ctx the parse tree
	 */
	void exitInterface_decl(IDLParser.Interface_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#interface_super}.
	 * @param ctx the parse tree
	 */
	void enterInterface_super(IDLParser.Interface_superContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#interface_super}.
	 * @param ctx the parse tree
	 */
	void exitInterface_super(IDLParser.Interface_superContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#interface_block}.
	 * @param ctx the parse tree
	 */
	void enterInterface_block(IDLParser.Interface_blockContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#interface_block}.
	 * @param ctx the parse tree
	 */
	void exitInterface_block(IDLParser.Interface_blockContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#interface_item}.
	 * @param ctx the parse tree
	 */
	void enterInterface_item(IDLParser.Interface_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#interface_item}.
	 * @param ctx the parse tree
	 */
	void exitInterface_item(IDLParser.Interface_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#function_decl}.
	 * @param ctx the parse tree
	 */
	void enterFunction_decl(IDLParser.Function_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#function_decl}.
	 * @param ctx the parse tree
	 */
	void exitFunction_decl(IDLParser.Function_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#function_param_list}.
	 * @param ctx the parse tree
	 */
	void enterFunction_param_list(IDLParser.Function_param_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#function_param_list}.
	 * @param ctx the parse tree
	 */
	void exitFunction_param_list(IDLParser.Function_param_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#function_param}.
	 * @param ctx the parse tree
	 */
	void enterFunction_param(IDLParser.Function_paramContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#function_param}.
	 * @param ctx the parse tree
	 */
	void exitFunction_param(IDLParser.Function_paramContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#param_dir_qualifier}.
	 * @param ctx the parse tree
	 */
	void enterParam_dir_qualifier(IDLParser.Param_dir_qualifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#param_dir_qualifier}.
	 * @param ctx the parse tree
	 */
	void exitParam_dir_qualifier(IDLParser.Param_dir_qualifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#const_def}.
	 * @param ctx the parse tree
	 */
	void enterConst_def(IDLParser.Const_defContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#const_def}.
	 * @param ctx the parse tree
	 */
	void exitConst_def(IDLParser.Const_defContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#enum_def}.
	 * @param ctx the parse tree
	 */
	void enterEnum_def(IDLParser.Enum_defContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#enum_def}.
	 * @param ctx the parse tree
	 */
	void exitEnum_def(IDLParser.Enum_defContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#enum_type}.
	 * @param ctx the parse tree
	 */
	void enterEnum_type(IDLParser.Enum_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#enum_type}.
	 * @param ctx the parse tree
	 */
	void exitEnum_type(IDLParser.Enum_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#enum_elements}.
	 * @param ctx the parse tree
	 */
	void enterEnum_elements(IDLParser.Enum_elementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#enum_elements}.
	 * @param ctx the parse tree
	 */
	void exitEnum_elements(IDLParser.Enum_elementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#enum_item}.
	 * @param ctx the parse tree
	 */
	void enterEnum_item(IDLParser.Enum_itemContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#enum_item}.
	 * @param ctx the parse tree
	 */
	void exitEnum_item(IDLParser.Enum_itemContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#any_literal}.
	 * @param ctx the parse tree
	 */
	void enterAny_literal(IDLParser.Any_literalContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#any_literal}.
	 * @param ctx the parse tree
	 */
	void exitAny_literal(IDLParser.Any_literalContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#numeric_lit}.
	 * @param ctx the parse tree
	 */
	void enterNumeric_lit(IDLParser.Numeric_litContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#numeric_lit}.
	 * @param ctx the parse tree
	 */
	void exitNumeric_lit(IDLParser.Numeric_litContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#integer_lit}.
	 * @param ctx the parse tree
	 */
	void enterInteger_lit(IDLParser.Integer_litContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#integer_lit}.
	 * @param ctx the parse tree
	 */
	void exitInteger_lit(IDLParser.Integer_litContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#float_lit}.
	 * @param ctx the parse tree
	 */
	void enterFloat_lit(IDLParser.Float_litContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#float_lit}.
	 * @param ctx the parse tree
	 */
	void exitFloat_lit(IDLParser.Float_litContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#string_lit}.
	 * @param ctx the parse tree
	 */
	void enterString_lit(IDLParser.String_litContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#string_lit}.
	 * @param ctx the parse tree
	 */
	void exitString_lit(IDLParser.String_litContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#qualified_ident}.
	 * @param ctx the parse tree
	 */
	void enterQualified_ident(IDLParser.Qualified_identContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#qualified_ident}.
	 * @param ctx the parse tree
	 */
	void exitQualified_ident(IDLParser.Qualified_identContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#qualified_part}.
	 * @param ctx the parse tree
	 */
	void enterQualified_part(IDLParser.Qualified_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#qualified_part}.
	 * @param ctx the parse tree
	 */
	void exitQualified_part(IDLParser.Qualified_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#qualified_separator}.
	 * @param ctx the parse tree
	 */
	void enterQualified_separator(IDLParser.Qualified_separatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#qualified_separator}.
	 * @param ctx the parse tree
	 */
	void exitQualified_separator(IDLParser.Qualified_separatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#member_decl}.
	 * @param ctx the parse tree
	 */
	void enterMember_decl(IDLParser.Member_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#member_decl}.
	 * @param ctx the parse tree
	 */
	void exitMember_decl(IDLParser.Member_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#type_decl}.
	 * @param ctx the parse tree
	 */
	void enterType_decl(IDLParser.Type_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#type_decl}.
	 * @param ctx the parse tree
	 */
	void exitType_decl(IDLParser.Type_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#type_modifier}.
	 * @param ctx the parse tree
	 */
	void enterType_modifier(IDLParser.Type_modifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#type_modifier}.
	 * @param ctx the parse tree
	 */
	void exitType_modifier(IDLParser.Type_modifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#pointer_type}.
	 * @param ctx the parse tree
	 */
	void enterPointer_type(IDLParser.Pointer_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#pointer_type}.
	 * @param ctx the parse tree
	 */
	void exitPointer_type(IDLParser.Pointer_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#any_type}.
	 * @param ctx the parse tree
	 */
	void enterAny_type(IDLParser.Any_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#any_type}.
	 * @param ctx the parse tree
	 */
	void exitAny_type(IDLParser.Any_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#utility_type}.
	 * @param ctx the parse tree
	 */
	void enterUtility_type(IDLParser.Utility_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#utility_type}.
	 * @param ctx the parse tree
	 */
	void exitUtility_type(IDLParser.Utility_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#integral_type}.
	 * @param ctx the parse tree
	 */
	void enterIntegral_type(IDLParser.Integral_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#integral_type}.
	 * @param ctx the parse tree
	 */
	void exitIntegral_type(IDLParser.Integral_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#float_type}.
	 * @param ctx the parse tree
	 */
	void enterFloat_type(IDLParser.Float_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#float_type}.
	 * @param ctx the parse tree
	 */
	void exitFloat_type(IDLParser.Float_typeContext ctx);
}