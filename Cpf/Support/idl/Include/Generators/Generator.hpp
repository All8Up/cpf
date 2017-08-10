//////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "Generators/CodeWriter.hpp"

namespace IDLTree
{
	class SymbolTable;
}

namespace IDL
{
	class Generator
	{
	public:
		enum class Type : int32_t
		{
			Cpp,
			Python3,
			Rust
		};

		virtual ~Generator() {}

		static std::shared_ptr<Generator> Create(Type type);

		virtual bool Generate(CodeWriter& context, const IDLTree::SymbolTable& symtab) = 0;

	protected:
	private:
	};
}
