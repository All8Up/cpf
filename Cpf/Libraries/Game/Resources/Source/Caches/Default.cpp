//////////////////////////////////////////////////////////////////////////
#include "Resources/Caches/Default.hpp"
#include "Resources/Resource.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Caches;

const char* const Default::kCacheName = "Default";


GOM::Result CPF_STDCALL Default::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iCache*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

iCache* Default::Create(const CacheDesc* const)
{
	return new Default(nullptr);
}

CacheDesc* Default::CreateDescriptor(const rapidjson::Value&)
{
	return nullptr;
}

///
Default::Default(iUnknown*)
	: tRefCounted<iCache>()
	, mShuttingDown(false)
{
	CPF_INIT_LOG(Default_Cache);
	CPF_LOG_LEVEL(Default_Cache, Trace);
	CPF_LOG(Default_Cache, Trace) << "Creating default cache.";
}

Default::~Default()
{
	CPF_LOG(Default_Cache, Trace) << "Destroying default cache.";
	mShuttingDown = true;
	while (!mResources.empty())
	{
		auto refCount = mResources.begin()->second->Release();
		// TODO: Re-enable this when the context does not leak shaders.
//		CPF_ASSERT(refCount == 0);
		if (refCount!=0)
		{
			CPF_LOG(Default_Cache, Warn) << "Leaked shader with ref count = " << refCount;
		}
		mResources.erase(mResources.begin());
	}
	mResources.clear();
	CPF_DROP_LOG(Default_Cache);
}

ResourceBase* Default::Get(ID id) const
{
	auto it = mResources.find(id.mID);
	if (it != mResources.end())
		return it->second;
	return nullptr;
}

void Default::Store(ID id, ResourceBase* resource)
{
	CPF_ASSERT(mResources.find(id.mID) == mResources.end());
	mResources[id.mID] = resource;
	resource->AddRef();
}

void Default::LastReference(ID id)
{
	auto it = mResources.find(id.mID);
	CPF_ASSERT(it != mResources.end());
	it->second->Release();
	// We don't want the normal behavior if we are in the process of shutting down.
	if (!mShuttingDown)
	{
		mResources.erase(it);
	}
}

void Default::Enumerate(Function<void(ResourceBase*)> cb)
{
	for (auto it : mResources)
	{
		cb(it.second);
	}
}
