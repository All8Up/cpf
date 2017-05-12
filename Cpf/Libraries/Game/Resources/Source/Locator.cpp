//////////////////////////////////////////////////////////////////////////
#include "Resources/Locator.hpp"
#include "Resources/iLoader.hpp"
#include "Resources/iVolume.hpp"
#include "Resources/iCache.hpp"
#include "Resources/iMonitor.hpp"
#include "Resources/ID.hpp"

using namespace Cpf;
using namespace Resources;

COM::Result CPF_STDCALL Locator::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iLocator*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool CPF_STDCALL Locator::Mount(const char* const mp, iVolume* volume)
{
	if (volume->Mount(mp))
	{
		volume->AddRef();
		mVolumes.insert(mVolumes.begin(), { String(mp), volume });
		mEmitter.Emit<Mounted>(mp, volume);
		return true;
	}
	return false;
}

bool CPF_STDCALL Locator::Unmount(iVolume* volume)
{
	for (auto it = mVolumes.begin(), iend=mVolumes.end(); it!=iend; ++it)
	{
		if (it->mpVolume == volume)
		{
			it->mpVolume->Unmount();
			it->mpVolume->Release();
			String mp = it->mMountPoint;
			mVolumes.erase(it);
			mEmitter.Emit<Unmounted>(mp.c_str(), volume);
			return true;
		}
	}
	return false;
}

bool CPF_STDCALL Locator::Attach(const char* const name, iCache* cache)
{
	if (cache != nullptr)
	{
		cache->AddRef();
		mCaches[name] = cache;
		return true;
	}
	return false;
}

bool CPF_STDCALL Locator::Detach(const char* const name)
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

iCache* CPF_STDCALL Locator::GetCache(const char* const name) const
{
	auto it = mCaches.find(name);
	if (it != mCaches.end())
		return it->second;
	return nullptr;
}

bool CPF_STDCALL Locator::Attach(iMonitor* monitor)
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

bool CPF_STDCALL Locator::Detach(iMonitor* monitor)
{
	if (mMonitors.find(monitor) != mMonitors.end())
	{
		mMonitors.erase(monitor);
		monitor->SetLocator(nullptr);
		return true;
	}
	return false;
}

bool CPF_STDCALL Locator::Install(iLoader* loader, iCache* cache)
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

bool CPF_STDCALL Locator::Remove(iLoader* loader)
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

const LoaderInfo* CPF_STDCALL Locator::GetLoader(uint32_t id) const
{
	auto it = mLoaders.find(id);
	if (it != mLoaders.end())
		return &it->second;
	return nullptr;
}

Platform::IO::Stream* CPF_STDCALL Locator::Open(ID id) const
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

ResourceBase* CPF_STDCALL Locator::GetResource(ID id) const
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

bool CPF_STDCALL Locator::Touch(ID id)
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

void CPF_STDCALL Locator::TouchAll()
{
	for (auto it : mCaches)
	{
		it.second->Enumerate([](ResourceBase* res) {
			res->Update();
		});
	}
}

Locator::Locator(iUnknown*)
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
