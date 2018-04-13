//////////////////////////////////////////////////////////////////////////
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Plugin/tClassFactory.hpp"
#include "CPF/BuildTools/iIDLParser.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Plugin.hpp"
#include "IDLParser.hpp"

using namespace CPF;

//////////////////////////////////////////////////////////////////////////
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Install(iIDLParser::kCID, new Plugin::tClassFactory<Parser>());
	}
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Remove(iIDLParser::kCID);
	}
	return GOM::kInvalidParameter;
}

CPF_REGISTER_PLUGIN(IDLParser)
	&Install,
	&Remove
};
