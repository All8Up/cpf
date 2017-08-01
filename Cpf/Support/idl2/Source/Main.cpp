#include "antlr4-runtime.h"
#include "IDLLexer.h"
#include "IDLParser.h"
#include "IDLParserBaseListener.h"
#include <Windows.h>

#pragma execution_character_set("utf-8")

class Listener : public IDLParserBaseListener
{
	void enterString_lit(IDLParser::String_litContext * ctx) override
	{
	}

	void exitString_lit(IDLParser::String_litContext * ctx) override
	{
	}

	void enterImport_stmt(IDLParser::Import_stmtContext * ctx) override
	{
		auto lit = ctx->STRING_LIT();

		if (lit)
		{

		}
	}
	void exitImport_stmt(IDLParser::Import_stmtContext * ctx) override
	{
		auto lit = ctx->STRING_LIT();

		if (lit)
		{

		}
	}

	void enterStruct_stmt(IDLParser::Struct_stmtContext * ctx) override
	{
		auto str_decl = ctx->struct_decl();
		if (str_decl)
		{
			static volatile int a = 0;
			++a;
		}
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
