//////////////////////////////////////////////////////////////////////////
#include "PluginHost/Registry.hpp"
#include "Plugin.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Move.hpp"
#include "Vector.hpp"
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

	COM::Result CPF_STDCALL FactoryInstall(int32_t count, const Plugin::IID_CID* pairs) override;
	COM::Result CPF_STDCALL FactoryRemove(int32_t count, const Plugin::IID_CID* pairs) override;

	COM::Result CPF_STDCALL GetClasses(COM::InterfaceID id, int32_t* count, COM::ClassID*) override;

private:
	int32_t mRefCount;

	using LibraryMap = Cpf::UnorderedMap<String, Plugin::Library>;
	using CreationMap = Cpf::UnorderedMap<COM::ClassID, IntrusivePtr<Plugin::iClassInstance>>;

	LibraryMap mLibraryMap;
	CreationMap mCreationMap;

	using ClassList = Cpf::Vector<COM::ClassID>;
	using ClassMap = Cpf::UnorderedMap<COM::InterfaceID, ClassList>;
	ClassMap mClasses;
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

COM::Result CPF_STDCALL Registry::GetClasses(COM::InterfaceID id, int32_t* count, COM::ClassID* outClasses)
{
	if (count)
	{
		auto it = mClasses.find(id);
		if (outClasses)
		{
			if (it != mClasses.end())
			{
				*count = int32_t(it->second.size());
				int32_t idx = 0;
				for (const auto& iid : it->second)
					outClasses[idx++] = iid;
				return COM::kOK;
			}
			else
				*count = 0;
			return COM::kOK;
		}
		else
		{
			if (it != mClasses.end())
				*count = int32_t(it->second.size());
			else
				*count = 0;
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Registry::FactoryInstall(int32_t count, const Plugin::IID_CID* pairs)
{
	if (pairs)
	{
		for (int i = 0; i < count; ++i)
		{
			auto cid = mClasses.find(pairs[i].mIID);
			if (cid == mClasses.end())
			{
				mClasses[pairs[i].mIID] = ClassList();
				cid = mClasses.find(pairs[i].mIID);
			}
			for (const auto& it : cid->second)
			{
				if (it == pairs[i].mCID)
					return COM::kDuplicateCID;
			}
			cid->second.push_back(pairs[i].mCID);
		}
	}
	return COM::kOK;
}

COM::Result CPF_STDCALL Registry::FactoryRemove(int32_t count, const Plugin::IID_CID* pairs)
{
	if (pairs)
	{
		for (int i = 0; i < count; ++i)
		{
			auto cid = mClasses.find(pairs[i].mIID);
			if (cid == mClasses.end())
			{
				// What is this about?
				return COM::kRegistryError;
			}
			for (auto ibegin = cid->second.begin(), iend = cid->second.end(); ibegin != iend; ++ibegin)
			{
				if (*ibegin == pairs[i].mCID)
				{
					cid->second.erase(ibegin);
					break;
				}
			}
		}
	}
	return COM::kOK;
}
