//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"

namespace IDL
{
	class SyntaxTree;
	namespace CodeGen
	{
		class Context;
	}

	class Node
	{
	public:
		using Children = Cpf::Vector<Node*>;

		virtual bool AddChild(Node*) { return false; }
		virtual const Children& GetChildren() const { return Children(); }

		virtual bool WriteProlog(CodeGen::Context&, SyntaxTree&) const = 0;
		virtual bool WriteEpilog(CodeGen::Context&, SyntaxTree&) const = 0;

	private:
		Children mChildren;
	};

	class ContainerNode : public Node
	{
	public:
		bool AddChild(Node* child) override { mChildren.push_back(child); return true; }
		const Children& GetChildren() const override { return mChildren; }

	private:
		Children mChildren;
	};

	class RootNode : public ContainerNode
	{
	public:
		bool WriteProlog(CodeGen::Context&, SyntaxTree&) const override { return true; }
		bool WriteEpilog(CodeGen::Context&, SyntaxTree&) const override { return true; }
	};
}
