//////////////////////////////////////////////////////////////////////////
#include "antlr4-runtime.h"
#include "IDLLexer.h"
#include "Visitor/Visitor.hpp"
#include "Generators/Generator.hpp"
#include <Windows.h>

int main(int argc, char** argv)
{
	antlr4::ANTLRFileStream input("C:/Projects/cpf/Cpf/Support/idl/TestData/FeatureTest.idl");
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);

	antlr4::tree::ParseTree* tree = parser.main();

	// Run the visitor.
	{
		IDL::Visitor visitor;
		visitor.visit(tree);

		// Test the Cpp generator.
		auto generator = IDL::Generator::Create(IDL::Generator::Type::Cpp);
		assert(generator != nullptr);
		IDL::Context context;
		generator->Generate(context, visitor.GetSymbolTable());
	}

	/*
	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());
	*/

	return 0;
}
