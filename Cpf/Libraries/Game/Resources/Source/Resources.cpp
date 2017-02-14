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

CPF_EXPORT_RESOURCES int ResourcesInitializer::Install()
{
	if (s_RefCount++ == 0)
	{
		CPF_INIT_LOG(Resources);
		CPF_LOG_LEVEL(Resources, Trace);

		Configuration::VolumeDescriptor fileSystemDesc
		{
			&Volumes::FileSystem::CreateDescriptor,
			&Volumes::FileSystem::Create
		};
		Configuration::InstallVolumeType(Volumes::FileSystem::kVolumeName, fileSystemDesc);

		Configuration::CacheDescriptor defaultCacheDesc
		{
			&Caches::Default::CreateDescriptor,
			&Caches::Default::Create
		};
		Configuration::InstallCacheType(Caches::Default::kCacheName, defaultCacheDesc);
	}
	return s_RefCount;
}

CPF_EXPORT_RESOURCES int ResourcesInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		CPF_DROP_LOG(Resources);
	}
	return 0;
}
