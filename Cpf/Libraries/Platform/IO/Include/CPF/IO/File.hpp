//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/Result.hpp"
#include "CPF/IO/Access.hpp"
#include "CPF/IO/iStream.hpp"
#include "CPF/Future.hpp"
#include "CPF/IO/iFile.hpp"

namespace CPF
{
	class Exception : public std::exception {};

	namespace IO
	{
		// This is a helper system for iFile.
		namespace File
		{
			template <typename IGNORED>
			class tFileSystemHelper
			{
			public:
				static void Initialize() {}
				static iFile* GetFileInterface() { return mpFileInterface; }

			private:
				static IntrusivePtr<iFile> mpFileInterface;
			};

			template <typename IGNORED>
			IntrusivePtr<iFile> tFileSystemHelper<IGNORED>::mpFileInterface;
			class FileSystemHelper : public tFileSystemHelper<void> {};


			//////////////////////////////////////////////////////////////////////////
			Future<GOM::Result> Exists(const char* name);
			Future<GOM::Result> Delete(const char* name);
			Future<iStream*> Open(const char* name, Access access);

			inline Future<GOM::Result> Exists(const char* name)
			{
				iFile* fileInterface = FileSystemHelper::GetFileInterface();
				Promise<GOM::Result>* promise = new Promise<GOM::Result>();
				fileInterface->Exists(name, promise, [](GOM::Result value, void* context)
				{
					Promise<GOM::Result>* promise = reinterpret_cast<Promise<GOM::Result>*>(context);
					if (GOM::Succeeded(value))
						promise->SetResult(Move(value));
					else
						promise->SetException(std::make_exception_ptr(Exception()));
					delete promise;
				});
				return promise->GetFuture();
			}
		}
	}
}
