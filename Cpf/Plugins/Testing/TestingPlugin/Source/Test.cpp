#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Logging/Logging.hpp"
#include "Test.hpp"

using namespace Cpf;
using namespace Testing;

//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(Testing);
		registry->Install(kTestCID, new Plugin::tClassInstance<Test>());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return true;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(kTestCID);
		CPF_DROP_LOG(Testing);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}


//////////////////////////////////////////////////////////////////////////
Test::Test(iBase*)
{

}

Test::~Test()
{}

GOM::Result CPF_STDCALL Test::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;

		case kIID.GetID():
			*outIface = static_cast<iTest*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
