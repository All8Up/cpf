//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/CodeWriter.hpp"
#include "IDL/Nodes/Node.hpp"
#include "Patterns/Factory.hpp"

namespace IDL
{
	namespace CodeGen
	{
		using NodeFactory = Cpf::Patterns::Factory<uint64_t, Node>;

		class Context
		{
		public:
			Context(CodeWriter& codeWriter, std::shared_ptr<NodeFactory> factory)
				: mCodeWriter(codeWriter)
				, mFactory(factory)
			{}

			CodeWriter& GetWriter() const { return mCodeWriter; }
			NodeFactory& GetFactory() const { return *mFactory; }

		private:
			CodeWriter& mCodeWriter;
			std::shared_ptr<NodeFactory> mFactory;
		};
	}
}
