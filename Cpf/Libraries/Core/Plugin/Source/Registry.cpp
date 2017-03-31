//////////////////////////////////////////////////////////////////////////
#include "PluginHost/Registry.hpp"
#include "Plugin/Library.hpp"
#include "Move.hpp"
#include "UnorderedMap.hpp"

using namespace Cpf;
using namespace PluginHost;

class Registry : public Plugin::iRegistry
{
public:
	//
	Registry();
	virtual ~Registry() override;

	// iUnknown overrides.
	int32_t CPF_STDCALL AddRef() override;
	int32_t CPF_STDCALL Release() override;
	bool CPF_STDCALL QueryInterface(InterfaceID id, void**) override;

	// iRegistry overrides.
	bool CPF_STDCALL Load(const char* const) override;
	bool CPF_STDCALL Install(InterfaceID, Creator) override;
	bool CPF_STDCALL Remove(InterfaceID) override;
	bool CPF_STDCALL Exists(InterfaceID id) override;
	bool CPF_STDCALL Create(iUnknown*, InterfaceID, void**) override;

private:
	int32_t mRefCount;

	using LibraryMap = Cpf::UnorderedMap<String, Plugin::Library>;
	using CreationMap = Cpf::UnorderedMap<InterfaceID, Creator>;

	LibraryMap mLibraryMap;
	CreationMap mCreationMap;
};

//////////////////////////////////////////////////////////////////////////
bool CPF_STDCALL PluginHost::CreateRegistry(Plugin::iRegistry** outRegistry)
{
	if (outRegistry)
	{
		*outRegistry = new Registry;
	}
	return outRegistry && (*outRegistry != nullptr);
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

bool CPF_STDCALL Registry::QueryInterface(InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		case iRegistry::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		default:
			*outIface = nullptr;
			return false;;
		}
		AddRef();
	}
	return outIface && (*outIface != nullptr);
}

bool CPF_STDCALL Registry::Load(const char* const name)
{
	if (name)
	{
		auto exists = mLibraryMap.find(name);
		if (exists == mLibraryMap.end())
		{
			Plugin::Library library;
			if (library.Load(name))
			{
				auto install = library.GetAddress<int32_t(*)(iRegistry*)>("Install");
				if (install)
				{
					if ((*install)(this) == 0)
					{
						mLibraryMap.insert(LibraryMap::value_type{ String(name), Move(library) });
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CPF_STDCALL Registry::Install(InterfaceID id, Creator creator)
{
	auto exists = mCreationMap.find(id);
	if (exists == mCreationMap.end())
	{
		mCreationMap.insert(CreationMap::value_type{id, creator});
		return true;
	}
	return false;
}

bool CPF_STDCALL Registry::Remove(InterfaceID id)
{
	auto exists = mCreationMap.find(id);
	if (exists != mCreationMap.end())
	{
		mCreationMap.erase(id);
		return true;
	}
	return false;
}

bool CPF_STDCALL Registry::Exists(InterfaceID id)
{
	auto exists = mCreationMap.find(id);
	return exists != mCreationMap.end();
}

bool CPF_STDCALL Registry::Create(iUnknown* outer, InterfaceID id, void** outIface)
{
	if (outIface)
	{
		auto creator = mCreationMap.find(id);
		if (creator != mCreationMap.end())
		{
			*outIface = (*creator->second)(outer);
			return *outIface != nullptr;
		}
	}
	return false;
}
