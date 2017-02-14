//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Volume.hpp"
#include "String.hpp"
#include "UnorderedMap.hpp"
#include "Vector.hpp"


namespace Cpf
{
	namespace Resources
	{
		namespace Volumes
		{
			class FileSystem : public tRefCounted<Volume>
			{
			public:
				static const char* const kVolumeName;

				struct Descriptor : public Volume::Descriptor
				{
					Descriptor(const char* const root) : mpRoot(root) {}

					const char* const mpRoot;
				};

				CPF_EXPORT_RESOURCES static Volume* Create(const Volume::Descriptor* const desc);
				CPF_EXPORT_RESOURCES static Volume::Descriptor* CreateDescriptor(const rapidjson::Value&);

				bool Mount(const char* const mountPoint) override;
				void Unmount() override;

				Platform::IO::Stream* Open(ID) override;

			private:
				FileSystem(const String& relRoot);
				~FileSystem() override;

				using EntryMap = UnorderedMap<uint32_t, String>;
				struct DirectoryMap
				{
					String mDirectory;
					EntryMap mEntries;
				};
				using DirMap = UnorderedMap<uint32_t, DirectoryMap>;

				String mRoot;
				Vector<String> mMountPoint;
				DirMap mContent;
			};
		}
	}
}
