#include "Plugin/iRegistry.hpp"
#include "Plugin/tClassInstance.hpp"
#include "CPF/Logging.hpp"

#include "Resources/ResourceConfig.hpp"
#include "Resources/Locator.hpp"
#include "Resources/Monitors/FileSystem.hpp"
#include "Resources/Monitors/Manual.hpp"
#include "Resources/Caches/Default.hpp"
#include "Resources/Volumes/FileSystem.hpp"
#include "Resources/ResourceConfig.hpp"

using namespace CPF;
using namespace Resources;

extern "C" void CPF_EXPORT InstallResources(Plugin::iRegistry* registry)
{
	CPF_INIT_LOG(Resources);
	CPF_LOG_LEVEL(Resources, Warn);
	IOInitializer::Install();

	registry->Install(Caches::kCacheDefaultCID.GetID(), new Plugin::tClassInstance<Caches::Default>());
	registry->Install(kLocatorCID.GetID(), new Plugin::tClassInstance<Locator>());
	registry->Install(kMonitorFileSystemCID.GetID(), new Plugin::tClassInstance<Monitors::FileSystem>());
	registry->Install(kMonitorManualCID.GetID(), new Plugin::tClassInstance<Monitors::Manual>());
	registry->Install(kConfigurationCID.GetID(), new Plugin::tClassInstance<Configuration>());

	Configuration::VolumeDescriptor fileSystemDesc
	{
		&Volumes::FileSystem::CreateDescriptor,
		&Volumes::FileSystem::Create
	};
	Configuration::InstallVolumeType(Volumes::FileSystem::kVolumeType, fileSystemDesc);

	Configuration::CacheDescriptor defaultCacheDesc
	{
		&Caches::Default::CreateDescriptor,
		&Caches::Default::Create
	};
	Configuration::InstallCacheType(Caches::Default::kCacheName, defaultCacheDesc);
}

extern "C" void CPF_EXPORT RemoveResources(Plugin::iRegistry* registry)
{
	registry->Remove(kConfigurationCID.GetID());
	registry->Remove(kMonitorManualCID.GetID());
	registry->Remove(kMonitorFileSystemCID.GetID());
	registry->Remove(kLocatorCID.GetID());
	registry->Remove(Caches::kCacheDefaultCID.GetID());

	IOInitializer::Remove();
	CPF_DROP_LOG(Resources);
}

//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		InstallResources(registry);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		RemoveResources(registry);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
