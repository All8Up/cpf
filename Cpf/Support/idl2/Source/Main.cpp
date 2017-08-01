#include "antlr4-runtime.h"
#include "IDLLexer.h"
#include "Listener.hpp"
#include <Windows.h>
#undef INTERFACE

int main(int argc, char** argv)
{
	antlr4::ANTLRFileStream input("C:/Projects/cpf/Cpf/Support/idl2/TestData/iRegistry.idl");
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);
	idl::Listener listener;
	parser.addParseListener(&listener);

	antlr4::tree::ParseTree* tree = parser.main();

	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());

	return 0;
}
