//////////////////////////////////////////////////////////////////////////
#include "Resources/ResourceConfig.hpp"
#include "IO/File.hpp"
#include "rapidjson/document.h"
#include "CPF/Logging.hpp"
#include "IO/Directory.hpp"
#include "jsoncons/json.hpp"
#include "Resources/Locator.hpp"
#include "CPF/Plugin/iRegistry.hpp"

using namespace CPF;
using namespace Resources;
using namespace IO;

namespace
{
	const char* const kMountArray = "Mounts";
	const char* const kCacheArray = "Caches";
	const char* const kLoaderArray = "Loaders";

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
	static bool Parse(const rapidjson::Value& value, iLocator* loc)
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

						VolumeDesc* desc = nullptr;
						if (it.HasMember(kDescriptor) && volumeInfo->CreateDescriptor)
							desc = volumeInfo->CreateDescriptor(it[kDescriptor]);

						iVolume* volume = volumeInfo->CreateVolume(desc);
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
	static bool Parse(const rapidjson::Value& value, iLocator* loc)
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

						CacheDesc* desc = nullptr;
						if (it.HasMember(kDescriptor) && cacheDesc->CreateDescriptor)
							desc = cacheDesc->CreateDescriptor(it[kDescriptor]);

						iCache* cache = cacheDesc->CreateCache(desc);
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
	static bool Parse(const rapidjson::Value& value, iLocator* loc)
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
	static bool Parse(const rapidjson::Document& doc, iLocator* loc)
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


Configuration::Configuration(Plugin::iRegistry* regy, const String& filename)
	: mpLocator(nullptr)
{
	CPF_INIT_LOG(ResourceConfig);
	CPF_LOG_LEVEL(ResourceConfig, Info);

	if (GOM::Failed(regy->Create(nullptr, kLocatorCID.GetID(), iLocator::kIID.GetID(), reinterpret_cast<void**>(&mpLocator))))
		return;

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

Configuration::Configuration(Plugin::iRegistry*, iUnknown*)
	: mpLocator(nullptr)
{
	CPF_INIT_LOG(ResourceConfig);
	CPF_LOG_LEVEL(ResourceConfig, Info);
}

GOM::Result CPF_STDCALL Configuration::Initialize(Plugin::iRegistry* regy, const char* filename)
{
	if (GOM::Failed(regy->Create(nullptr, kLocatorCID.GetID(), iLocator::kIID.GetID(), reinterpret_cast<void**>(&mpLocator))))
		return GOM::kError;

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
			return GOM::kOK;
		}
	}
	else
	{
		CPF_LOG(ResourceConfig, Error) << "Failed to find resource configuration file.";
		CPF_LOG(ResourceConfig, Info) << "- Current working directory: " << Directory::GetWorkingDirectory();
	}

	/* New stuff to test out jsoncons.
	if (filename)
	{
		GOM::Result result;
		if (Failed(result = regy->Create(nullptr, kLocatorCID, iLocator::kIID, reinterpret_cast<void**>(&mpLocator))))
			return result;

		if (File::Exists(filename))
		{
			mpLocator->AddRef();

			Error fileError;
			Stream* file = File::Create(filename, Stream::Access::eRead, &fileError);
			if (fileError == Error::eNone)
			{
				int64_t jsonLength = file->GetLength(&fileError);
				if (fileError == Error::eNone)
				{
					std::string jsonData;
					jsonData.resize(jsonLength);
					if (file->Read(&jsonData[0], jsonLength, &fileError) == jsonLength)
					{
						auto inputJson = jsoncons::json::parse(jsonData);

						//
						if (inputJson.has_key(kMountArray))
						{
							auto mounts = inputJson[kMountArray];
							if (mounts.is_array())
							{
								for (auto mount : mounts.array_range())
								{
									auto volumeType = mount.get(kVolumeType);
									if (!volumeType.is_null())
									{
										auto mountPoint = mount.get(kMountPoint);
										if (!mountPoint.is_null())
										{
											auto descriptor = mount.get(kDescriptor);
											if (descriptor.is_object())
											{
												CPF_LOG(ResourceConfig, Info) << "Type: " << volumeType << " Mount: " << mountPoint << " Desc: " << descriptor;
												const auto vd = GetVolumeDescriptor(volumeType.as_string().c_str());
												if (vd)
												{
#if 0
													auto desc = vd->CreateDescriptor(descriptor.as_string().c_str());

													Volume* volume = volumeInfo->CreateVolume(desc);
													if (volume)
													{
														if (!loc->Mount(it[kMountPoint].GetString(), volume))
															return false;
														volume->Release();
													}
													if (desc)
														delete desc;
#endif
												}
											}
										}
									}
								}
							}
						}
						auto caches = inputJson.find(kCacheArray);
						if (caches != inputJson.object_range().end())
						{
							
						}
						auto loaders = inputJson.find(kLoaderArray);
						if (loaders != inputJson.object_range().end())
						{
							
						}
						file->Release();
						return GOM::kOK;
					}
				}
			}
		}
	}
	*/
	return GOM::kInvalidParameter;
}


Configuration::~Configuration()
{
	if (mpLocator)
		mpLocator->Release();
}

GOM::Result CPF_STDCALL Configuration::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case iConfiguration::kIID.GetID():
			*outIface = static_cast<iConfiguration*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

iLocator* Configuration::GetLocator()
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
