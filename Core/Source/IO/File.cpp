//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/File.hpp"
#include "CPF/IO/Path.hpp"
#include "CPF/IO/FileSystem.hpp"
#include "CPF/Option.hpp"

using namespace CPF;
using namespace IO;

namespace
{
	class RawFileStream : public tRefCounted<Stream>
	{
	public:
		//
		RawFileStream();
		~RawFileStream();

		//
		Access GetAccess() override;
		bool CanSeek() override;
		bool CanRead() override;
		bool CanWrite() override;

		//
		Option<Error> Close() override;
		Option<Error> Flush() override;
		Outcome<int64_t, Error> GetPosition() override;
		Outcome<int64_t, Error> GetLength() override;
		Option<Error> Seek(int64_t offset, Origin origin) override;

		//
		Outcome<int64_t, Error> Read(void* outBuffer, int64_t length) override;
		Outcome<int64_t, Error> Write(const void* inBuffer, int64_t length) override;

		//
		operator bool() const override;

		//////////////////////////////////////////////////////////////////////////
		Option<Error> Open(const STD::Utf8String& name, Access access);

	private:
		FileHandle mpFile;
	};


	//////////////////////////////////////////////////////////////////////////
	RawFileStream::RawFileStream()
		: mpFile(nullptr)
	{}

	RawFileStream::~RawFileStream()
	{
		GetFileSystem()->Close(mpFile);
	}

	Option<Error> RawFileStream::Open(const STD::Utf8String& name, Access access)
	{
		auto file = GetFileSystem()->Open(name, access);
		if (file.CheckOK(mpFile))
			return Option<Error>::None();
		return Option<Error>::Some(Error::eInvalidFile);
	}

	Stream::Access RawFileStream::GetAccess()
	{
		return Access::eBoth;
	}

	bool RawFileStream::CanSeek()
	{
		return true;
	}

	bool RawFileStream::CanRead()
	{
		return true;
	}

	bool RawFileStream::CanWrite()
	{
		return true;
	}

	Option<Error> RawFileStream::Close()
	{
		Error error;
		GetFileSystem()->Close(mpFile, &error);
		if (error!=Error::eNone)
			return Option<Error>::None();
		return Option<Error>::Some(error);
	}

	Option<Error> RawFileStream::Flush()
	{
		Error error;
		GetFileSystem()->Flush(mpFile, &error);
		if (error != Error::eNone)
			return Option<Error>::None();
		return Option<Error>::Some(error);
	}

	Outcome<int64_t, Error> RawFileStream::GetPosition()
	{
		Error error;
		auto pos = GetFileSystem()->GetPosition(mpFile, &error);
		if (error != Error::eNone)
			return Outcome<int64_t, Error>::Error(error);
		return Outcome<int64_t, Error>::OK(pos);
	}

	Outcome<int64_t, Error> RawFileStream::GetLength()
	{
		Error error;
		auto len = GetFileSystem()->GetLength(mpFile, &error);
		if (error != Error::eNone)
			return Outcome<int64_t, Error>::Error(error);
		return Outcome<int64_t, Error>::OK(len);
	}

	Option<Error> RawFileStream::Seek(int64_t offset, Origin origin)
	{
		Error error;
		GetFileSystem()->Seek(mpFile, offset, origin, &error);
		if (error != Error::eNone)
			return Option<Error>::Some(error);
		return Option<Error>::None();
	}

	Outcome<int64_t, Error> RawFileStream::Read(void* outBuffer, int64_t length)
	{
		Error error;
		auto size = GetFileSystem()->Read(mpFile, outBuffer, length, &error);
		if (error != Error::eNone)
			return Outcome<int64_t, Error>::Error(error);
		return Outcome<int64_t, Error>::OK(size);
	}

	Outcome<int64_t, Error> RawFileStream::Write(const void* inBuffer, int64_t length)
	{
		Error error;
		auto size = GetFileSystem()->Write(mpFile, inBuffer, length, &error);
		if (error != Error::eNone)
			return Outcome<int64_t, Error>::Error(error);
		return Outcome<int64_t, Error>::OK(size);
	}


	RawFileStream::operator bool() const
	{
		return mpFile && GetFileSystem()->GetError(mpFile) == Error::eNone;
	}
}


/**
* @brief Creates a new file stream.
* @return A StreamPtr.
*/
CPF_EXPORT Outcome<Stream*, Error> File::Create(const STD::Utf8String& name, Access access)
{
	RawFileStream* filestream = new RawFileStream;
	if (!filestream)
	{
		return Outcome<Stream*, Error>::Error(Error::eOutOfMemory);
	}
	Error result;
	if (filestream->Open(name, access).CheckSome(result))
		return Outcome<Stream*, Error>::Error(result);
	return Outcome<Stream*, Error>::OK(static_cast<Stream*>(filestream));
}


#if CPF_TARGET_WINDOWS
STD::Utf8String CPF_EXPORT File::GetExecutableFilePath()
{
	HMODULE module = GetModuleHandle(nullptr);
	WCHAR path[MAX_PATH];
	DWORD length = 0;
	if ((length = GetModuleFileNameW(module, path, MAX_PATH)) > 0)
	{
		auto dir = Path::GetDirectory(STD::WString(path));
		return dir;
	}
	return STD::String();
}
#else
#endif
