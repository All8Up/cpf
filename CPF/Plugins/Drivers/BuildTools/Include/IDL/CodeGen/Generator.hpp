//////////////////////////////////////////////////////////////////////////
#pragma once
#include <memory>
#include "IDLVisitor.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include "CPF/BuildTools/OutputLanguage.hpp"

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

		std::shared_ptr<Generator> Create(CPF::OutputLanguage language);
	}
}
