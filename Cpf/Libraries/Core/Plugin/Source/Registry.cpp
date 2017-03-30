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
	int32_t AddRef() override;
	int32_t Release() override;
	bool QueryInterface(InterfaceID id, void**) override;

	// iRegistry overrides.
	bool Load(const char* const) override;
	bool Install(InterfaceID, Creator) override;
	bool Remove(InterfaceID) override;
	bool Registry::Exists(InterfaceID id) override;
	bool Create(InterfaceID, void**) override;

private:
	int32_t mRefCount;

	using LibraryMap = Cpf::UnorderedMap<String, Plugin::Library>;
	LibraryMap mLibraryMap;
	using CreationMap = Cpf::UnorderedMap<InterfaceID, Creator>;
	CreationMap mCreationMap;
};

//////////////////////////////////////////////////////////////////////////
bool PluginHost::CreateRegistry(Plugin::iRegistry** outRegistry)
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

int32_t Registry::AddRef()
{
	return ++mRefCount;
}

int32_t Registry::Release()
{
	if (--mRefCount == 0)
	{
		delete this;
		return 0;
	}
	return mRefCount;
}

bool Registry::QueryInterface(InterfaceID id, void** outIface)
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

bool Registry::Load(const char* const name)
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

bool Registry::Install(InterfaceID id, Creator creator)
{
	auto exists = mCreationMap.find(id);
	if (exists == mCreationMap.end())
	{
		mCreationMap.insert(CreationMap::value_type{id, creator});
		return true;
	}
	return false;
}

bool Registry::Remove(InterfaceID id)
{
	auto exists = mCreationMap.find(id);
	if (exists != mCreationMap.end())
	{
		mCreationMap.erase(id);
		return true;
	}
	return false;
}

bool Registry::Exists(InterfaceID id)
{
	auto exists = mCreationMap.find(id);
	return exists != mCreationMap.end();
}

bool Registry::Create(InterfaceID id, void** outIface)
{
	if (outIface)
	{
		auto creator = mCreationMap.find(id);
		if (creator != mCreationMap.end())
		{
			*outIface = (*creator->second)();
			return *outIface != nullptr;
		}
	}
	return false;
}
