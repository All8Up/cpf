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
#include "IO/IO.hpp"
#include "IO/Stream.hpp"
#include "IO/File.hpp"
#include "IO/TextWriter.hpp"


int main(int argc, char** argv)
{
	(void)argc; (void)argv;
	Cpf::IOInitializer::Install();

	//////////////////////////////////////////////////////////////////////////
	// Parse the IDL file.
	antlr4::ANTLRFileStream input("C:/Projects/cpf/Cpf/Support/idl/TestData/iUnknown.idl");
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);
	antlr4::tree::ParseTree* parseTree = parser.main();

	//////////////////////////////////////////////////////////////////////////
	// Transform the parse tree to the IDL syntax tree.
	IDL::Visitor visitor;
	Cpf::IO::StreamPtr outStream(Cpf::IO::File::Create("iUnknown.txt", Cpf::IO::StreamAccess::eWrite));
	Cpf::IO::TextWriter textWriter(outStream);
	IDL::CodeGen::CodeWriter writer(textWriter);
	{
		auto generator = Create(IDL::CodeGen::Language::Cpp);
		generator->Begin(visitor, writer);
		visitor.visit(parseTree);
		generator->End();
	}

	/*
	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());
	*/

	Cpf::IOInitializer::Remove();
	return 0;
}
