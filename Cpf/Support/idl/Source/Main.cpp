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
	antlr4::ANTLRFileStream input("C:/Projects/cpf/Cpf/Support/idl/TestData/FeatureTest.idl");
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);

	antlr4::tree::ParseTree* tree = parser.main();

	//////////////////////////////////////////////////////////////////////////
	IDL::Visitor visitor;
	visitor.visit(tree);

	IDL::CodeGen::CodeWriter writer;
	std::shared_ptr<IDL::CodeGen::Generator> generator;

	// Run the visitor.
	/*
	{
		// Test the Cpp generator.
		auto generator = IDL::Generator::Create(IDL::Generator::Type::Cpp);
		assert(generator != nullptr);
		IDL::CodeWriter context;
		generator->Generate(context, visitor.GetSymbolTable());
	}
	*/

	/*
	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());
	*/

	return 0;
}
