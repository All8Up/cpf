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

	// iBase overrides.
	int32_t CPF_STDCALL AddRef() override;
	int32_t CPF_STDCALL Release() override;
	GOM::Result CPF_STDCALL Cast(GOM::InterfaceID id, void**) override;

	// iRegistry overrides.
	GOM::Result CPF_STDCALL Load(const char* const) override;

	GOM::Result CPF_STDCALL Create(GOM::iBase*, GOM::ClassID, GOM::InterfaceID, void**) override;

	GOM::Result CPF_STDCALL Install(GOM::ClassID, Plugin::iClassInstance*) override;
	GOM::Result CPF_STDCALL Remove(GOM::ClassID) override;
	GOM::Result CPF_STDCALL Exists(GOM::ClassID id) override;

	GOM::Result CPF_STDCALL ClassInstall(int32_t count, const Plugin::IID_CID* pairs) override;
	GOM::Result CPF_STDCALL ClassRemove(int32_t count, const Plugin::IID_CID* pairs) override;
	GOM::Result CPF_STDCALL GetClasses(GOM::InterfaceID id, int32_t* count, GOM::ClassID*) override;

	GOM::Result CPF_STDCALL InstanceInstall(GOM::InterfaceID id, void*) override;
	GOM::Result CPF_STDCALL InstanceRemove(GOM::InterfaceID id) override;
	GOM::Result CPF_STDCALL GetInstances(GOM::InterfaceID id, void**) override;

private:
	int32_t mRefCount;

	using LibraryMap = Cpf::UnorderedMap<String, Plugin::Library>;
	using CreationMap = Cpf::UnorderedMap<GOM::ClassID, IntrusivePtr<Plugin::iClassInstance>>;

	LibraryMap mLibraryMap;
	CreationMap mCreationMap;

	using ClassList = Cpf::Vector<GOM::ClassID>;
	using ClassMap = Cpf::UnorderedMap<GOM::InterfaceID, ClassList>;
	ClassMap mClasses;

	using InstanceMap = Cpf::UnorderedMap<GOM::InterfaceID, void*>;
	InstanceMap mInstances;
};

//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL PluginHost::CreateRegistry(Plugin::iRegistry** outRegistry)
{
	if (outRegistry)
	{
		*outRegistry = new Registry;
		if (*outRegistry)
			return GOM::kOK;
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
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

GOM::Result CPF_STDCALL Registry::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;

		case iRegistry::kIID.GetID():
			*outIface = static_cast<iRegistry*>(this);
			break;

		default:
			*outIface = nullptr;
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::Load(const char* const name)
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
						return GOM::kOK;
					}
				}
			}
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::Install(GOM::ClassID id, Plugin::iClassInstance* clsInst)
{
	auto exists = mCreationMap.find(id);
	if (exists == mCreationMap.end())
	{
		mCreationMap.insert(CreationMap::value_type{id, clsInst});
		return GOM::kOK;
	}
	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::Remove(GOM::ClassID id)
{
	auto exists = mCreationMap.find(id);
	if (exists != mCreationMap.end())
	{
		mCreationMap.erase(id);
		return GOM::kOK;
	}
	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::Exists(GOM::ClassID id)
{
	auto exists = mCreationMap.find(id);
	return exists != mCreationMap.end() ? GOM::kOK : GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::Create(GOM::iBase* outer, GOM::ClassID cid, GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		auto creator = mCreationMap.find(cid);
		if (creator != mCreationMap.end())
		{
			GOM::iBase* instance;
			creator->second->CreateInstance(static_cast<Plugin::iRegistry*>(this), outer, &instance);
			if (instance)
			{
				GOM::Result result = instance->Cast(id, outIface);
				instance->Release();
				return result;
			}
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::GetClasses(GOM::InterfaceID id, int32_t* count, GOM::ClassID* outClasses)
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
				return GOM::kOK;
			}
			else
				*count = 0;
			return GOM::kOK;
		}
		else
		{
			if (it != mClasses.end())
				*count = int32_t(it->second.size());
			else
				*count = 0;
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::ClassInstall(int32_t count, const Plugin::IID_CID* pairs)
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
					return GOM::kDuplicateCID;
			}
			cid->second.push_back(pairs[i].mCID);
		}
	}
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Registry::ClassRemove(int32_t count, const Plugin::IID_CID* pairs)
{
	if (pairs)
	{
		for (int i = 0; i < count; ++i)
		{
			auto cid = mClasses.find(pairs[i].mIID);
			if (cid == mClasses.end())
			{
				// What is this about?
				return GOM::kRegistryError;
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
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Registry::InstanceInstall(GOM::InterfaceID id, void* instance)
{
	auto it = mInstances.find(id);
	if (it != mInstances.end())
		return Plugin::kInstanceExists;
	mInstances[id] = instance;
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Registry::InstanceRemove(GOM::InterfaceID id)
{
	auto it = mInstances.find(id);
	if (it != mInstances.end())
	{
		mInstances.erase(it);
		return GOM::kOK;
	}
	return Plugin::kNotInstalled;
}

GOM::Result CPF_STDCALL Registry::GetInstances(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		auto it = mInstances.find(id);
		if (it != mInstances.end())
		{
			*outIface = it->second;
			return GOM::kOK;
		}

		return Plugin::kNotInstalled;
	}
	return GOM::kInvalidParameter;
}
