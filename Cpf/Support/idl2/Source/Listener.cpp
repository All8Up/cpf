//////////////////////////////////////////////////////////////////////////
#include "Listener.hpp"
#include "Handlers.hpp"

using namespace IDL;

void Listener::exitNamespace_stmt(IDLParser::Namespace_stmtContext * ctx)
{
	if (ctx->namespace_name())
	{
		std::string name = ctx->namespace_name()->getText();
		printf("Namespace: %s\n", name.c_str());
	}
}

void Listener::exitEnum_def(IDLParser::Enum_defContext * ctx)
{
	if (ctx->IDENT())
	{
		std::string name = ctx->IDENT()->toString();
		printf("Enum: %s\n", name.c_str());
	}
}

/**
 * @brief Exit import statement.
 * @param [in,out] ctx If non-null, the context.
 */
void Listener::exitImport_stmt(IDLParser::Import_stmtContext * ctx)
{
	auto test = ctx->children[1]->children[0]->toString();
	printf("Import: %s\n", test.c_str());
}

/**
 * @brief Exit structure statement.
 * @param [in,out] ctx If non-null, the context.
 */
void Listener::exitStruct_stmt(IDLParser::Struct_stmtContext * ctx)
{
	auto str_decl = ctx->struct_decl();
	if (str_decl)
	{
		static volatile int a = 0;
		++a;
	}
}

/**
 * @brief Exit interface declaration.
 * @param [in,out] ctx If non-null, the context.
 */
void Listener::exitInterface_decl(IDLParser::Interface_declContext * ctx)
{
	auto iface = ctx->IDENT()->toString();
	printf("Interface: %s\n", iface.c_str());

	auto super = ctx->interface_super();
	if (super)
	{
		auto super_name = GetQualifiedIdent(super->qualified_ident());
		printf("  -> %s\n", super_name.c_str());
	}
}

void Listener::exitConst_def(IDLParser::Const_defContext * ctx)
{}
