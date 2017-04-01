//////////////////////////////////////////////////////////////////////////
#include "iTestPlugin.hpp"
#include "Plugin/iRegistry.hpp"

//////////////////////////////////////////////////////////////////////////
using namespace Cpf;

//////////////////////////////////////////////////////////////////////////
class TestPlugin : public iTestPlugin
{
public:
	TestPlugin();
	virtual ~TestPlugin();

	// iRefCounted overrides.
	int32_t AddRef() override;
	int32_t Release() override;

	// iUnknown overrides.
	COM::Result QueryInterface(COM::InterfaceID id, void**) override;

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
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return registry->Install(kTestPluginCID, [](COM::iUnknown*) -> COM::iUnknown* {++sRefCount; return new TestPlugin; });
	}
	return COM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return sRefCount == 0;
}

extern "C"
bool CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(kTestPluginCID);
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
TestPlugin::TestPlugin()
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

COM::Result TestPlugin::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		*outIface = nullptr;
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		case iTestPlugin::kIID.GetID():
			*outIface = static_cast<iTestPlugin*>(this);
			break;

		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

uint32_t TestPlugin::Test()
{
	return 0;
}
