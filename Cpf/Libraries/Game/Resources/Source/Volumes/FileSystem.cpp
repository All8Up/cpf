//////////////////////////////////////////////////////////////////////////
#include "Resources/Volumes/FileSystem.hpp"
#include "Logging/Logging.hpp"
#include "Resources/ID.hpp"
#include "IO/Directory.hpp"
#include "IO/Path.hpp"
#include "IO/File.hpp"
#include "Hash/Crc.hpp"

using namespace Cpf;
using namespace IO;

using namespace Resources;
using namespace Volumes;

namespace
{
	const char* const kDirectory = "Directory";
}

const char* const FileSystem::kVolumeType = "FileSystem";


GOM::Result CPF_STDCALL FileSystem::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case iVolume::kIID.GetID():
			*outIface = static_cast<iVolume*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

//////////////////////////////////////////////////////////////////////////

iVolume* FileSystem::Create(const VolumeDesc* const desc)
{
	const Descriptor* const fsDesc = static_cast<const Descriptor* const>(desc);
	return new FileSystem(fsDesc->mpRoot);
}

VolumeDesc* FileSystem::CreateDescriptor(const rapidjson::Value& value)
{
	if (value.IsObject())
	{
		const auto& obj = value.GetObject();
		if (obj.HasMember(kDirectory) && obj[kDirectory].IsString())
		{
			Descriptor* result = new Descriptor(obj[kDirectory].GetString());
			return result;
		}
	}
	return nullptr;
}

bool FileSystem::Mount(const char* const mp)
{
	mMountPoint = Path::Components(mp);
	if (Directory::Exists(mRoot))
	{
		Vector<String> dirs = { "" };

		while (!dirs.empty())
		{
			auto realSubDir = dirs.back();
			dirs.pop_back();

			auto subPath = Path::Combine(mMountPoint);
			subPath = Path::EnsureTrailingSeparator(Path::Combine(subPath, realSubDir));

			// TODO: Add logging if anything contains upper case.

			String dir = Path::Normalize(subPath);
			uint32_t dirHash = Hash::Crc32(dir.data(), dir.length());

			auto dirIt = mContent.find(dirHash);
			if (dirIt == mContent.end())
			{
				mContent.insert(DirMap::value_type(dirHash, DirectoryMap{ dir, EntryMap() }));
				dirIt = mContent.find(dirHash);
			}
			CPF_ASSERT(dirIt != mContent.end());

			for (const auto& entry : Directory::Entries(Path::Combine(mRoot, realSubDir), [](const Directory::DirEntry& entry) -> bool {
				if (entry.mName == "." || entry.mName == "..")
					return false;
				return true;
			}))
			{
				if (entry.mAttributes & Directory::Attributes::eDirectory)
				{
					dirs.push_back(entry.mName);
				}
				else
				{
					CPF_LOG(Resources, Trace) << "File scan: adding - " << dir << entry.mName;

					// TODO: Add logging if anything contains upper case.
					String file = entry.mName;
					uint32_t fileHash = Hash::Crc32(file.data(), file.length());
					CPF_ASSERT(dirIt->second.mEntries.find(fileHash) == dirIt->second.mEntries.end());
					dirIt->second.mEntries[fileHash] = file;
				}
			}
		}

		return true;
	}
	return false;
}

void FileSystem::Unmount()
{
	mContent.clear();
}

Stream* FileSystem::Open(ID id)
{
	auto dirIt = mContent.find(id.mDirectory);
	if (dirIt != mContent.end())
	{
		auto fileIt = dirIt->second.mEntries.find(id.mFile);
		if (fileIt != dirIt->second.mEntries.end())
		{
			auto realDir = Path::Components(dirIt->second.mDirectory);
			realDir.erase(realDir.begin(), realDir.begin() + mMountPoint.size());
			String openPath = Path::Combine(mRoot, Path::Combine(realDir));
			openPath = Path::Combine(openPath, fileIt->second);
			return File::Create(openPath, StreamAccess::eRead);
		}
	}
	return nullptr;
}

FileSystem::FileSystem(const String& relRoot)
	: tRefCounted<iVolume>()
	, mRoot(relRoot)
{
}

FileSystem::~FileSystem()
{
}
