//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "IO/FileSystem.hpp"
#include "Move.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ANSI_C_FILESYSTEM
#		define CPF_EXPORT_ANSI_C_FILESYSTEM
#	else
#		if CPF_BUILD_ANSI_C_FILESYSTEM
#			define CPF_EXPORT_ANSI_C_FILESYSTEM CPF_EXPORT
#		else
#			define CPF_EXPORT_ANSI_C_FILESYSTEM CPF_IMPORT
#		endif
#	endif
#else
#		define CPF_EXPORT_ANSI_C_FILESYSTEM CPF_EXPORT
#endif


namespace Cpf
{
	namespace Adapter
	{
		class ANSI_C_FileSystem : public IO::iFileSystem
		{
		public:
			using Error = IO::Error;
			using FileHandle = IO::FileHandle;
			using StreamAccess = IO::StreamAccess;
			using StreamOrigin = IO::StreamOrigin;

			~ANSI_C_FileSystem() override;

			FileHandle Open(const String&, StreamAccess, Error*) override;
			void Close(FileHandle, Error*) override;
			void Flush(FileHandle, Error*) override;
			int64_t GetPosition(FileHandle, Error*) override;
			int64_t GetLength(FileHandle, Error*) override;
			void Seek(FileHandle, int64_t, StreamOrigin, Error*) override;
			int64_t Read(FileHandle, void*, int64_t, Error*) override;
			int64_t Write(FileHandle, const void*, int64_t, Error* = nullptr) override;
			Error GetError(FileHandle handle) override;
		};
	}
}
