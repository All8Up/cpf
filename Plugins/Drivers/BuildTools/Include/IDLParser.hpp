//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/BuildTools/iIDLParser.hpp"
#include "CPF/GOM/tUnknown.hpp"
#undef ERROR
#include "antlr4-runtime.h"

namespace CPF
{
	class Parser : public GOM::tUnknown<iIDLParser>
	{
	public:
		Parser()
			: mpParseTree(nullptr)
		{}

		GOM::Result Generate(OutputLanguage language, const char* name, const char* outName) override;

	private:
		antlr4::tree::ParseTree* mpParseTree;
	};
}
