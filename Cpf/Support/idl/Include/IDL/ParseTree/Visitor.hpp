//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"
#include "IDL/SyntaxTree.hpp"

namespace IDL
{
	class Visitor : public IDLParserBaseVisitor
	{
	public:
		Visitor(SyntaxTree& tree);

		antlrcpp::Any visitModule_stmt(IDLParser::Module_stmtContext *context) override;

	private:
		SyntaxTree& mpSyntaxTree;
	};
}
