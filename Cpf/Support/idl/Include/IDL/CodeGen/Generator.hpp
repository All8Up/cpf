//////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "Generators/CodeWriter.hpp"
#include "IDL/SymbolTable.hpp"

namespace IDL
{
	namespace CodeGen
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

			virtual bool Generate(CodeWriter& context, const SymbolTable& symtab) = 0;

		protected:
		private:
		};
	}
}
