//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/FileSystem.hpp"
#include "CPF/Logging.hpp"
#include "CPF/IO/Path.hpp"
#include "CPF/IO/Stream.hpp"
#include "CPF/Std/String.hpp"
#include "CPF/Std/IO.hpp"
#include "CPF/Threading/Thread.hpp"
#include "CPF/Threading/Reactor.hpp"

namespace CPF
{
	namespace Adapter
	{
		class ANSI_C_FileSystem : public IO::iFileSystem
		{
		public:
			using Error = IO::Error;
			using FileHandle = IO::FileHandle;
			using Access = IO::Access;
			using Origin = IO::Origin;

			ANSI_C_FileSystem();
			~ANSI_C_FileSystem() override;

			Outcome<FileHandle, Error> Open(const Std::Utf8String&, Access) override;
			void Close(FileHandle, Error*) override;
			void Flush(FileHandle, Error*) override;
			int64_t GetPosition(FileHandle, Error*) override;
			int64_t GetLength(FileHandle, Error*) override;
			void Seek(FileHandle, int64_t, Origin, Error*) override;
			int64_t Read(FileHandle, void*, int64_t, Error*) override;
			int64_t Write(FileHandle, const void*, int64_t, Error* = nullptr) override;
			Error GetError(FileHandle handle) override;

		private:
			Threading::Reactor mReactor;
			Threading::ReactorQueue mQueue;
			Threading::Thread mWorker;
		};
	}
}

using namespace CPF;
using namespace Adapter;
using namespace IO;

namespace CPF
{
	namespace IO
	{
		iFileSystem* CreateFileSystem()
		{
			CPF_INIT_LOG(ANSI_C_FileSystem);
			return new ANSI_C_FileSystem;
		}
		void DestroyFileSystem(iFileSystem*)
		{
			delete GetFileSystem();
			SetFileSystem(nullptr);
			CPF_DROP_LOG(ANSI_C_FileSystem);
		}
	}
}

enum class FSCommands
{
	eOpen
};

struct FSOpenCmd
{
	const char* mpName;
	Access mAccess;
};
struct FSGetLengthCmd
{
	Stream* mpStream;
};

struct FSCmd
{
	FSCommands mCommand;
	union
	{
		FSOpenCmd mOpen;
		FSGetLengthCmd mGetLength;
	};
};

//////////////////////////////////////////////////////////////////////////
ANSI_C_FileSystem::ANSI_C_FileSystem()
	: mReactor()
	, mQueue(&mReactor)
	, mWorker([&]() {
		mReactor.Run();
	})
{
}

ANSI_C_FileSystem::~ANSI_C_FileSystem()
{
	mReactor.Quit();
	mWorker.Join();
}

Outcome<FileHandle, Error> ANSI_C_FileSystem::Open(const Std::Utf8String& name, Access access)
{
	char mode[4];
	switch (access)
	{
	case Access::eRead:
		Std::StrCpy(mode, "rb");
		break;
	case Access::eWrite:
		Std::StrCpy(mode, "wb");
		break;
	case Access::eBoth:
		Std::StrCpy(mode, "rb+");
		break;
	}

	// TODO: This is not utf8 safe!!
	FileHandle handle = Std::FOpen(Path::ToOS(name.data()).c_str(), mode);

	if (handle)
		return Outcome<FileHandle, Error>::OK(handle);
	return Outcome<FileHandle, Error>::Error(Error::eUnknownError);
}

void ANSI_C_FileSystem::Close(FileHandle handle, Error* error)
{
	if (handle)
		Std::FClose((FILE*)handle);
	else
	{
		if (error)
			*error = Error::eInvalidFile;
	}
}

void ANSI_C_FileSystem::Flush(FileHandle handle, Error* error)
{
	if (handle)
	{
		Std::FFlush((FILE*)handle);
	}
	else
	{
		if (error)
			*error = Error::eInvalidFile;
	}
}

int64_t ANSI_C_FileSystem::GetPosition(FileHandle handle, Error* error)
{
	fpos_t pos;
	auto res = Std::FGetPos((FILE*)handle, &pos);
	if (error)
		*error = res == 0 ? Error::eNone : Error::eUnknownError;
	return pos;
}

