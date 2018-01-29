//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO.hpp"
#include "CPF/Std/Utf8String.hpp"

namespace CPF
{
	namespace IO
	{
		using FileHandle = void*;

		class iFileSystem
		{
		public:
			virtual ~iFileSystem() = 0;

			virtual FileHandle Open(const Std::Utf8String& name, Access access, Error* = nullptr) = 0;
			virtual void Close(FileHandle, Error* = nullptr) = 0;
			virtual void Flush(FileHandle, Error* = nullptr) = 0;
			virtual int64_t GetPosition(FileHandle, Error* = nullptr) = 0;
			virtual int64_t GetLength(FileHandle, Error* = nullptr) = 0;
			virtual void Seek(FileHandle, int64_t, Origin, Error* = nullptr) = 0;
			virtual int64_t Read(FileHandle, void*, int64_t, Error* = nullptr) = 0;
			virtual int64_t Write(FileHandle, const void*, int64_t, Error* = nullptr) = 0;
			virtual Error GetError(FileHandle) = 0;

			// Preparation for Async IO.
//			virtual Future<FileHandle, GOM::Result> Open(const String& name, StreamAccess access) = 0;
		};

		CPF_EXPORT iFileSystem* GetFileSystem();
		CPF_EXPORT void SetFileSystem(iFileSystem*);
	}
}
