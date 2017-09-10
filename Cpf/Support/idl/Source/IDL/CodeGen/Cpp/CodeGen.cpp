//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Cpp/CodeGen.hpp"
#include "IDL/SyntaxTree.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include "IDL/Nodes/Node.hpp"

using namespace IDL;
using namespace CodeGen;

void Cpp::PopulateNodeFactory(std::shared_ptr<NodeFactory> factory)
{

}


//////////////////////////////////////////////////////////////////////////
bool Cpp::Generator::Generate(Context& context, SyntaxTree& source)
{
	if (HandleProlog(context, source))
	{
		if (HandleNode(context, source, source.GetRoot()))
		{
			if (HandleEpilog(context, source))
			{
				return true;
			}
		}
	}
	return false;
}

bool Cpp::Generator::HandleProlog(Context& context, SyntaxTree& src)
{
	const auto& module = src.GetModule();
	if (!module.Empty())
	{
		for (const auto& part : module.GetPath())
		{
			context.GetWriter().OutputLine("namespace %s", part.c_str());
			context.GetWriter().OutputLine("{");
			context.GetWriter().Indent();
		}
	}

	return true;
}

bool Cpp::Generator::HandleEpilog(Context& context, SyntaxTree& src)
{
	const auto& module = src.GetModule();
	if (!module.Empty())
	{
		for (const auto& part : module.GetPath())
		{
			(void)part;
			context.GetWriter().Unindent();
			context.GetWriter().OutputLine("}");
		}
	}
	return true;
}

bool Cpp::Generator::HandleNode(Context& context, SyntaxTree& src, const Node& node)
{
	if (node.WriteProlog(context, src))
	{
		for (const auto& child : node.GetChildren())
		{
			if (!HandleNode(context, src, *child))
				return false;
		}

		if (node.WriteEpilog(context, src))
		{
			return true;
		}
	}
	return false;
}