int64_t ANSI_C_FileSystem::GetLength(FileHandle handle, Error* error)
{
	int64_t len = 0;
	if (handle)
	{
		auto origin = Std::FTell((FILE*)handle);
		Std::FSeek((FILE*)handle, 0, SEEK_END);

		len = Std::FTell((FILE*)handle);
		Std::FSeek((FILE*)handle, origin, SEEK_SET);

		if (error)
			*error = Error::eNone;
	}
	else
		if (error)
			*error = Error::eUnknownError;

	return len;
}

void ANSI_C_FileSystem::Seek(FileHandle handle, int64_t offset, Origin origin, Error* error)
{
	auto err = Std::FSeek(
		(FILE*)handle,
		long(offset),
		(origin == Origin::eBegin) ? SEEK_SET : ((origin == Origin::eCurrent) ? SEEK_CUR : SEEK_END));
	if (error)
		*error = err == 0 ? Error::eNone : Error::eUnknownError;
}

int64_t ANSI_C_FileSystem::Read(FileHandle handle, void* buffer, int64_t length, Error* error)
{
	int64_t len = Std::FRead((FILE*)handle, buffer, 1, length);
	if (error)
		*error = len < 0 ? Error::eNone : Std::FError((FILE*)handle) == 0 ? Error::eNone : Error::eUnknownError;
	return len;
}

int64_t ANSI_C_FileSystem::Write(FileHandle handle, const void* buffer, int64_t length, Error* error)
{
	int64_t len = Std::FWrite((FILE*)handle, buffer, 1, length);
	if (error)
		*error = len < length ? Error::eNone : Std::FError((FILE*)handle) == 0 ? Error::eNone : Error::eUnknownError;
	return len;
}

IO::Error ANSI_C_FileSystem::GetError(FileHandle handle)
{
	auto error = Std::FError((FILE*)handle);
	Error result = Error::eNone;
	switch (error)
	{
	case E2BIG:
	case EACCES:
	case EADDRINUSE:
	case EADDRNOTAVAIL:
	case EAFNOSUPPORT:
	case EALREADY:
	case EBADF:
	case EBADMSG:
	case EBUSY:
	case ECANCELED:
	case ECHILD:
	case ECONNABORTED:
	case ECONNREFUSED:
	case ECONNRESET:
	case EDEADLK:
	case EDESTADDRREQ:
	case EDOM:
	case EEXIST:
	case EFAULT:
	case EFBIG:
	case EHOSTUNREACH:
	case EIDRM:
	case EILSEQ:
	case EINPROGRESS:
	case EINTR:
	case EINVAL:
	case EIO:
	case EISCONN:
	case EISDIR:
	case ELOOP:
	case EMFILE:
	case EMLINK:
	case EMSGSIZE:
	case ENAMETOOLONG:
	case ENETDOWN:
	case ENETRESET:
	case ENETUNREACH:
	case ENFILE:
	case ENOBUFS:
	case ENODATA:
	case ENODEV:
	case ENOENT:
	case ENOEXEC:
	case ENOLCK:
	case ENOLINK:
	case ENOMEM:
	case ENOMSG:
	case ENOPROTOOPT:
	case ENOSPC:
	case ENOSTR:
	case ENOSYS:
	case ENOTCONN:
	case ENOTDIR:
	case ENOTEMPTY:
	case ENOTSOCK:
	case ENOTSUP:
	case ENOTTY:
	case ENXIO:
	case EOPNOTSUPP:
	case EOVERFLOW:
	case EPERM:
	case EPIPE:
	case EPROTO:
	case EPROTONOSUPPORT:
	case EPROTOTYPE:
	case ERANGE:
	case EROFS:
	case ESPIPE:
	case ESRCH:
	case ETIME:
	case ETIMEDOUT:
	case ETXTBSY:
	case EWOULDBLOCK:
	case EXDEV:
		result = Error::eUnknownError;
		break;
	}
	return result;
}
