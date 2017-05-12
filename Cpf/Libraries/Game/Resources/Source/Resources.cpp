//////////////////////////////////////////////////////////////////////////
#include "Resources/Resources.hpp"
#include "Resources/ResourceConfig.hpp"
#include "Resources/Volumes/FileSystem.hpp"
#include "Resources/Caches/Default.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Resources;

namespace
{
	uint32_t s_RefCount = 0;
}

extern "C" void CPF_EXPORT InstallResources(Plugin::iRegistry* registry);
extern "C" void CPF_EXPORT RemoveResources(Plugin::iRegistry* registry);


int ResourcesInitializer::Install(Plugin::iRegistry* registry)
{
	if (s_RefCount++ == 0)
	{
		InstallResources(registry);

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
	return s_RefCount;
}

int ResourcesInitializer::Remove(Plugin::iRegistry* registry)
{
	if (--s_RefCount == 0)
	{
		RemoveResources(registry);
	}
	return 0;
}
