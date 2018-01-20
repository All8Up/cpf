//////////////////////////////////////////////////////////////////////////
#include "iTestPlugin.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Plugin/tClassFactory.hpp"

//////////////////////////////////////////////////////////////////////////
using namespace CPF;

//////////////////////////////////////////////////////////////////////////
class TestPlugin : public iTestPlugin
{
public:
	TestPlugin(Plugin::iRegistry*, iUnknown* outer);
	virtual ~TestPlugin();

	// iRefCounted overrides.
	int32_t AddRef() override;
	int32_t Release() override;

	// iBase overrides.
	GOM::Result QueryInterface(GOM::IID id, void**) override;

	// iTestPlugin overrides.
	uint32_t Test() override;

private:
	int32_t mRefCount;
};

//////////////////////////////////////////////////////////////////////////
TestPlugin::TestPlugin(Plugin::iRegistry*, iUnknown*)
	: mRefCount(1)
{}

TestPlugin::~TestPlugin()
{
	CPF_ASSERT(mRefCount == 0);
}

int32_t TestPlugin::AddRef()
{
	return ++mRefCount;
}

int32_t TestPlugin::Release()
{
	if (mRefCount-- == 0)
	{
		delete this;
		return 0;
	}
	return mRefCount;
}

GOM::Result TestPlugin::QueryInterface(GOM::IID id, void** outIface)
{
	if (outIface)
	{
		*outIface = nullptr;
		switch (uint64_t(id))
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		case iTestPlugin::kIID.GetID():
			*outIface = static_cast<iTestPlugin*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

uint32_t TestPlugin::Test()
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Install(kTestPluginCID, new Plugin::tClassFactory<TestPlugin>());
	}
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Remove(kTestPluginCID);
	}
	return GOM::kInvalidParameter;
}

CPF_REGISTER_PLUGIN(TestPlugin)
	&Install,
	&Remove
};
