#include "antlr4-runtime.h"
#include "IDLLexer.h"
#include "Visitor.hpp"
#include <Windows.h>
#undef INTERFACE

int main(int argc, char** argv)
{
	antlr4::ANTLRFileStream input("C:/Projects/cpf/Cpf/Support/idl/TestData/iRegistry.idl");
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);

	antlr4::tree::ParseTree* tree = parser.main();

	// Run the visitor.
	{
		IDL::Visitor visitor;
		visitor.visit(tree);
		printf("-------------------------------------\n");
		for (auto it : visitor.GetSymbolTable())
		{
			auto scope = visitor.GetSymbolTable().GetScopeString(it);
			printf("%s = %s\n", scope.c_str(), it->ToString().c_str());
		}
	}

	/*
	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());
	*/

	return 0;
}
