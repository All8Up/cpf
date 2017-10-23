#include "CPF/Plugin/iRegistry.hpp"
#include "Plugin/tClassInstance.hpp"
#include "CPF/Logging.hpp"
#include "Test.hpp"

using namespace CPF;
using namespace Testing;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID classPairs[] = { iTest::kIID.GetID(), kTestCID.GetID() };

extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(Testing);
		registry->Install(kTestCID.GetID(), new Plugin::tClassInstance<Test>());
		registry->ClassInstall(1, classPairs);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->ClassRemove(1, classPairs);
		registry->Remove(kTestCID.GetID());
		CPF_DROP_LOG(Testing);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}


//////////////////////////////////////////////////////////////////////////
Test::Test(Plugin::iRegistry*, iUnknown*)
	: mRefCount(1)
{
}

Test::~Test()
{}

int32_t CPF_STDCALL Test::AddRef()
{
	return ++mRefCount;
}

int32_t CPF_STDCALL Test::Release()
{
	int32_t result = --mRefCount;
	if (result == 0)
		delete this;
	return result;
}

GOM::Result CPF_STDCALL Test::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
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

int32_t CPF_STDCALL Test::Tester(int64_t i)
{
	return int32_t(i);
}
