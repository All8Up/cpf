//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO/iFile.hpp"
#include "Threading/Reactor.hpp"
#include "Threading/Thread.hpp"
#include "DefaultFileStream.hpp"

namespace CPF
{
	namespace IO
	{
		static constexpr GOM::ClassID kDefaultFileCID = GOM::ClassID("CPF::IO::DefaultFile"_crc64);

		class DefaultFile : public tRefCounted<iFile>
		{
		public:
			DefaultFile(Plugin::iRegistry* regy, GOM::iUnknown* outer);
			virtual ~DefaultFile();

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;
			GOM::Result CPF_STDCALL Exists(const char* name, void* context, OnComplete cb) override;
			GOM::Result CPF_STDCALL Delete(const char* name, void* context, OnComplete cb) override;
			GOM::Result CPF_STDCALL Open(const char* name, Access access, void* context, OnOpen cb) override;

		private:
			Plugin::iRegistry* mpRegistry;
			IntrusivePtr<iExecutor> mpExecutor;
		};


		//////////////////////////////////////////////////////////////////////////
		inline DefaultFile::DefaultFile(Plugin::iRegistry* regy, GOM::iUnknown*)
			: tRefCounted<iFile>()
			, mpRegistry(regy)
		{
			regy->GetInstance(iExecutor::kIID.GetID(), mpExecutor.AsPP<iUnknown>());
		}

		inline DefaultFile::~DefaultFile()
		{
		}

		inline GOM::Result CPF_STDCALL DefaultFile::QueryInterface(uint64_t id, void** outIface)
		{
			if (outIface)
			{
				switch (id)
				{
				case GOM::iUnknown::kIID.GetID():
					*outIface = static_cast<GOM::iUnknown*>(this);
					break;
				case kIID.GetID():
					*outIface = static_cast<iFile*>(this);
					break;
				default:
					return GOM::kUnknownInterface;
				}
				AddRef();
				return GOM::kOK;
			}
			return GOM::kInvalidParameter;
		}

		inline GOM::Result CPF_STDCALL DefaultFile::Exists(const char* name, void* context, OnComplete cb)
		{
			(*mpExecutor->GetQueue())( [=]() {
				DWORD ftype = GetFileAttributesA(name);
				if ((ftype & FILE_ATTRIBUTE_DIRECTORY) == 0)
					(*cb)(GOM::kOK, context);
				(*cb)(GOM::kError, context);
			});
			return GOM::kOK;
		}

		inline GOM::Result CPF_STDCALL DefaultFile::Delete(const char* name, void* context, OnComplete cb)
		{
			(*mpExecutor->GetQueue())( [=]() {
				DWORD error = ::DeleteFileA(name);
				if (error != 0)
					(*cb)(GOM::kOK, context);
				(*cb)(GOM::kError, context);
			});
			return GOM::kOK;
		}

		inline GOM::Result CPF_STDCALL DefaultFile::Open(const char* name, Access access, void* context, OnOpen cb)
		{
			if (mpRegistry)
			{
				GOM::Result result;
				iFileStream* fileStream = nullptr;

				if (GOM::Succeeded(result = mpRegistry->Create(nullptr, kDefaultFileStreamCID.GetID(), iFileStream::kIID.GetID(), (void**)&fileStream)))
					return fileStream->Open(name, access, context, cb);

				return result;
			}
			return GOM::kNotInitialized;
		}
	}
}
