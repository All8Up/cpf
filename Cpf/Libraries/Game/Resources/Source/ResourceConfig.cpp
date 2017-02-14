//////////////////////////////////////////////////////////////////////////
#include "Resources/ResourceConfig.hpp"
#include "IO/File.hpp"
#include "rapidjson/document.h"
#include "Logging/Logging.hpp"
#include "IO/Directory.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Platform;
using namespace IO;

namespace
{
	const char* const kVolumeType = "VolumeType";
	const char* const kMountPoint = "MountPoint";
	const char* const kDescriptor = "Descriptor";

	const char* const kCacheType = "CacheType";
	const char* const kName = "Name";
}

UnorderedMap<String, Configuration::VolumeDescriptor> Configuration::mVolumeTypes;
UnorderedMap<String, Configuration::CacheDescriptor> Configuration::mCacheTypes;


struct Configuration::MountReader
{
	static bool Parse(const rapidjson::Value& value, Locator* loc)
	{
		if (value.IsArray())
		{
			auto entries = value.GetArray();
			for (const auto& it : entries)
			{
				if (it.IsObject())
				{
					if (it.HasMember(kVolumeType) && it[kVolumeType].IsString() &&
						it.HasMember(kMountPoint) && it[kMountPoint].IsString())
					{
						//
						auto volumeInfo = GetVolumeDescriptor(it[kVolumeType].GetString());
						if (volumeInfo == nullptr)
							return false;

						Volume::Descriptor* desc = nullptr;
						if (it.HasMember(kDescriptor) && volumeInfo->CreateDescriptor)
							desc = volumeInfo->CreateDescriptor(it[kDescriptor]);

						Volume* volume = volumeInfo->CreateVolume(desc);
						if (volume)
						{
							if (!loc->Mount(it[kMountPoint].GetString(), volume))
								return false;
							volume->Release();
						}
						if (desc)
							delete desc;
					}
				}
				else
					return false;
			}

			return true;
		}
		return false;
	}
};

struct Configuration::CacheReader
{
	static bool Parse(const rapidjson::Value& value, Locator* loc)
	{
		if (value.IsArray())
		{
			auto entries = value.GetArray();
			for (const auto& it : entries)
			{
				if (it.IsObject())
				{
					if (it.HasMember(kCacheType) && it[kCacheType].IsString() &&
						it.HasMember(kName) && it[kName].IsString())
					{
						const CacheDescriptor* cacheDesc = GetCacheDescriptor(it[kCacheType].GetString());
						if (cacheDesc == nullptr)
							return false;

						Cache::Descriptor* desc = nullptr;
						if (it.HasMember(kDescriptor) && cacheDesc->CreateDescriptor)
							desc = cacheDesc->CreateDescriptor(it[kDescriptor]);

						Cache* cache = cacheDesc->CreateCache(desc);
						if (cache)
						{
							if (!loc->Attach(it[kName].GetString(), cache))
								return false;
							cache->Release();
						}
						if (desc)
							delete desc;
					}
					else
						return false;
				}
			}
			return true;
		}
		return false;
	}
};

struct Configuration::LoaderReader
{
	static bool Parse(const rapidjson::Value& value, Locator* loc)
	{
		(void)loc;
		if (value.IsArray())
		{
			return true;
		}
		return false;
	}
};


struct Configuration::Reader
{
	static bool Parse(const rapidjson::Document& doc, Locator* loc)
	{
		if (doc.IsObject())
		{
			for (auto it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
			{
				const char* name = it->name.GetString();
				if (strcmp(name, "Mounts") == 0)
				{
					if (!MountReader::Parse(it->value, loc))
						return false;
				}
				else if (strcmp(name, "Caches") == 0)
				{
					if (!CacheReader::Parse(it->value, loc))
						return false;
				}
				else if (strcmp(name, "Loaders") == 0)
				{
					if (!LoaderReader::Parse(it->value, loc))
						return false;
				}
				else
					return false;
			}
			return true;
		}
		return false;
	}
};


Configuration::Configuration(const String& filename)
	: mpLocator(nullptr)
{
	CPF_INIT_LOG(ResourceConfig);
	CPF_LOG_LEVEL(ResourceConfig, Info);

	mpLocator = Locator::Create();

	if (mpLocator && File::Exists(filename))
	{
		mpLocator->AddRef();

		Error fileError;
		Stream* file = File::Create(filename, Stream::Access::eRead, &fileError);
		if (fileError == Error::eNone)
		{
			int64_t jsonLength = file->GetLength(&fileError);
			if (fileError == Error::eNone)
			{
				char* jsonData = new char[jsonLength + 1];
				if (jsonData && file->Read(jsonData, jsonLength, &fileError) == jsonLength)
				{
					jsonData[jsonLength] = 0;
					rapidjson::Document configDocument;
					configDocument.Parse(jsonData);
					if (!configDocument.HasParseError() && Reader::Parse(configDocument, mpLocator))
					{
					}

					delete[] jsonData;
				}
			}
			file->Release();
		}
	}
	else
	{
		CPF_LOG(ResourceConfig, Error) << "Failed to find resource configuration file.";
		CPF_LOG(ResourceConfig, Info) << "- Current working directory: " << Directory::GetWorkingDirectory();
	}
}

Configuration::~Configuration()
{
	if (mpLocator)
		mpLocator->Release();
}

Locator* Configuration::GetLocator() const
{
	return mpLocator;
}

const Configuration::VolumeDescriptor* Configuration::GetVolumeDescriptor(const char* const name)
{
	auto it = mVolumeTypes.find(name);
	if (it != mVolumeTypes.end())
		return &it->second;
	return nullptr;
}

bool Configuration::InstallVolumeType(const String name, const VolumeDescriptor& desc)
{
	if (mVolumeTypes.find(name)==mVolumeTypes.end())
	{
		mVolumeTypes[name] = desc;
		return true;
	}

	return false;
}

const Configuration::CacheDescriptor* Configuration::GetCacheDescriptor(const char* const name)
{
	auto it = mCacheTypes.find(name);
	if (it != mCacheTypes.end())
		return &it->second;
	return nullptr;
}

bool Configuration::InstallCacheType(const String& name, const CacheDescriptor& desc)
{
	if (mCacheTypes.find(name) == mCacheTypes.end())
	{
		mCacheTypes[name] = desc;
		return true;
	}
	return false;
}
