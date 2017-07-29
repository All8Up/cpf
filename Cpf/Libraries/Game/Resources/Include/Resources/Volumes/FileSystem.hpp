//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/iVolume.hpp"
#include "String.hpp"
#include "UnorderedMap.hpp"
#include "Vector.hpp"


namespace Cpf
{
	namespace Resources
	{
		namespace Volumes
		{
			class FileSystem : public tRefCounted<iVolume>
			{
			public:
				static const char* const kVolumeType;

				struct Descriptor : VolumeDesc
				{
					Descriptor(const char* const root) : mpRoot(root) {}

					const char* const mpRoot;
				};

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				// TODO: Remove.
				static iVolume* Create(const VolumeDesc* const desc);
				static VolumeDesc* CreateDescriptor(const rapidjson::Value&);

				bool CPF_STDCALL Mount(const char* const mountPoint) override;
				void CPF_STDCALL Unmount() override;

				Platform::IO::Stream* Open(ID) override;

			private:
				FileSystem(const String& relRoot);
				virtual ~FileSystem();

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
