//////////////////////////////////////////////////////////////////////////
#include "IDLParser.hpp"
#include "IDLLexer.h"
#include "IDLParser.h"
#include "IDLVisitor.hpp"
#include "IDL/CodeGen/Generator.hpp"
#include "CPF/IO/File.hpp"

using namespace CPF;

GOM::Result Parser::Generate(OutputLanguage language, const char* name, const char* outName)
{
	antlr4::ANTLRFileStream input(name);
	IDLLexer lexer(&input);
	antlr4::CommonTokenStream tokenStream(&lexer);
	IDLParser parser(&tokenStream);
	mpParseTree = parser.main();

	if (mpParseTree)
	{
		IDL::Visitor visitor;
		IO::StreamPtr outStream;
		if (IO::File::Create(outName, IO::Access::eWrite).CheckOK(outStream.AsTypePP()))
		{
			IO::TextWriter textWriter(outStream);
			IDL::CodeGen::CodeWriter writer(textWriter);
			{
				auto generator = IDL::CodeGen::Create(language);
				generator->Begin(visitor, writer);
				visitor.visit(mpParseTree);
				generator->End();

				return GOM::kOK;
			}
		}
	}

	return GOM::kInvalidParameter;
}
