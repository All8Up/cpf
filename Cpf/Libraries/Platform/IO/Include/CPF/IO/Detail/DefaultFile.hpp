//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO/iFile.hpp"
#include "Threading/Reactor.hpp"
#include "Threading/Thread.hpp"

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
			void CPF_STDCALL Exists(const char* name, void* context, OnComplete cb) override;
			void CPF_STDCALL Delete(const char* name, void* context, OnComplete cb) override;
			void CPF_STDCALL Create(const char* name, Access access, void* context, OnCreate cb) override;

		private:
			Threading::Reactor mReactor;
			Threading::Reactor::WorkQueue mQueue;
			Threading::Thread mWorker;
		};

		inline DefaultFile::DefaultFile(Plugin::iRegistry* regy, GOM::iUnknown* outer)
			: tRefCounted<iFile>()
		{
			mQueue.Initialize(&mReactor);
			mWorker = Move(Threading::Thread([&]()
			{
				mReactor.Run();
			}));
		}

		inline DefaultFile::~DefaultFile()
		{}

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

		inline void CPF_STDCALL DefaultFile::Exists(const char* name, void* context, OnComplete cb)
		{
			mQueue([=]() {
				DWORD ftype = GetFileAttributesA(name);
				if ((ftype & FILE_ATTRIBUTE_DIRECTORY) == 0)
					(*cb)(GOM::kOK, context);
				(*cb)(GOM::kError, context);
			});
		}

		inline void CPF_STDCALL DefaultFile::Delete(const char* name, void* context, OnComplete cb)
		{
			mQueue([=]() {
				DWORD error = ::DeleteFileA(name);
				if (error != 0)
					(*cb)(GOM::kOK, context);
				(*cb)(GOM::kError, context);
			});
		}

		inline void CPF_STDCALL DefaultFile::Create(const char* name, Access access, void* context, OnCreate cb)
		{}
	}
}
