//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources.hpp"
#include "Resources/iConfiguration.hpp"
#include "Resources/iCache.hpp"
#include "Resources/iLocator.hpp"
#include "String.hpp"
#include "Resources/iVolume.hpp"
#include <rapidjson/document.h>

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}
}

namespace CPF
{
	namespace Resources
	{
		class Configuration : public tRefCounted<iConfiguration>
		{
		public:
			Configuration(iUnknown*);
			Configuration(Plugin::iRegistry* regy, const String& filename);
			~Configuration();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;
			GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* regy, const char* filename) override;
			iLocator* CPF_STDCALL GetLocator() override;

			struct VolumeDescriptor
			{
				VolumeDesc* (*CreateDescriptor)(const rapidjson::Value&);
				iVolume* (*CreateVolume)(const VolumeDesc* const);
			};
			static const VolumeDescriptor* GetVolumeDescriptor(const char* const name);
			static bool InstallVolumeType(const String name, const VolumeDescriptor&);

			struct CacheDescriptor
			{
				CacheDesc* (*CreateDescriptor)(const rapidjson::Value&);
				iCache* (*CreateCache)(const CacheDesc* const);
			};
			static const CacheDescriptor* GetCacheDescriptor(const char* const name);
			static bool InstallCacheType(const String& name, const CacheDescriptor&);

		private:
			iLocator* mpLocator;

			struct Reader;
			struct MountReader;
			struct CacheReader;
			struct LoaderReader;

			static UnorderedMap<String, VolumeDescriptor> mVolumeTypes;
			static UnorderedMap<String, CacheDescriptor> mCacheTypes;
		};
	}
}
