//////////////////////////////////////////////////////////////////////////
#include "Resources/Locator.hpp"
#include "Resources/Monitor.hpp"
#include "Resources/Loader.hpp"
#include "Resources/Volume.hpp"
#include "Resources/Cache.hpp"
#include "Resources/ID.hpp"

using namespace Cpf;
using namespace Resources;

CPF_EXPORT_RESOURCES Locator* Locator::Create()
{
	return new Locator();
}

bool Locator::Mount(const char* const mp, Volume* volume)
{
	if (volume->Mount(mp))
	{
		volume->AddRef();
		mVolumes.insert(mVolumes.begin(), { String(mp), volume });
		Emit<Mounted>(mp, volume);
		return true;
	}
	return false;
}

bool Locator::Unmount(Volume* volume)
{
	for (auto it = mVolumes.begin(), iend=mVolumes.end(); it!=iend; ++it)
	{
		if (it->mpVolume == volume)
		{
			it->mpVolume->Unmount();
			it->mpVolume->Release();
			String mp = it->mMountPoint;
			mVolumes.erase(it);
			Emit<Unmounted>(mp.c_str(), volume);
			return true;
		}
	}
	return false;
}

bool Locator::Attach(const char* const name, Cache* cache)
{
	if (cache != nullptr)
	{
		cache->AddRef();
		mCaches[name] = cache;
		return true;
	}
	return false;
}

bool Locator::Detach(const char* const name)
{
	if (name != nullptr)
	{
		auto it = mCaches.find(name);
		if (it != mCaches.end())
		{
			it->second->Release();
			mCaches.erase(it);
			return true;
		}
	}
	return false;
}

Cache* Locator::GetCache(const char* const name) const
{
	auto it = mCaches.find(name);
	if (it != mCaches.end())
		return it->second;
	return nullptr;
}

bool Locator::Attach(Monitor* monitor)
{
	if (mMonitors.find(monitor) == mMonitors.end())
	{
		mMonitors.insert(monitor);
		monitor->AddRef();
		monitor->SetLocator(this);
		return true;
	}
	return false;
}

bool Locator::Detach(Monitor* monitor)
{
	if (mMonitors.find(monitor) != mMonitors.end())
	{
		mMonitors.erase(monitor);
		monitor->SetLocator(nullptr);
		return true;
	}
	return false;
}

bool Locator::Install(Loader* loader, Cache* cache)
{
	auto it = mLoaders.find(loader->GetID());
	if (it == mLoaders.end())
	{
		loader->AddRef();
		cache->AddRef();
		LoaderInfo info{ loader, cache };
		mLoaders[loader->GetID()] = info;
		return true;
	}
	return false;
}

bool Locator::Remove(Loader* loader)
{
	auto it = mLoaders.find(loader->GetID());
	if (it != mLoaders.end())
	{
		it->second.mpLoader->Release();
		it->second.mpCache->Release();
		mLoaders.erase(loader->GetID());
		return true;
	}
	return false;
}

const Locator::LoaderInfo* Locator::GetLoader(uint32_t id) const
{
	auto it = mLoaders.find(id);
	if (it != mLoaders.end())
		return &it->second;
	return nullptr;
}

Platform::IO::Stream* Locator::Open(ID id) const
{
	Platform::IO::Stream* result = nullptr;
	for (const auto& volume : mVolumes)
	{
		result = volume.mpVolume->Open(id);
		if (result != nullptr)
			break;
	}
	return result;
}

ResourceBase* Locator::GetResource(ID id) const
{
	ResourceBase* result = nullptr;
	for (auto ibegin = mCaches.begin(), iend = mCaches.end(); ibegin != iend; ++ibegin)
	{
		result = ibegin->second->Get(id);
		if (result != nullptr)
			break;
	}
	return result;
}

bool Locator::Touch(ID id)
{
	for (auto it : mCaches)
	{
		auto res = it.second->Get(id);
		if (res)
		{
			res->Update();
			return true;
		}
	}
	return false;
}

void Locator::TouchAll()
{
	for (auto it : mCaches)
	{
		it.second->Enumerate([](ResourceBase* res) {
			res->Update();
		});
	}
}

Locator::Locator()
	: tRefCounted<iRefCounted>()
	, Emitter()
{}

Locator::~Locator()
{
	// Remove all the loaders.
	for (auto it : mLoaders)
	{
		it.second.mpLoader->Release();
		it.second.mpCache->Release();
	}
	mLoaders.clear();

	// Remove all the monitors.
	for (auto it : mMonitors)
	{
		it->Release();
	}
	mMonitors.clear();

	// Remove all the caches.
	for (auto it : mCaches)
		it.second->Release();
	mCaches.clear();

	// Remove all the volumes.
	while (!mVolumes.empty())
	{
		mVolumes[0].mpVolume->Unmount();
		mVolumes[0].mpVolume->Release();
		mVolumes.erase(mVolumes.begin());
	}
}
