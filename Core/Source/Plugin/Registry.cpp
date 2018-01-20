//////////////////////////////////////////////////////////////////////////
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Plugin/Registry.hpp"
#include "CPF/Plugin/Library.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Plugin/iClassFactory.hpp"
#include "CPF/Std/Move.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/UnorderedMap.hpp"
#include "CPF/IO/Directory.hpp"
#include "CPF/Logging.hpp"
#include "CPF/IO/Path.hpp"

using namespace CPF;
using namespace PluginHost;

#ifdef CPF_CSHARP
extern "C"
bool CPF_IMPORT_ATTR CPF_STDCALL LoadCSharpPlugin(Plugin::iRegistry*, const char*);
#endif

class Registry : public Plugin::iRegistry
{
public:
	//
	Registry();
	virtual ~Registry();

	// iBase overrides.
	int32_t CPF_STDCALL AddRef() override;
	int32_t CPF_STDCALL Release() override;
	GOM::Result CPF_STDCALL QueryInterface(GOM::IID id, void**) override;

	// iRegistry overrides.
	GOM::Result CPF_STDCALL Load(const char*) override;
	GOM::Result CPF_STDCALL Unload(const char* library) override;

	GOM::Result CPF_STDCALL Create(iUnknown*, GOM::CID, GOM::IID, void**) override;

	GOM::Result CPF_STDCALL Install(GOM::CID, Plugin::iClassFactory*) override;
	GOM::Result CPF_STDCALL Remove(GOM::CID) override;
	GOM::Result CPF_STDCALL GetClassInstance(GOM::CID cid, Plugin::iClassFactory** clsInst) override;
	GOM::Result CPF_STDCALL Exists(GOM::CID cid) override;

	GOM::Result CPF_STDCALL ClassInstall(int32_t count, const Plugin::IID_CID* pairs) override;
	GOM::Result CPF_STDCALL ClassRemove(int32_t count, const Plugin::IID_CID* pairs) override;
	GOM::Result CPF_STDCALL GetClasses(GOM::IID id, int32_t* count, GOM::CID*) override;

	GOM::Result CPF_STDCALL InstanceInstall(GOM::IID id, iUnknown*) override;
	GOM::Result CPF_STDCALL InstanceRemove(GOM::IID id) override;
	GOM::Result CPF_STDCALL GetInstance(GOM::IID id, iUnknown**) override;

private:
	int32_t mRefCount;

	struct LibraryDesc
	{
		Plugin::Library Library;
		PluginDesc Desc;
	};

	using LibraryMap = UnorderedMap<String, LibraryDesc>;
	using CreationMap = UnorderedMap<GOM::CID, IntrusivePtr<Plugin::iClassFactory>>;

	LibraryMap mLibraryMap;
	CreationMap mCreationMap;

	using ClassList = Vector<GOM::CID>;
	using ClassMap = UnorderedMap<GOM::IID, ClassList>;
	ClassMap mClasses;

	using InstanceMap = UnorderedMap<GOM::IID, iUnknown*>;
	InstanceMap mInstances;
};

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT GOM::Result CPF_STDCALL PluginHost::CreateRegistry(Plugin::iRegistry** outRegistry)
{
	if (outRegistry)
	{
		*outRegistry = new Registry;
		if (*outRegistry)
		{
			return GOM::kOK;
		}
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

GOM::Result CPF_STDCALL Registry::QueryInterface(GOM::IID id, void** outIface)
{
	if (outIface)
	{
		switch (uint64_t(id))
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		case kIID.GetID():
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
#ifdef CPF_CSHARP
			if (IO::Path::GetExtension(name) == "csp")
			{
				if (LoadCSharpPlugin(this, name))
					return GOM::kOK;
				return GOM::kInvalid;
			}
#endif

			Plugin::Library library;
			if (library.Load(name))
			{
				auto getDesc = library.GetAddress<PluginAPIGetDesc>(kPluginAPIGetDesc);
				if (getDesc)
				{
					const PluginDesc* desc = (*getDesc)();
					if (desc && desc->Install && (*desc->Install)(this) == GOM::kOK)
					{
						// TODO: Need to copy the desc Name if this intends to remain valid after unload.
						mLibraryMap.insert(LibraryMap::value_type{ CPF::String(name), LibraryDesc{ Move(library), *desc } });
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
		auto remove = (exists->second).Desc.Remove;
		if (remove)
		{
			auto result = (*remove)(this);
			if (GOM::Succeeded(result))
			{
				if ((exists->second).Library.Unload())
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

GOM::Result CPF_STDCALL Registry::Install(GOM::CID id, Plugin::iClassFactory* clsInst)
{
	auto exists = mCreationMap.find(id);
	if (exists == mCreationMap.end() && clsInst)
	{
		mCreationMap.insert(CreationMap::value_type{id, clsInst});
		return GOM::kOK;
	}
	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::Remove(GOM::CID id)
{
	auto exists = mCreationMap.find(id);
	if (exists != mCreationMap.end())
	{
		mCreationMap.erase(id);
		return GOM::kOK;
	}
	return GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::GetClassInstance(GOM::CID cid, Plugin::iClassFactory** clsInst)
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

GOM::Result CPF_STDCALL Registry::Exists(GOM::CID id)
{
	auto exists = mCreationMap.find(id);
	return exists != mCreationMap.end() ? GOM::kOK : GOM::kUnknownClass;
}

GOM::Result CPF_STDCALL Registry::Create(iUnknown* outer, GOM::CID cid, GOM::IID id, void** outIface)
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

GOM::Result CPF_STDCALL Registry::GetClasses(GOM::IID id, int32_t* count, GOM::CID* outClasses)
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

GOM::Result CPF_STDCALL Registry::InstanceInstall(GOM::IID id, iUnknown* instance)
{
	auto it = mInstances.find(id);
	if (it != mInstances.end())
		return Plugin::kInstanceExists;
	instance->AddRef();
	mInstances[id] = instance;
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Registry::InstanceRemove(GOM::IID id)
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

GOM::Result CPF_STDCALL Registry::GetInstance(GOM::IID id, iUnknown** outIface)
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
