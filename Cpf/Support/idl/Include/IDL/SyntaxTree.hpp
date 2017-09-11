//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"
#include "Vector.hpp"

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
		SyntaxTree() {}

		void SetModule(const SymbolPath& path) { mModule = path; }
		const SymbolPath& GetModule() const { return mModule; }

	private:
		SymbolPath mModule;
	};
}
