//////////////////////////////////////////////////////////////////////////
#include "antlr4-runtime.h"
#include "IDLLexer.h"
#include "IDLParser.h"
#include "IDL/ParseTree/Visitor.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include "IDL/CodeGen/Generator.hpp"
#ifdef _WIN32
#   include <Windows.h>
#endif

int main(int argc, char** argv)
{
	(void)argc; (void)argv;

	//////////////////////////////////////////////////////////////////////////
	// Parse the IDL file.
	antlr4::ANTLRFileStream input("C:/Projects/cpf/Cpf/Support/idl/TestData/iUnknown.idl");
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);
	antlr4::tree::ParseTree* parseTree = parser.main();

	//////////////////////////////////////////////////////////////////////////
	// Transform the parse tree to the IDL syntax tree.
	IDL::SyntaxTree syntaxTree;
	IDL::CodeGen::CodeWriter writer;
	auto nodeFactory = CreateNodeFactory(IDL::CodeGen::Language::Cpp);
	IDL::CodeGen::Context context(writer, nodeFactory);
	IDL::Visitor visitor(context, syntaxTree);
	visitor.visit(parseTree);

	auto generator = Create(IDL::CodeGen::Language::Cpp);
	generator->Generate(context, syntaxTree);

	/*
	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());
	*/

	return 0;
}
