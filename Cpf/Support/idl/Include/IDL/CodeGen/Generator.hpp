//////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "Generators/CodeWriter.hpp"
#include "IDL/SymbolTable.hpp"


namespace IDL
{
	class SyntaxTree;
}

namespace IDL
{
	namespace CodeGen
	{
		class Generator
		{
		public:
			virtual ~Generator() {}

			virtual bool Generate(CodeWriter& context, SyntaxTree&) = 0;

		protected:
		private:
		};

		enum class Language
		{
			Cpp,
			Rust,
			Python3
		};
		std::shared_ptr<Generator> Create(Language language);
	}
}
