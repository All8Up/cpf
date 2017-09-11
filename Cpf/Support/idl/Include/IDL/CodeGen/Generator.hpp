//////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "IDL/ParseTree/Visitor.hpp"

namespace IDL
{
	namespace CodeGen
	{
		class Generator
		{
		public:
			virtual ~Generator() {}

			virtual void Begin(IDL::Visitor&, IDL::CodeGen::CodeWriter&) = 0;
			virtual void End() = 0;

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
