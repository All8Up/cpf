//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"
#include "Vector.hpp"
#include "IDL/Nodes/Node.hpp"

namespace IDL
{
	class SymbolPath
	{
	public:
		using Path = Cpf::Vector<Cpf::String>;

		SymbolPath() {}
		SymbolPath(const Cpf::String& path) : mPath{ path } {}
		~SymbolPath() {}

		bool Empty() const { return mPath.empty(); }
		void Push(const Cpf::String& part) { mPath.push_back(part); }
		const Path& GetPath() const { return mPath; }

	private:
		Path mPath;
	};

	class SyntaxTree
	{
	public:
		SyntaxTree() : mpCurrent(&mRoot) {}

		void SetModule(const SymbolPath& path) { mModule = path; }
		const SymbolPath& GetModule() const { return mModule; }

		const Node& GetRoot() const { return mRoot; }

		bool Append(Node* node)
		{
			CPF_ASSERT(mpCurrent != nullptr);

			if (mpCurrent->AddChild(node))
				return true;
			return false;
		}

	private:
		SymbolPath mModule;
		RootNode mRoot;
		Node* mpCurrent;
	};
}
