//////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "IDL/CodeGen/Context.hpp"


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

			virtual bool Generate(Context& context, SyntaxTree&) = 0;

		protected:
		private:
		};

		enum class Language
		{
			Cpp,
			Rust,
			Python3
		};
		std::shared_ptr<NodeFactory> CreateNodeFactory(Language language);
		std::shared_ptr<Generator> Create(Language language);
	}
}
