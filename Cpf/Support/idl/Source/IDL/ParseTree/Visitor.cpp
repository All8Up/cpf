//////////////////////////////////////////////////////////////////////////
#include "IDL/ParseTree/Visitor.hpp"

using namespace IDL;

//////////////////////////////////////////////////////////////////////////
CPF::String TrimStringLit(const CPF::String& lit)
{
	if (lit.empty())
		return CPF::String();
	return CPF::String(lit.begin() + 1, lit.end() - 1);
}

SymbolPath GetPath(IDLParser::Qualified_identContext* ctx)
{
	const auto ident = ctx->IDENT()->toString();
	SymbolPath path(ident);

	for (const auto& p : ctx->qualified_part())
	{
		path.Push(CPF::String(p->IDENT()->toString().c_str()));
	}
	return path;
}

//////////////////////////////////////////////////////////////////////////
Visitor::Visitor()
{}

antlrcpp::Any Visitor::visitMain(IDLParser::MainContext *ctx)
{
	Emit<Start>();
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitModule_stmt(IDLParser::Module_stmtContext *ctx)
{
	const auto ident = ctx->qualified_ident()->IDENT()->toString();
	SymbolPath path(ident);

	for (const auto& p : ctx->qualified_ident()->qualified_part())
	{
		path.Push(CPF::String(p->IDENT()->toString().c_str()));
	}
	Emit<ModuleStmt>(path);

	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitSuccess_stmt(IDLParser::Success_stmtContext *ctx)
{
	auto name = ctx->IDENT()->toString();
	auto subSystem = TrimStringLit(ctx->STRING_LIT()[0]->toString());
	auto desc = TrimStringLit(ctx->STRING_LIT()[1]->toString());
	Emit<SuccessType>(name, subSystem, desc);

	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitFailure_stmt(IDLParser::Failure_stmtContext *ctx)
{
	auto name = ctx->IDENT()->toString();
	auto subSystem = TrimStringLit(ctx->STRING_LIT()[0]->toString());
	auto desc = TrimStringLit(ctx->STRING_LIT()[1]->toString());
	Emit<FailureType>(name, subSystem, desc);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx)
{
	String source;
	if (ctx->all_or_ident()->IDENT())
		source = ctx->all_or_ident()->IDENT()->toString();
	else
		source = "*";
	Emit<ImportStmt>(source, GetPath(ctx->qualified_ident()));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitImport_stmt(IDLParser::Import_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitInterface_decl(IDLParser::Interface_declContext *ctx)
{
	InterfaceDecl decl;
	decl.mName = ctx->IDENT()->toString();
	if (ctx->interface_super())
	{
		// Have a parent.
		decl.mSuper = GetPath(ctx->interface_super()->qualified_ident());
	}

	for (const auto& item : ctx->interface_block()->interface_item())
	{
		if (item->const_def())
		{

		}
		else if (item->enum_def())
		{

		}
		else if (item->function_decl())
		{
			auto func = item->function_decl();
			FunctionDecl funcDecl;
			funcDecl.mName = func->IDENT()->toString();
			funcDecl.mReturnType = ParseTypeDecl(func->type_decl());
			funcDecl.mConst = (func->Const() != nullptr ? true : false);
			if (func->function_param_list())
			{
				for (auto param : func->function_param_list()->function_param())
				{
					ParamDecl paramDecl;
					paramDecl.mName = param->IDENT() ? param->IDENT()->toString() : String();
					paramDecl.mType = ParseTypeDecl(param->type_decl());
					funcDecl.mParams.push_back(paramDecl);
				}
			}

			decl.mFunctions.push_back(funcDecl);
		}
	}

	Emit<InterfaceDeclStmt>(decl);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitInterface_fwd(IDLParser::Interface_fwdContext *ctx)
{
	Emit<InterfaceFwdStmt>(GetPath(ctx->qualified_ident()).ToString("::"));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitStruct_fwd(IDLParser::Struct_fwdContext *ctx)
{
	Emit<StructFwdStmt>(GetPath(ctx->qualified_ident()).ToString("::"));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitStruct_decl(IDLParser::Struct_declContext *ctx)
{
	StructDecl structDecl;
	structDecl.mName = ctx->IDENT()->toString();
	auto members = ctx->struct_block()->struct_item();
	for (const auto& item : members)
	{
		if (item->const_def())
		{

		}
		else if (item->enum_def())
		{

		}
		else if (item->member_decl())
		{
			auto decl = item->member_decl();
			DataMemberDecl data;
			data.mName = decl->IDENT()->toString();
			data.mType = ParseTypeDecl(decl->type_decl());
			structDecl.mDataMembers.push_back(data);
		}
	}

	Emit<StructDeclStmt>(structDecl);
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitEnum_fwd(IDLParser::Enum_fwdContext *ctx)
{
	Emit<EnumForwardStmt>(ctx->IDENT()->toString(), ParseIntegralType(ctx->enum_type()->integral_type()));
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitEnum_def(IDLParser::Enum_defContext *ctx)
{
	EnumDecl enumDecl;
	enumDecl.mName = ctx->IDENT()->toString();
	enumDecl.mType = Visitor::Type::Void;
	if (ctx->enum_type() && ctx->enum_type()->integral_type())
		enumDecl.mType = ParseIntegralType(ctx->enum_type()->integral_type()).mType;

	auto items = ctx->enum_elements()->enum_item();
	for (const auto& item : items)
	{
		EnumEntry entry;
		entry.mName = item->IDENT()->toString();
		entry.mValue = 0x7fffffffffffffff;
		if (item->EQUALS())
		{
			entry.mValue = ParseEnumExpr(item->enum_expr());
		}
		enumDecl.mEntries.push_back(entry);
	}

	Emit<EnumDeclStmt>(enumDecl);
	return visitChildren(ctx);
}

Visitor::TypeDecl Visitor::ParseIntegralType(IDLParser::Integral_typeContext* integralType)
{
	TypeDecl result;
	result.mConst = false;

	if (integralType->U8()) result.mType = Type::U8;
	else if (integralType->S8()) result.mType = Type::S8;
	else if (integralType->U16()) result.mType = Type::U16;
	else if (integralType->S16()) result.mType = Type::S16;
	else if (integralType->U32()) result.mType = Type::U32;
	else if (integralType->S32()) result.mType = Type::S32;
	else if (integralType->U64()) result.mType = Type::U64;
	else if (integralType->S64()) result.mType = Type::S64;

	return result;
}


Visitor::TypeDecl Visitor::ParseTypeDecl(IDLParser::Type_declContext* typeDecl)
{
	TypeDecl result;
	result.mConst = typeDecl->type_modifier() == nullptr ? false : true;

	auto anyType = typeDecl->any_type();
	if (anyType->integral_type())
	{
		result.mType = ParseIntegralType(anyType->integral_type()).mType;
	}
	else if (anyType->float_type())
	{
		auto floatType = anyType->float_type();
		if (floatType->F32()) result.mType = Type::F32;
		else if (floatType->F64()) result.mType = Type::F64;
	}
	else if (anyType->utility_type())
	{
		auto utilType = anyType->utility_type();
		if (utilType->Void()) result.mType = Type::Void;
		else if (utilType->RESULT()) result.mType = Type::Result;
	}
	else if (anyType->qualified_ident())
	{
		result.mType = Type::Ident;
		result.mIdent = GetPath(anyType->qualified_ident());
	}
	else
	{
		// Error.
	}

	if (typeDecl->pointer_type())
	{
		for (const auto& ptr : typeDecl->pointer_type()->pointer_decl())
		{
			Pointer pointer;
			if (ptr->Const())
				pointer.mConst = true;
			else
				pointer.mConst = false;
			result.mPointer.push_back(pointer);
		}
	}

	return result;
}

int64_t Visitor::ParseEnumExpr(IDLParser::Enum_exprContext* expr)
{
	auto addSubExpr = expr->expr_add_sub();
	if (addSubExpr->expr_mul_div())
	{
		auto mulDivExpr = addSubExpr->expr_mul_div();
		if (mulDivExpr)
		{
			auto shiftExpr = mulDivExpr->expr_shift();
			if (shiftExpr)
			{
				auto valueExpr = shiftExpr->expr_value();
				if (valueExpr)
				{
					auto litExpr = valueExpr->integer_lit();
					if (litExpr)
					{
						if (litExpr->BIN_LIT())
						{
							
						}
						else if (litExpr->DECIMAL_LIT())
						{
							return atoi(litExpr->DECIMAL_LIT()->toString().c_str());
						}
						else if (litExpr->HEX_LIT())
						{
							
						}
						else if (litExpr->OCT_LIT())
						{
							
						}
					}
				}
			}
		}
	}
	return 0;
}
