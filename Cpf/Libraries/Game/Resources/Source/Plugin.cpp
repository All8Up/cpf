#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Logging/Logging.hpp"

#include "Resources/ResourceConfig.hpp"
#include "Resources/Locator.hpp"
#include "Resources/Monitors/FileSystem.hpp"
#include "Resources/Monitors/Manual.hpp"
#include "Resources/Caches/Default.hpp"
#include "Resources/Volumes/FileSystem.hpp"
#include "Resources/ResourceConfig.hpp"

using namespace Cpf;
using namespace Resources;

extern "C" void CPF_EXPORT InstallResources(Plugin::iRegistry* registry)
{
	CPF_INIT_LOG(Resources);
	CPF_LOG_LEVEL(Resources, Warn);
	Platform::IOInitializer::Install();

	registry->Install(Resources::Caches::kCacheDefaultCID.GetID(), new Plugin::tClassInstance<Resources::Caches::Default>());
	registry->Install(Resources::kLocatorCID.GetID(), new Plugin::tClassInstance<Resources::Locator>());
	registry->Install(Resources::kMonitorFileSystemCID.GetID(), new Plugin::tClassInstance<Resources::Monitors::FileSystem>());
	registry->Install(Resources::kMonitorManualCID.GetID(), new Plugin::tClassInstance<Resources::Monitors::Manual>());
	registry->Install(Resources::kConfigurationCID.GetID(), new Plugin::tClassInstance<Resources::Configuration>());

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
	registry->Remove(Resources::kConfigurationCID.GetID());
	registry->Remove(Resources::kMonitorManualCID.GetID());
	registry->Remove(Resources::kMonitorFileSystemCID.GetID());
	registry->Remove(Resources::kLocatorCID.GetID());
	registry->Remove(Resources::Caches::kCacheDefaultCID.GetID());

	Platform::IOInitializer::Remove();
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
