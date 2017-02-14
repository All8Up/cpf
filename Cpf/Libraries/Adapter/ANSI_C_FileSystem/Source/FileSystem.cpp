//////////////////////////////////////////////////////////////////////////
#include "Adapter/FileSystem.hpp"
#include "Logging/Logging.hpp"
#include "IO/Stream.hpp"
#include "IO/Path.hpp"
#include "Std/String.hpp"
#include "Std/IO.hpp"

using namespace Cpf;
using namespace Adapter;

namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			CPF_EXPORT_ANSI_C_FILESYSTEM iFileSystem* CreateFileSystem()
			{
				CPF_INIT_LOG(ANSI_C_FileSystem);
				CPF_LOG(ANSI_C_FileSystem, Info) << "Installing ANSI C FileSystem";
				CPF_ASSERT(GetFileSystem() == nullptr);
				return new ANSI_C_FileSystem;
			}
			CPF_EXPORT_ANSI_C_FILESYSTEM void DestroyFileSystem(iFileSystem*)
			{
				CPF_LOG(ANSI_C_FileSystem, Info) << "Removing ANSI C FileSystem";
				delete GetFileSystem();
				SetFileSystem(nullptr);
				CPF_DROP_LOG(ANSI_C_FileSystem);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
ANSI_C_FileSystem::~ANSI_C_FileSystem()
{}

Platform::IO::FileHandle ANSI_C_FileSystem::Open(const String& name, StreamAccess access, Error* error)
{
	char mode[4];
	switch (access)
	{
	case StreamAccess::eRead:
		Std::StrCpy(mode, "rb");
		break;
	case StreamAccess::eWrite:
		Std::StrCpy(mode, "wb");
		break;
	case StreamAccess::eBoth:
		Std::StrCpy(mode, "rb+");
		break;
	}

	FileHandle handle = Std::FOpen(Platform::IO::Path::ToOS(name).c_str(), mode);

	if (error && handle == nullptr)
	{
		// TODO: Flesh out errors.
		*error = Error::eUnknownError;
	}
	return handle;
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

void ANSI_C_FileSystem::Seek(FileHandle handle, int64_t offset, StreamOrigin origin, Error* error)
{
	auto err = Std::FSeek(
		(FILE*)handle,
		long(offset),
		(origin == StreamOrigin::eBegin) ? SEEK_SET : ((origin == StreamOrigin::eCurrent) ? SEEK_CUR : SEEK_END));
	if (error)
		*error = err == 0 ? Error::eNone : Error::eUnknownError;
}

int64_t ANSI_C_FileSystem::Read(FileHandle handle, void* buffer, int64_t length, Error* error)
{
	int64_t len = Std::FRead(buffer, 1, length, (FILE*)handle);
	if (error)
		*error = len < 0 ? Error::eNone : Std::FError((FILE*)handle) == 0 ? Error::eNone : Error::eUnknownError;
	return len;
}

int64_t ANSI_C_FileSystem::Write(FileHandle handle, const void* buffer, int64_t length, Error* error)
{
	int64_t len = Std::FWrite(buffer, 1, length, (FILE*)handle);
	if (error)
		*error = len < length ? Error::eNone : Std::FError((FILE*)handle) == 0 ? Error::eNone : Error::eUnknownError;
	return len;
}

Platform::IO::Error ANSI_C_FileSystem::GetError(FileHandle handle)
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
//	case EAGAIN:
	case EALREADY:
//	case EBADE:
	case EBADF:
//	case EBADFD:
	case EBADMSG:
//	case EBADR:
//	case EBADRQC:
//	case EBADSLT:
	case EBUSY:
	case ECANCELED:
	case ECHILD:
//	case ECHRNG:
//	case ECOMM:
	case ECONNABORTED:
	case ECONNREFUSED:
	case ECONNRESET:
	case EDEADLK:
//	case EDEADLOCK:
	case EDESTADDRREQ:
	case EDOM:
//	case EDQUOT:
	case EEXIST:
	case EFAULT:
	case EFBIG:
//	case EHOSTDOWN:
	case EHOSTUNREACH:
	case EIDRM:
	case EILSEQ:
	case EINPROGRESS:
	case EINTR:
	case EINVAL:
	case EIO:
	case EISCONN:
	case EISDIR:
//	case EISNAM:
//	case EKEYEXPIRED:
//	case EKEYREJECTED:
//	case EKEYREVOKED:
//	case EL2HLT:
//	case EL2NSYNC:
//	case EL3HLT:
//	case EL3RST:
//	case ELIBACC:
//	case ELIBBAD:
//	case ELIBMAX:
//	case ELIBSCN:
//	case ELIBEXEC:
	case ELOOP:
//	case EMEDIUMTYPE:
	case EMFILE:
	case EMLINK:
	case EMSGSIZE:
//	case EMULTIHOP:
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
//	case ENOKEY:
	case ENOLCK:
	case ENOLINK:
//	case ENOMEDIUM:
	case ENOMEM:
	case ENOMSG:
//	case ENONET:
//	case ENOPKG:
	case ENOPROTOOPT:
	case ENOSPC:
	case ENOSTR:
	case ENOSYS:
//	case ENOTBLK:
	case ENOTCONN:
	case ENOTDIR:
	case ENOTEMPTY:
	case ENOTSOCK:
	case ENOTSUP:
	case ENOTTY:
//	case ENOTUNIQ:
	case ENXIO:
	case EOPNOTSUPP:
	case EOVERFLOW:
	case EPERM:
//	case EPFNOSUPPORT:
	case EPIPE:
	case EPROTO:
	case EPROTONOSUPPORT:
	case EPROTOTYPE:
	case ERANGE:
//	case EREMCHG:
//	case EREMOTE:
//	case EREOMTEIO:
//	case ERESTART:
	case EROFS:
//	case ESHUTDOWN:
	case ESPIPE:
//	case ESOCKTNOSUPPORT:
	case ESRCH:
//	case ESTALE:
//	case ESTRPIPE:
	case ETIME:
	case ETIMEDOUT:
	case ETXTBSY:
//	case EUCLEAN:
//	case EUNATCH:
//	case EUSERS:
	case EWOULDBLOCK:
	case EXDEV:
//	case EXFULL:
		result = Error::eUnknownError;
		break;
	}
	return result;
}
