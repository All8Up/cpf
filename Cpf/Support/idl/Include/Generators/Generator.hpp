//////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "Generators/Context.hpp"

namespace AST
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

		virtual bool Generate(Context& context, const AST::SymbolTable& symtab) = 0;

	protected:
	private:
	};
}
