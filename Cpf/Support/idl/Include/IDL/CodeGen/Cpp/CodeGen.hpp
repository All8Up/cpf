//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/Generator.hpp"
#include "IDL/Nodes/Success.hpp"

namespace IDL
{
	class Node;

	namespace CodeGen
	{
		namespace Cpp
		{
			void PopulateNodeFactory(std::shared_ptr<NodeFactory> factory);

			class Generator : public CodeGen::Generator
			{
			public:
				bool Generate(Context& context, SyntaxTree& src) override;
				bool HandleProlog(Context& context, SyntaxTree& src);
				bool HandleEpilog(Context& context, SyntaxTree& src);
				bool HandleNode(Context& context, SyntaxTree& src, const Node& node);
			};

			class Success : public IDL::Success
			{

			};
		}
	}
}
