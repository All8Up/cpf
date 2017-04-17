//////////////////////////////////////////////////////////////////////////
#include "IO/File.hpp"
#include "IO/Path.hpp"
#include "IO/FileSystem.hpp"

using namespace Cpf;
using namespace Platform;
using namespace IO;

namespace
{
	class RawFileStream : tRefCounted<Stream>
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
		bool CanTimeout() override;

		//
		void Close(Error* error = nullptr) override;
		void Flush(Error* error = nullptr) override;
		int64_t GetPosition(Error* error = nullptr) override;
		int64_t GetLength(Error* error = nullptr) override;
		void Seek(int64_t offset, StreamOrigin origin, Error* error = nullptr) override;

		//
		int64_t Read(void* outBuffer, int64_t length, Error* error = nullptr) override;
		int64_t Write(const void* inBuffer, int64_t length, Error* error = nullptr) override;

		//
		void CopyTo(Stream* target, Error* error = nullptr) const override;

		//
		operator bool() const override;

		//////////////////////////////////////////////////////////////////////////
		bool Open(const String& name, StreamAccess access, Error* error);

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

	bool RawFileStream::Open(const String& name, StreamAccess access, Error* error)
	{
		mpFile = GetFileSystem()->Open(name, access, error);
		return mpFile != nullptr;
	}

	Stream::Access RawFileStream::GetAccess()
	{
		return StreamAccess::eBoth;
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

	bool RawFileStream::CanTimeout()
	{
		return false;
	}

	void RawFileStream::Close(Error* error)
	{
		GetFileSystem()->Close(mpFile, error);
	}

	void RawFileStream::Flush(Error* error)
	{
		GetFileSystem()->Flush(mpFile, error);
	}

	int64_t RawFileStream::GetPosition(Error* error)
	{
		return GetFileSystem()->GetPosition(mpFile, error);
	}

	int64_t RawFileStream::GetLength(Error* error)
	{
		return GetFileSystem()->GetLength(mpFile, error);
	}

	void RawFileStream::Seek(int64_t offset, StreamOrigin origin, Error* error)
	{
		GetFileSystem()->Seek(mpFile, offset, origin, error);
	}

	int64_t RawFileStream::Read(void* outBuffer, int64_t length, Error* error)
	{
		return GetFileSystem()->Read(mpFile, outBuffer, length, error);
	}

	int64_t RawFileStream::Write(const void* inBuffer, int64_t length, Error* error)
	{
		return GetFileSystem()->Write(mpFile, inBuffer, length, error);
	}


	void RawFileStream::CopyTo(Stream* target, Error*) const
	{
		(void)target;

		// Not implemented.
		CPF_ASSERT_ALWAYS;
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
CPF_EXPORT_IO Stream* File::Create(const String& name, StreamAccess access, Error* error)
{
	RawFileStream* filestream = new RawFileStream;
	if (!filestream)
	{
		if (error)
			*error = Error::eOutOfMemory;
		return nullptr;
	}
	if (filestream->Open(name, access, error))
	{
		if (error)
			*error = Error::eNone;
		return reinterpret_cast<Stream*>(filestream);
	}
	return nullptr;
}


#if CPF_TARGET_WINDOWS
String CPF_EXPORT_IO File::GetExecutableFilePath()
{
	HMODULE module = GetModuleHandle(nullptr);
	CHAR path[MAX_PATH];
	DWORD length = 0;
	if ((length = GetModuleFileName(module, path, MAX_PATH)) > 0)
	{
		auto dir = Path::GetDirectory(path);
		return dir;
	}
	return String();
}
#else
#endif
