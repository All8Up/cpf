//////////////////////////////////////////////////////////////////////////
#include "PluginHost/Registry.hpp"
#include "Plugin/Library.hpp"
#include "Plugin.hpp"
#include "CPF/Plugin/iClassInstance.hpp"
#include "Move.hpp"
#include "Vector.hpp"
#include "UnorderedMap.hpp"
#include "IO/Directory.hpp"
#include "CPF/Logging.hpp"

using namespace CPF;
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
	GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void**) override;

	// iRegistry overrides.
	GOM::Result CPF_STDCALL Load(const char*) override;
	GOM::Result CPF_STDCALL Unload(const char* library) override;

	GOM::Result CPF_STDCALL Create(iUnknown*, uint64_t, uint64_t, void**) override;

	GOM::Result CPF_STDCALL Install(uint64_t, Plugin::iClassInstance*) override;
	GOM::Result CPF_STDCALL Remove(uint64_t) override;
	GOM::Result CPF_STDCALL GetClassInstance(uint64_t cid, Plugin::iClassInstance** clsInst) override;
	GOM::Result CPF_STDCALL Exists(uint64_t id) override;

	GOM::Result CPF_STDCALL ClassInstall(int32_t count, const Plugin::IID_CID* pairs) override;
	GOM::Result CPF_STDCALL ClassRemove(int32_t count, const Plugin::IID_CID* pairs) override;
	GOM::Result CPF_STDCALL GetClasses(uint64_t id, int32_t* count, uint64_t*) override;

	GOM::Result CPF_STDCALL InstanceInstall(uint64_t id, iUnknown*) override;
	GOM::Result CPF_STDCALL InstanceRemove(uint64_t id) override;
	GOM::Result CPF_STDCALL GetInstance(uint64_t id, iUnknown**) override;

private:
	int32_t mRefCount;

	using LibraryMap = UnorderedMap<String, Plugin::Library>;
	using CreationMap = UnorderedMap<uint64_t, IntrusivePtr<Plugin::iClassInstance>>;

	LibraryMap mLibraryMap;
	CreationMap mCreationMap;

	using ClassList = Vector<uint64_t>;
	using ClassMap = UnorderedMap<uint64_t, ClassList>;
	ClassMap mClasses;

	using InstanceMap = UnorderedMap<uint64_t, iUnknown*>;
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

GOM::Result CPF_STDCALL Registry::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
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

GOM::Result CPF_STDCALL Registry::Load(const char* name)
{
	if (name)
	{
		auto exists = mLibraryMap.find(name);
		if (exists == mLibraryMap.end())
		{
			Plugin::Library library;
			if (library.Load(name))
			{
				auto install = library.GetAddress<PluginAPIInstall>(kPluginAPIInstall);
				if (install)
				{
					if ((*install)(this) == GOM::kOK)
					{
						mLibraryMap.insert(LibraryMap::value_type{ CPF::String(name), Move(library) });
						return GOM::kOK;
					}
				}
			}
			CPF_LOG(PluginHost, Error) << "Failed to load: " << name << " Working dir:" << IO::Directory::GetWorkingDirectory();
			return GOM::kNotFound;
		}
		return GOM::kAlreadyLoaded;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::Unload(const char* name)
{
	if (name)
	{
		auto exists = mLibraryMap.find(name);
		if (exists == mLibraryMap.end())
			return Plugin::kNotLoaded;
		auto unload = (exists->second).GetAddress<PluginAPIRemove>(kPluginAPIRemove);
		if (unload)
		{
			auto result = (*unload)(this);
			if (GOM::Succeeded(result))
			{
				if ((exists->second).Unload())
				{
					mLibraryMap.erase(exists);
					return GOM::kOK;
				}
				return Plugin::kCantUnload;
			}
			return result;
		}
		return Plugin::kExportMissing;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::Install(uint64_t id, Plugin::iClassInstance* clsInst)
{
	auto exists = mCreationMap.find(id);
	if (exists == mCreationMap.end() && clsInst)
	{
		mCreationMap.insert(CreationMap::value_type{id, clsInst});
		return GOM::kOK;
	}
	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::Remove(uint64_t id)
{
	auto exists = mCreationMap.find(id);
	if (exists != mCreationMap.end())
	{
		mCreationMap.erase(id);
		return GOM::kOK;
	}
	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::GetClassInstance(uint64_t cid, Plugin::iClassInstance** clsInst)
{
	if (clsInst)
	{
		auto it = mCreationMap.find(cid);
		if (it!=mCreationMap.end())
		{
			*clsInst = it->second;
			(*clsInst)->AddRef();
			return GOM::kOK;
		}
		return GOM::kUnknownClass;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::Exists(uint64_t id)
{
	auto exists = mCreationMap.find(id);
	return exists != mCreationMap.end() ? GOM::kOK : GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::Create(iUnknown* outer, uint64_t cid, uint64_t id, void** outIface)
{
	if (outIface)
	{
		auto creator = mCreationMap.find(cid);
		if (creator != mCreationMap.end())
		{
			iUnknown* instance;
			if (GOM::Succeeded(creator->second->CreateInstance(static_cast<iRegistry*>(this), outer, &instance)))
			{
				if (instance)
				{
					GOM::Result result = instance->QueryInterface(id, outIface);
					if (instance)
						instance->Release();
					return result;
				}
				// There is an error in the plugin.
				return GOM::kInvalid;
			}
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Registry::GetClasses(uint64_t id, int32_t* count, uint64_t* outClasses)
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
			*count = 0;
			return GOM::kOK;
		}
		if (it != mClasses.end())
			*count = int32_t(it->second.size());
		else
			*count = 0;
		return GOM::kOK;
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

GOM::Result CPF_STDCALL Registry::InstanceInstall(uint64_t id, iUnknown* instance)
{
	auto it = mInstances.find(id);
	if (it != mInstances.end())
		return Plugin::kInstanceExists;
	instance->AddRef();
	mInstances[id] = instance;
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Registry::InstanceRemove(uint64_t id)
{
	auto it = mInstances.find(id);
	if (it != mInstances.end())
	{
		it->second->Release();
		mInstances.erase(it);
		return GOM::kOK;
	}
	return Plugin::kNotInstalled;
}

GOM::Result CPF_STDCALL Registry::GetInstance(uint64_t id, iUnknown** outIface)
{
	if (outIface)
	{
		auto it = mInstances.find(id);
		if (it != mInstances.end())
		{
			*outIface = it->second;
			(*outIface)->AddRef();
			return GOM::kOK;
		}

		return Plugin::kNotInstalled;
	}
	return GOM::kInvalidParameter;
}
