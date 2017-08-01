//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseListener.h"

namespace idl
{
	class Listener : public IDLParserBaseListener
	{
		void exitImport_stmt(IDLParser::Import_stmtContext * ctx) override;
		void exitConst_def(IDLParser::Const_defContext * ctx) override;
		void exitStruct_stmt(IDLParser::Struct_stmtContext * ctx) override;
		void exitInterface_decl(IDLParser::Interface_declContext * ctx) override;
	};
}
