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
#include "IO/Path.hpp"
#include "IO/File.hpp"
#include "IO/Stream.hpp"
#include "IO/Directory.hpp"
#include "IO/TextWriter.hpp"
#include "Logging/Logging.hpp"
#include <gflags/gflags.h>

DEFINE_string(input, "", "Input file to process.");
DEFINE_string(output, "", "Output file.");
DEFINE_bool(cpp, false, "Output C++ targets.");
DEFINE_bool(rust, false, "Output rust targets.");

int main(int argc, char** argv)
{
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	CPF_LOG_LEVELS(Warn);
	CPF::IOInitializer::Install();

	if (FLAGS_input.empty())
	{
		printf("Error: no input file given.\n");
		return -1;
	}
	if (FLAGS_output.empty())
	{
		printf("Error: no output file given.\n");
		return -1;
	}
	IDL::CodeGen::Language language;
	if (FLAGS_cpp)
		language = IDL::CodeGen::Language::Cpp;
	else if (FLAGS_rust)
		language = IDL::CodeGen::Language::Rust;
	else
	{
		printf("Error: no target language specified.\n");
		return -1;
	}

	CPF::IO::Directory::Create(CPF::IO::Path::GetDirectory(FLAGS_output));

	//////////////////////////////////////////////////////////////////////////
	// Parse the IDL file.
	antlr4::ANTLRFileStream input(FLAGS_input);
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);
	antlr4::tree::ParseTree* parseTree = parser.main();

	//////////////////////////////////////////////////////////////////////////
	// Transform the parse tree to the IDL syntax tree.
	IDL::Visitor visitor;
	CPF::IO::StreamPtr outStream(CPF::IO::File::Create(FLAGS_output, CPF::IO::StreamAccess::eWrite));
	CPF::IO::TextWriter textWriter(outStream);
	IDL::CodeGen::CodeWriter writer(textWriter);
	{
		auto generator = Create(language);
		generator->Begin(visitor, writer);
		visitor.visit(parseTree);
		generator->End();
	}

	/*
	std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
	OutputDebugString(s.data());
	*/

	CPF::IOInitializer::Remove();
	return 0;
}
