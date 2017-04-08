//////////////////////////////////////////////////////////////////////////
#include "PluginHost/Registry.hpp"
#include "Plugin.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Move.hpp"
#include "UnorderedMap.hpp"

using namespace Cpf;
using namespace PluginHost;

class Registry : public Plugin::iRegistry
{
public:
	//
	Registry();
	virtual ~Registry();

	// iUnknown overrides.
	int32_t CPF_STDCALL AddRef() override;
	int32_t CPF_STDCALL Release() override;
	COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void**) override;

	// iRegistry overrides.
	COM::Result CPF_STDCALL Load(const char* const) override;
	COM::Result CPF_STDCALL Install(COM::ClassID, Plugin::iClassInstance*) override;
	COM::Result CPF_STDCALL Remove(COM::ClassID) override;
	COM::Result CPF_STDCALL Exists(COM::ClassID id) override;
	COM::Result CPF_STDCALL Create(COM::iUnknown*, COM::ClassID, COM::InterfaceID, void**) override;

private:
	int32_t mRefCount;

	using LibraryMap = Cpf::UnorderedMap<String, Plugin::Library>;
	using CreationMap = Cpf::UnorderedMap<COM::ClassID, IntrusivePtr<Plugin::iClassInstance>>;

	LibraryMap mLibraryMap;
	CreationMap mCreationMap;
};

//////////////////////////////////////////////////////////////////////////
COM::Result CPF_STDCALL PluginHost::CreateRegistry(Plugin::iRegistry** outRegistry)
{
	if (outRegistry)
	{
		*outRegistry = new Registry;
		if (*outRegistry)
			return COM::kOK;
		return COM::kOutOfMemory;
	}
	return COM::kInvalidParameter;
}


//////////////////////////////////////////////////////////////////////////
Registry::Registry()
	: mRefCount(1)
{}

Registry::~Registry()
{
	CPF_ASSERT(mRefCount == 0);
}

int32_t CPF_STDCALL Registry::AddRef()
{
	return ++mRefCount;
}

int32_t CPF_STDCALL Registry::Release()
{
	if (--mRefCount == 0)
	{
		delete this;
		return 0;
	}
	return mRefCount;
}

COM::Result CPF_STDCALL Registry::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;

		case iRegistry::kIID.GetID():
			*outIface = static_cast<iRegistry*>(this);
			break;

		default:
			*outIface = nullptr;
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Registry::Load(const char* const name)
{
	if (name)
	{
		auto exists = mLibraryMap.find(name);
		if (exists == mLibraryMap.end())
		{
			Plugin::Library library;
			if (library.Load(name))
			{
				auto install = library.GetAddress<int32_t(*)(iRegistry*)>(kPluginAPIInstall);
				if (install)
				{
					if ((*install)(this) != 0)
					{
						mLibraryMap.insert(LibraryMap::value_type{ String(name), Move(library) });
						return COM::kOK;
					}
				}
			}
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Registry::Install(COM::ClassID id, Plugin::iClassInstance* clsInst)
{
	auto exists = mCreationMap.find(id);
	if (exists == mCreationMap.end())
	{
		mCreationMap.insert(CreationMap::value_type{id, clsInst});
		return COM::kOK;
	}
	return COM::kUnknownClass;
}

COM::Result CPF_STDCALL Registry::Remove(COM::ClassID id)
{
	auto exists = mCreationMap.find(id);
	if (exists != mCreationMap.end())
	{
		mCreationMap.erase(id);
		return COM::kOK;
	}
	return COM::kUnknownClass;
}

COM::Result CPF_STDCALL Registry::Exists(COM::ClassID id)
{
	auto exists = mCreationMap.find(id);
	return exists != mCreationMap.end() ? COM::kOK : COM::kUnknownClass;
}

COM::Result CPF_STDCALL Registry::Create(COM::iUnknown* outer, COM::ClassID cid, COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		auto creator = mCreationMap.find(cid);
		if (creator != mCreationMap.end())
		{
			COM::iUnknown* instance;
			creator->second->CreateInstance(static_cast<Plugin::iRegistry*>(this), outer, &instance);
			if (instance)
			{
				COM::Result result = instance->QueryInterface(id, outIface);
				instance->Release();
				return result;
			}
		}
	}
	return COM::kInvalidParameter;
}
