//////////////////////////////////////////////////////////////////////////
#include "iTestPlugin.hpp"
#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"

//////////////////////////////////////////////////////////////////////////
using namespace Cpf;

//////////////////////////////////////////////////////////////////////////
class TestPlugin : public iTestPlugin
{
public:
	TestPlugin(iBase* outer);
	virtual ~TestPlugin();

	// iRefCounted overrides.
	int32_t AddRef() override;
	int32_t Release() override;

	// iBase overrides.
	GOM::Result Cast(uint64_t id, void**) override;

	// iTestPlugin overrides.
	uint32_t Test() override;

private:
	int32_t mRefCount;
};

//////////////////////////////////////////////////////////////////////////
namespace
{
	int32_t sRefCount = 0;
}

extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Install(kTestPluginCID.GetID(), new Plugin::tClassInstance<TestPlugin>());
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Remove(kTestPluginCID.GetID());
	}
	return GOM::kInvalidParameter;
}


//////////////////////////////////////////////////////////////////////////
TestPlugin::TestPlugin(iBase*)
	: mRefCount(1)
{}

TestPlugin::~TestPlugin()
{
	CPF_ASSERT(mRefCount == 0);
	--sRefCount;
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

GOM::Result TestPlugin::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		*outIface = nullptr;
		switch (id)
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
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
