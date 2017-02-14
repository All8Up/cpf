//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources.hpp"
#include "Locator.hpp"
#include "String.hpp"
#include "Volume.hpp"
#include "Cache.hpp"
#include <rapidjson/document.h>

namespace Cpf
{
	namespace Resources
	{
		class CPF_EXPORT_RESOURCES Configuration
		{
		public:
			Configuration(const String& filename);
			~Configuration();

			Locator* GetLocator() const;

			struct VolumeDescriptor
			{
				Volume::Descriptor* (*CreateDescriptor)(const rapidjson::Value&);
				Volume* (*CreateVolume)(const Volume::Descriptor* const);
			};
			static const VolumeDescriptor* GetVolumeDescriptor(const char* const name);
			static bool InstallVolumeType(const String name, const VolumeDescriptor&);

			struct CacheDescriptor
			{
				Cache::Descriptor* (*CreateDescriptor)(const rapidjson::Value&);
				Cache* (*CreateCache)(const Cache::Descriptor* const);
			};
			static const CacheDescriptor* GetCacheDescriptor(const char* const name);
			static bool InstallCacheType(const String& name, const CacheDescriptor&);

		private:
			Locator* mpLocator;

			struct Reader;
			struct MountReader;
			struct CacheReader;
			struct LoaderReader;

			static UnorderedMap<String, VolumeDescriptor> mVolumeTypes;
			static UnorderedMap<String, CacheDescriptor> mCacheTypes;
		};
	}
}