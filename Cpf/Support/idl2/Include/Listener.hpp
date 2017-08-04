//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseListener.h"

namespace IDL
{
	class Listener : public IDLParserBaseListener
	{
		void exitNamespace_stmt(IDLParser::Namespace_stmtContext * ctx) override;
		void exitImport_stmt(IDLParser::Import_stmtContext * ctx) override;
		void exitConst_def(IDLParser::Const_defContext * ctx) override;
		void exitEnum_def(IDLParser::Enum_defContext * ctx) override;
		void exitStruct_stmt(IDLParser::Struct_stmtContext * ctx) override;
		void exitInterface_decl(IDLParser::Interface_declContext * ctx) override;
	};
}
