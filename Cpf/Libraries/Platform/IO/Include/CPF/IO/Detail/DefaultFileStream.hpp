//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO/iFileStream.hpp"
#include <stdio.h>

namespace CPF
{
	namespace IO
	{
		static constexpr GOM::ClassID kDefaultFileStreamCID = GOM::ClassID("CPF::IO::DefaultFileStream"_crc64);

		class DefaultFileStream : public tRefCounted<iFileStream>
		{
		public:
			DefaultFileStream(Plugin::iRegistry*, iUnknown*);

			// Overrides for iUnknown.
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			// Overrides for iStream.
			Access CPF_STDCALL GetAccess() override;
			bool CPF_STDCALL CanSeek() override;
			bool CPF_STDCALL CanRead() override;
			bool CPF_STDCALL CanWrite() override;
			void CPF_STDCALL Close(OnComplete cb) override;
			void CPF_STDCALL Flush(OnComplete cb) override;
			void CPF_STDCALL GetPosition(OnPosition cb) override;
			void CPF_STDCALL GetLength(OnLength cb) override;
			void CPF_STDCALL Seek(int32_t offset, StreamOrigin origin, OnSeek cb) override;
			void CPF_STDCALL Read(void* outBuffer, int64_t length, OnRead cb) override;
			void CPF_STDCALL Write(const void* inBuffer, int64_t length, OnWrite cb) override;

			// Overrides for iFileStream.
			GOM::Result CPF_STDCALL Open(const char* name, Access access, void* context, OnOpen cb) override;

		private:
			IntrusivePtr<iExecutor> mpExecutor;
			FILE* mpFile;
			Access mAccess;
		};

		//////////////////////////////////////////////////////////////////////////
		inline DefaultFileStream::DefaultFileStream(Plugin::iRegistry* regy, iUnknown*)
			: mpFile(nullptr)
			, mAccess(Access::eNone)
		{
			regy->GetInstance(iExecutor::kIID.GetID(), mpExecutor.AsPP<iUnknown>());
		}

		inline GOM::Result CPF_STDCALL DefaultFileStream::QueryInterface(uint64_t id, void** outIface)
		{
			if (outIface)
			{
				switch (id)
				{
				case iUnknown::kIID.GetID():
					*outIface = static_cast<iUnknown*>(this);
					break;
				case iStream::kIID.GetID():
					*outIface = static_cast<iStream*>(this);
					break;
				case iFileStream::kIID.GetID():
					*outIface = static_cast<iFileStream*>(this);
					break;
				default:
					return GOM::kUnknownInterface;
				}
				AddRef();
				return GOM::kOK;
			}
			return GOM::kInvalidParameter;
		}

		inline Access CPF_STDCALL DefaultFileStream::GetAccess()
		{
			return mAccess;
		}

		inline bool CPF_STDCALL DefaultFileStream::CanSeek()
		{
			return true;
		}

		inline bool CPF_STDCALL DefaultFileStream::CanRead()
		{
			return (mAccess & Access::eRead) != Access::eNone;
		}

		inline bool CPF_STDCALL DefaultFileStream::CanWrite()
		{
			return (mAccess & Access::eRead) != Access::eWrite;
		}

		inline void CPF_STDCALL DefaultFileStream::Close(OnComplete cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				if (fclose(mpFile) == 0)
				{
					(*cb)(GOM::kOK);
					mpFile = nullptr;
					return;
				}
				(*cb)(GOM::kError);
			});
		}

		inline void CPF_STDCALL DefaultFileStream::Flush(OnComplete cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				if (fflush(mpFile) == 0)
				{
					(*cb)(GOM::kOK);
					return;
				}
				(*cb)(GOM::kError);
			});
		}

		inline void CPF_STDCALL DefaultFileStream::GetPosition(OnPosition cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				fpos_t pos;
				auto res = fgetpos(mpFile, &pos);
				if (res == 0)
				{
					(*cb)(GOM::kOK, pos);
					return;
				}
				(*cb)(GOM::kError, 0);
			});
		}

		inline void CPF_STDCALL DefaultFileStream::GetLength(OnLength cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				int64_t len = 0;
				auto origin = ftell(mpFile);
				fseek(mpFile, 0, SEEK_END);

				len = ftell(mpFile);
				fseek(mpFile, origin, SEEK_SET);

				(*cb)(GOM::kOK, len);
			});
		}

		inline void CPF_STDCALL DefaultFileStream::Seek(int32_t offset, StreamOrigin origin, OnSeek cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				/* auto err = */ fseek(
					mpFile,
					long(offset),
					(origin == StreamOrigin::eBegin) ? SEEK_SET : ((origin == StreamOrigin::eCurrent) ? SEEK_CUR : SEEK_END));
				(*cb)(GOM::kOK);
			});
		}

		inline void CPF_STDCALL DefaultFileStream::Read(void* outBuffer, int64_t length, OnRead cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				int64_t len = fread(outBuffer, 1, length, mpFile);
				GOM::Result result = len < 0 ? GOM::kOK : ferror(mpFile) == 0 ? GOM::kOK : GOM::kError;
				(*cb)(result, len);
			});
		}

		inline void CPF_STDCALL DefaultFileStream::Write(const void* inBuffer, int64_t length, OnWrite cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				int64_t len = fwrite(inBuffer, 1, length, mpFile);
				GOM::Result result = len < 0 ? GOM::kOK : ferror(mpFile) == 0 ? GOM::kOK : GOM::kError;
				(*cb)(result, len);
			});
		}

		inline GOM::Result CPF_STDCALL DefaultFileStream::Open(const char* name, Access access, void* context, OnOpen cb)
		{
			(*mpExecutor->GetQueue())([=, this]() {
				char mode[4] = {0};
				switch (access)
				{
				case Access::eRead:
					strcpy(mode, "rb");
					break;
				case Access::eWrite:
					strcpy(mode, "wb");
					break;
				case Access::eBoth:
					strcpy(mode, "rb+");
					break;
				}

				mpFile = fopen(name, mode);
				if (mpFile)
					(*cb)(GOM::kOK, this, context);
				(*cb)(GOM::kError, this, context);
			});
			return GOM::kOK;
		}
	}
}
