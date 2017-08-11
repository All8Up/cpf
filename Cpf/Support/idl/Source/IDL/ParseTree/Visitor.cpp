//////////////////////////////////////////////////////////////////////////
#include "IDL/ParseTree/Visitor.hpp"

using namespace IDL;

Visitor::Visitor(SyntaxTree& tree)
	: mpSyntaxTree(tree)
{}

antlrcpp::Any Visitor::visitModule_stmt(IDLParser::Module_stmtContext *context)
{
	return visitChildren(context);
}
