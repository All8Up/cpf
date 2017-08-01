#include "antlr4-runtime.h"
#include "IDLLexer.h"
#include "IDLParser.h"
#include "IDLParserBaseListener.h"
#include <Windows.h>
#undef INTERFACE

#pragma execution_character_set("utf-8")

std::string ParseQualifiedIdent(IDLParser::Qualified_identContext* ctx)
{
	std::string result;

	result = ctx->IDENT()->toString();
	const auto& parts = ctx->qualified_part();
	for (auto* part : parts)
	{
		result += "::" + part->IDENT()->toString();
	}

	return result;
}

class Listener : public IDLParserBaseListener
{
	void exitImport_stmt(IDLParser::Import_stmtContext * ctx) override
	{
		auto test = ctx->children[1]->children[0]->toString();
		printf("Import: %s\n", test.c_str());
	}

	void exitStruct_stmt(IDLParser::Struct_stmtContext * ctx) override
	{
		auto str_decl = ctx->struct_decl();
		if (str_decl)
		{
			static volatile int a = 0;
			++a;
		}
	}

	void exitInterface_decl(IDLParser::Interface_declContext * ctx) override
	{
		auto iface = ctx->IDENT();
		auto iface_name = iface->toString();
		printf("Interface: %s\n", iface_name.c_str());

		auto super = ctx->interface_super();
		if (super)
		{
			auto super_name = ParseQualifiedIdent(super->qualified_ident());
			printf("  -> %s\n", super_name.c_str());
		}
	}
};

int main(int argc, char** argv)
{
	antlr4::ANTLRFileStream input("C:/Projects/cpf/Cpf/Support/idl2/TestData/iRegistry.idl");
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);
	Listener listener;
	parser.addParseListener(&listener);

	antlr4::tree::ParseTree* tree = parser.main();

	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());

	return 0;
}
